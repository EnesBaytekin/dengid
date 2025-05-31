#pragma once

#include "math/vector2.hpp"
#include <memory>

class Object;

class Camera {
private:
    Vector2 position;
    std::shared_ptr<Object> target;
    float smoothing_factor = 0.1f;

public:
    Camera()
        : position(0, 0), target(nullptr) {}
    Camera(Vector2& initial_position)
        : position(initial_position) {}
    Camera(std::shared_ptr<Object>& initial_target)
        : target(initial_target) {}

    void                     set_position(Vector2& new_position) { position = new_position; }
    Vector2                  get_position() { return position; }
    void                     set_target(std::shared_ptr<Object>& new_target) { target = new_target; }
    std::shared_ptr<Object>& get_target() { return target; }

    void update();
};
