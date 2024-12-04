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
    
    ImGui::Dummy(ImVec2(0, 20));

    ImGui::TextWrapped("Project Path: %s", app.get_project_path().string().c_str());

    ImGui::Dummy(ImVec2(0, 20));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 20));

    ImGui::Text("%s", "Game Window Size:");
    static bool size_initialized = false;
    static int game_window_size[2];
    if (!size_initialized) {
        auto settings = app.get_project_settings();
        game_window_size[0] = settings.get_window_width();
        game_window_size[1] = settings.get_window_height();
        size_initialized = true;
    }
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    if (ImGui::InputInt2("##game_window_size", game_window_size)) {
        auto settings = app.get_project_settings();
        settings.set_window_width(game_window_size[0]);
        settings.set_window_width(game_window_size[1]);
    }

    ImGui::End();
}

void ImguiWindowSettings::show(AppMain& app) {
    static bool settings_window_is_shown = true;
    if (settings_window_is_shown) {
        show_settings_window(app, settings_window_is_shown);
    }
}
