//
// Created by derek on 3/24/2017.
//

#include "RpnStack.h"

void RpnStack::add() {
    if (!isEmpty()) {
        push(pop() + pop());
    }
}

void RpnStack::subtract() {
    if (!isEmpty()) {
        push(pop() - pop());
    }
}

void RpnStack::multiply() {
    if (!isEmpty()) {
        push(pop() * pop());
    }
}

void RpnStack::divide() {
    if (!isEmpty()){
        push(pop() / pop());
    }
}

RpnStack &RpnStack::operator++() {
    add();
    return *this;
}

float RpnStack::display() {
    return *getTop();
}
