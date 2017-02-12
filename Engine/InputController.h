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
    int key;
    GameObject* object;
    void(GameObject::*func)();

    InputDelegate(int k, GameObject *o, void(GameObject::*p)()) : key(k), object(o), func(p) {}
};

class InputController {
    std::map<int, InputDelegate*> inputs;

public:
    void RegisterKeyboardInput(int key, GameObject* object, void (GameObject::*ptr)());

    void HandleInput(ALLEGRO_EVENT* event);
};
