//
// Created by derek on 3/29/2017.
//

#pragma once

#include <map>
#include "Core.h"

enum class EFontWeight {
    REGULAR,
    THIN,
    BOLD
};

class Font {
    /**
     * Map of font references using the size as a key
     */
    std::map<int, ALLEGRO_FONT*> fonts;

    /**
     * The string of the path to the font file
     */
    std::string fontFile;

public:
    /**
     * Public constructor
     * @param font Path to the font to load
     */
    Font(std::string font);

    /**
     * Get a reference to the font of the specified size
     * @param size The font size
     * @return ALLEGRO_FONT reference
     */
    ALLEGRO_FONT* Get(int size);

    /**
     * Removes the font reference for the specified size
     * @param size The font size to remove;
     */
    void Remove(int size);

    ~Font();
};

