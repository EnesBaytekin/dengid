#include "engine/components/component_save_visitor.hpp"
#include "engine/components/image_component.hpp"
#include "app/app_main.hpp"
#include "imgui.h"

void ComponentSaveVisitor::visit_image_component(ImageComponent& component) {
    components_data += "image,";
    components_data += component.get_image_id()+",";
}
