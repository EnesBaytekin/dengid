#pragma once

#include "math/rect.hpp"
#include "engine/object.hpp"
#include "engine/scene.hpp"
#include "engine/components/image_component.hpp"
#include "engine/components/script_component.hpp"
#include "engine/components/hitbox_component.hpp"
#include "engine/components/ysort_component.hpp"
#include "engine/components/component_type.hpp"
#include <cstdlib>

class EditorUtility {
private:
    static void debug_draw_ysort_component(YSortComponent& ysort_component, Object& object) {
        AppMain& app = AppMain::get_instance();
        auto selected_object = dynamic_cast<ImguiWindowInspector*>(app.get_view()->get_window("inspector").get())->selected_object;
        if (selected_object.get() == &object) {
            auto offset = ysort_component.get_offset();
            app.draw_rect(object.position.x, object.position.y+offset, 32, 1, 255, 255, 255, 192);
        }
    }
    static void debug_draw_hitbox_component(HitboxComponent& hitbox_component, Object& object) {
        AppMain& app = AppMain::get_instance();
        auto selected_object = dynamic_cast<ImguiWindowInspector*>(app.get_view()->get_window("inspector").get())->selected_object;
        if (selected_object.get() == &object) {
            auto offset = hitbox_component.get_offset();
            auto size = hitbox_component.get_size();
            app.draw_rect(object.position.x+offset.x, object.position.y+offset.y, size.x, size.y, 255, 255, 255, 64);
        }
    }
    static void debug_draw_component(IComponent& component, Object& object) {
        if (component.get_type() == ComponentType::HITBOX_COMPONENT) {
            auto& hitbox_component = *dynamic_cast<HitboxComponent*>(&component);
            debug_draw_hitbox_component(hitbox_component, object);
        } else if (component.get_type() == ComponentType::SCRIPT_COMPONENT) {
            auto& script_component = *dynamic_cast<ScriptComponent*>(&component);
        } else if (component.get_type() == ComponentType::IMAGE_COMPONENT) {
            auto& image_component = *dynamic_cast<ImageComponent*>(&component);
        } else if (component.get_type() == ComponentType::YSORT_COMPONENT) {
            auto& ysort_component = *dynamic_cast<YSortComponent*>(&component);
            debug_draw_ysort_component(ysort_component, object);
        }
    }
    static void debug_draw_object(Object& object) {
        for (auto& component : object.get_components()) {
            debug_draw_component(*component, object);
        }
    }
public:
    static void debug_draw_scene(Scene& scene) {
        for (auto& object : scene.get_objects()) {
            debug_draw_object(*object);
        }
    }
    static std::unique_ptr<Rect> get_object_rect(std::shared_ptr<Object>& object) {
        if (!object) {
            return std::make_unique<Rect>(0, 0, 0, 0);
        }
        if (object->has_component(ComponentType::HITBOX_COMPONENT)) {
            auto& hitbox_component = *dynamic_cast<HitboxComponent*>(object->get_component(ComponentType::HITBOX_COMPONENT).get());
            return std::make_unique<Rect>(hitbox_component.get_rect_at(object->position));
        } else if (object->has_component(ComponentType::IMAGE_COMPONENT)) {
            auto& image_component = *dynamic_cast<ImageComponent*>(object->get_component(ComponentType::IMAGE_COMPONENT).get());
            return std::make_unique<Rect>(object->position, image_component.get_size());
        } else {
            return std::make_unique<Rect>(object->position, 32, 32);
        }
    }

    static void open_folder(const std::string& path) {
    #if defined(_WIN32)
        std::string command = "start \"\" \"" + path + "\"";
    #elif defined(__APPLE__)
        std::string command = "open \"" + path + "\"";
    #else // Linux
        std::string command = "xdg-open \"" + path + "\"";
    #endif
        system(command.c_str());
    }
};
