#include "imgui_windows/imgui_window_main_menu_bar.hpp"
#include "app/app_main.hpp"
#include "app_views/app_view.hpp"
#include "project/project_manager.hpp"
#include "engine/scene.hpp"
#include "engine/object.hpp"
#include "engine/components/component_type.hpp"
#include "engine/components/script_component.hpp"
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

    ProjectManager& project_manager = ProjectManager::get_instance();
    project_manager.save_project();
    std::filesystem::path project_path = project_manager.get_project_path();
    std::string project_name = project_path.filename().string();

    file << "#pragma once\n";
    file << "#define PROJECT_PATH \"";
    file << project_path.string();
    file << "\"\n";
    file.close();

    std::system("rm ./game_build/scripts/*.cpp");
    std::system("mkdir -p ./game_build/scripts");
    AppMain& app = AppMain::get_instance();
    auto scene = app.get_main_scene();
    for (auto& object : scene->get_objects()) {
        for (auto& component : object->get_components()) {
            if (component->get_type() == ComponentType::SCRIPT_COMPONENT) {
                std::string script_name = (dynamic_cast<ScriptComponent*>(component.get()))->get_script_file_name();
                std::system(("cp "+(project_path/script_name).string()+" ./game_build/scripts/"+script_name).c_str());
            }
        }
    }

    std::system(("make all && mv ./game_build/game \""+(project_path/project_name).string()+"\"").c_str());
}

void run_game() {
    ProjectManager& project_manager = ProjectManager::get_instance();
    std::filesystem::path project_path = project_manager.get_project_path();
    std::string project_name = project_path.filename().string();

    std::system((project_path/project_name).string().c_str());
}

void build_and_run_game() {
    build_game();
    run_game();
}

void ImguiWindowMainMenuBar::update() {
    AppMain& app = AppMain::get_instance();

    auto view_type = app.get_current_view_type();
    if (view_type == EnumAppViewType::PROJECT_VIEW) {
        if (app.is_key_just_pressed(SDL_SCANCODE_F5)) {
            if (app.is_key_pressed(SDL_SCANCODE_LCTRL)) {
                std::thread build_thread(build_and_run_game);
                build_thread.detach();
            } else {
                std::thread build_thread(run_game);
                build_thread.detach();
            }
        }
        if (app.is_key_just_pressed(SDL_SCANCODE_S)) {
            if (app.is_key_pressed(SDL_SCANCODE_LCTRL)) {
                std::cout << "Scene is saving..." << std::endl;
                ProjectManager& project_manager = ProjectManager::get_instance();
                project_manager.save_project();
                std::cout << "Scene has saved" << std::endl;
            }
        }
    }
}

void ImguiWindowMainMenuBar::show() {
    AppMain& app = AppMain::get_instance();
    
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Save", "Ctrl+S")) {
                std::cout << "Scene is saving..." << std::endl;
                ProjectManager& project_manager = ProjectManager::get_instance();
                project_manager.save_project();
                std::cout << "Scene has saved" << std::endl;
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
                if (ImGui::MenuItem("Build Game", "Ctrl+F5")) {
                    std::thread build_thread(build_and_run_game);
                    build_thread.detach();
                }
                if (ImGui::MenuItem("Run Game", "F5")) {
                    std::thread build_thread(run_game);
                    build_thread.detach();
                }
                ImGui::EndMenu();
            }
        }

        ImGui::EndMainMenuBar();
    }
}
