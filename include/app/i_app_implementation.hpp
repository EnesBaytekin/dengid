#ifndef I_APP_IMPLEMENTATION_HPP
#define I_APP_IMPLEMENTATION_HPP

#include <string>
#include <memory>
#include <SDL2/SDL.h>
#include "image/image.hpp"

class IAppImplementation {
protected:
    std::string window_name;
    int window_width;
    int window_height;
    SDL_Window* window;
public:
    IAppImplementation(std::string name, int width, int height):
        window_name(name),
        window_width(width),
        window_height(height) {}
    virtual ~IAppImplementation() = default;
    SDL_Window* get_window() { return window; }
    virtual void setup() = 0;
    virtual void update() = 0;
    virtual void create_frame() = 0;
    virtual void clear_renderer() = 0;
    virtual void render() = 0;

    virtual void draw_rect(int x, int y, int width, int height, int r, int g, int b, int a, bool fill) = 0;
    virtual std::shared_ptr<Image> load_image(const std::string& file_path) = 0;
    virtual void draw_image(const std::string& image_id, int x, int y, float scale_x, float scale_y, bool flip_x, bool flip_y, int src_x, int src_y, int src_w, int src_h) = 0;
    virtual void draw_imgui_image(const std::string& image_id, int width, int height) = 0;
};

#endif
