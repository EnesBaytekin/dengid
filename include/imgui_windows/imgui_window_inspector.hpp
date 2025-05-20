#ifndef IMGUI_WINDOW_INSPECTOR_HPP
#define IMGUI_WINDOW_INSPECTOR_HPP

#include "imgui_windows/imgui_window.hpp"
#include "engine/object.hpp"
#include <memory>

class AppMain;

class ImguiWindowInspector : public ImguiWindow {
public:
    std::shared_ptr<Object> selected_object = nullptr;
    bool is_dragging = false;
    
    ImguiWindowInspector() : ImguiWindow() {};
    ~ImguiWindowInspector() override = default;

    void show() override;
};

#endif
