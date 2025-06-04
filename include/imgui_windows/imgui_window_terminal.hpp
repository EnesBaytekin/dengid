#ifndef IMGUI_WINDOW_TERMINAL_HPP
#define IMGUI_WINDOW_TERMINAL_HPP

#include "imgui_windows/imgui_window.hpp"
#include <string>
#include <vector>
#include <mutex>

class AppMain;

class ImguiWindowTerminal : public ImguiWindow {
private:
    std::mutex print_mutex;
    std::vector<char> buffer = {'\0'};
public:
    ImguiWindowTerminal() : ImguiWindow() {};
    ~ImguiWindowTerminal() override = default;

    void show() override;
    void update() override;

    void clear() {
        std::lock_guard<std::mutex> guard(print_mutex);
        buffer.clear();
        buffer.push_back('\0');
    }
    void print(const std::string& line) { 
        if (!buffer.empty() && buffer.back() == '\0') {
            buffer.pop_back();
        }
        std::lock_guard<std::mutex> guard(print_mutex); 
        buffer.insert(buffer.end(), line.begin(), line.end());
        buffer.push_back('\0');
    }

    std::vector<char>& get_buffer() { return buffer; }
};

#endif
