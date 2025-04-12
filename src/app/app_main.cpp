#include "app/app_main.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "app_views/app_view_initial.hpp"
#include "app_views/app_view_project.hpp"
#include "engine/scene.hpp"
#include "math/rect.hpp"
#include "engine/components/image_component.hpp"

void AppMain::setup() {
    this->add_view(EnumAppViewType::INITIAL_VIEW, get_app_view_initial());
    this->add_view(EnumAppViewType::PROJECT_VIEW, get_app_view_project());
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
        if (is_mouse_button_just_pressed(SDL_BUTTON_LEFT)) {
            Vector2 mouse_position = get_mouse_position();
            for (auto& object : main_scene->get_objects()) {
                if (object->has_component(ComponentType::IMAGE_COMPONENT)) {
                    auto& image_component = *dynamic_cast<ImageComponent*>(object->get_component(ComponentType::IMAGE_COMPONENT).get());
                    Rect rect(object->position, image_component.get_size());
                    if (rect.is_colliding(mouse_position)) {
                        ImguiWindowInspector* inspector = dynamic_cast<ImguiWindowInspector*>(get_view()->get_window("inspector").get());
                        if (inspector) {
                            inspector->selected_object = object;
                        }
                    }
                }
            }
        }
    }
}

void AppMain::draw() {
    this->get_view()->show();
    if (main_scene) {
        main_scene->draw();
    }
}

