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

    auto& settings = project_manager.get_project_settings();
    
    static bool settings_initialized = false;
    static int viewport_size[2];
    static int game_window_size[2];
    static int pixel_per_unit;
    if (!settings_initialized) {
        settings_initialized = true;

        viewport_size[0] = settings.viewport_width;
        viewport_size[1] = settings.viewport_height;
        game_window_size[0] = settings.window_width;
        game_window_size[1] = settings.window_height;
        pixel_per_unit = settings.pixel_per_unit;
    }

    ImGui::Text("%s", "Viewport Size:");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    if (ImGui::InputInt2("##viewport_size", viewport_size)) {
        settings.viewport_width = viewport_size[0];
        settings.viewport_height = viewport_size[1];
    }

    ImGui::Text("%s", "Game Window Size:");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    if (ImGui::InputInt2("##game_window_size", game_window_size)) {
        settings.window_width = game_window_size[0];
        settings.window_height = game_window_size[1];
    }

    ImGui::Text("%s", "Pixel Per Unit:");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    if (ImGui::InputInt("##pixel_per_unit", &pixel_per_unit)) {
        settings.pixel_per_unit = std::max(0, pixel_per_unit);
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
