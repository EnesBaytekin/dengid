#include "engine/components/component_draw_inspector_visitor.hpp"
#include "engine/components/image_component.hpp"
#include "app/app_main.hpp"
#include "imgui.h"

void ComponentDrawInspectorVisitor::visit_image_component(ImageComponent& component) {
    const void* obj_address = &component;
    char buffer[20];
    std::snprintf(buffer, sizeof(buffer), "%p", obj_address);
    std::string obj_id(buffer);

    if (ImGui::TreeNode(("Image Component##"+obj_id).c_str())) {
        AppMain& app = AppMain::get_instance();
        
        ImGui::Text("%s", "Image:");
        ImGui::SameLine();
        app.draw_imgui_image(component.get_image_id(), 32, 32);

        ImGui::TreePop();
    }
}
