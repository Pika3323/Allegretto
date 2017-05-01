//
// Created by derek on 4/20/2017.
//

#include "HanoiScreen.h"

HanoiScreen::HanoiScreen(int screenWidth, int screenHeight) : Screen(screenWidth, screenHeight) {}

void HanoiScreen::Init(InputController *input) {
    for (int i = 0; i < 3; i++) {
        pegs[i] = new Peg();
    }


}

void HanoiScreen::Tick(float delta) {

}

void HanoiScreen::Destroy() {

}

void HanoiScreen::Draw() {
    Screen::Draw();
}
