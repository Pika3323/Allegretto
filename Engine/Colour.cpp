//
// Created by Derek on 2/15/2017.
//

#include "Colour.h"

const Colour Colour::BLACK = Colour(0, 0, 0);
const Colour Colour::WHITE = Colour(255, 255, 255);
const Colour Colour::RED = Colour(255, 0, 0);
const Colour Colour::GREEN = Colour(0, 255, 0);
const Colour Colour::BLUE = Colour(0, 0, 255);
const Colour Colour::YELLOW = Colour(255, 255, 0);
const Colour Colour::CYAN = Colour(0, 255, 255);
const Colour Colour::MAGENTA = Colour(255, 0, 255);

ALLEGRO_COLOR Colour::ToAllegroColor() {
    return al_map_rgba(red, green, blue, alpha);
}

void Colour::SetAlpha(uint8_t a) {
    alpha = a;
}
