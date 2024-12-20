#include "engine/components/component_save_visitor.hpp"
#include "engine/components/image_component.hpp"
#include "app/app_main.hpp"
#include "imgui.h"

void ComponentSaveVisitor::visit_image_component(ImageComponent& component) {
    components_data += "image,";
    components_data += component.get_image_id()+",";
    Vector2 scale = component.get_scale();
    components_data += std::to_string(scale.x)+",";
    components_data += std::to_string(scale.y)+",";
    components_data += std::to_string(component.get_flip_x())+",";
    components_data += std::to_string(component.get_flip_y())+",";
    components_data += std::to_string(component.get_is_animated())+",";
    components_data += std::to_string(component.get_frame_count())+",";
    components_data += std::to_string(component.get_frame())+",";
    components_data += std::to_string(component.get_animation_speed())+",";
}
