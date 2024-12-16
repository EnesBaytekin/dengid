#include "imgui_windows/imgui_window_main_menu_bar.hpp"
#include "app/app_main.hpp"
#include "app_views/app_view.hpp"
#include "imgui.h"
#include <iostream>

void ImguiWindowMainMenuBar::show() {
    AppMain& app = AppMain::get_instance();
    
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
            ImGui::Separator();
            if (ImGui::MenuItem("Exit", "Alt+F4")) {
                app.quit();
            }
            ImGui::EndMenu();
        }

        auto view_type = app.get_current_view_type();
        if (view_type == EnumAppViewType::PROJECT_VIEW) {
            auto view = app.get_view();
            if (ImGui::BeginMenu("View")) {
                if (ImGui::MenuItem("Settings Window")) {
                    auto window = view->get_window("settings");
                    window->set_visible(!window->is_visible());
                }
                if (ImGui::MenuItem("Hierarchy Window")) {
                    auto window = view->get_window("hierarchy");
                    window->set_visible(!window->is_visible());
                }
                if (ImGui::MenuItem("Inspector Window")) {
                    auto window = view->get_window("inspector");
                    window->set_visible(!window->is_visible());
                }
                ImGui::EndMenu();
            }
        }

        ImGui::EndMainMenuBar();
    }
}
