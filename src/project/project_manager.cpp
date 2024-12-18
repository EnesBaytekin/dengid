#include "project/project_manager.hpp"
#include "engine/scene.hpp"
#include "engine/object.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "app/app_main.hpp"
#include "engine/components/image_component.hpp"
#include "engine/components/component_save_visitor.hpp"
#include <deque>

std::deque<std::string> split(const std::string& str, char delimiter) {
    std::deque<std::string> tokens;
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
    
    std::string object_raw_data;
    while (std::getline(scene_file, object_raw_data)) {
        std::deque<std::string> object_data = split(object_raw_data, ',');

        std::string name = object_data.front();
        object_data.pop_front();

        int x = std::stoi(object_data.front());
        object_data.pop_front();

        int y = std::stoi(object_data.front());
        object_data.pop_front();

        auto object = std::make_shared<Object>(x, y);
        object->name = name;
        
        while (!object_data.empty()) {
            std::string& data = object_data.front();
            object_data.pop_front();

            if (data == "image") {
                std::string image_id = object_data.front();
                object_data.pop_front();

                Vector2 scale;
                scale.x = std::stof(object_data.front());
                object_data.pop_front();

                scale.y = std::stof(object_data.front());
                object_data.pop_front();

                auto image_component = std::make_unique<ImageComponent>(image_id);
                image_component->set_scale(scale);
                object->add_component(std::move(image_component));
            }
        }

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