//
// Created by derek on 5/1/2017.
//

#pragma once

#include "Core.h"
#include "Vertex.h"

class Mesh {
    std::vector<Vertex> vertices;

public:
    Mesh(int size) {
        vertices.push_back(Vertex(Vector3D(-size, -size, 0), Colour::GREEN, 0, 0));
        vertices.push_back(Vertex(Vector3D(size, -size, 0), Colour::GREEN, 0, 0));
        vertices.push_back(Vertex(Vector3D(size, size, 0), Colour::GREEN, 0, 0));
    }

    virtual void Draw() {
        al_draw_prim(&vertices, nullptr, nullptr, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_STRIP);
    }
};

