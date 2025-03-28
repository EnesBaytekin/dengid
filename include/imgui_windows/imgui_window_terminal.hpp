#ifndef IMGUI_WINDOW_TERMINAL_HPP
#define IMGUI_WINDOW_TERMINAL_HPP

#include "imgui_windows/imgui_window.hpp"
#include <string>
#include <vector>

class AppMain;

class ImguiWindowTerminal : public ImguiWindow {
private:
    std::vector<std::string> lines;
public:
    ImguiWindowTerminal() : ImguiWindow() {};
    ~ImguiWindowTerminal() override = default;

    void show() override;
    void update() override;

    void clear() { lines.clear(); }
    void print(const std::string& line) { lines.push_back(line); }

    std::vector<std::string>& get_lines() { return lines; }
};

#endif
