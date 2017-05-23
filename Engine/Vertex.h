//
// Created by derek on 5/1/2017.
//

#pragma once

#include "Core.h"
#include "Vector3D.h"
#include "Colour.h"

class Vertex {
    /**
     * The 3D position of the vertex
     */
    Vector3D position;

    /**
     * The vertex's colour
     */
    Colour colour;

    /**
     * Texture coordinates for the vertex
     */
    float u, v;

public:

    Vertex(const Vector3D &position, const Colour &colour, float u, float v);

    Vertex();

    const Vector3D& getPosition() const;

    void setPosition(const Vector3D& position);

    const Colour& getColour() const;

    void setColour(const Colour& colour);

    float getU() const;

    void setU(float u);

    float getV() const;

    void setV(float v);

    operator ALLEGRO_VERTEX();
};

