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

    //static const Vector2D zero = {0.f, 0.f};

    Vector2D operator+(const Vector2D &V) const {
        return Vector2D(x + V.x, y + V.y);
    }

    //Subtracts two vectors
    Vector2D operator-(const Vector2D &V) const {
        return Vector2D(x - V.x, y - V.y);
    }

    //Multiplies a vector by a scalar value
    Vector2D operator*(float scale) const {
        return Vector2D(x * scale, y * scale);
    }

    //Divides a vector by a scalar value
    Vector2D operator/(float scale) const {
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
    float Magnitude() {
        return sqrtf(x * x + y * y);
    }

    /**
     * Calculates the distance between the current vector and a given vector
     * @param V The vector to find the distance to
     * @return The distance between the vector coordinates
     */
    float DistanceTo(const Vector2D& V) {
        return Vector2D(*this - V).Magnitude();
    }

    /**
     * Calculates the distance between two vector coordinates
     * @param A The first vector
     * @param B The second vector
     * @return The distance between the two vector coordinates
     */
    static float DistanceBetween(const Vector2D& A, const Vector2D& B) {
        return Vector2D(A - B).Magnitude();
    }
};

