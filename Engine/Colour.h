//
// Created by Derek on 2/15/2017.
//

#pragma once

#include <cstdint>
#include "Core.h"

struct Colour {
    uint8_t red;

    uint8_t green;

    uint8_t blue;

    uint8_t alpha;

    Colour(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b), alpha(0xFF) {}

    Colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : red(r), green(g), blue(b), alpha(a) {}

    ALLEGRO_COLOR ToAllegroColor();

    void SetAlpha(uint8_t alpha);

    static const Colour BLACK;
    static const Colour WHITE;
    static const Colour RED;
    static const Colour GREEN;
    static const Colour BLUE;
    static const Colour YELLOW;
    static const Colour CYAN;
    static const Colour MAGENTA;
};




