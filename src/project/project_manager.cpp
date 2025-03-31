#include "project/project_manager.hpp"
#include "engine/scene.hpp"
#include "engine/object.hpp"
#include <iostream>
#include <fstream>
#include "app/app_main.hpp"
#include "engine/components/component_save_visitor.hpp"
#include "engine/object_loader.hpp"
#include "engine/components/script_component.hpp"

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
    std::ofstream file("./include/project_path_macro.hpp");
    if (!file.is_open()) {
        std::cerr << "Failed to create project path macro file." << std::endl;
        return;
    }

    AppMain& app = AppMain::get_instance();
    
    app.print("Building game...\n");

    save_project();
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
    if (game_is_running) {
        return;
    }
    std::filesystem::path project_path = get_project_path();
    std::string project_name = project_path.filename().string();

    std::string command = project_path/project_name;

    AppMain& app = AppMain::get_instance();
    
    game_is_running = true;
    app.print("Running game...\n");

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        return;
    }

    std::string line = "";
    char buffer[256];
    while (!feof(pipe)) {
        if (fgets(buffer, 256, pipe) != NULL) {
            line += buffer;
            if (line.back() == '\n') {
                app.print(line);
                line = "";
            }
        }
    }

    pclose(pipe);

    app.print("Game has stopped.\n");
    game_is_running = false;
}

