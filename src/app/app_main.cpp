#include "app/app_main.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_windows/main_menu_bar.hpp"
#include "imgui_windows/initial_view.hpp"
#include "imgui_windows/project_view.hpp"

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
    AppMain& app = *this;
    
    show_main_menu_bar(app);

    switch (app.get_view_state()) {
        case AppViewState::INITIAL_VIEW: {
            show_initial_view(app);
            break;
        }
        case AppViewState::PROJECT_VIEW: {
            show_project_view(app);
            break;
        }
    }
}

