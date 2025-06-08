#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include "engine/object.hpp"
#include "engine/scene.hpp"
#include "engine/components/image_component.hpp"
#include "engine/components/hitbox_component.hpp"
#include "engine/components/ysort_component.hpp"

class Script {
public:
    virtual ~Script() = default;
    virtual void init(Object& obj) {};
    virtual void draw(Object& obj) {};
    virtual void update(Object& obj) {};
};

class ScriptFactory {
    using create_func = std::unique_ptr<Script> (*)();
private:
    static std::unordered_map<std::string, create_func>& get_registry() {
        static std::unordered_map<std::string, create_func> registry;
        return registry;
    }
public:
    static void register_script(const std::string& name, create_func func) {
        get_registry()[name] = func;
    }
    static std::unique_ptr<Script> create_script(const std::string& name) {
        auto& registry = get_registry();
        if (registry.find(name) != registry.end()) {
            return registry[name]();
        }
        return nullptr;
    }
};

#define REGISTER_SCRIPT(CLASS_NAME) \
    static std::unique_ptr<Script> create_##CLASS_NAME() { \
        return std::make_unique<CLASS_NAME>(); \
    } \
    static bool registered_##CLASS_NAME = [] { \
        ScriptFactory::register_script(#CLASS_NAME, create_##CLASS_NAME); \
        return true; \
    }();

#define GET_COMPONENT(obj, Component, TYPE)     dynamic_cast<Component*>(obj.get_component(TYPE).get());
#define GET_SCRIPT_COMPONENT(obj)               dynamic_cast<ScriptComponent*>(obj.get_component(ComponentType::SCRIPT_COMPONENT).get())
#define GET_IMAGE_COMPONENT(obj)                dynamic_cast<ImageComponent*>(obj.get_component(ComponentType::IMAGE_COMPONENT).get())
#define GET_HITBOX_COMPONENT(obj)               dynamic_cast<HitboxComponent*>(obj.get_component(ComponentType::HITBOX_COMPONENT).get())
#define GET_YSORT_COMPONENT(obj)                dynamic_cast<YSortComponent*>(obj.get_component(ComponentType::YSORT_COMPONENT).get())

inline AppMain& app = AppMain::get_instance();

#define DELTA_TIME      app.get_delta_time()
#define NOW             app.get_now()
#define SCENE           app.get_main_scene()
