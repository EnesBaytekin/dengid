#include "app/app_main.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "app_views/app_view_initial.hpp"
#include "app_views/app_view_project.hpp"
#include "engine/scene.hpp"

void AppMain::setup() {

}

void AppMain::update() {
    for (SDL_Event event : event_list) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT) {
            quit();
        }
    }

    if (main_scene) {
        main_scene->update();
    }
}

void AppMain::draw() {
    if (main_scene) {
        main_scene->draw();
    }
}

