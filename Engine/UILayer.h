//
// Created by Derek on 2/15/2017.
//

#pragma once

#include "Engine.h"


class UILayer : public GameObject {
    ALLEGRO_BITMAP* buffer;

    std::vector<class UIComponent*> components;

    friend class Engine;

public:
    virtual void Init(InputController* inputController) override = 0;

    virtual void Draw() = 0;

    virtual void Tick(float delta) override = 0;

    virtual void Destroy() override = 0;
};


