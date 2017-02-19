//
// Created by Derek on 2/15/2017.
//

#include "Colour.h"

const Colour Colour::BLACK(0, 0, 0);
const Colour Colour::WHITE(255, 255, 255);
const Colour Colour::RED(255, 0, 0);
const Colour Colour::GREEN(0, 255, 0);
const Colour Colour::BLUE(0, 0, 255);
const Colour Colour::YELLOW(255, 255, 0);
const Colour Colour::CYAN(0, 255, 255);
const Colour Colour::MAGENTA(255, 0, 255);
const Colour Colour::TRANSPARENT(0, 0, 0, 0);

ALLEGRO_COLOR Colour::ToAllegroColor() {
    return al_map_rgba(red, green, blue, alpha);
}

void Colour::SetAlpha(uint8_t a) {
    alpha = a;
}
