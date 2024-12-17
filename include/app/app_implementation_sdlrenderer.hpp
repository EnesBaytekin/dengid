#ifndef APP_IMPLEMENTATION_SDLRENDERER_HPP
#define APP_IMPLEMENTATION_SDLRENDERER_HPP

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "app/i_app_implementation.hpp"
#include <memory>

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

class AppImplementationSDLRenderer: public IAppImplementation {
private:
    SDL_Renderer* renderer;
public:
    AppImplementationSDLRenderer(std::string window_name, int window_width, int window_height);
    ~AppImplementationSDLRenderer() override;
    void setup() override;
    void update() override;
    void create_frame() override;
    void clear_renderer() override;
    void render() override;
    
    void draw_rect(int x, int y, int width, int height) override;
    std::shared_ptr<Image> load_image(const std::string& file_path) override;
    void draw_image(const std::string& image_id, int x, int y) override;
    void draw_imgui_image(const std::string& image_id, int width, int height) override;
};

#endif
