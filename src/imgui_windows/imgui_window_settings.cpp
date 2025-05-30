#include "imgui.h"
#include <SDL2/SDL.h>
#include "app/app_main.hpp"
#include "app_views/app_view.hpp"
#include "imgui_windows/imgui_window_settings.hpp"
#include "project/project_manager.hpp"

void show_settings_window() {
    AppMain& app = AppMain::get_instance();
    ProjectManager& project_manager = ProjectManager::get_instance();
    
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

    ImGui::TextWrapped("Project Path: %s", project_manager.get_project_path().string().c_str());

    ImGui::Dummy(ImVec2(0, 20));
    ImGui::Separator();
    ImGui::Dummy(ImVec2(0, 20));

    ImGui::Text("%s", "Game Window Size:");

    auto& settings = project_manager.get_project_settings();
    
    static bool size_initialized = false;
    static int game_window_size[2];
    if (!size_initialized) {
        game_window_size[0] = settings.window_width;
        game_window_size[1] = settings.window_height;
        size_initialized = true;
    }
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    if (ImGui::InputInt2("##game_window_size", game_window_size)) {
        settings.window_width = game_window_size[0];
        settings.window_height = game_window_size[1];
    }

    ImGui::End();
}

void ImguiWindowSettings::show() {
    AppMain& app = AppMain::get_instance();
    auto window = app.get_view()->get_window("settings");
    if (window->is_visible()) {
        show_settings_window();
    }
}
