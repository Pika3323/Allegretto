//
// Created by Derek on 2/9/2017.
//

#include "Engine.h"

Engine::Engine() {
    active_screen = nullptr;
}

void Engine::Init() {
    if (!al_init()) {
        std::cerr << "Could not initialize Allegro" << std::endl;
        Quit();
    }

    std::cout << ALLEGRO_VERSION_STR << std::endl;

    if (!al_init_primitives_addon()) {
        std::cerr << "Allegro Primitives Add-on could not be initialized" << std::endl;
        Quit();
    }

    if (!al_install_keyboard()) {
        std::cerr << "Keyboard drivers could not be installed" << std::endl;
        Quit();
    }

    if (!al_install_mouse()) {
        std::cerr << "Mouse drivers could not be installed" << std::endl;
        Quit();
    }

    event_queue = al_create_event_queue();
    if (!event_queue) {
        std::cerr << "Event queue could not be created" << std::endl;
        Quit();
    }
    timer = al_create_timer(1.0 / FPS);

    al_set_new_display_flags(ALLEGRO_OPENGL);
    al_set_new_window_title("The Game of Life");

    display = al_create_display(SCREEN_W, SCREEN_H);

    screen_buffer = al_create_bitmap(SCREEN_W, SCREEN_H);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_start_timer(timer);

    inputController = new InputController();

    if (active_screen) {
        active_screen->Init(inputController);
    }
}

void Engine::Tick(float delta) {
    //Gets the current inputController states
    al_get_mouse_state(&mouse_state);
    al_get_keyboard_state(&keyboard_state);

    //Tick the current active screen, if it exists
    if (active_screen) {
        active_screen->Tick(delta);
    }

    bShouldRedraw = true;
}

bool Engine::ShouldTick() {
    return !bShouldExit;
}

void Engine::SetActiveScreen(Screen *screen) {
    active_screen = screen;
    if (active_screen) {
        active_screen->Init(inputController);
    }
}

void Engine::Draw() {
    //Clears the screen to black
    al_set_target_bitmap(screen_buffer);
    al_clear_to_color(BLACK);

    //Draws the current screen, if present
    if (active_screen) {
        active_screen->Draw();
    }

    bShouldRedraw = false;

    al_set_target_bitmap(screen_buffer);

    for (auto bitmap : draw_stack) {
        al_draw_bitmap(bitmap, 0, 0, 0);
    }

    //Draws the engine buffer to the screen buffer
    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_bitmap(screen_buffer, 0, 0, 0);

    al_flip_display();
    al_clear_to_color(BLACK);

    draw_stack.clear();
}

void Engine::Kill() {
    active_screen->Destroy();
    delete active_screen;

    delete inputController;

    al_destroy_bitmap(screen_buffer);

    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    al_shutdown_primitives_addon();
}

void Engine::Quit() {
    bShouldExit = true;
}

ALLEGRO_DISPLAY *Engine::getDisplay() const {
    return display;
}

const ALLEGRO_DISPLAY_MODE &Engine::getDisplayMode() const {
    return display_mode;
}

ALLEGRO_EVENT_QUEUE *Engine::getEventQueue() const {
    return event_queue;
}

ALLEGRO_TIMER *Engine::getTimer() const {
    return timer;
}

void Engine::HandleInput(ALLEGRO_EVENT *event) {
    if (inputController) {
        inputController->HandleInput(event);
    }
}

bool Engine::ShouldDraw() {
    return bShouldRedraw;
}

void Engine::AddToDrawStack(ALLEGRO_BITMAP *buffer) {
    draw_stack.push_back(buffer);
}
