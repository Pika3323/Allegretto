//
// Created by Derek on 2/12/2017.
//

#pragma once

#include "Core.h"
#include "Colour.h"

struct DebugOutput{
    /**
     * The message to be displayed on screen
     */
    std::string text;

    /**
     * The colour in which to display the message
     */
    Colour color;

    /**
     * The amount of time to display the message on screen
     */
    float duration;

    /**
     * The amount of time the message has already been disabled
     */
    float elapsedTime = 0.f;

    /**
     * Constructs a message structure
     * @param text The message
     * @param colour The colour
     * @param duration The duration
     */
    explicit DebugOutput(const std::string &text, const Colour &colour = Colour::GREEN, float duration = 5.f) : text(text), color(colour),
                                                                                                                duration(duration) {}
};