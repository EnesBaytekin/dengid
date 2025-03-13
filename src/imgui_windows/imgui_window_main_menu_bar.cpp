#include "imgui_windows/imgui_window_main_menu_bar.hpp"
#include "app/app_main.hpp"
#include "app_views/app_view.hpp"
#include "project/project_manager.hpp"
#include "imgui.h"
#include <iostream>
#include <fstream>
#include <thread>

void build_game() {
    std::ofstream file("./include/project_path_macro.hpp");
    if (!file.is_open()) {
        std::cerr << "Failed to create project path macro file." << std::endl;
        return;
    }

    std::filesystem::path project_path = ProjectManager::get_instance().get_project_path();
    std::string project_name = project_path.filename().string();

    file << "#pragma once\n";
    file << "#define PROJECT_PATH \"";
    file << project_path.string();
    file << "\"\n";
    file.close();

    std::string build_command = "make clean all && mv ./game_build/game "+(project_path/project_name).string();
    std::system(build_command.c_str());
    std::cout << "Game built successfully." << std::endl;
}

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

            if (ImGui::BeginMenu("Build")) {
                if (ImGui::MenuItem("Build Game")) {
                    std::thread build_thread(build_game);
                    build_thread.detach();
                }
                ImGui::EndMenu();
            }
        }

        ImGui::EndMainMenuBar();
    }
}
