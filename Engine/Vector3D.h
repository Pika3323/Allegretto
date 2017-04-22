//
// Created by derek on 4/11/2017.
//

#pragma once

#include <cmath>

struct Vector3D {
    /**
     * The X component of the vector
     */
    float x;

    /**
     * The Y component of the vector
     */
    float y;

    /**
     * The Z component of the vector
     */
    float z;

    /**
     * Empty default constructor
     */
    Vector3D() {}

    /**
     * Constructs a vector from three components
     * @param x The X component
     * @param y The Y component
     * @param z The Z component
     */
    Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}

    /**
     * Copy constructor
     * @param V Vector to copy
     */
    Vector3D(const Vector3D &V) : x(V.x), y(V.y), z(V.z) {}

    /**
     * Addition operator
     * Add two vectors together
     * @param V Vector to add on to the current vector
     * @return The sum of the two vectors
     */
    Vector3D operator+(const Vector3D &V) const {
        return Vector3D(x + V.x, y + V.y, z + V.z);
    }

    /**
     * Subtraction operator
     * Subtract two vectors
     * @param V
     * @return
     */
    Vector3D operator-(const Vector3D &V) const {
        return Vector3D(x - V.x, y - V.y, z - V.z);
    }

    /**
     * Multiplication operator
     * Multiply a vector by a scalar value
     * @param scale The scale to multiply the vector by
     * @return The scaled vector
     */
    Vector3D operator*(float scale) const {
        return Vector3D(x * scale, y * scale, z * scale);
    }

    /**
     * Division operator
     * Divide a vector by a scalar value
     * @param scale The scale to divide the vector by
     * @return The scaled vector
     */
    Vector3D operator/(float scale) const {
        return Vector3D(x / scale, y / scale, z / scale);
    }

    /**
     * Dot product operator
     * No, dots can't be overloaded in C++
     * @param V Vector to dot product with
     * @return The dot product of the two vectors
     */
    float operator|(const Vector3D &V) const {
        return x * V.x + y * V.y + z * V.z;
    }

    /**
     * Cross product
     * TODO: Check implementation
     * @param V Vector to cross product with
     * @return The cross product of the two vectors
     */
    Vector3D operator^(const Vector3D &V) const {
        return Vector3D(y * V.z - z * V.y, z * V.x - x * V.z, x * V.y - y * V.x);
    }

    /**
     * Calculates the magnitude of the current vector
     * @return Magnitude of the vector
     */
    float Magnitude() {
        return sqrtf(x * x + y * y + z * z);
    }

    /**
     * Calculates the distance between this vector, and another vector
     * @param V The other vector
     * @return The distance between the two vectors
     */
    float DistanceTo(const Vector3D& V) {
        return Vector3D(*this - V).Magnitude();
    }

    /**
     * Calculates the distance between two vector coordinates
     * @param A The first vector
     * @param B The second vector
     * @return The distance between the two vector coordinates
     */
    static float DistanceBetween(const Vector3D &A, const Vector3D &B) {
        return Vector3D(A - B).Magnitude();
    }
};
