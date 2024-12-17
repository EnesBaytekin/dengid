#include "engine/components/component_draw_inspector_visitor.hpp"
#include "engine/components/image_component.hpp"
#include "app/app_main.hpp"
#include "imgui.h"
#include "imfilebrowser.hpp"
#include "globals.hpp"
#include "project/project_manager.hpp"

void ComponentDrawInspectorVisitor::visit_image_component(ImageComponent& component) {
    const void* obj_address = &component;
    char buffer[20];
    std::snprintf(buffer, sizeof(buffer), "%p", obj_address);
    std::string obj_id(buffer);

    if (ImGui::TreeNode(("Image Component##"+obj_id).c_str())) {
        AppMain& app = AppMain::get_instance();
        
        ImGui::Text("%s", "Image:");
        ImGui::SameLine();
        
        ProjectManager& project_manager = ProjectManager::get_instance();
        std::filesystem::path project_path = project_manager.get_project_path();
        
        static ImGui::FileBrowser file_dialog(
            ImGuiFileBrowserFlags_SkipItemsCausingError |
            ImGuiFileBrowserFlags_EditPathString,
            project_path
        );
        if (ImGui::Button("Select Image")) {
            file_dialog.Open();
        }
        file_dialog.Display();
        if (file_dialog.HasSelected()) {
            std::string image_path = std::filesystem::relative(file_dialog.GetSelected(), project_path).string();
            component.set_image_id(image_path);
            file_dialog.ClearSelected();
        }

        app.draw_imgui_image(component.get_image_id(), 32, 32);

        ImGui::TreePop();
    }
}
