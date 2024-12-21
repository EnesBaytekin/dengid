#include "project/project_manager.hpp"
#include "engine/scene.hpp"
#include "engine/object.hpp"
#include <iostream>
#include <fstream>
#include "app/app_main.hpp"
#include "engine/components/component_save_visitor.hpp"
#include "engine/object_loader.hpp"

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