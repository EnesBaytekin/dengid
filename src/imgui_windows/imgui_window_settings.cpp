#include "imgui.h"
#include <SDL2/SDL.h>
#include "app/app_main.hpp"
#include "imgui_windows/imgui_window_settings.hpp"

void show_settings_window(AppMain& app, bool& settings_window_is_shown) {
    static bool window_is_initialized = false;
    if (!window_is_initialized) {
        int width, height;
        SDL_GetWindowSize(app.window, &width, &height);
        ImGui::SetNextWindowPos(ImVec2(width*0.25f, height*0.25f));
        ImGui::SetNextWindowSize(ImVec2(width*0.5f, height*0.5f));
        window_is_initialized = true;
    }
    ImGui::Begin("Settings", &settings_window_is_shown,
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize
    );
    ImGui::TextWrapped("%s", app.get_project_path().string().c_str());
    ImGui::End();
}

void ImguiWindowSettings::show(AppMain& app) {
    static bool settings_window_is_shown = true;
    if (settings_window_is_shown) {
        show_settings_window(app, settings_window_is_shown);
    }
}
