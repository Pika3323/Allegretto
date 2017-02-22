//
// Created by Derek on 2/9/2017.
//

#include "InputController.h"

// Assign value to static invalidBound member
const Bound2D MouseInputDelegate::invalidBound = Bound2D(Vector2D(-1, -1), Vector2D(-1, -1));

void InputController::HandleInput(ALLEGRO_EVENT *event) {
    if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
        //Gets all delegates for this key code
        auto range = keyInputs.equal_range(event->keyboard.keycode);
        for (auto it = range.first; it != range.second; ++it) {
            //Calls associated functions
            (it->second->object->*it->second->func)();
        }
    } else if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ||
            event->type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY || event->type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY ||
            event->type == ALLEGRO_EVENT_MOUSE_AXES) {
        // Iterates through the multimap of mouse inputs to find all the ones with the specified mouse event type
        auto range = mouseInputs.equal_range(EMouseEvent(event->type));
        for (auto it = range.first; it != range.second; ++it) {
            // Checks if this mouse event is bound to a specific screen region or not
            if (it->second->bounds == MouseInputDelegate::invalidBound) {
                // Non-bound mouse event call
                (it->second->object->*it->second->delegate)(EMouseButton(event->mouse.button), event->mouse.x, event->mouse.y);
            } else {
                // Screen region bound event call
                if (it->second->bounds.contains(Vector2D(event->mouse.x, event->mouse.y))) {
                    (it->second->object->*it->second->delegate)(EMouseButton(event->mouse.button), event->mouse.x, event->mouse.y);
                }
            }

        }
    }
}