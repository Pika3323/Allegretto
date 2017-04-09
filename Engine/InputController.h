//
// Created by Derek on 2/9/2017.
//

#pragma once

#include "Core.h"
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
    LeaveDisplay = ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY,
    Hover,
    Enter,
    Exit
};

/**
 * An object that encapsulates the data required for binding a function to an keyboard input method
 */
class KeyboardInputDelegate : public Delegate<void (GameObject::*)()> {
    /**
     * The key code corresponding to this delegate
     */
    int key;

public:
    /**
     * Constructor
     * @param key The key code to bind the function to
     * @param object Object whose method will be called
     * @param ptr Pointer to the method function
     */
     template<typename T>
    KeyboardInputDelegate(T* object, void (T::*ptr)()) : key(key), Delegate(object, ptr) {}

    /*virtual void Call() override {
        (object->*method)();
    }*/
};

/**
 * An object that encapsulates the data required for binding a function to mouse input
 */
class MouseInputDelegate : public Delegate<void (GameObject::*)(EMouseButton, int, int)> {
    /**
     * The area one screen at which this click should be registered to
     */
    Bound2D bounds = Bound2D(Vector2D(-1, -1), Vector2D(-1, -1));

    /**
     * Whether this mouse event is bound by a region
     * @see bounds
     */
    bool isBound = false;

public:
    /**
     * Constructor
     * @param object The object whose function will be called
     * @param d A pointer to the function to be called
     */
    template<typename T>
    MouseInputDelegate(T* object, void (T::*d)(EMouseButton, int, int)) : Delegate(object, d) {}
    /**
     * Constructor with bounds
     * @param object The object whose function will be called
     * @param d Pointer to the funciton to be called
     * @param screenRegion The area in the window where this event should be called
     */
    MouseInputDelegate(GameObject* object, void (GameObject::*d)(EMouseButton, int, int), Bound2D screenRegion) :
            Delegate(object, d), bounds(screenRegion), isBound(true){}

    /**
     * Whether the event is location-bound
     * @return Whether the event is location-bound
     */
    bool IsBound() const {
        return isBound;
    }

    /**
     * Gets the bounds of the event
     * @return The bounds
     */
    Bound2D GetBounds() const {
        return bounds;
    }
};

class OtherMouseInputDelegate : public Delegate<void (GameObject::*)(EMouseEvent, int, int)> {
    /**
     * The area for this event to take place on the screen
     */
    Bound2D area;

public:
    template<typename T>
    OtherMouseInputDelegate(T* object, void (GameObject::*method)(EMouseEvent, int, int), Bound2D bounds) : Delegate(object, method), area(bounds) {}

    Bound2D GetArea() const {
        return area;
    }
};

/**
 * Handles and delegates input forms to the functions that are meant to be called using that input.
 *
 * The InputController uses multimaps as a storage mechanism because each key press or mouse event could have multiple
 * functions bound to it which will all be called
 */
class InputController {
    /**
     * Multimap containing all input events bound to keyboard input
     */
    std::multimap<int, KeyboardInputDelegate*> keyInputs;

    /**
     * Multimap containing all input events bound to mouse input events
     */
    std::multimap<EMouseEvent, MouseInputDelegate*> mouseInputs;



public:
    /**
     * Binds a class's method function to a keyboard input.
     * The method will be called every time that key is pressed
     * @tparam T Type of the object whose method is being bound
     * @param key The key to bind this method to
     * @param object The object whose method will be called
     * @param ptr Pointer to the method function
     */
    template <typename T>
    void RegisterKeyboardInput(int key, T* object, void (T::*ptr)()) {
        keyInputs.insert(std::make_pair(key,
                                        new KeyboardInputDelegate((GameObject *) object, (void (GameObject::*)()) ptr)));
    }

    /**
     * Binds a class's method function to a mouse event
     * The method will be called every time the mouse event occurs
     * @tparam T The type of the object whose method will be called
     * @param event The type of mouse event to be bound.
     * @param object The object whose method will be called
     * @param ptr Pointer to the method function to be called
     * @see EMouseEvent
     */
    template <typename T>
    void RegisterMouseInput(EMouseEvent event, T* object, void (T::*ptr)(EMouseButton, int, int)) {
        mouseInputs.insert(std::make_pair(event, new MouseInputDelegate((GameObject*) object, (void (GameObject::*)(EMouseButton, int, int)) ptr)));
    }

    /**
     * Binds a class's method function to a mouse event
     * The method will be called every time the mouse event occurs within the 2D bounds provided by the bounds param
     * @tparam T The type of the object whose method will be called
     * @param event The type of mouse event to be bound.
     * @param object The object whose method will be called
     * @param ptr Pointer to the method function to be called
     * @param bounds The 2D bounds in which the method should be triggered in
     */
    template <typename T>
    void RegisterMouseInput(EMouseEvent event, T* object, void (T::*ptr)(EMouseButton, int, int), Bound2D bounds) {
        mouseInputs.insert(std::make_pair(event, new MouseInputDelegate((GameObject*) object, (void (GameObject::*)(EMouseButton, int, int)) ptr, bounds)));
    }

    template<typename T>
    void RegisterMouseInput(EMouseEvent event, T* object, void (T::*ptr)(EMouseEvent, int, int), Bound2D bounds) {
        mouseInputs.insert(std::make_pair(event, (MouseInputDelegate*) new OtherMouseInputDelegate(object, (void (GameObject::*)(EMouseEvent, int, int)) ptr, bounds)));
    }

    /**
     * Clears all inputs bound to a specific object reference
     * @tparam T The type of object
     * @param object The object to clear all bound functions for
     */
    template <typename T>
    void ClearForObject(T* object) {
        for (auto it = keyInputs.begin(); it != keyInputs.end(); ++it) {
            if (it->second->GetObject<T>() == object) {
                keyInputs.erase(it);
            }
        }

        for (auto it = mouseInputs.begin(); it != mouseInputs.end(); ++it) {
            if (it->second->GetObject<T>() == object) {
                mouseInputs.erase(it);
            }
        }
    }

    /**
     * Handle inputs from the engine and dispatch bound inputs
     * @param event Event queue
     */
    void HandleInput(ALLEGRO_EVENT* event);
};
