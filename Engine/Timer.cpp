//
// Created by derek on 5/16/2017.
//

#include "Timer.h"
#include "Engine.h"

Timer::Timer(float time, Delegate<void()> callback) : target(time), callback(callback) {}

void Timer::Fire() {
    callback.Call();
    isFired = true;
}

void Timer::Cancel() {
    isCancelled = true;
}

bool Timer::IsFired() const {
    return isFired;
}