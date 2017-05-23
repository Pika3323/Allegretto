//
// Created by derek on 5/1/2017.
//

#include "Vertex.h"

Vertex::operator ALLEGRO_VERTEX() {
    return { position.x, position.y, position.z, u, v, colour };
}

Vertex::Vertex() : colour(Colour::BLACK) {}

Vertex::Vertex(const Vector3D &position, const Colour &colour, float u, float v) : position(position), colour(colour),
                                                                                   u(u), v(v) {}

const Vector3D& Vertex::getPosition() const {
    return position;
}

void Vertex::setPosition(const Vector3D& position) {
    Vertex::position = position;
}

const Colour& Vertex::getColour() const {
    return colour;
}

void Vertex::setColour(const Colour& colour) {
    Vertex::colour = colour;
}

float Vertex::getU() const {
    return u;
}

void Vertex::setU(float u) {
    Vertex::u = u;
}

float Vertex::getV() const {
    return v;
}

void Vertex::setV(float v) {
    Vertex::v = v;
}

