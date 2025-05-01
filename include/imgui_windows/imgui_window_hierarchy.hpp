#ifndef IMGUI_WINDOW_HIERARCHY_HPP
#define IMGUI_WINDOW_HIERARCHY_HPP

#include "imgui_windows/imgui_window.hpp"

class AppMain;

class ImguiWindowHierarchy : public ImguiWindow {
public:
    ImguiWindowHierarchy() : ImguiWindow() {};
    ~ImguiWindowHierarchy() override = default;

    void show() override;
    void update() override;
};

#endif
