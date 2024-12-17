#include "imgui_windows/imgui_window_inspector.hpp"
#include <project/project_manager.hpp>
#include "imgui.h"
#include <SDL2/SDL.h>
#include "app/app_main.hpp"
#include "app_views/app_view.hpp"
#include "engine/components/image_component.hpp"
#include "engine/components/component_draw_inspector_visitor.hpp"

void ImguiWindowInspector::show() {
    if (!is_visible()) return;

    AppMain& app = AppMain::get_instance();
    ProjectManager& project_manager = ProjectManager::get_instance();

    static bool window_is_initialized = false;
    if (!window_is_initialized) {
        int width, height;
        SDL_GetWindowSize(app.window, &width, &height);
        ImGui::SetNextWindowPos(ImVec2(width-320, 18));
        ImGui::SetNextWindowSize(ImVec2(320.0f, (float)(height-18)));
        window_is_initialized = true;
    }
    bool visible = true;
    ImGui::Begin("Inspector", &visible,
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove
    );

    if (!visible) {
        set_visible(false);
    }
    
    ImGui::Dummy(ImVec2(0, 8));

    if (!selected_object) {
        ImGui::TextWrapped("%s", "No object selected.");
    } else {
        const void* obj_address = selected_object.get();
        char buffer[20];
        std::snprintf(buffer, sizeof(buffer), "%p", obj_address);
        std::string obj_id(buffer);

        ImGui::Text("Object id: %s", obj_id.c_str());

        ImGui::Dummy(ImVec2(0, 8));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0, 8));

        static char name[32];
        if (selected_object->name != name) {
            strcpy(name, selected_object->name.c_str());
        }
        ImGui::Text("%s", "Name:");
        ImGui::SameLine();
        if (ImGui::InputText("##object_name", name, IM_ARRAYSIZE(name))) {
            selected_object->name = name;
        }

        ImGui::Dummy(ImVec2(0, 8));
        ImGui::Separator();
        ImGui::Dummy(ImVec2(0, 8));

        ImGui::Text("%s", "position: ");
        ImGui::SameLine();
        ImGui::DragFloat2(("##obj_inputs"+obj_id).c_str(), selected_object->position);

        ComponentDrawInspectorVisitor visitor;
        for (auto& component : selected_object->get_components()) {
            ImGui::Dummy(ImVec2(0, 8));
            ImGui::Separator();
            ImGui::Dummy(ImVec2(0, 8));

            component->accept_visitor(visitor);
        }
    }

    ImGui::End();
}
