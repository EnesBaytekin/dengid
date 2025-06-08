#include "engine/camera.hpp"
#include "engine/object.hpp"
#include "project/project_manager.hpp"

void Camera::update() {
    if (target) {
        auto& settings = ProjectManager::get_instance().get_project_settings();
        Vector2 screen_size(
            settings.viewport_width,
            settings.viewport_height
        );
        Vector2 mid_position = position + (screen_size / 2.0f);
        Vector2 new_position = position + (target->position - mid_position)*smoothing_factor;
        if (follow_x) { position.x = new_position.x; }
        if (follow_y) { position.y = new_position.y; }
    }
}
