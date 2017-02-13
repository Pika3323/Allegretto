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
        std::cerr << "Allegro Primitives add-on could not be initialized" << std::endl;
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

    if (!al_init_font_addon() || !al_init_ttf_addon()) {
        std::cerr << "Font add-on could not be initialized" << std::endl;
        Quit();
    }

    default_font = al_load_font("Roboto-Regular.ttf", 11, 0);
    if (!default_font) {
        std::cerr << "Could not load default font" << std::endl;
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
    currentDelta = delta;

    //Gets the current inputController states
    al_get_mouse_state(&mouse_state);
    al_get_keyboard_state(&keyboard_state);

    //Tick the current active screen, if it exists
    if (active_screen) {
        active_screen->Tick(delta);
    }

    //Counts the duration of debug outputs and deletes them once they have been on screen for their allotted time
    for (int i = 0; i < (int)debug_strings.size(); i++){
        debug_strings[i].elapsedTime += delta;
        if (debug_strings[i].elapsedTime >= debug_strings[i].duration){
            debug_strings.erase(debug_strings.begin() + i);
        }
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

    al_set_target_bitmap(screen_buffer);

    al_draw_bitmap(active_screen->screen_buffer, 0, 0, 0);

    for (auto bitmap : draw_stack) {
        al_draw_bitmap(bitmap, 0, 0, 0);
    }

    //Draws the engine buffer to the screen buffer
    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_bitmap(screen_buffer, 0, 0, 0);

    DrawFps(currentDelta);

    //Draws debug strings to the screen
    for (int i = 0; i < (int)debug_strings.size(); i++){
        al_draw_textf(default_font, al_map_rgb(0, 0, 0), 6, i * 16 + 50, ALLEGRO_ALIGN_LEFT, "%s", debug_strings[i].text.c_str());
        al_draw_textf(default_font, debug_strings[i].color, 5, i * 16 + 49, ALLEGRO_ALIGN_LEFT, "%s", debug_strings[i].text.c_str());
    }

    al_flip_display();
    al_clear_to_color(BLACK);

    draw_stack.clear();

    bShouldRedraw = false;
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

ALLEGRO_DISPLAY* Engine::getDisplay() const {
    return display;
}

ALLEGRO_DISPLAY_MODE Engine::getDisplayMode() const {
    return display_mode;
}

ALLEGRO_EVENT_QUEUE* Engine::getEventQueue() const {
    return event_queue;
}

ALLEGRO_TIMER* Engine::getTimer() const {
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

void Engine::DrawFps(float delta) {
    ALLEGRO_COLOR textColor;
    if (1 / delta >= 30){
        textColor = al_map_rgb(0, 255, 0);
    }
    else{
        textColor = al_map_rgb(255, 0 , 0);
    }

    al_draw_textf(default_font, al_map_rgb(0, 0, 0), al_get_display_width(display) - 5, 17, ALLEGRO_ALIGN_RIGHT, "%.2f FPS", 1 / delta);
    al_draw_textf(default_font, al_map_rgb(0, 0, 0), al_get_display_width(display) - 5, 33, ALLEGRO_ALIGN_RIGHT, "%.2fMS", delta * 1000);

    al_draw_textf(default_font, textColor, al_get_display_width(display) - 6, 16, ALLEGRO_ALIGN_RIGHT, "%.2f FPS", 1 / delta);
    al_draw_textf(default_font, textColor, al_get_display_width(display) - 6, 32, ALLEGRO_ALIGN_RIGHT, "%.2fMS", delta * 1000);
}

void Engine::PrintDebugText(const std::string &text, ALLEGRO_COLOR color, float duration) {
    debug_strings.push_back(DebugOutput(text, color, duration));
    std::clog << text << std::endl;
}
