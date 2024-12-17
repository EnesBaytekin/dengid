#include "engine/components/component_visitor.hpp"
#include "engine/components/image_component.hpp"
#include "app/app_main.hpp"
#include "imgui.h"

void ComponentVisitor::visit_image_component(ImageComponent& component) {
    if (ImGui::TreeNode("Image Component")) {
        AppMain& app = AppMain::get_instance();
        
        ImGui::Text("%s", "Image:");
        ImGui::SameLine();
        app.draw_imgui_image(component.get_image_id(), 32, 32);

        ImGui::TreePop();
    }
}
