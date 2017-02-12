//
// Created by Derek on 2/9/2017.
//

#include "InputController.h"

void InputController::HandleInput(ALLEGRO_EVENT *event) {
    if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
        //Gets all delegates for this keycode
        auto range = inputs.equal_range(event->keyboard.keycode);
        for (auto it = range.first; it != range.second; ++it) {
            //Calls associated functions
            (it->second->object->*it->second->func)();
        }
    }
}

void InputController::RegisterKeyboardInput(int key, GameObject* object, void (GameObject::*ptr)()) {
    inputs.insert(std::pair<int, InputDelegate*>(key, new InputDelegate(key, object, ptr)));
}
