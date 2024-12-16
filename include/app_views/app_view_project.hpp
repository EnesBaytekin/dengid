#ifndef APP_VIEW_PROJECT_HPP
#define APP_VIEW_PROJECT_HPP

#include <memory>
#include "app_views/app_view.hpp"
#include "imgui_windows/imgui_window_settings.hpp"
#include "imgui_windows/imgui_window_main_menu_bar.hpp"
#include "imgui_windows/imgui_window_hierarchy.hpp"
#include "imgui_windows/imgui_window_inspector.hpp"

std::shared_ptr<AppView> get_app_view_project() {
    auto project_view = std::make_shared<AppView>();

    auto main_menu_bar_window = std::make_shared<ImguiWindowMainMenuBar>();
    project_view->add_window("main_menu_bar", main_menu_bar_window);

    auto settings_window = std::make_shared<ImguiWindowSettings>();
    project_view->add_window("settings", settings_window);

    auto hierarchy_window = std::make_shared<ImguiWindowHierarchy>();
    project_view->add_window("hierarchy", hierarchy_window);

    auto inspector_window = std::make_shared<ImguiWindowInspector>();
    project_view->add_window("inspector", inspector_window);

    return project_view;
}

#endif
