#include "imgui.h"
#include <SDL2/SDL.h>
#include "app/app_main.hpp"
#include "app_views/app_view.hpp"
#include "imgui_windows/imgui_window_terminal.hpp"

void show_terminal_window() {
    AppMain& app = AppMain::get_instance();
    
    static bool window_is_initialized = false;
    if (!window_is_initialized) {
        int width, height;
        SDL_GetWindowSize(app.window, &width, &height);
        ImGui::SetNextWindowPos(ImVec2(320.0f, height*0.8f));
        ImGui::SetNextWindowSize(ImVec2(width-640.0f, height*0.2f));
        window_is_initialized = true;
    }
    bool visible = true;
    ImGui::Begin("Terminal", &visible,
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize
    );

    if (!visible) {
        auto window = app.get_view()->get_window("terminal");
        window->set_visible(false);
    }
    
    ImGui::Dummy(ImVec2(0, 20));

    ImGui::Text("Terminal Window");

    ImGui::End();
}

void ImguiWindowTerminal::show() {
    AppMain& app = AppMain::get_instance();
    auto window = app.get_view()->get_window("terminal");
    if (window->is_visible()) {
        show_terminal_window();
    }
}
