#include "engine/object_loader.hpp"
#include "engine/components/image_component.hpp"
#include "engine/components/script_component.hpp"
#include "engine/components/hitbox_component.hpp"
#include <fstream>
#include "engine/components/component_save_visitor.hpp"

std::shared_ptr<Object> ObjectLoader::load_object(const json& object_json) {
    std::shared_ptr<Object> object = std::make_shared<Object>(
        object_json["x"].get<float>(),
        object_json["y"].get<float>()
    );
    object->name = object_json["name"].get<std::string>();
    
    if (object_json.contains("components")) {
        for (auto& component_json : object_json["components"]) {
            std::unique_ptr<IComponent> component = ObjectLoader::load_component(component_json);
            object->add_component(std::move(component));
        }
    }

    return object;
}

std::shared_ptr<Object> ObjectLoader::load_object_from_template(const std::string& template_name, Vector2 position) {
    std::ifstream file(template_name);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << template_name << std::endl;
        return nullptr;
    }
    
    json object_json;
    file >> object_json;
    file.close();

    object_json["x"] = position.x;
    object_json["y"] = position.y;

    return load_object(object_json);
}

json ObjectLoader::save_object(const std::shared_ptr<Object>& object) {
    json object_data;
    object_data["name"] = object->name;
    object_data["x"] = object->position.x;
    object_data["y"] = object->position.y;
    
    ComponentSaveVisitor visitor;
    for (auto& component : object->get_components()) {
        component->accept_visitor(visitor);
    }
    json component_data = visitor.get_components_data();

    object_data["components"] = component_data;

    return object_data;
}

void ObjectLoader::save_object_to_template(const std::shared_ptr<Object>& object, const std::string& template_name) {
    json object_data = save_object(object);
    object_data.erase("x");
    object_data.erase("y");
    
    std::ofstream file(template_name);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << template_name << std::endl;
        return;
    }
    
    file << object_data.dump(4);
    file.close();
}

std::unique_ptr<IComponent> ObjectLoader::load_component(const json& component_json) {
    std::string type = component_json["type"].get<std::string>();
    if (type == "image") {
        return load_image_component(component_json);
    } else if (type == "script") {
        return load_script_component(component_json);
    } else if (type == "hitbox") {
        return load_hitbox_component(component_json);
    }
    return nullptr;
}

std::unique_ptr<ImageComponent> ObjectLoader::load_image_component(const json& component_json) {
    auto image_component = std::make_unique<ImageComponent>(component_json["image"].get<std::string>());
    image_component->set_scale({
        component_json["scale_x"].get<float>(),
        component_json["scale_y"].get<float>()
    });
    image_component->set_flip_x(component_json["flip_x"].get<bool>());
    image_component->set_flip_y(component_json["flip_y"].get<bool>());
    image_component->set_is_animated(component_json["is_animated"].get<bool>());
    image_component->set_frame_count(component_json["frame_count"].get<int>());
    image_component->set_frame(component_json["frame"].get<int>());
    image_component->set_animation_speed(component_json["animation_speed"].get<float>());
    return std::move(image_component);
}

std::unique_ptr<ScriptComponent> ObjectLoader::load_script_component(const json& component_json) {
    auto script_component = std::make_unique<ScriptComponent>(component_json["script"].get<std::string>());
    return std::move(script_component);
}

std::unique_ptr<HitboxComponent> ObjectLoader::load_hitbox_component(const json& component_json) {
    auto hitbox_component = std::make_unique<HitboxComponent>(
        component_json["offset_x"].get<float>(),
        component_json["offset_y"].get<float>(),
        component_json["width"].get<float>(),
        component_json["height"].get<float>()
    );
    return std::move(hitbox_component);
}