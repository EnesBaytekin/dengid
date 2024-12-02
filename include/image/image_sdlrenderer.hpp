#ifndef IMAGE_SDLRENDERER_HPP
#define IMAGE_SDLRENDERER_HPP

#include "image/image.hpp"
#include <SDL2/SDL.h>

class ImageSDLRenderer: public Image {
public:
    ImageSDLRenderer(SDL_Texture* sdl_image): image(sdl_image) {}
    void* get_native_image() override { return image; }
private:
    SDL_Texture* image;
};

#endif
