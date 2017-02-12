//
// Created by Derek on 2/9/2017.
//

#pragma once

#include "Engine.h"
#include "InputController.h"


class Screen : public GameObject {
    friend class Engine;

public:
    virtual void Init(InputController* input) override = 0 ;

    virtual void Tick(float delta) override = 0;

    virtual void Destroy() override = 0;

    virtual void Draw() = 0;

protected:
    ALLEGRO_BITMAP* screen_buffer;
};


