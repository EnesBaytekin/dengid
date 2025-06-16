#include "project/project_manager.hpp"
#include "engine/scene.hpp"
#include "engine/object.hpp"
#include <iostream>
#include <fstream>
#include "app/app_main.hpp"
#include "engine/components/component_save_visitor.hpp"
#include "engine/object_loader.hpp"
#include "engine/components/script_component.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <csignal>
#include "json.hpp"
#include <globals.hpp>

using json = nlohmann::ordered_json;

void ProjectManager::close_project() {
    std::string command = EXECUTABLE_DIRECTORY/"dengid";
    execl(command.c_str(), command.c_str(), (char *)NULL);

    app.print("Failed to close the project.\n");
}

void ProjectManager::load_project(bool is_engine) {
    auto main_scene = std::make_shared<Scene>();

    std::ifstream scene_file((project_path/"main_scene.data"));
    if (!scene_file.is_open()) {
        std::cerr << "Scene file 'main_scene.data' could not found in the project folder!" << std::endl;
        return;
    }

    json json_data;
    scene_file >> json_data;
    scene_file.close();

    auto& settings = ProjectManager::get_instance().get_project_settings();

    if (json_data.contains("settings")) {
        auto& s = json_data["settings"];

        if (s.contains("viewport_width") && s["viewport_width"].is_number_integer())
            settings.viewport_width = s["viewport_width"];

        if (s.contains("viewport_height") && s["viewport_height"].is_number_integer())
            settings.viewport_height = s["viewport_height"];

        if (s.contains("window_width") && s["window_width"].is_number_integer())
            settings.window_width = s["window_width"];

        if (s.contains("window_height") && s["window_height"].is_number_integer())
            settings.window_height = s["window_height"];

        if (s.contains("pixel_per_unit") && s["pixel_per_unit"].is_number_integer())
            settings.pixel_per_unit = s["pixel_per_unit"];

        if (s.contains("bg_color") && s["bg_color"].is_array() && s["bg_color"].size() >= 3) {
            auto& color = s["bg_color"];
            if (color[0].is_number_integer() && color[1].is_number_integer() && color[2].is_number_integer())
                settings.bg_color.set_rgb(color[0], color[1], color[2]);
        }
    }


    for (auto& object_json : json_data["objects"]) {
        auto object = ObjectLoader::load_object(object_json);
        main_scene->spawn_object(object);
    }

    AppMain& app = AppMain::get_instance();
    app.set_main_scene(main_scene);

    if (is_engine) {
        std::ifstream editor_data_file((project_path/"editor.data"));
        if (editor_data_file.is_open()) {
            json editor_data;
            editor_data_file >> editor_data;
            editor_data_file.close();

            auto& camera = app.get_camera();
            
            Vector2 camera_position(
                editor_data["camera"]["x"].get<float>(),
                editor_data["camera"]["y"].get<float>()
            );
            camera->set_position(camera_position);

            float camera_zoom = editor_data["camera"]["zoom"].get<float>();
            camera->set_zoom(camera_zoom);
        }
    }
}

void ProjectManager::save_project() {
    AppMain& app = AppMain::get_instance();
    auto main_scene = app.get_main_scene();

    auto& settings = ProjectManager::get_instance().get_project_settings();

    json project_data;
    project_data["settings"] = json::object();
    project_data["settings"]["viewport_width"] = settings.viewport_width;
    project_data["settings"]["viewport_height"] = settings.viewport_height;
    project_data["settings"]["window_width"] = settings.window_width;
    project_data["settings"]["window_height"] = settings.window_height;
    project_data["settings"]["pixel_per_unit"] = settings.pixel_per_unit;
    project_data["settings"]["bg_color"] = {
        settings.bg_color.r,
        settings.bg_color.g,
        settings.bg_color.b
    };


    project_data["objects"] = json::array();
    
    for (auto object : main_scene->get_objects()) {
        json object_data = ObjectLoader::save_object(object);
        project_data["objects"].push_back(object_data);
    }

    std::ofstream scene_file(project_path/"main_scene.data");
    scene_file << project_data.dump(4);
    scene_file.close();

    // save editor data
    json editor_data;
    auto& camera = app.get_camera();
    editor_data["camera"] = json::object();
    editor_data["camera"]["x"] = camera->get_position().x;
    editor_data["camera"]["y"] = camera->get_position().y;
    editor_data["camera"]["zoom"] = camera->get_zoom();
    std::ofstream editor_data_file(project_path/"editor.data");
    editor_data_file << editor_data.dump(4);
    editor_data_file.close();
    
    app.print("Scene has saved");
}

void ProjectManager::build_game() {
    AppMain& app = AppMain::get_instance();

    if (game_is_running) {
        app.print("Could not build game.\n");
        return;
    }

    app.print("Building game...\n");

    save_project();

    // create project path macro file
    std::ofstream file("./include/project_settings_macro.hpp");
    if (!file.is_open()) {
        std::cerr << "Failed to create project path macro file." << std::endl;
        app.print("Failed to build game.\n");
        return;
    }

    std::filesystem::path project_path = get_project_path();
    std::string project_name = project_path.filename().string();

    file << "#pragma once\n";
    file << "#define PROJECT_PATH \"" << project_path.string() << "\"\n";
    file << "\n";
    file << "#define WINDOW_WIDTH " << project_settings.window_width << "\n";
    file << "#define WINDOW_HEIGHT " << project_settings.window_height << "\n";
    file << "\n";
    file.close();

    // copy scripts to game_build/scripts
    std::system("rm ./game_build/scripts/*.cpp");
    std::system("mkdir -p ./game_build/scripts");

    auto scene = app.get_main_scene();
    // Load all script files from the project directory
    std::filesystem::path scripts_directory = project_path;
    if (std::filesystem::exists(scripts_directory) && std::filesystem::is_directory(scripts_directory)) {
        for (const auto& entry : std::filesystem::directory_iterator(scripts_directory)) {
            if (entry.is_regular_file() && entry.path().extension() == ".cpp") {
                std::string script_name = entry.path().filename().string();
                std::system(("cp " + entry.path().string() + " ./game_build/scripts/" + script_name).c_str());
            }
        }
    }

    // compile and move game binary
    std::system(("make all && mv ./game_build/game \""+(project_path/project_name).string()+"\"").c_str());

    app.print("Game has built successfully.\n");
}

void ProjectManager::run_game() {
    AppMain& app = AppMain::get_instance();

    if (game_is_running) {
        app.print("Game is already running.\n");
        return;
    }
    
    game_is_running = true;
    app.print("Running game...\n");

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        app.print("Failed to start game.\n");
        game_is_running = false;
        return;
    }

    pid_t pid = fork();
    if (pid == -1) {
        app.print("Failed to start game.\n");
        game_is_running = false;
        return;
    }

    // child
    if (pid == 0) {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        dup2(pipe_fd[1], STDERR_FILENO);
        close(pipe_fd[1]);

        std::filesystem::path project_path = get_project_path();
        std::string project_name = project_path.filename();
        std::string command = project_path/project_name;
        execl(command.c_str(), command.c_str(), (char *)NULL);

        app.print("Failed to start game. Try to build it first.\n");
        game_is_running = false;
        exit(1);
    }

    // parent
    close(pipe_fd[1]);

    game_pid = pid;

    std::string line = "";
    char buffer[256];
    while (game_is_running) {
        ssize_t length = read(pipe_fd[0], buffer, sizeof(buffer)-1);
        if (length <= 0) {
            break;
        }
        buffer[length] = '\0';
        line += buffer;
        if (line.back() == '\n') {
            app.print(line);
            line = "";
        }
    }

    close(pipe_fd[0]);

    app.print("Game has stopped.\n");
    game_is_running = false;
}

void ProjectManager::stop_game() {
    if (game_is_running && game_pid > 0) {
        kill(game_pid, SIGTERM);
        game_pid = -1;
        game_is_running = false;
    }
}
