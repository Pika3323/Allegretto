//
// Created by Derek on 2/12/2017.
//

#pragma once

#include <allegro5/color.h>
#include <string>
#include "Colour.h"

struct DebugOutput{
    //String to output
    std::string text;

    //Color of the output
    Colour color;

    //Maximum duration of the output
    float duration;

    //Time that the output has been on the screen
    float elapsedTime;

    DebugOutput(const std::string &text, const Colour &color, float duration) : text(text), color(color),
                                                                                       duration(duration) {}
};