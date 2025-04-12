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
    Vector2 operator/(float scalar) const { return Vector2(x/scalar, y/scalar); }
    Vector2 operator-() const { return Vector2(-x, -y); }
    Vector2& operator+=(const Vector2& other) { x += other.x; y += other.y; return *this; }
    Vector2& operator-=(const Vector2& other) { x -= other.x; y -= other.y; return *this; }
    Vector2& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
    Vector2& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }
    bool operator==(const Vector2& other) const { return (x == other.x && y == other.y); }
    bool operator!=(const Vector2& other) const { return !(*this == other); }
    float length() const {
        return std::sqrt(x*x+y*y);
    }

    operator float*() { return &x; }
    
    static const Vector2 ZERO;
    static const Vector2 UP;
    static const Vector2 RIGHT;
};

#endif
