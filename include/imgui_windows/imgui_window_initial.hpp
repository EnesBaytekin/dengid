#ifndef IMGUI_WINDOW_INITIAL_HPP
#define IMGUI_WINDOW_INITIAL_HPP

#include "imgui_windows/imgui_window.hpp"

class AppMain;

class ImguiWindowInitial : public ImguiWindow {
public:
    ImguiWindowInitial() : ImguiWindow() {};
    ~ImguiWindowInitial() override = default;

    void show() override;
};

#endif
