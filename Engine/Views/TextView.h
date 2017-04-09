//
// Created by derek on 3/27/2017.
//

#pragma once

#include "../View.h"
#include "../Font.h"


class TextView : public View {
    std::string text;

    Colour textColour = Colour::BLACK;

    Font* font;

    int fontSize = 16;

public:
    /**
     * Constructor.
     *
     * Constructs the TextView using the default view constructor
     * @param bounds
     */
    TextView(const Bound2D &bounds);

    TextView(const Vector2D position);

    /**
     * Sets the text for the text view
     * @param text The new string of text
     */
    void SetText(std::string text);

    /**
     * Gets the current text being displayed in the TextView
     * @return The text
     */
    std::string* const GetText();

    /**
     * Gets a reference to the font class being used to render text
     * @return The font
     */
    Font* const GetFont();

    /**
     * Sets the font to be used by the TextView
     * @param font
     */
    void SetFont(Font* font);

    /**
     * Sets the colour of the text
     * @param colour
     */
    void SetTextColour(Colour colour);

    /**
     * Sets the size of the text
     * @param size
     */
    void SetTextSize(int size);

    /**
     * Gets the size of the text being displayed
     * @return
     */
    int GetTextSize();

    void Draw() override;
};

