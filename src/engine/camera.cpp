#include "engine/camera.hpp"
#include "engine/object.hpp"
#include "project/project_manager.hpp"

void Camera::update() {
    if (target) {
        auto& settings = ProjectManager::get_instance().get_project_settings();
        Vector2 screen_size(
            settings.window_width,
            settings.window_height
        );
        Vector2 mid_position = position + (screen_size / 2.0f);
        position += (target->position - mid_position)*smoothing_factor;
    }
}
