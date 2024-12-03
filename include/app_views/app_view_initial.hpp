#ifndef APP_VIEW_INITIAL_HPP
#define APP_VIEW_INITIAL_HPP

#include <memory>
#include "app_views/app_view.hpp"
#include "imgui_windows/imgui_window_initial.hpp"

std::shared_ptr<AppView> get_app_view_initial() {
    auto initial_view = std::make_shared<AppView>();

    auto initial_window = std::make_shared<ImguiWindowInitial>();
    initial_view->add_window("initial", initial_window);

    return initial_view;
}

#endif
