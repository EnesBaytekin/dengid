#include "app/app_main.hpp"
#include "imgui.h"
#include <iostream>

void show_main_menu_bar(AppMain& app) {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Save", "Ctrl+S")) {
                std::cout << "Saving..." << std::endl;
            }
            if (ImGui::MenuItem("Save as...", "Ctrl+Shift+S")) {
                std::cout << "Saving as..." << std::endl;
            }
            if (ImGui::MenuItem("Open", "Ctrl+O")) {
                std::cout << "Opening..." << std::endl;
            }
            ImGui::SeparatorText("");
            if (ImGui::MenuItem("Exit", "Alt+F4")) {
                app.quit();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}