#include "app/app_main.hpp"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "app_views/app_view_initial.hpp"
#include "app_views/app_view_project.hpp"
#include "engine/scene.hpp"
#include "engine/camera.hpp"
#include "math/rect.hpp"
#include "engine/components/image_component.hpp"
#include "engine/editor_utility.hpp"
#include "project/project_manager.hpp"

void AppMain::setup() {
    this->add_view(EnumAppViewType::INITIAL_VIEW, get_app_view_initial());
    this->add_view(EnumAppViewType::PROJECT_VIEW, get_app_view_project());
}

void update_object_selections() {
    AppMain& app = AppMain::get_instance();
    ImguiWindowInspector* inspector = dynamic_cast<ImguiWindowInspector*>(app.get_view()->get_window("inspector").get());

    // drag object
    if (app.is_mouse_button_just_pressed(SDL_BUTTON_LEFT)) {
        Vector2 mouse_position = app.get_mouse_position_on_scene();
        for (auto& object : app.get_main_scene()->get_objects()) {
            auto rect = EditorUtility::get_object_rect(object);
            if (rect->is_colliding(mouse_position)) {
                if (inspector) {
                    inspector->selected_object = object;
                    inspector->is_dragging = true;
                }
            }
        }
    }
    if (inspector && inspector->is_dragging) {
        Vector2 mouse_motion = app.get_mouse_motion() / app.get_camera()->get_zoom();
        if (inspector->selected_object) {
            inspector->selected_object->position += mouse_motion;
        }
    }
    if (app.is_mouse_button_just_released(SDL_BUTTON_LEFT)) {
        if (inspector) {
            inspector->is_dragging = false;
        }
    }

    auto& camera = app.get_camera();
    if (camera) {
        // drag camera
        static bool is_camera_dragging = false;
        static Vector2 camera_drag_start_position = Vector2::ZERO;
        static Vector2 camera_drag_start_mouse_position = Vector2::ZERO;

        if (app.is_mouse_button_just_pressed(SDL_BUTTON_RIGHT)) {
            is_camera_dragging = true;
            camera_drag_start_position = camera->get_position();
            camera_drag_start_mouse_position = app.get_mouse_position();
        }
        if (is_camera_dragging) {
            Vector2 drag_offset = (app.get_mouse_position() - camera_drag_start_mouse_position) / camera->get_zoom();
            Vector2 camera_position = camera_drag_start_position - drag_offset;
            camera->set_position(camera_position);
        }
        if (app.is_mouse_button_just_released(SDL_BUTTON_RIGHT)) {
            is_camera_dragging = false;
        }

        // camera zoom
        if (app.is_key_pressed(SDL_SCANCODE_LCTRL) || app.is_key_pressed(SDL_SCANCODE_RCTRL)) {
            int mouse_wheel = app.get_mouse_wheel();
            if (mouse_wheel != 0) {
                Vector2 mouse_position_before_zoom = app.get_mouse_position_on_scene();
                float zoom_factor = camera->get_zoom();

                if (mouse_wheel > 0) {
                    if (zoom_factor < 10.0f) {
                        zoom_factor *= 1.1f;
                    }
                } else if (mouse_wheel < 0) {
                    if (zoom_factor > 0.1f) {
                        zoom_factor /= 1.1f;
                    }
                }

                camera->set_zoom(zoom_factor);

                Vector2 mouse_position_after_zoom = app.get_mouse_position_on_scene();
                Vector2 zoom_offset = mouse_position_before_zoom - mouse_position_after_zoom;
                Vector2 camera_position = camera->get_position() + zoom_offset;
                camera->set_position(camera_position);
            }
        }
    }
}

void AppMain::update() {
    for (SDL_Event event : event_list) {
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

    if (camera) {
        camera->update();
    }
}

void AppMain::draw() {
    this->get_view()->show();
    if (main_scene) {
        main_scene->draw();
        EditorUtility::debug_draw_scene(*main_scene);
    }
    if (camera && current_view_type == EnumAppViewType::PROJECT_VIEW) {
        auto project_settings = ProjectManager::get_instance().get_project_settings();
        Vector2 window_size = Vector2(project_settings.window_width, project_settings.window_height);
        draw_rect(0, 0, window_size.x, 1, 255, 255, 255, 128);
        draw_rect(0, window_size.y, window_size.x, 1, 255, 255, 255, 128);
        draw_rect(0, 0, 1, window_size.y, 255, 255, 255, 128);
        draw_rect(window_size.x, 0, 1, window_size.y, 255, 255, 255, 128);
    }
}

