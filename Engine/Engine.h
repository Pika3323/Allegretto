//
// Created by Derek on 2/9/2017.
//

#pragma once

#include "Core.h"
#include "Screen.h"
#include "InputController.h"
#include "DebugOutput.h"
#include "Colour.h"

#define SCREEN_W 1280
#define SCREEN_H 720

#define FPS 60

/**
 * The primary Engine class that controls and manages the running of the game
 */
class Engine {
    /**
     * The main display of the program
     */
    ALLEGRO_DISPLAY* display;

    /**
     * The queue of Allegro events
     */
    ALLEGRO_EVENT_QUEUE* event_queue;

    /**
     * The timer controlling the primary game loop
     */
    ALLEGRO_TIMER* timer;

    /**
     * The current state of the mouse
     */
    ALLEGRO_MOUSE_STATE mouse_state;

    /**
     * The current state of the keyboard
     */
    ALLEGRO_KEYBOARD_STATE keyboard_state;

    /**
     * The default font used for things like displaying frame rate, and debugging. Currently "Roboto".
     */
    ALLEGRO_FONT* default_font;

    /**
     * Whether the game loop should exit and end the program
     */
    bool bShouldExit = false;

    /**
     * Whether the engine should redraw the screen
     */
    bool bShouldRedraw = false;

    /**
     * Reference to the current active screen
     */
    class Screen* active_screen;

    /**
     * Reference to the input controller that manages most forms of user input
     */
    class InputController* input_controller;

    /**
     * The stack of bitmaps to draw to the screen buffer
     */
    std::vector<ALLEGRO_BITMAP*> draw_stack;

    /**
     * The set of UILayers to be handled
     */
    std::vector<class UILayer*> ui_layers;

    /**
     * The buffer used to draw things to the screen
     */
    ALLEGRO_BITMAP* screen_buffer;

    /**
     * Used in calculating delta time.
     * The exact time at which the previous frame was drawn
     */
    double old_time;

    /**
     * The current delta time for the latest frame
     */
    float current_delta;

    /**
     * Draws the current frame rate and frame timing on the screen
     * @param delta The time between the two latest frames
     */
    void DrawFps(float delta);

    /**
     * Array of all messages that should be drawn onto the screen for debug purposes
     */
    std::vector<DebugOutput> debug_strings;

    /**
     * Any special bit flags that should be taken in consideration for drawing while debugging
     */
    uint8_t debug_flags = 0;

public:
    /**
     * Gets a reference to the current program display
     * @return The current display
     */
    ALLEGRO_DISPLAY* getDisplay() const;

    /**
     * Gets a reference to the current event queue
     * @return The current event queue
     */
    ALLEGRO_EVENT_QUEUE* getEventQueue() const;

    /**
     * Gets a reference to the current game timer
     * @return The current game timer
     */
    ALLEGRO_TIMER* getTimer() const;

    /**
     * Called to initialize the Engine and prepares it for drawing, and other game-related functions
     */
    void Init();

    /**
     * Called every single frame from the primary game loop.
     */
    void Tick();

    /**
     * Called on every draw tick. Handles all drawing and displays it on the screen.
     */
    void Draw();

    /**
     * Called when the engine class is being destroyed, for cleaning things up.
     */
    void Kill();

    /**
     * Triggers the primary game loop to quit, thus quitting the program
     */
    void Quit();

    /**
     * Called for every input, whether it be keyboard, mouse, or display.
     * Passes most input events to the #input_controller
     * @param event The current event being processed
     * @see InputController
     */
    void HandleInput(ALLEGRO_EVENT* event);

    /**
     * Checks whether the current loop of the primary game loop should be taken as a tick loop
     * @return Is the current loop a game tick loop
     */
    bool ShouldTick();

    /**
     * Checks whether the current iteration of the primary game loop should be used to draw to the screen
     * @return Whether the current loop should be used to draw
     */
    bool ShouldDraw();

    /**
     * Adds a bitmap to be drawn onto the screen by the engine.
     * @param buffer The image buffer that should be drawn
     */
    void AddToDrawStack(ALLEGRO_BITMAP* buffer);

    void AddNewUiLayer(class UILayer* layer);

    /**
     * Sets the current active screen class of the primary display
     * @param screen The subclass of Screen that should be displayed
     */
    void SetActiveScreen(Screen* screen);

    /**
     * Default contstructor
     */
    Engine();

    /**
     * Prints a bit of text onto the screen. Useful for debugging certain values
     * @param text The message to be printed
     * @param colour The colour to print the message in. Default is Colour::GREEN.
     * @param duration How long to display the message for. Default for 5 seconds.
     */
    void PrintDebugText(const std::string &text, Colour colour = Colour::GREEN, float duration = 5.f);

    /**
     * Controls whether to draw the current frame rate to the screen
     */
    static const uint8_t ENGINE_DEBUG_DRAW_FPS = 0x01;
    /**
     * Controls whether to draw debug strings to the screen
     */
    static const uint8_t ENGINE_DEBUG_DRAW_DEBUG_STRINGS = 0x02;
    static const uint8_t ENGINE_DEBUG_3 = 0x04;
    static const uint8_t ENGINE_DEBUG_4 = 0x08;
    static const uint8_t ENGINE_DEBUG_5 = 0x10;
    static const uint8_t ENGINE_DEBUG_6 = 0x20;
    static const uint8_t ENGINE_DEBUG_7 = 0x40;
    static const uint8_t ENGINE_DEBUG_8 = 0x80;

    /**
     * Enables an Engine debug flag
     * @param flag The flag to be enabled
     */
    void AddEngineDebugFlag(uint8_t flag);

    /**
     * Sets all Engine debug flags
     * @param flags The flags to replace the active flags
     */
    void SetEngineDebugFlag(uint8_t flags);

    /**
     * Disables an Engine debug flag
     * @param flag The flag to be disabled
     */
    void RemoveEngineDebugFlag(uint8_t flag);

    /**
     * Toggles an Engine flag
     * @param flag The flag to be toggled
     */
    void ToggleEngineDebugFlag(uint8_t flag);
};

/**
 * Global singleton variable reference to the game engine class
 */
extern Engine* GEngine;
