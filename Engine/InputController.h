//
// Created by Derek on 2/9/2017.
//

#pragma once

#include <vector>
#include <map>
#include <allegro5/events.h>
#include "GameObject.h"

class GameObject;

typedef void (GameObject::*InDelegate)();

struct InputDelegate {
    //The key code corresponding to this input method
    int key;

    //The object in which the input function will be called
    GameObject* object;

    //Pointer to the function to be called on the keypress
    void(GameObject::*func)();

    InputDelegate(int key, GameObject *object, void(GameObject::*ptr)()) : key(key), object(object), func(ptr) {}
};

class InputController {
    //Multimap of all the input delegates and their corresponding key(s)
    std::multimap<int, InputDelegate*> inputs;

public:
    //Registers an object's function to be called on a certain keyboard key press
    void RegisterKeyboardInput(int key, GameObject* object, void (GameObject::*ptr)());

    //Handle different types of inputs and fire off their delegates
    void HandleInput(ALLEGRO_EVENT* event);
};
