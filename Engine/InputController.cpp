//
// Created by Derek on 2/9/2017.
//

#include "InputController.h"

void InputController::HandleInput(ALLEGRO_EVENT *event) {
    if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
        InputDelegate* delegate = inputs[event->keyboard.keycode];
        if (delegate && delegate->object) {
            (delegate->object->*delegate->func)();
        }
    }
}

void InputController::RegisterKeyboardInput(int key, GameObject* object, void (GameObject::*ptr)()) {
    inputs.insert(std::pair<int, InputDelegate*>(key, new InputDelegate(key, object, ptr)));
}
