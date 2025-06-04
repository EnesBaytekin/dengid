#include "imgui_windows/imgui_window_main_menu_bar.hpp"
#include "app/app_main.hpp"
#include "app_views/app_view.hpp"
#include "project/project_manager.hpp"
#include "engine/scene.hpp"
#include "engine/object.hpp"
#include "engine/components/component_type.hpp"
#include "imgui.h"
#include <iostream>
#include <fstream>
#include <thread>

void ImguiWindowMainMenuBar::update() {
    AppMain& app = AppMain::get_instance();
    ProjectManager& project_manager = ProjectManager::get_instance();

    auto view_type = app.get_current_view_type();
    if (view_type == EnumAppViewType::PROJECT_VIEW) {
        if (app.is_key_just_pressed(SDL_SCANCODE_F6)) {
            std::thread build_thread([&project_manager]() {
                project_manager.build_game();
                project_manager.run_game();
            });
            build_thread.detach();
        }
        if (app.is_key_just_pressed(SDL_SCANCODE_F5)) {
            if (app.is_key_pressed(SDL_SCANCODE_LSHIFT)) { // Shift+F5
                project_manager.stop_game();
            } else { // F5
                std::thread run_thread([&project_manager]() {
                    project_manager.run_game();
                });
                run_thread.detach();
            }
        }
        if (app.is_key_just_pressed(SDL_SCANCODE_S)) {
            if (app.is_key_pressed(SDL_SCANCODE_LCTRL)) {
                project_manager.save_project();
            }
        }
        if (app.is_key_just_pressed(SDL_SCANCODE_F4)) {
            if (app.is_key_pressed(SDL_SCANCODE_LCTRL)) {
                project_manager.close_project();
            }
        }
    }
}

void ImguiWindowMainMenuBar::show() {
    AppMain& app = AppMain::get_instance();
    ProjectManager& project_manager = ProjectManager::get_instance();
    auto view_type = app.get_current_view_type();
    
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 10));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    ImGui::Begin("FakeMainMenuBar", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_MenuBar |
        ImGuiWindowFlags_NoNavFocus |
        ImGuiWindowFlags_NoBackground
    );

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Save", "Ctrl+S")) {
                project_manager.save_project();
            }
            if (view_type == EnumAppViewType::PROJECT_VIEW) {
                if (ImGui::MenuItem("Close Project", "Ctrl+F4")) {
                    project_manager.close_project();
                }
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit", "Alt+F4")) {
                app.quit();
            }
            ImGui::EndMenu();
        }

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
                if (ImGui::MenuItem("Console Window")) {
                    auto window = view->get_window("terminal");
                    window->set_visible(!window->is_visible());
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Build")) {
                if (ImGui::MenuItem("Build Game", "F6")) {
                    std::thread build_thread([&project_manager]() {
                        project_manager.build_game();
                        project_manager.run_game();
                    });
                    build_thread.detach();
                }
                if (ImGui::MenuItem("Run Game", "F5")) {
                    std::thread run_thread([&project_manager]() {
                        project_manager.run_game();
                    });
                    run_thread.detach();
                }
                if (ImGui::MenuItem("Stop Game", "Shift+F5")) {
                    project_manager.stop_game();
                }
                ImGui::EndMenu();
            }
        }

        ImGui::EndMenuBar();
    }
    ImGui::End();
    ImGui::PopStyleVar(2);
}
