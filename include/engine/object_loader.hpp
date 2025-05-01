#ifndef OBJECT_LOADER_HPP
#define OBJECT_LOADER_HPP

#include "engine/object.hpp"
#include <string>
#include <memory>
#include <deque>
#include "json.hpp"

using json = nlohmann::ordered_json;

class ImageComponent;
class ScriptComponent;
class HitboxComponent;

class ObjectLoader {
private:
    static std::unique_ptr<IComponent> load_component(const json& component_json);
    static std::unique_ptr<ImageComponent> load_image_component(const json& component_json);
    static std::unique_ptr<ScriptComponent> load_script_component(const json& component_json);
    static std::unique_ptr<HitboxComponent> load_hitbox_component(const json& component_json);
public:
    static std::shared_ptr<Object> load_object(const json& json_data);
};


#endif