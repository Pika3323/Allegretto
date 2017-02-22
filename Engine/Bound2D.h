//
// Created by Derek on 2/21/2017.
//

#pragma once

#include "Vector2D.h"

struct Bound2D {
    Vector2D upperBound;

    Vector2D lowerBound;

    Bound2D(Vector2D pointOne, Vector2D pointTwo) {
        if (pointOne < pointTwo) {
            upperBound = pointOne;
            lowerBound = pointTwo;
        } else {
            upperBound = pointTwo;
            lowerBound = pointOne;
        }
    }

    bool operator==(const Bound2D &bound) {
        return upperBound == bound.upperBound && lowerBound == bound.lowerBound;
    }

    /**
     * Checks if this bound contains the specified coordinate
     * @param V The coordinate to check
     * @return Whether the coordinate exists in these bounds
     */
    bool contains(const Vector2D V) {
        return V.x > upperBound.x && V.x < lowerBound.x && V.y > upperBound.y && V.y < lowerBound.y;
    }

    /**
     * Checks if this bound overlaps another bound
     * @param bound The bound to check with the current one
     * @return Whether the two bounds overlap
     */
    bool overlaps(const Bound2D bound) {
        return (lowerBound.x > bound.upperBound.x && lowerBound.x < bound.lowerBound.x &&
                                                    lowerBound.y > bound.upperBound.y && lowerBound.y < bound.lowerBound.y)
                || (bound.upperBound.x < lowerBound.x && bound.upperBound.x > upperBound.x &&
                                                        bound.upperBound.y < lowerBound.y && bound.upperBound.y > upperBound.y);
    }
};


