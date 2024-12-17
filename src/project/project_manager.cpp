#include "project/project_manager.hpp"
#include "engine/scene.hpp"
#include "engine/object.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <app/app_main.hpp>
#include <engine/components/image_component.hpp>

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

void ProjectManager::load_project() {
    auto main_scene = std::make_shared<Scene>();

    std::ifstream scene_file((project_path/"main_scene.data"));
    if (!scene_file.is_open()) {
        std::cerr << "Scene file 'main_scene.data' could not found in the project folder!" << std::endl;
        exit(1);
    }

    AppMain& app = AppMain::get_instance();

    app.load_image("icon.png");
    
    std::string object_raw_data;
    while (std::getline(scene_file, object_raw_data)) {
        auto object_data = split(object_raw_data, ',');
        int x = std::stoi(object_data[0]);
        int y = std::stoi(object_data[1]);
        
        auto object = std::make_shared<Object>(x, y);
        object->add_component(std::make_unique<ImageComponent>("icon.png"));
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
        scene_file << object->position.x << ",";
        scene_file << object->position.y << "\n";
    }
    scene_file.close();
}