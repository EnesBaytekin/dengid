#pragma once

#include "math/vector2.hpp"

class Rect {
public:
    float x, y, w, h;
    Rect(float x=0.0f, float y=0.0f, float w=0.0f, float h=0.0f): x(x), y(y), w(w), h(h) {}
    Rect(const Vector2& position, const Vector2& size): x(position.x), y(position.y), w(size.x), h(size.y) {}
    Rect(const Vector2& position, float width, float height): x(position.x), y(position.y), w(width), h(height) {}
    Rect(const Vector2& position): x(position.x), y(position.y), w(0.0f), h(0.0f) {}

    bool is_colliding(const Rect& other) const {
        return (x < other.x + other.w && x + w > other.x && y < other.y + other.h && y + h > other.y);
    }
    bool is_colliding(const Vector2& point) const {
        return (point.x >= x && point.x <= x + w && point.y >= y && point.y <= y + h);
    }
    bool is_colliding(const Vector2& point, const Vector2& offset) const {
        return (point.x >= x - offset.x && point.x <= x + w + offset.x && point.y >= y - offset.y && point.y <= y + h + offset.y);
    }
};
