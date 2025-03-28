#ifndef IMGUI_WINDOW_MAIN_MENU_BAR_HPP
#define IMGUI_WINDOW_MAIN_MENU_BAR_HPP

#include "imgui_windows/imgui_window.hpp"

class AppMain;

class ImguiWindowMainMenuBar : public ImguiWindow {
public:
    ImguiWindowMainMenuBar() : ImguiWindow() {};
    ~ImguiWindowMainMenuBar() override = default;

    void show() override;
    void update() override;
};

#endif
