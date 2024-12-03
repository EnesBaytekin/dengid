#ifndef IMGUI_WINDOW_HPP
#define IMGUI_WINDOW_HPP

class AppMain;

class ImguiWindow {
public:
    ImguiWindow() = default;
    virtual ~ImguiWindow() = default;
    
    virtual void show(AppMain& app) = 0;
};

#endif
