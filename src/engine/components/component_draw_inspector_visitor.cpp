#include "engine/components/component_draw_inspector_visitor.hpp"
#include "engine/components/image_component.hpp"
#include "app/app_main.hpp"
#include "imgui.h"
#include "imfilebrowser.hpp"
#include "globals.hpp"
#include "project/project_manager.hpp"
#include "image/image_resource.hpp"

void ComponentDrawInspectorVisitor::visit_image_component(ImageComponent& component) {
    const void* obj_address = &component;
    char buffer[20];
    std::snprintf(buffer, sizeof(buffer), "%p", obj_address);
    std::string obj_id(buffer);

    if (ImGui::TreeNodeEx(("Image Component##"+obj_id).c_str(), ImGuiTreeNodeFlags_DefaultOpen)) {
        AppMain& app = AppMain::get_instance();

        ImGui::Text("%s", "Image:");
        ImGui::SameLine();
        
        ProjectManager& project_manager = ProjectManager::get_instance();
        std::filesystem::path project_path = project_manager.get_project_path();
        
        static ImGui::FileBrowser file_dialog(
            ImGuiFileBrowserFlags_SkipItemsCausingError |
            ImGuiFileBrowserFlags_CloseOnEsc |
            ImGuiFileBrowserFlags_ConfirmOnEnter |
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

        ImGui::Separator();

        ImageResource& image_resource = ImageResource::get_instance();
        auto image = image_resource.get_image(component.get_image_id());
        int image_width = image->get_width();
        int image_height = image->get_height();
        if (image_width > image_height) {
            image_height = image_height*256/image_width;
            image_width = 256;
        } else {
            image_width = image_width*256/image_height;
            image_height = 256;
        }

        float remaining_width = ImGui::GetContentRegionAvail().x;
        float image_offset_x = (remaining_width-image_width)*0.5f;
        if (image_offset_x > 0.0f) {
            ImGui::SetCursorPosX(ImGui::GetCursorPosX()+image_offset_x);
        }
        app.draw_imgui_image(component.get_image_id(), image_width, image_height);

        ImGui::Separator();
        ImGui::Dummy(ImVec2(0, 4));
        
        ImGui::Text("%s", "Scale:");
        ImGui::SameLine();

        auto scale = component.get_scale();
        if (ImGui::DragFloat2("##image_scale", scale, 0.05f, 0.0f, (float)UINT8_MAX, "%.3f", ImGuiSliderFlags_Logarithmic)) {
            component.set_scale(scale);
        }

        bool flip_x = component.get_flip_x();
        if (ImGui::Checkbox("Flip x", &flip_x)) {
            component.set_flip_x(flip_x);
        }

        bool flip_y = component.get_flip_y();
        if (ImGui::Checkbox("Flip y", &flip_y)) {
            component.set_flip_y(flip_y);
        }

        if (ImGui::TreeNode("Animate")) {
            ImGui::Text("Frame Count:");
            ImGui::SameLine();

            int frame_count = component.get_frame_count();
            if (ImGui::DragInt("##frame_count", &frame_count, 0.1f, 1)) {
                component.set_frame_count(frame_count);
            }

            ImGui::Text("Frame:");
            ImGui::SameLine();

            int frame = component.get_frame();
            if (ImGui::SliderInt("##frame", &frame, 0, frame_count-1)) {
                component.set_frame(frame);
            }

            ImGui::Text("Animation Speed:");
            ImGui::SameLine();

            float animation_speed = component.get_animation_speed();
            if (ImGui::DragFloat("##animation_speed", &animation_speed, 0.05f, 0.0f, (float)UINT8_MAX, "%.3f", ImGuiSliderFlags_Logarithmic)) {
                component.set_animation_speed(animation_speed);
            }

            ImGui::TreePop();
        }

        ImGui::TreePop();
    }
}
