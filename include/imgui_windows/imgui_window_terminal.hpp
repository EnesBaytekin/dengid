#ifndef IMGUI_WINDOW_TERMINAL_HPP
#define IMGUI_WINDOW_TERMINAL_HPP

#include "imgui_windows/imgui_window.hpp"

class AppMain;

class ImguiWindowTerminal : public ImguiWindow {
public:
    ImguiWindowTerminal() : ImguiWindow() {};
    ~ImguiWindowTerminal() override = default;

    void show() override;
};

#endif
