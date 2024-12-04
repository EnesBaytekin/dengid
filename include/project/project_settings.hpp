#ifndef PROJECT_SETTINGS_HPP
#define PROJECT_SETTINGS_HPP

class ProjectSettings {
private:
    int window_width = 640;
    int window_height = 360;
public:
    ProjectSettings() = default;
    ~ProjectSettings() = default;

    void set_window_width(int new_window_width) { window_width = new_window_width; }
    int  get_window_width() { return window_width; }

    void set_window_height(int new_window_height) { window_height = new_window_height; }
    int  get_window_height() { return window_height; }
};

#endif
