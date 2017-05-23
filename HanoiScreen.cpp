//
// Created by derek on 4/20/2017.
//

#include "HanoiScreen.h"
#include "allegro5/transformations.h"
#include "allegro5/allegro_opengl.h"
#include "allegro5/display.h"

HanoiScreen::HanoiScreen(int screenWidth, int screenHeight) : Screen(screenWidth, screenHeight) {}

void HanoiScreen::Init(InputController *input) {
    pegs[0] = new Peg(2);
    pegs[1] = new Peg(0);
    pegs[2] = new Peg(0);


    Hanoi(2, pegs[0], pegs[1], pegs[2]);
}

void HanoiScreen::Tick(float delta) {
}

void HanoiScreen::Destroy() {

}

void HanoiScreen::Draw() {
    Screen::Draw();
}

void HanoiScreen::setupTransform(ALLEGRO_TRANSFORM* transform) {
    ALLEGRO_DISPLAY *display = al_get_current_display();
    int dw = al_get_display_width(display);
    int dh = al_get_display_height(display);
    al_perspective_transform(transform, -180 * dw / dh, -180, 180,
                             180 * dw / dh, 180, 3000);
    //al_set_projection_transform(display, transform);
}

void HanoiScreen::Hanoi(int rings, Peg *start, Peg *end, Peg *intermediate) {
    if (rings > 0) {
        Hanoi(rings - 1, start, intermediate, end);
        start->MoveTopTo(end);
        Hanoi(rings - 1, intermediate, end, start);
    } else {
        start->MoveTopTo(end);
    }
}

