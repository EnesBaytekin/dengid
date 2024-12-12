#include "imgui.h"
#include <SDL2/SDL.h>
#include "app/app_main.hpp"
#include "app_views/app_view.hpp"
#include "imgui_windows/imgui_window_settings.hpp"

void show_settings_window(AppMain& app) {
    static bool window_is_initialized = false;
    if (!window_is_initialized) {
        int width, height;
        SDL_GetWindowSize(app.window, &width, &height);
        ImGui::SetNextWindowPos(ImVec2(width*0.25f, height*0.25f));
        ImGui::SetNextWindowSize(ImVec2(width*0.5f, height*0.5f));
        window_is_initialized = true;
    }
    bool visible = true;
    ImGui::Begin("Settings", &visible,
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize
    );

    if (!visible) {
        auto window = app.get_view()->get_window("settings");
        window->set_visible(false);
    }
    
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
        game_window_size[0] = settings.window_width;
        game_window_size[1] = settings.window_height;
        size_initialized = true;
    }
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    if (ImGui::InputInt2("##game_window_size", game_window_size)) {
        auto settings = app.get_project_settings();
        settings.window_width = game_window_size[0];
        settings.window_height = game_window_size[1];
    }

    ImGui::End();
}

void ImguiWindowSettings::show(AppMain& app) {
    auto window = app.get_view()->get_window("settings");
    if (window->is_visible()) {
        show_settings_window(app);
    }
}
