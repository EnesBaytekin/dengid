#include "imgui.h"
#include <SDL2/SDL.h>
#include "app/app_main.hpp"
#include "app_views/app_view.hpp"
#include "imgui_windows/imgui_window_terminal.hpp"

void show_terminal_window(ImguiWindowTerminal* window) {
    AppMain& app = AppMain::get_instance();
    
    static bool auto_scroll = true;
    static bool window_is_initialized = false;
    if (!window_is_initialized) {
        int width, height;
        SDL_GetWindowSize(app.window, &width, &height);
        ImGui::SetNextWindowPos(ImVec2(320.0f, height*0.8f));
        ImGui::SetNextWindowSize(ImVec2(width-640.0f, height*0.2f));
        window_is_initialized = true;
        window->clear();
    }
    bool visible = true;
    ImGui::Begin("Console", &visible,
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize
    );

    if (!visible) {
        window->set_visible(false);
    }

    if (ImGui::Button("Clear##terminal")) {
        window->clear();
    }
    
    ImGui::SameLine();
    ImGui::Checkbox("Auto-scroll", &auto_scroll);

    auto& buffer = window->get_buffer();
    ImGui::InputTextMultiline("##ConsoleText", buffer.data(), buffer.size(),
                              ImVec2(-FLT_MIN, -FLT_MIN),
                              ImGuiInputTextFlags_ReadOnly);
    
    ImGui::BeginChild("##ConsoleText", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);

    static float current_scroll_y = ImGui::GetScrollMaxY();
    float scroll_max_y = ImGui::GetScrollMaxY();
    if (current_scroll_y != scroll_max_y) {
        current_scroll_y = scroll_max_y;
        if (auto_scroll) {
            ImGui::SetScrollHereY(1.0f);
        }
    }

    ImGui::EndChild();

    ImGui::End();
}

void ImguiWindowTerminal::update() {
    
}

void ImguiWindowTerminal::show() {
    AppMain& app = AppMain::get_instance();
    auto window = app.get_view()->get_window("terminal");
    if (window->is_visible()) {
        show_terminal_window(this);
    }
}
