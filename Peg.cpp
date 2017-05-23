//
// Created by derek on 4/24/2017.
//

#include "Peg.h"

PegRing::PegRing(int number) : number(number) {}

int PegRing::GetNumber() const {
    return number;
}

void Peg::MoveTopTo(Peg *destination) {
    if (!rings.isEmpty()) {
        destination->AddRing(rings.pop());
    }
}

void Peg::AddRing(PegRing *ring) {
    rings.push(ring);
}

Peg::Peg(int ringCount) {
    for (int i = 0; i < ringCount; ++i) {
        rings.push(new PegRing(i + 1));
    }
}
