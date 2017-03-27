//
// Created by derek on 3/24/2017.
//

#pragma once

#include "Stack.h"

class RpnStack : public Stack<float> {
public:
    void add();

    void subtract();

    void multiply();

    void divide();

    float display();

    RpnStack& operator++();
};

