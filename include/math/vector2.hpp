#ifndef VECTOR2_HPP
#define VECTOR2_HPP

#include <cmath>

struct Vector2 {
    float x;
    float y;

    Vector2(float x=0.0f, float y=0.0f): x(x), y(y) {}

    Vector2 operator+(const Vector2& other) const { return Vector2(x+other.x, y+other.y); }
    Vector2 operator-(const Vector2& other) const { return Vector2(x-other.x, y-other.y); }
    Vector2 operator*(float scalar) const { return Vector2(x*scalar, y*scalar); }
    float length() const {
        return std::sqrt(x*x+y*y);
    }
    
    static const Vector2 ZERO;
    static const Vector2 UP;
    static const Vector2 RIGHT;
};

const Vector2 Vector2::ZERO(0.0f, 0.0f);
const Vector2 Vector2::UP(0.0f, 1.0f);
const Vector2 Vector2::RIGHT(1.0f, 0.0f);

#endif
