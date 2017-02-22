//
// Created by Derek on 2/9/2017.
//

#pragma once

#include <vector>
#include <map>
#include <allegro5/events.h>
#include "GameObject.h"
#include "Vector2D.h"
#include "Bound2D.h"

// Forward declaration of GameObject class
class GameObject;

/**
 * An enum representing the buttons of the mouse
 */
enum class EMouseButton {
    Left = 1,
    Right = 2,
    Middle = 3
};

/**
 * An enum representing the different type of mouse events
 */
enum class EMouseEvent {
    AxesChange = ALLEGRO_EVENT_MOUSE_AXES,
    ButtonDown = ALLEGRO_EVENT_MOUSE_BUTTON_DOWN,
    ButtonUp = ALLEGRO_EVENT_MOUSE_BUTTON_UP,
    EnterDisplay = ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY,
    LeaveDisplay = ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY
};

/**
 * An object that encapsulates the data required for binding a function to an keyboard input method
 */
struct KeyboardInputDelegate {
    /**
     * The key code corresponding to this delegate
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
     * @param key The key code
     * @param object Object whose function will be called
     * @param ptr Pointer to the function
     */
    KeyboardInputDelegate(int key, GameObject *object, void(GameObject::*ptr)()) : key(key), object(object), func(ptr) {}
};

/**
 * An object that encapsulates the data required for binding a function to mouse input
 */
struct MouseInputDelegate {
    /**
     * The object in which the bound function will be called using
     */
    GameObject* object;

    /**
     * The area one screen at which this click should be registered to
     */
    Bound2D bounds = Bound2D(Vector2D(-1, -1), Vector2D(-1, -1));

    /**
     * Pointer to the function that will be called on the key event
     */
    void (GameObject::*delegate)(EMouseButton, int, int);

    /**
     * Constructor
     * @param object The object whose function will be called
     * @param d A pointer to the function to be called
     */
    MouseInputDelegate(GameObject* object, void (GameObject::*d)(EMouseButton, int, int)) : object(object),
                                                                                             delegate(d) {}
    /**
     * Constructor with bounds
     * @param object The object whose function will be called
     * @param d Pointer to the funciton to be called
     * @param screenRegion The area in the window where this event should be called
     */
    MouseInputDelegate(GameObject* object, void (GameObject::*d)(EMouseButton, int, int), Bound2D screenRegion) :
            object(object), delegate(d), bounds(screenRegion){

    }

    /**
     * An invalid bound (one that can be ignored)
     */
    static const Bound2D invalidBound;
};

/**
 * Handles and delegates input forms to the functions that are meant to be called using that input
 */
class InputController {
    //Multimap of all the input delegates and their corresponding key(s)
    std::multimap<int, KeyboardInputDelegate*> keyInputs;

    std::multimap<EMouseEvent, MouseInputDelegate*> mouseInputs;

public:
    //Registers an object's function to be called on a certain keyboard key press
    template <class T>
    void RegisterKeyboardInput(int key, T* object, void (T::*ptr)()) {
        keyInputs.insert(std::make_pair(key, new KeyboardInputDelegate(key, (GameObject*) object, (void (GameObject::*)()) ptr)));
    }

    template <class T>
    void RegisterMouseInput(EMouseEvent event, T* object, void (T::*ptr)(EMouseButton, int, int)) {
        mouseInputs.insert(std::make_pair(event, new MouseInputDelegate((GameObject*) object, (void (GameObject::*)(EMouseButton, int, int)) ptr)));
    }

    template <class T>
    void RegisterMouseInput(EMouseEvent event, T* object, void (T::*ptr)(EMouseButton, int, int), Bound2D bounds) {
        mouseInputs.insert(std::make_pair(event, new MouseInputDelegate((GameObject*) object, (void (GameObject::*)(EMouseButton, int, int)) ptr, bounds)));
    }

    //Handle different types of inputs and fire off their delegates
    void HandleInput(ALLEGRO_EVENT* event);
};
