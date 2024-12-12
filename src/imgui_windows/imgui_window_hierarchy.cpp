#include "imgui.h"
#include <SDL2/SDL.h>
#include "app/app_main.hpp"
#include "imgui_windows/imgui_window_hierarchy.hpp"

void show_hierarchy_window(AppMain& app, bool& hierarchy_window_is_shown) {
    static bool window_is_initialized = false;
    if (!window_is_initialized) {
        int width, height;
        SDL_GetWindowSize(app.window, &width, &height);
        ImGui::SetNextWindowPos(ImVec2(0, 18));
        ImGui::SetNextWindowSize(ImVec2(256.0f, (float)(height-18)));
        window_is_initialized = true;
    }
    ImGui::Begin("Hierarchy", &hierarchy_window_is_shown,
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove
    );
    
    ImGui::Dummy(ImVec2(0, 20));

    ImGui::TextWrapped("%s", "Scene and objects are shown here.");

    ImGui::Dummy(ImVec2(0, 20));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 20));

    ImGui::End();
}

void ImguiWindowHierarchy::show(AppMain& app) {
    static bool hierarchy_window_is_shown = true;
    if (hierarchy_window_is_shown) {
        show_hierarchy_window(app, hierarchy_window_is_shown);
    }
}
