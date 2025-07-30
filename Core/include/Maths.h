#pragma once
#include "cmath"

struct Vec2 {
    float x = 0.0f, y = 0.0f;

    Vec2() = default;
    Vec2(float x, float y) : x(x), y(y) {}

    Vec2 operator+(const Vec2& v) const { return {x + v.x, y + v.y}; }
    Vec2 operator-(const Vec2& v) const { return {x - v.x, y - v.y}; }
    Vec2 operator*(float s) const { return {x * s, y * s}; }
    Vec2 operator/(float s) const { return {x / s, y / s}; }
    Vec2& operator+=(const Vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    float dot(const Vec2& v) const { return x * v.x + y * v.y; }
    float length() const { return std::sqrt(x*x + y*y); }
    Vec2 normalize() const {
        float len = length();
        return len == 0 ? Vec2(0,0) : Vec2(x / len, y / len);
    }

    static float distance(const Vec2& a, const Vec2& b) {
        return (a - b).length();
    }

    static Vec2 mix(const Vec2& a, const Vec2& b, float t) {
        return a * (1.0f - t) + b * t;
    }
};

struct Vec3 {
    float x = 0.0f, y = 0.0f, z = 0.0f;

    Vec3() = default;
    Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3& v) const { return {x + v.x, y + v.y, z + v.z}; }
    Vec3 operator-(const Vec3& v) const { return {x - v.x, y - v.y, z - v.z}; }
    Vec3 operator*(float s) const { return {x * s, y * s, z * s}; }

    float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }
    Vec3 cross(const Vec3& v) const {
        return {
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        };
    }

    float length() const { return std::sqrt(x*x + y*y + z*z); }
    Vec3 normalize() const {
        float len = length();
        return len == 0 ? Vec3(0,0,0) : Vec3(x / len, y / len, z / len);
    }
};

struct Mat4 {
    float m[16] = {0};

    static Mat4 identity() {
        Mat4 result;
        result.m[0] = result.m[5] = result.m[10] = result.m[15] = 1.0f;
        return result;
    }

    static Mat4 ortho(float l, float r, float b, float t, float n, float f) {
        Mat4 result = identity();
        result.m[0] = 2 / (r - l);
        result.m[5] = 2 / (t - b);
        result.m[10] = -2 / (f - n);
        result.m[12] = -(r + l) / (r - l);
        result.m[13] = -(t + b) / (t - b);
        result.m[14] = -(f + n) / (f - n);
        return result;
    }

    static Mat4 translate(const Vec2& v) {
        Mat4 result = identity();
        result.m[12] = v.x;
        result.m[13] = v.y;
        return result;
    }

    float* value_ptr() { return m; }

    static Mat4 rotate(float radians) {
        Mat4 result = identity();
        float c = std::cos(radians);
        float s = std::sin(radians);
        result.m[0] = c; result.m[4] = -s;
        result.m[1] = s; result.m[5] =  c;
        return result;
    }

    static Mat4 scale(const Vec2& v) {
        Mat4 result = identity();
        result.m[0] = v.x;
        result.m[5] = v.y;
        return result;
    }
    

 Mat4 operator*(const Mat4& o) const {
    Mat4 result;
    for (int col = 0; col < 4; ++col) {
        for (int row = 0; row < 4; ++row) {
            result.m[col * 4 + row] =
                m[0 * 4 + row] * o.m[col * 4 + 0] +
                m[1 * 4 + row] * o.m[col * 4 + 1] +
                m[2 * 4 + row] * o.m[col * 4 + 2] +
                m[3 * 4 + row] * o.m[col * 4 + 3];
        }
    }
    return result;
}

};
