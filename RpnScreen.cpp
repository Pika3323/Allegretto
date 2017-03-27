//
// Created by derek on 3/24/2017.
//

#include "RpnScreen.h"
#include "LifeScreen.h"

void RpnScreen::Init(InputController *input) {
    input->RegisterKeyboardInput(ALLEGRO_KEY_K, this, &RpnScreen::switchScreens);
}

void RpnScreen::switchScreens() {
    GEngine->SetActiveScreen(new LifeScreen(width, height));
}
