#ifndef PROJECT_SETTINGS_HPP
#define PROJECT_SETTINGS_HPP

#include "image/color.hpp"

struct ProjectSettings {
    int viewport_width = 320;
    int viewport_height = 180;
    int window_width = 1920;
    int window_height = 1080;
    int pixel_per_unit = 1;
    Color bg_color = Color(33, 88, 88);
};

#endif
