#include "app/app_main.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_windows/main_menu_bar.hpp"
#include "imgui_windows/initial_window.hpp"

void AppMain::setup() {}

void AppMain::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT) {
            quit();
        }
    }
}

void AppMain::draw() {
    show_main_menu_bar(*this);
    show_initial_window(*this);
    // ImGui::ShowDemoWindow();
}

