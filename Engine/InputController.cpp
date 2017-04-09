//
// Created by Derek on 2/9/2017.
//

#include "InputController.h"

void InputController::HandleInput(ALLEGRO_EVENT *event) {
    if (event->type == ALLEGRO_EVENT_KEY_DOWN) {
        // Gets all delegates for this key code
        auto range = keyInputs.equal_range(event->keyboard.keycode);

        for (auto it = range.first; it != range.second; ++it) {
            // Calls the associated bound functions
            it->second->Call();
        }

    } else if (event->type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || event->type == ALLEGRO_EVENT_MOUSE_BUTTON_UP ||
            event->type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY || event->type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY ||
            event->type == ALLEGRO_EVENT_MOUSE_AXES) {
        // Iterates through the multimap of mouse inputs to find all the ones with the specified mouse event type
        auto range = mouseInputs.equal_range(EMouseEvent(event->type));
        for (auto it = range.first; it != range.second; ++it) {
            if (dynamic_cast<MouseInputDelegate*>(it->second)) {
                MouseInputDelegate *mouseInputDelegate = it->second;

                // Checks if this mouse event is bound to a specific screen region or not
                if (!mouseInputDelegate->IsBound()) {
                    mouseInputDelegate->Call(EMouseButton(event->mouse.button), event->mouse.x, event->mouse.y);
                } else {
                    // Screen region bound event Call
                    if (mouseInputDelegate->GetBounds().Contains(Vector2D(event->mouse.x, event->mouse.y))) {
                        mouseInputDelegate->Call(EMouseButton(event->mouse.button), event->mouse.x, event->mouse.y);
                    }
                }
            }
        }

        for (auto it = mouseInputs.begin(); it != mouseInputs.end(); it++) {
            if ((it->first == EMouseEvent::Hover || it->first == EMouseEvent::Enter || it->first == EMouseEvent::Exit)) {
                OtherMouseInputDelegate* delegate = (OtherMouseInputDelegate *) it->second;
                if (it->first == EMouseEvent::Hover && delegate->GetArea().Contains(event->mouse.x, event->mouse.y)) {
                    delegate->Call(EMouseEvent::Hover, event->mouse.x - event->mouse.dx, event->mouse.y - event->mouse.dy);
                }

                if (it->first == EMouseEvent::Enter && !delegate->GetArea().Contains(
                        event->mouse.x - event->mouse.dx, event->mouse.y - event->mouse.dy)
                    && delegate->GetArea().Contains(event->mouse.x, event->mouse.y)) {
                    delegate->Call(EMouseEvent::Enter, event->mouse.x - event->mouse.dx, event->mouse.y - event->mouse.dy);
                }

                if (it->first == EMouseEvent::Exit && delegate->GetArea().Contains(
                        event->mouse.x - event->mouse.dx, event->mouse.y - event->mouse.dy)
                        && !delegate->GetArea().Contains(event->mouse.x, event->mouse.y)) {
                    delegate->Call(EMouseEvent::Exit, event->mouse.x - event->mouse.dx, event->mouse.y - event->mouse.dy);
                }
            }
        }
    }
}