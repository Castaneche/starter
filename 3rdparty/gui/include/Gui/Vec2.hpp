#pragma once

#include <cmath>
#include <vector>

namespace gui {

struct Vec2 {
    Vec2() : x(0), y(0) {}
    Vec2(float x, float y) : x(x), y(y) {}
    float  operator[](std::size_t i) const { return (&x)[i]; }
    float &operator[](std::size_t i) { return (&x)[i]; }
    float  x;
    float  y;
};

//=============================================================================
// OPERATOR OVERLOADS
//=============================================================================

Vec2  operator-(const Vec2 &right);
Vec2 &operator+=(Vec2 &left, const Vec2 &right);
Vec2 &operator-=(Vec2 &left, const Vec2 &right);
Vec2  operator+(const Vec2 &left, const Vec2 &right);
Vec2  operator-(const Vec2 &left, const Vec2 &right);
Vec2  operator*(const Vec2 &left, float right);
Vec2  operator*(float left, const Vec2 &right);
Vec2 &operator*=(Vec2 &left, float right);
Vec2  operator/(const Vec2 &left, float right);
Vec2 &operator/=(Vec2 &left, float right);
bool  operator==(const Vec2 &left, const Vec2 &right);
bool  operator!=(const Vec2 &left, const Vec2 &right);

}  // namespace gui

#include <Gui/Vec2.inl>