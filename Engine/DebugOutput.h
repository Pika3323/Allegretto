//
// Created by Derek on 2/12/2017.
//

#pragma once

#include <allegro5/color.h>
#include <string>

struct DebugOutput{
    //String to output
    std::string text;

    //Color of the output
    ALLEGRO_COLOR color;

    //Maximum duration of the output
    float duration;

    //Time that the output has been on the screen
    float elapsedTime;

    DebugOutput(const std::string &text, const ALLEGRO_COLOR &color, float duration) : text(text), color(color),
                                                                                       duration(duration) {}
};