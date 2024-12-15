#ifndef APP_VIEW_HPP
#define APP_VIEW_HPP

#include <string>
#include <map>
#include <memory>
#include "app_views/enum_app_view_type.hpp"
#include "imgui_windows/imgui_window.hpp"

class AppView {
private:
    std::map<std::string, std::shared_ptr<ImguiWindow>> windows;
public:
    AppView() = default;
    ~AppView() = default;

    void                         add_window(std::string name, std::shared_ptr<ImguiWindow> window) { windows.insert({name, window}); }
    std::shared_ptr<ImguiWindow> get_window(std::string name) { return windows[name]; }
    void show() {
        for (auto [name, window] : windows) {
            if (window->is_visible()) {
                window->show();
            }
        }
    }
};

#endif
