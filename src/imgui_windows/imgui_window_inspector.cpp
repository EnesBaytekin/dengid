#include "imgui_windows/imgui_window_inspector.hpp"
#include <project/project_manager.hpp>
#include "imgui.h"
#include <SDL2/SDL.h>
#include "app/app_main.hpp"
#include "app_views/app_view.hpp"

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
    
    ImGui::Dummy(ImVec2(0, 20));

    if (!selected_object) {
        ImGui::TextWrapped("%s", "Objects properties are shown here.");
    } else {
        const void* obj_address = selected_object.get();
        char buffer[20];
        std::snprintf(buffer, sizeof(buffer), "%p", obj_address);
        std::string obj_id(buffer);

        ImGui::Text("Object %s", obj_id.c_str());

        ImGui::Dummy(ImVec2(0, 20));

        ImGui::Text("%s", "position: ");
        ImGui::SameLine();
        ImGui::DragFloat2(("##obj_inputs"+obj_id).c_str(), selected_object->position);
    }

    ImGui::End();
}
