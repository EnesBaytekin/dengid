#ifndef APP_VIEW_PROJECT_HPP
#define APP_VIEW_PROJECT_HPP

#include <memory>
#include "app_views/app_view.hpp"
#include "imgui_windows/imgui_window_settings.hpp"

std::shared_ptr<AppView> get_app_view_project() {
    auto project_view = std::make_shared<AppView>();

    auto settings_window = std::make_shared<ImguiWindowSettings>();
    project_view->add_window("project", settings_window);

    return project_view;
}

#endif