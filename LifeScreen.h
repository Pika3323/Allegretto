//
// Created by Derek on 2/9/2017.
//

#pragma once

#include "Engine/Engine.h"

class LifeScreen : public Screen{
public:
    LifeScreen();

    virtual void Init(InputController* input) override;

    virtual void Tick(float delta) override;

    virtual void Draw() override;

    virtual void Destroy() override;

    void exit();

    void test1();

    void test2();

private:

    float posX = 0, posY = 0;

    ALLEGRO_COLOR blue = al_map_rgb(0, 0, 255);
};


