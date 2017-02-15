//
// Created by Derek on 2/9/2017.
//

#pragma once

#include "Core.h"
#include "Screen.h"
#include "InputController.h"
#include "DebugOutput.h"
#include "Colour.h"

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

    uint8_t debug_flags = 0;

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

    void PrintDebugText(const std::string &text, Colour color, float duration);

    static const uint8_t ENGINE_DEBUG_DRAW_FPS = 0x01;
    static const uint8_t ENGINE_DEBUG_DRAW_DEBUG_STRINGS = 0x02;
    static const uint8_t ENGINE_DEBUG_3 = 0x04;
    static const uint8_t ENGINE_DEBUG_4 = 0x08;
    static const uint8_t ENGINE_DEBUG_5 = 0x10;
    static const uint8_t ENGINE_DEBUG_6 = 0x20;
    static const uint8_t ENGINE_DEBUG_7 = 0x40;
    static const uint8_t ENGINE_DEBUG_8 = 0x80;

    void AddEngineDebugFlag(uint8_t flag);

    void SetEngineDebugFlag(uint8_t flags);

    void RemoveEngineDebugFlag(uint8_t flag);

    void ToggleEngineDebugFlag(uint8_t flag);
};

extern Engine* GEngine;
