//
// Created by Derek on 2/21/2017.
//

#pragma once
#include <cmath>

/**
 * A Two-Dimensional vector structure
 */
struct Vector2D{
    /**
     * X component of the vector
     */
    float x;

    /**
     * Y component of the vector
     */
    float y;

    Vector2D() {}
    Vector2D(float x, float y) : x(x), y(y){}
    Vector2D(const Vector2D &V) {
        x = V.x;
        y = V.y;
    }

    Vector2D operator+(const Vector2D &V) {
        return Vector2D(x + V.x, y + V.y);
    }

    //Subtracts two vectors
    Vector2D operator-(const Vector2D &V) {
        return Vector2D(x - V.x, y - V.y);
    }

    //Multiplies a vector by a scalar value
    Vector2D operator*(float scale) {
        return Vector2D(x * scale, y * scale);
    }

    //Divides a vector by a scalar value
    Vector2D operator/(float scale) {
        return Vector2D(x / scale, y / scale);
    }

    Vector2D operator+=(const Vector2D &V) {
        x += V.x;
        y += V.y;
        return *this;
    }

    Vector2D operator-=(const Vector2D &V) {
        x -= V.x;
        y -= V.y;
        return *this;
    }

    Vector2D operator*=(float scale) {
        x *= scale;
        y *= scale;
        return *this;
    }

    Vector2D operator/=(float scale) {
        x /= scale;
        y /= scale;
        return *this;
    }

    bool operator>(const Vector2D &V) {
        return x > V.x && y > V.y;
    }

    bool operator<(const Vector2D &V) {
        return x < V.x && y < V.y;
    }

    bool operator>=(const Vector2D &V) {
        return (x >= V.x && y >= V.y);
    }

    bool operator<=(const Vector2D &V) {
        return (x <= V.x && y <= V.y);
    }

    bool operator==(const Vector2D &V) {
        return x == V.x && y == V.y;
    }

    bool operator!=(const Vector2D &V) {
        return x != V.x || y != V.y;
    }

    /**
     * Dot product
     */
    float operator|(const Vector2D &V) {
        return x * V.x + y * V.y;
    }

    /**
     * Cross product
     */
    float operator^(const Vector2D &V) {
        return x * V.y - y * V.x;
    }

    /**
     * Calculates the magnitude of the vector
     * @return Magnitude of the vector
     */
    float magnitude() {
        return sqrtf(x * x + y * y);
    }
};


