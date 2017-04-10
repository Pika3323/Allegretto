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

Colour::operator ALLEGRO_COLOR() const {
    return al_map_rgba(red, green, blue, alpha);
}

Colour Colour::Grayscale() {
    uint8_t gray = (uint8_t) ((0.3 * red) + (0.59 * green) + (0.11 * blue));
    return Colour(gray, gray, gray, alpha);
}

double Colour::Luminance() {
    return 0.2126 * red + 0.7152 * green + 0.0722 * blue;
}
