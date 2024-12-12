#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "math/vector2.hpp"

class Object {
public:
    Vector2 position;

    Object(Vector2 _position): position(_position) {};
    Object(float x, float y): position(Vector2(x, y)) {};
    Object(): position(Vector2::ZERO) {};
    ~Object() = default;

    void draw() {}
    void update() {}
};

#endif
