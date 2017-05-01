//
// Created by derek on 4/20/2017.
//

#pragma once

#include "Engine/Engine.h"
#include "Engine/Screen.h"
#include "Peg.h"

class HanoiScreen : public Screen{
    Peg* pegs[3];

public:
    HanoiScreen(int screenWidth, int screenHeight);

    void Init(InputController *input) override;

    void Tick(float delta) override;

    void Destroy() override;

protected:
    void Draw() override;
};


