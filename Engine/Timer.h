//
// Created by derek on 5/16/2017.
//

#pragma once

#include "Delegate.h"

class Timer {
    friend class Engine;

    /**
     * The function to be called when the timer is fired
     */
    Delegate<void()> callback;

    /**
     * Whether this timer has been cancelled now
     */
    bool isCancelled = false;

    /**
     * Whether this timer has been fired
     */
    bool isFired = false;

    /**
     * The time since the timer was created at which the callback should be called
     */
    float target;

    /**
     * The time elapsed since the timer was created
     */
    float elapsed;

protected:
    /**
     * Fire the timer, cancel and call the callback
     */
    void Fire();

    /**
     * Constructor
     * @param time The target amount of time for the timer
     * @param callback The callback to be called when the timer is fired
     */
    Timer(float time, Delegate<void()> callback);
public:

    /**
     * Cancel and remove the timer
     */
    void Cancel();

    bool IsFired() const;
};

