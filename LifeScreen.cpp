//
// Created by Derek on 2/9/2017.
//

#include "LifeScreen.h"

LifeScreen::LifeScreen() {
    screen_buffer = al_create_bitmap(1280, 720);
}

void LifeScreen::Init(InputController* inputController) {
    std::cout << "Life Screen initialized!" << std::endl;

    //Set up keyboard input
    inputController->RegisterKeyboardInput(ALLEGRO_KEY_O, this, (InDelegate) &LifeScreen::keyPress);
    inputController->RegisterKeyboardInput(ALLEGRO_KEY_M, this, (InDelegate) &LifeScreen::manage);
    inputController->RegisterKeyboardInput(ALLEGRO_KEY_B, this, (InDelegate) &LifeScreen::testFunction);
    inputController->RegisterKeyboardInput(ALLEGRO_KEY_SPACE, this, (InDelegate) &LifeScreen::function);
    inputController->RegisterKeyboardInput(ALLEGRO_KEY_ESCAPE, this, (InDelegate) &LifeScreen::exit);
}

void LifeScreen::Tick(float delta) {
    posX = (posX + (50 * delta));
    posY = (posY + (50 * delta));
}

void LifeScreen::Draw() {
    al_set_target_bitmap(screen_buffer);
    al_clear_to_color(BLACK);

    al_draw_pixel(posX, posY, blue);
    al_draw_filled_circle(posX, posY, 50, blue);

    GEngine->AddToDrawStack(screen_buffer);
}

void LifeScreen::Destroy() {
    al_destroy_bitmap(screen_buffer);
}

void LifeScreen::keyPress() {
    blue = al_map_rgb(255, 0, 0);
}

void LifeScreen::manage() {
    blue = al_map_rgb(255, 0, 255);
}

void LifeScreen::testFunction() {
    blue = al_map_rgb(0, 255, 0);
}

void LifeScreen::function() {
    std::cout << "Isaac is garbage" << std::endl;
}

void LifeScreen::exit() {
    GEngine->Quit();
}
