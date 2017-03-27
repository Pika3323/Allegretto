//
// Created by Derek on 2/9/2017.
//

#include "Engine.h"

Engine::Engine() {
    activeScreen = nullptr;
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

    defaultFont = al_load_font("Roboto-Regular.ttf", 11, 0);
    if (!defaultFont) {
        std::cerr << "Could not load default font" << std::endl;
        Quit();
    }

    eventQueue = al_create_event_queue();
    if (!eventQueue) {
        std::cerr << "Event queue could not be created" << std::endl;
        Quit();
    }
    timer = al_create_timer(1.0 / FPS);

    //Get the current time for time calculations
    oldTime = al_get_time();

    al_set_new_display_flags(ALLEGRO_OPENGL);
    al_set_new_window_title("The Game of Life");

    display = al_create_display(displayWidth, displayHeight);

    al_acknowledge_resize(display);

    screenBuffer = al_create_bitmap(displayWidth, displayHeight);

    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_mouse_event_source());

    al_start_timer(timer);

    inputController = new InputController();

    if (activeScreen) {
        activeScreen->Init(inputController);
    }
}

void Engine::Tick() {
    currentDelta = (float) (al_get_time() - oldTime);
    oldTime = al_get_time();

    //Gets the current state of input methods
    al_get_mouse_state(&mouseState);
    al_get_keyboard_state(&keyboardState);

    //Tick the current active screen, if it exists
    if (activeScreen) {
        activeScreen->Tick(currentDelta);
    }

    //Counts the duration of debug outputs and deletes them once they have been on screen for their allotted time
    for (int i = 0; i < (int)debugStrings.size(); i++){
        debugStrings[i].elapsedTime += currentDelta;
        if (debugStrings[i].elapsedTime >= debugStrings[i].duration){
            debugStrings.erase(debugStrings.begin() + i);
        }
    }

    bShouldRedraw = true;
}

bool Engine::ShouldTick() {
    return !bShouldExit;
}

void Engine::SetActiveScreen(Screen *screen) {
    // Remove the old screen
    if (activeScreen != nullptr) {
        inputController->ClearForObject(screen);
        activeScreen->Destroy();
        delete activeScreen;
    }

    // Load and initialize the new screen
    activeScreen = screen;
    if (activeScreen) {
        activeScreen->Init(inputController);
    }
}

void Engine::Draw() {
    //Clears the screen to black
    al_set_target_bitmap(screenBuffer);
    al_clear_to_color(Colour::BLACK);

    //Draws the current screen, if present
    if (activeScreen) {
        activeScreen->Draw();
    }

    al_set_target_bitmap(screenBuffer);

    al_draw_bitmap(activeScreen->screen_buffer, 0, 0, 0);

    for (auto bitmap : drawStack) {
        al_draw_bitmap(bitmap, 0, 0, 0);
    }

    //Draws the engine buffer to the screen buffer
    al_set_target_bitmap(al_get_backbuffer(display));
    al_draw_bitmap(screenBuffer, 0, 0, 0);

    if (debugFlags & ENGINE_DEBUG_DRAW_FPS) {
        DrawFps(currentDelta);
    }

    if (debugFlags & ENGINE_DEBUG_DRAW_DEBUG_STRINGS) {
        //Draws debug strings to the screen
        for (int i = 0; i < (int) debugStrings.size(); i++) {
            al_draw_textf(defaultFont, Colour::BLACK, 6, i * 16 + 50, ALLEGRO_ALIGN_LEFT, "%s",
                          debugStrings[i].text.c_str());
            al_draw_textf(defaultFont, debugStrings[i].color, 5, i * 16 + 49, ALLEGRO_ALIGN_LEFT, "%s",
                          debugStrings[i].text.c_str());
        }
    }

    al_flip_display();
    al_clear_to_color(Colour::BLACK);

    drawStack.clear();

    bShouldRedraw = false;
}

void Engine::Kill() {
    activeScreen->Destroy();
    delete activeScreen;

    delete inputController;

    al_destroy_bitmap(screenBuffer);

    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(eventQueue);
    al_shutdown_primitives_addon();
}

void Engine::Quit() {
    bShouldExit = true;
}

ALLEGRO_DISPLAY* Engine::getDisplay() const {
    return display;
}

ALLEGRO_EVENT_QUEUE* Engine::getEventQueue() const {
    return eventQueue;
}

ALLEGRO_TIMER* Engine::getTimer() const {
    return timer;
}

void Engine::HandleInput(ALLEGRO_EVENT *event) {
    switch (event->type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            //Quit the game, close the window
            Quit();
            break;
        case ALLEGRO_EVENT_TIMER:
            //Handle current tick functions
            Tick();
            break;
        case ALLEGRO_EVENT_DISPLAY_RESIZE:
            al_destroy_bitmap(screenBuffer);
            screenBuffer = al_create_bitmap(event->display.width, event->display.height);

            activeScreen->Resize(event->display.width, event->display.height);
        default:
            if (inputController) {
                inputController->HandleInput(event);
            }
            break;
    }

}

bool Engine::ShouldDraw() {
    return bShouldRedraw;
}

void Engine::AddToDrawStack(ALLEGRO_BITMAP *buffer) {
    drawStack.push_back(buffer);
}

void Engine::DrawFps(float delta) {
    ALLEGRO_COLOR textColor;
    if (1 / delta >= 30){
        textColor = al_map_rgb(0, 255, 0);
    }
    else{
        textColor = al_map_rgb(255, 0 , 0);
    }

    al_draw_textf(defaultFont, al_map_rgb(0, 0, 0), al_get_display_width(display) - 5, 17, ALLEGRO_ALIGN_RIGHT, "%.2f FPS", 1 / delta);
    al_draw_textf(defaultFont, al_map_rgb(0, 0, 0), al_get_display_width(display) - 5, 33, ALLEGRO_ALIGN_RIGHT, "%.2fMS", delta * 1000);

    al_draw_textf(defaultFont, textColor, al_get_display_width(display) - 6, 16, ALLEGRO_ALIGN_RIGHT, "%.2f FPS", 1 / delta);
    al_draw_textf(defaultFont, textColor, al_get_display_width(display) - 6, 32, ALLEGRO_ALIGN_RIGHT, "%.2fMS", delta * 1000);
}

void Engine::PrintDebugText(const std::string &text, Colour colour, float duration) {
    debugStrings.push_back(DebugOutput(text, colour, duration));
    std::clog << text << std::endl;
}

void Engine::AddEngineDebugFlag(uint8_t flag) {
    debugFlags |= flag;
}

void Engine::SetEngineDebugFlag(uint8_t flags) {
    debugFlags = flags;
}

void Engine::RemoveEngineDebugFlag(uint8_t flag) {
    debugFlags &= ~flag;
}

void Engine::ToggleEngineDebugFlag(uint8_t flag) {
    debugFlags ^= flag;
}

void Engine::AddNewUiLayer(class UILayer *layer) {
    uiLayers.push_back(layer);
}

int Engine::getDisplayHeight() const {
    return displayHeight;
}

void Engine::setDisplayHeight(int displayHeight) {
    Engine::displayHeight = displayHeight;
    activeScreen->Resize(displayWidth, displayHeight);

    // Recreates the screen buffer with the new display dimensions
    al_destroy_bitmap(screenBuffer);
    screenBuffer = al_create_bitmap(displayWidth, displayHeight);
}

int Engine::getDisplayWidth() const {
    return displayWidth;
}

void Engine::setDisplayWidth(int displayWidth) {
    Engine::displayWidth = displayWidth;
    activeScreen->Resize(displayWidth, displayHeight);

    // Recreates the screen buffer with the new display dimensions
    al_destroy_bitmap(screenBuffer);
    screenBuffer = al_create_bitmap(displayWidth, displayHeight);
}

ALLEGRO_FONT* Engine::getDefaultFont() const {
    return defaultFont;
}

InputController *Engine::getInputController() const {
    return inputController;
}
