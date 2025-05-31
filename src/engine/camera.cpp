#include "engine/camera.hpp"
#include "engine/object.hpp"

void Camera::update() {
    if (target) {
        position += (target->position - position)*smoothing_factor;
    }
}
