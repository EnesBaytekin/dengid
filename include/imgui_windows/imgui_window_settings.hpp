#ifndef IMGUI_WINDOW_SETTINGS_HPP
#define IMGUI_WINDOW_SETTINGS_HPP

#include "imgui_windows/imgui_window.hpp"

class AppMain;

class ImguiWindowSettings : public ImguiWindow {
public:
    ImguiWindowSettings() : ImguiWindow() {};
    ~ImguiWindowSettings() override = default;

    void show() override;
};

#endif
