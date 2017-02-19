//
// Created by Derek on 2/9/2017.
//

#pragma once

#include <vector>
#include <map>
#include <allegro5/events.h>
#include "GameObject.h"

// Forward declaration of GameObject class
class GameObject;

/**
 * An enum representing the buttons of the mouse
 */
enum class EMouseButton {
    Left,
    Right,
    Middle
};

/**
 * An object that encapsulates the data required for binding a function to an keyboard input method
 */
struct KeyboardInputDelegate {
    /**
     * The keycode corresponding to this delegate
     */
    int key;

    /**
     * The object in which the function will be called on keypress
     */
    GameObject* object;

    /**
     * Pointer to the function to be called on the keypress
     */
    void (GameObject::*func)();

    /**
     * Constructor
     * @param key The keycode
     * @param object Object whose function will be called
     * @param ptr Pointer to the function
     */
    KeyboardInputDelegate(int key, GameObject *object, void(GameObject::*ptr)()) : key(key), object(object), func(ptr) {}
};

struct MouseInputDelegate {
    GameObject* object;

    void (GameObject::*delegate)(EMouseButton, int ,int);

    /*MouseInputDelegate(GameObject *object, void (GameObject::*delegate)(EMouseButton, int, int) const) : object(object),
                                                                                             delegate(delegate) {}*/
};

class InputController {
    //Multimap of all the input delegates and their corresponding key(s)
    std::multimap<int, KeyboardInputDelegate*> keyInputs;

    std::multimap<int, MouseInputDelegate*> mouseInputs;

public:
    //Registers an object's function to be called on a certain keyboard key press
    void RegisterKeyboardInput(int key, GameObject* object, void (GameObject::*ptr)());

    void RegisterMouseInput(GameObject* object, void (GameObject::*ptr)(EMouseButton, int, int));

    //Handle different types of inputs and fire off their delegates
    void HandleInput(ALLEGRO_EVENT* event);
};
