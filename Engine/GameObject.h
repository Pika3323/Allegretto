//
// Created by Derek on 2/9/2017.
//

#pragma once


#include "InputController.h"

class GameObject {
public:
    virtual void Init(class InputController* inputController) = 0;

    virtual void Tick(float delta) = 0;

    virtual void Destroy() = 0;
};
