#include "engine/object_loader.hpp"
#include "engine/components/image_component.hpp"
#include "engine/components/script_component.hpp"
#include <sstream>

ObjectLoader::ObjectLoader(const std::string& raw_data) {
    std::stringstream ss(raw_data);
    std::string token;

    while (std::getline(ss, token, ',')) {
        object_data.push_back(token);
    }
}

std::shared_ptr<Object> ObjectLoader::load_object() {
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

        if      (data == "image")   { object->add_component(load_image_component()); }
        else if (data == "script")  { object->add_component(load_script_component()); }
    }

    return object;
}

std::unique_ptr<ImageComponent> ObjectLoader::load_image_component() {
    std::string image_id = object_data.front();
    object_data.pop_front();

    Vector2 scale;
    scale.x = std::stof(object_data.front());
    object_data.pop_front();

    scale.y = std::stof(object_data.front());
    object_data.pop_front();

    bool flip_x = object_data.front() == "1";
    object_data.pop_front();

    bool flip_y = object_data.front() == "1";
    object_data.pop_front();

    bool is_animated = object_data.front() == "1";
    object_data.pop_front();

    int frame_count = std::stoi(object_data.front());
    object_data.pop_front();

    int frame = std::stoi(object_data.front());
    object_data.pop_front();

    float animation_speed = std::stof(object_data.front());
    object_data.pop_front();

    auto image_component = std::make_unique<ImageComponent>(image_id);
    image_component->set_scale(scale);
    image_component->set_flip_x(flip_x);
    image_component->set_flip_y(flip_y);
    image_component->set_is_animated(is_animated);
    image_component->set_frame_count(frame_count);
    image_component->set_frame(frame);
    image_component->set_animation_speed(animation_speed);
    return std::move(image_component);
}

std::unique_ptr<ScriptComponent> ObjectLoader::load_script_component() {
    std::string script_file_name = object_data.front();
    object_data.pop_front();

    auto script_component = std::make_unique<ScriptComponent>(script_file_name);

    return std::move(script_component);
}