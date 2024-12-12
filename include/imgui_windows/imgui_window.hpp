#ifndef IMGUI_WINDOW_HPP
#define IMGUI_WINDOW_HPP

class AppMain;

class ImguiWindow {
protected:
    bool visible;
public:
    ImguiWindow(bool visible_at_start=true): visible(visible_at_start) {};
    virtual ~ImguiWindow() = default;
    
    void set_visible(bool new_visiblity) { visible = new_visiblity; }
    bool is_visible() { return visible; }
    virtual void show(AppMain& app) = 0;
};

#endif
