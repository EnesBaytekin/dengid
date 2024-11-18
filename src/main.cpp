#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[]) {
    // SDL'i başlat
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Pencere oluştur
    SDL_Window* window = SDL_CreateWindow("SDL Loop Example",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          800, 600,
                                          SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Renderer oluştur
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Ana döngü
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        // Ekranı temizle
        SDL_SetRenderDrawColor(renderer, 33, 88, 88, 255); // Siyah arkaplan
        SDL_RenderClear(renderer);

        // Basit bir dikdörtgen çiz
        SDL_SetRenderDrawColor(renderer, 192, 0, 0, 255); // Kırmızı
        SDL_Rect rect = { 100, 100, 200, 150 };
        SDL_RenderFillRect(renderer, &rect);

        // Çizim işlemlerini ekrana yansıt
        SDL_RenderPresent(renderer);

        // Döngüyü yavaşlatmak için kısa bir gecikme ekle
        SDL_Delay(16); // Yaklaşık 60 FPS
    }

    // SDL kaynaklarını serbest bırak
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
