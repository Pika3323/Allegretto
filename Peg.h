//
// Created by derek on 4/24/2017.
//

#pragma once

#include "Stack.h"

/**
 * A ring that goes on the peg
 */
class PegRing {
    int number;

public:
    explicit PegRing(int number);

    int GetNumber() const;

};


/**
 * The pegs that the rings go on
 */
class Peg {
    Stack<PegRing*> rings;

protected:
    void AddRing(PegRing* ring);

public:

    explicit Peg (int ringCount);

    void MoveTopTo(Peg* destination);
};


