//
// Created by Derek on 2/9/2017.
//

#pragma once

#include "Engine/Engine.h"
#include <APMATRIX.H>

class LifeScreen : public Screen{
    const char ALIVE = 'x';
    const char DEAD = '.';

public:
    LifeScreen();

    virtual void Init(InputController* input) override;

    virtual void Tick(float delta) override;

    virtual void Draw() override;

    virtual void Destroy() override;

    void exit();

    void nextGeneration();

private:

    float posX = 0, posY = 0;

    ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);

    apmatrix<char> lifeMatrix = apmatrix<char>(20, 50);
};


