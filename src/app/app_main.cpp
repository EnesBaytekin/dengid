#include "app/app_main.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "app_views/app_view_initial.hpp"
#include "app_views/app_view_project.hpp"
#include "engine/scene.hpp"
#include "math/rect.hpp"
#include "engine/components/image_component.hpp"
#include "engine/editor_utility.hpp"

void AppMain::setup() {
    this->add_view(EnumAppViewType::INITIAL_VIEW, get_app_view_initial());
    this->add_view(EnumAppViewType::PROJECT_VIEW, get_app_view_project());
}

void update_object_selections() {
    AppMain& app = AppMain::get_instance();
    if (app.is_mouse_button_just_pressed(SDL_BUTTON_LEFT)) {
        Vector2 mouse_position = app.get_mouse_position();
        for (auto& object : app.get_main_scene()->get_objects()) {
            auto rect = EditorUtility::get_object_rect(object);
            if (rect->is_colliding(mouse_position)) {
                ImguiWindowInspector* inspector = dynamic_cast<ImguiWindowInspector*>(app.get_view()->get_window("inspector").get());
                if (inspector) {
                    inspector->selected_object = object;
                }
            }
        }
    }
}

void AppMain::update() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT) {
            quit();
        }
    }

    this->get_view()->update();

    if (main_scene) {
        main_scene->update();
        update_object_selections();
    }
}

void AppMain::draw() {
    this->get_view()->show();
    if (main_scene) {
        main_scene->draw();
        EditorUtility::debug_draw_scene(*main_scene);
    }
}

