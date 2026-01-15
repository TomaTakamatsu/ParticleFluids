#pragma once
#include <cmath>

struct Vec2
{
    float x, y;

    Vec2() : x(0), y(0) {}
    Vec2(float x, float y) : x(x), y(y) {}

    Vec2 operator+(const Vec2& other) const { return Vec2(x + other.x, y + other.y); }
    Vec2 operator-(const Vec2& other) const { return Vec2(x - other.x, y - other.y); }
    Vec2 operator*(float scalar) const      { return Vec2(x * scalar, y * scalar); }
    Vec2 operator/(float scalar) const      { return Vec2(x / scalar, y / scalar); }

    void operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
    }

    void operator-=(const Vec2& other) {
        x -= other.x;
        y -= other.y;
    }

    void operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
    }

    float Length() const {
        return std::sqrt(x * x + y * y);
    }

    float Distance(const Vec2& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    Vec2 Normalized() const {
        float len = Length();
        if (len == 0) return Vec2(0, 0);
        return Vec2(x / len, y / len);
    }

};

inline Vec2 operator*(float scalar, const Vec2& v) {
    return Vec2(v.x * scalar, v.y * scalar);
}