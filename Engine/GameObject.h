//
// Created by Derek on 2/9/2017.
//

#pragma once


#include "InputController.h"

/**
 * A general GameObject class for any object used in a game.
 * This class acts as a base for all objects so that casting certain properties between them is easier.
 */
class GameObject {
public:
    /**
     * Called when the object is initialized
     * @param inputController A reference to the game's input controller to set up input with the object
     */
    virtual void Init(class InputController* inputController) = 0;

    /**
     * Called every frame
     * @param delta The time elapsed between frames
     */
    virtual void Tick(float delta) = 0;

    /**
     * Called when the object is destroyed
     */
    virtual void Destroy() = 0;
};
