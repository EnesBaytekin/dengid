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

std::unique_ptr<Rect> get_ui_rect(Object* object) {
    if (object->has_component(ComponentType::IMAGE_COMPONENT)) {
        auto& image_component = *dynamic_cast<ImageComponent*>(object->get_component(ComponentType::IMAGE_COMPONENT).get());
        return std::make_unique<Rect>(object->position, image_component.get_size());
    } else {
        return std::make_unique<Rect>(object->position, 32, 32);
    }
}

void update_object_selections() {
    AppMain& app = AppMain::get_instance();
    if (app.is_mouse_button_just_pressed(SDL_BUTTON_LEFT)) {
        Vector2 mouse_position = app.get_mouse_position();
        for (auto& object : app.get_main_scene()->get_objects()) {
            auto rect = get_ui_rect(object.get());
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
    }
}

