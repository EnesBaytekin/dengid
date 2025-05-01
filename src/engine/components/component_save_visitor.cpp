#include "engine/components/component_save_visitor.hpp"
#include "engine/components/image_component.hpp"
#include "engine/components/script_component.hpp"
#include "engine/components/hitbox_component.hpp"
#include "app/app_main.hpp"
#include "imgui.h"

void ComponentSaveVisitor::visit_image_component(ImageComponent& component) {
    json component_data;
    component_data["type"] = "image";
    component_data["image"] = component.get_image_id();
    component_data["scale_x"] = component.get_scale().x;
    component_data["scale_y"] = component.get_scale().y;
    component_data["flip_x"] = component.get_flip_x();
    component_data["flip_y"] = component.get_flip_y();
    component_data["is_animated"] = component.get_is_animated();
    component_data["frame_count"] = component.get_frame_count();
    component_data["frame"] = component.get_frame();
    component_data["animation_speed"] = component.get_animation_speed();
    components_data += component_data;
}

void ComponentSaveVisitor::visit_script_component(ScriptComponent& component) {
    json component_data;
    component_data["type"] = "script";
    component_data["script"] = component.get_script_file_name();
    components_data += component_data;
}

void ComponentSaveVisitor::visit_hitbox_component(HitboxComponent& component) {
    json component_data;
    component_data["type"] = "hitbox";
    component_data["offset_x"] = component.get_offset().x;
    component_data["offset_y"] = component.get_offset().y;
    component_data["width"] = component.get_size().x;
    component_data["height"] = component.get_size().y;
    components_data += component_data;
}