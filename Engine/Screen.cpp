//
// Created by derek on 3/28/2017.
//

#include "Screen.h"

void Screen::DrawToBuffer() {
    al_set_target_bitmap(screenBuffer);
    al_clear_to_color(Colour::BLACK);

    Draw();

    DrawViews();
}

void Screen::Draw() {

}

void Screen::DrawViews() {
    std::map<int, View*>::iterator it;

    // Iterates through the list of views and draws them all onto the screen
    for (it = viewList.begin(); it != viewList.end(); it++) {
        View* view = it->second;

        // Tell the view to draw itself to its texture
        view->Draw();

        // Reset the target bitmap to be that of the Screen's buffer
        al_set_target_bitmap(screenBuffer);

        // Draw the resulting texture to the screen
        al_draw_bitmap(view->GetTexture(), view->GetPosition().x, view->GetPosition().y, 0);
    }
}

ALLEGRO_BITMAP* const Screen::GetBuffer() {
    return screenBuffer;
}

void Screen::Resize(int newX, int newY)  {
    al_destroy_bitmap(screenBuffer);
    screenBuffer = al_create_bitmap(newX, newY);
}

Screen::Screen(int screenWidth, int screenHeight) : width(screenWidth), height(screenHeight) {
    screenBuffer = al_create_bitmap(screenWidth, screenHeight);
}

void Screen::AddView(View* view) {
    viewList.insert(std::make_pair(view->GetId(), view));

    if (GEngine) {
        auto inputController = GEngine->GetInputController();
        inputController->RegisterMouseInput(EMouseEvent::ButtonDown, view,
                                            (void (View::*)(EMouseButton, int, int)) &View::OnClick,
        view->GetBounds());

        inputController->RegisterMouseInput(EMouseEvent::Hover, view, &View::OnHover, view->GetBounds());
        inputController->RegisterMouseInput(EMouseEvent::Enter, view, &View::OnHover, view->GetBounds());
        inputController->RegisterMouseInput(EMouseEvent::Exit, view, &View::OnHover, view->GetBounds());
    }
}

View* Screen::GetViewById(int id) {
    return viewList[id];
}
