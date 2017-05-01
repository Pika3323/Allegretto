//
// Created by derek on 4/24/2017.
//

#pragma once

#include <vector>

/**
 * A ring that goes on the peg
 */
class PegRing {
    int number;

public:
    PegRing(int number);

    int GetNumber() const;
};


/**
 * The pegs that the rings go on
 */
class Peg {
    std::vector<PegRing*> rings;

public:

};


