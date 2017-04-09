//
// Created by Derek on 2/15/2017.
//

#pragma once

#include <cstdint>
#include "Core.h"
/**
 * A custom Colour structure that will allow for more custom colour functionalities
 * Includes automatic casting to ALLEGRO_COLOR.
 * @see ALLEGRO_COLOR
 */
struct Colour {
    /**
     * The red component of the colour
     */
    uint8_t red;

    /**
     * The green component of the colour
     */
    uint8_t green;

    /**
     * The blue component of the colour
     */
    uint8_t blue;

    /**
     * The alpha component of the colour
     * (Opacity)
     */
    uint8_t alpha;

    /**
     * Constructs a fully opaque colour. Alpha is set to 0xFF by default.
     * @param r The red component of the colour
     * @param g The green component of the colour
     * @param b The blue component of the colour
     */
    Colour(uint8_t r, uint8_t g, uint8_t b) : red(r), green(g), blue(b), alpha(0xFF) {}

    /**
     * Constructs a colour with a custom alpha component.
     * @param r The red component of the colour
     * @param g The green component of the colour
     * @param b The blue component of the colour
     * @param a The alpha (opacity) component of the colour
     */
    Colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : red(r), green(g), blue(b), alpha(a) {}

    Colour(uint32_t c) : red((uint8_t) ((c >> 8) & 0xFF)), green((uint8_t) ((c >> 4) & 0xFF)), blue(
            (uint8_t) ((c >> 2) & 0xFF)), alpha(0xFF) {}

    /**
     * Automatically casts the colour to an ALLEGRO_COLOR
     * @return The colour in ALLEGRO_COLOR format
     */
    operator ALLEGRO_COLOR() const;

    /**
     * A default black colour
     */
    static const Colour BLACK;

    /**
     * A default white colour
     */
    static const Colour WHITE;

    /**
     * A default red colour
     */
    static const Colour RED;

    /**
     * A default green colour
     */
    static const Colour GREEN;

    /**
     * A default blue colour
     */
    static const Colour BLUE;

    /**
     * A default yellow colour
     */
    static const Colour YELLOW;

    /**
     * A default cyan colour
     */
    static const Colour CYAN;

    /**
     * A default magenta colour
     */
    static const Colour MAGENTA;

    /**
     * A default transparent colour
     */
    static const Colour TRANSPARENT;
};




