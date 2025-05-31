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

void ProjectManager::load_project() {
    auto main_scene = std::make_shared<Scene>();

    std::ifstream scene_file((project_path/"main_scene.data"));
    if (!scene_file.is_open()) {
        std::cerr << "Scene file 'main_scene.data' could not found in the project folder!" << std::endl;
        exit(1);
    }

    json json_data;
    scene_file >> json_data;
    scene_file.close();

    auto& settings = ProjectManager::get_instance().get_project_settings();
    
    settings.window_width = json_data["settings"]["window_width"].get<int>();
    settings.window_height = json_data["settings"]["window_height"].get<int>();

    for (auto& object_json : json_data["objects"]) {
        auto object = ObjectLoader::load_object(object_json);
        main_scene->spawn_object(object);
    }

    AppMain& app = AppMain::get_instance();
    app.set_main_scene(main_scene);
}

void ProjectManager::save_project() {
    AppMain& app = AppMain::get_instance();
    auto main_scene = app.get_main_scene();

    auto& settings = ProjectManager::get_instance().get_project_settings();

    json project_data;
    project_data["settings"] = json::object();
    project_data["settings"]["window_width"] = settings.window_width;
    project_data["settings"]["window_height"] = settings.window_height;

    project_data["objects"] = json::array();
    
    for (auto object : main_scene->get_objects()) {
        json object_data = ObjectLoader::save_object(object);
        project_data["objects"].push_back(object_data);
    }

    std::ofstream scene_file(project_path/"main_scene.data");
    scene_file << project_data.dump(4);
    scene_file.close();
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
    for (auto& object : scene->get_objects()) {
        for (auto& component : object->get_components()) {
            if (component->get_type() == ComponentType::SCRIPT_COMPONENT) {
                std::string script_name = (dynamic_cast<ScriptComponent*>(component.get()))->get_script_file_name();
                std::system(("cp "+(project_path/script_name).string()+" ./game_build/scripts/"+script_name).c_str());
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
