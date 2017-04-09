//
// Created by derek on 3/29/2017.
//

#include "Font.h"

Font::Font(std::string font) : fontFile(font) {}

ALLEGRO_FONT* Font::Get(int size) {
    if (fonts.find(size) == fonts.end()) {
        fonts.insert(std::make_pair(size, al_load_font(fontFile.c_str(), size, 0)));
    }

    return fonts[size];
}

Font::~Font() {
    std::map<int, ALLEGRO_FONT*>::iterator it;

    for (it = fonts.begin(); it != fonts.end(); it++) {
        al_destroy_font(it->second);
    }
}

void Font::Remove(int size) {
    al_destroy_font(fonts[size]);
    fonts.erase(size);
}
