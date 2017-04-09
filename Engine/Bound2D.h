//
// Created by Derek on 2/21/2017.
//

#pragma once

#include "Vector2D.h"

struct Bound2D {
    /**
     * The upper corner of the bound. Can be visualized as being the "top-left" corner of the box that represents
     * this bound.
     */
    Vector2D upper;

    /**
     * The lower corner of the bound. Can be visualized as being the "bottom-right" corner of the box that represents
     * this bound.
     */
    Vector2D lower;

    Bound2D(Vector2D pointOne, Vector2D pointTwo) {
        if (pointOne < pointTwo) {
            upper = pointOne;
            lower = pointTwo;
        } else {
            upper = pointTwo;
            lower = pointOne;
        }
    }

    /**
     * Comparison operator between two bounds
     * @param bound The bound to be compared
     * @return Whether the two bounds are equal
     */
    bool operator==(const Bound2D &bound) {
        return upper == bound.upper && lower == bound.lower;
    }

    /**
     * Checks if this bound contains the specified coordinate
     * @param V The coordinate to check
     * @return Whether the coordinate exists in these bounds
     */
    bool Contains(const Vector2D V) {
        return V.x > upper.x && V.x < lower.x && V.y > upper.y && V.y < lower.y;
    }

    /**
     * Checks if this bound contains the specified coordinate
     * @param x The x coordinate to check
     * @param y The y coordinate to check
     * @return Whether the coordinate exists in these bounds
     */
    bool Contains(float x, float y) {
        return Contains(Vector2D(x, y));
    }

    /**
     * Checks if this bound overlaps another bound
     * @param bound The bound to check with the current one
     * @return Whether the two bounds overlap
     */
    bool Overlaps(const Bound2D bound) {
        return (lower.x > bound.upper.x && lower.x < bound.lower.x &&
                                                    lower.y > bound.upper.y && lower.y < bound.lower.y)
                || (bound.upper.x < lower.x && bound.upper.x > upper.x &&
                                                        bound.upper.y < lower.y && bound.upper.y > upper.y);
    }

    /**
     * Calculates the width of this bound based on the positions of the upper and lower bound coordinates
     * @return The width of the bound
     */
    float GetWidth() {
        return lower.x - upper.x;
    }

    /**
     * Calculates the height of this bound based on the positions of the upper and lower bound coordinates
     * @return The height of the bound
     */
    float GetHeight() {
        return lower.y - upper.y;
    }
};


