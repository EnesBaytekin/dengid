#include "engine/components/component_visitor.hpp"
#include "engine/components/image_component.hpp"
#include "app/app_main.hpp"
#include "imgui.h"

void ComponentVisitor::visit_image_component(ImageComponent& component) {
    if (ImGui::TreeNode("Image Component")) {
        
        AppMain& app = AppMain::get_instance();
        app.draw_imgui_image(component.get_image(), 32, 32);

        ImGui::TreePop();
    }
}
