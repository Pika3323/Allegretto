//
// Created by derek on 3/24/2017.
//

#pragma once


#include "Engine/Engine.h"

class RpnScreen : public Screen {
public:
    RpnScreen(int screenWidth, int screenHeight) : Screen(screenWidth, screenHeight) {}

    void Init(InputController *input) override;

    void Tick(float delta) override {

    }

    void Destroy() override {

    }

    void Draw() override {

    }

    void Resize(int newX, int newY) override {
        Screen::Resize(newX, newY);
    }

    void switchScreens();
};

