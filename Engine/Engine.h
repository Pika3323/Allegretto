//
// Created by Derek on 2/9/2017.
//

#pragma once

#include "Core.h"
#include "Screen.h"
#include "InputController.h"
#include "DebugOutput.h"

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

    ALLEGRO_FONT* default_font;

    bool bShouldExit = false;

    bool bShouldRedraw = false;

    //The active screen class
    class Screen* active_screen;

    //Class controlling all forms of input
    class InputController* inputController;

    //The stack of bitmaps to draw to the screen buffer
    std::vector<ALLEGRO_BITMAP*> draw_stack;

    //The buffer used to draw things to the screen
    ALLEGRO_BITMAP* screen_buffer;

    //Used in calculating delta time
    double old_time;

    //The current delta time for the latest frame
    float current_delta;

    //Draws the current frame rate and frame timing on the screen
    void DrawFps(float delta);

    std::vector<DebugOutput> debug_strings;

public:
    ALLEGRO_DISPLAY* getDisplay() const;

    ALLEGRO_DISPLAY_MODE getDisplayMode() const;

    ALLEGRO_EVENT_QUEUE* getEventQueue() const;

    ALLEGRO_TIMER* getTimer() const;

    void Init();

    void Tick();

    void Draw();

    void Kill();

    void Quit();

    void HandleInput(ALLEGRO_EVENT* event);

    bool ShouldTick();

    bool ShouldDraw();

    void AddToDrawStack(ALLEGRO_BITMAP* buffer);

    void SetActiveScreen(Screen* screen);

    Engine();

    void PrintDebugText(const std::string &text, ALLEGRO_COLOR color, float duration);
};

extern Engine* GEngine;
