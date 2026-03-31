#pragma once
#include <math.h>

struct Vector2D
{
    float x;
    float y;

    Vector2D() : x(0), y(0) {}
    Vector2D(float x, float y) : x(x), y(y) {}

    Vector2D operator+(const Vector2D& other) const { return Vector2D(x + other.x, y + other.y); }
    Vector2D operator-(const Vector2D& other) const { return Vector2D(x - other.x, y - other.y); }
    Vector2D operator*(const Vector2D& other) const { return Vector2D(x * other.x, y * other.y); }
    Vector2D operator/(const Vector2D& other) const { return Vector2D(x / other.x, y / other.y); }
    Vector2D operator*(float multiplier)      const { return Vector2D(x * multiplier, y * multiplier); }

    Vector2D& operator+=(const Vector2D& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    float Length() const                          
    {
        return sqrt(x * x + y * y);
    }

    Vector2D Normalize() const                    
    {
        float len = Length();
        if(len == 0) return Vector2D(0, 0); 
        return Vector2D(x / len, y / len);
    }

    
    static Vector2D Direction(const Vector2D& from, const Vector2D& to)
    {
        return to - from;                         
    }

    static float Distance(const Vector2D& from, const Vector2D& to)
    {
        float dx = from.x - to.x;
        float dy = from.y - to.y;
        return sqrt(dx * dx + dy * dy);
    }

    static float DotProduct(const Vector2D& a, const Vector2D& b)
    {
        return a.x * b.x + a.y * b.y;
    }
};