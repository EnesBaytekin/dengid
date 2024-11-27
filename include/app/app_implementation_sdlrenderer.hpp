#ifndef APP_IMPLEMENTATION_SDLRENDERER_HPP
#define APP_IMPLEMENTATION_SDLRENDERER_HPP

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <stdio.h>
#include <SDL2/SDL.h>

#include "app/i_app_implementation.hpp"

#if !SDL_VERSION_ATLEAST(2,0,17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

class AppImplementationSDLRenderer: public IAppImplementation {
private:
    SDL_Window* window;
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
};

#endif
