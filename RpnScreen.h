//
// Created by derek on 3/24/2017.
//

#pragma once


#include "Engine/Engine.h"
#include "RpnStack.h"

class RpnScreen : public Screen {
    RpnStack stack;

    static const int ADD_BUTTON = 15;
    static const int SUBTRACT_BUTTON = 16;
    static const int MULTIPLY_BUTTON = 17;
    static const int DIVIDE_BUTTON = 18;
    static const int ENTER_BUTTON = 19;

    /**
     * The number that is currently being inputted into the stack
     */
    float currentInput;

public:
    ///
    /// \param screenWidth
    /// \param screenHeight
    RpnScreen(int screenWidth, int screenHeight) : Screen(screenWidth, screenHeight) {}

    void Init(InputController *input) override;

    void Tick(float delta) override {

    }

    void Destroy() override {

    }

    void Draw() override;

    void Resize(int newX, int newY) override {
        Screen::Resize(newX, newY);
    }

    void PressKey(class View *view);

    void switchScreens();
};

