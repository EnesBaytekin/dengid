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

void ProjectManager::load_project() {
    auto main_scene = std::make_shared<Scene>();

    std::ifstream scene_file((project_path/"main_scene.data"));
    if (!scene_file.is_open()) {
        std::cerr << "Scene file 'main_scene.data' could not found in the project folder!" << std::endl;
        exit(1);
    }

    AppMain& app = AppMain::get_instance();
    
    std::string object_raw_data;
    while (std::getline(scene_file, object_raw_data)) {
        ObjectLoader object_loader(object_raw_data);
        std::shared_ptr<Object> object = object_loader.load_object();
        main_scene->spawn_object(object);
    }

    scene_file.close();

    app.set_main_scene(main_scene);
}

void ProjectManager::save_project() {
    AppMain& app = AppMain::get_instance();
    auto main_scene = app.get_main_scene();
    
    std::ofstream scene_file(project_path/"main_scene.data");
    for (auto object : main_scene->get_objects()) {
        scene_file << object->name << ",";
        scene_file << object->position.x << ",";
        scene_file << object->position.y << ",";
        ComponentSaveVisitor visitor;
        for (auto& component : object->get_components()) {
            component->accept_visitor(visitor);
        }
        std::string component_data = visitor.get_components_data();
        scene_file << component_data << "\n";
    }
    scene_file.close();
}

void ProjectManager::build_game() {
    AppMain& app = AppMain::get_instance();

    if (game_is_running) {
        app.print("Could not build game.\n");
        return;
    }

    app.print("Building game...\n");

    save_project();

    std::ofstream file("./include/project_path_macro.hpp");
    if (!file.is_open()) {
        std::cerr << "Failed to create project path macro file." << std::endl;
        app.print("Failed to build game.\n");
        return;
    }

    std::filesystem::path project_path = get_project_path();
    std::string project_name = project_path.filename().string();

    file << "#pragma once\n";
    file << "#define PROJECT_PATH \"";
    file << project_path.string();
    file << "\"\n";
    file.close();

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
        execl(command.c_str(), command.c_str(), NULL);

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
