//
// Created by Derek on 2/9/2017.
//

#pragma once

#include "Core.h"
#include "Screen.h"
#include "InputController.h"

#define MOUSE_LB 1
#define MOUSE_RB 2
#define MOUSE_MB 3

#define SCREEN_W 1280
#define SCREEN_H 720

#define BLACK al_map_rgb(0, 0, 0)

#define FPS 60

class Engine {
    ALLEGRO_DISPLAY* display;

    ALLEGRO_DISPLAY_MODE display_mode;

    ALLEGRO_EVENT_QUEUE* event_queue;

    ALLEGRO_TIMER* timer;

    ALLEGRO_MOUSE_STATE mouse_state;

    ALLEGRO_KEYBOARD_STATE keyboard_state;

    bool bShouldExit = false;

    bool bShouldRedraw = false;

    class Screen* active_screen;

    class InputController* inputController;

    std::vector<ALLEGRO_BITMAP*> draw_stack;

    ALLEGRO_BITMAP* screen_buffer;

public:
    ALLEGRO_DISPLAY *getDisplay() const;

    const ALLEGRO_DISPLAY_MODE &getDisplayMode() const;

    ALLEGRO_EVENT_QUEUE *getEventQueue() const;

    ALLEGRO_TIMER *getTimer() const;

    void Init();

    void Tick(float delta);

    void Draw();

    void Kill();

    void Quit();

    void HandleInput(ALLEGRO_EVENT* event);

    bool ShouldTick();

    bool ShouldDraw();

    void AddToDrawStack(ALLEGRO_BITMAP* buffer);

    void SetActiveScreen(Screen* screen);

    Engine();
};

extern Engine* GEngine;
