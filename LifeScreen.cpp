//
// Created by Derek on 2/9/2017.
//

#include "LifeScreen.h"

LifeScreen::LifeScreen() {
    screen_buffer = al_create_bitmap(1280, 720);
}

void LifeScreen::Init(InputController* inputController) {
    std::cout << "Life Screen initialized!" << std::endl;

    //Setup keyboard input
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
}

void LifeScreen::Destroy() {
    al_destroy_bitmap(screen_buffer);
}


void LifeScreen::exit() {
    GEngine->Quit();
}
