#ifndef IMGUI_VIEW_PROJECT_HPP
#define IMGUI_VIEW_PROJECT_HPP

#include "imgui_windows/imgui_window.hpp"

class AppMain;

class ImguiWindowSettings : public ImguiWindow {
public:
    ImguiWindowSettings() : ImguiWindow() {};
    ~ImguiWindowSettings() override = default;

    void show() override;
};

#endif
