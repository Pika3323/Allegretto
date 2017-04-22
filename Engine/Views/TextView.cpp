//
// Created by derek on 3/27/2017.
//

#include "TextView.h"

TextView::TextView(const Bound2D &bounds) : View(bounds) {
    font = new Font("Roboto-Regular.ttf");
}

TextView::TextView(const Vector2D& position) : View(position, 0, 0){
    font = new Font("Roboto-Regular.ttf");
}

void TextView::SetText(std::string text) {
    TextView::text = text;

    SetHeight(al_get_font_line_height(font->Get(fontSize)));
    SetWidth(al_get_text_width(font->Get(fontSize), TextView::text.c_str()));
}

std::string *const TextView::GetText() {
    return &text;
}

void TextView::Draw() {
    View::Draw();

    al_draw_text(font->Get(fontSize), textColour, GetPaddingLeft(), GetPaddingTop(), 0, text.c_str());
}

Font* const TextView::GetFont() {
    return font;
}

void TextView::SetFont(Font* font) {
    TextView::font = font;

    // Reset the layout bounds for the TextView
    SetText(text);
}

void TextView::SetTextColour(Colour colour) {
    textColour = colour;
}

int TextView::GetTextSize() {
    return fontSize;
}

void TextView::SetTextSize(int size) {
    fontSize = size;
    SetText(text);
}
