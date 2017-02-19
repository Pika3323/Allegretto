//
// Created by Derek on 2/9/2017.
//

#include "LifeScreen.h"
#include <fstream>

LifeScreen::LifeScreen() {
    screen_buffer = al_create_bitmap(1280, 720);
}

void LifeScreen::Init(InputController* inputController) {
    GEngine->PrintDebugText("Life Screen Initialized!", Colour::GREEN, 5.f);

    //Setup keyboard input
    inputController->RegisterKeyboardInput(ALLEGRO_KEY_ESCAPE, this, (void (GameObject::*)()) &LifeScreen::exit);
    inputController->RegisterKeyboardInput(ALLEGRO_KEY_SPACE, this,
                                           (void (GameObject::*)()) &LifeScreen::nextGeneration);
    inputController->RegisterKeyboardInput(ALLEGRO_KEY_TILDE, this, (void (GameObject::*)()) &LifeScreen::toggleDebugs);

    std::ifstream file("LIFE_GLI.DAT");
    //Reads the file into the matrix
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 50; ++j) {
            char state;
            file >> state;
            lifeMatrix[i][j] = state;
        }
    }

    GEngine->PrintDebugText("File Open", Colour::GREEN, 5.f);
}

void LifeScreen::Tick(float delta) {

}

void LifeScreen::Draw() {
    al_set_target_bitmap(screen_buffer);
    al_clear_to_color(Colour::BLACK);

    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 50; ++j) {
            if (lifeMatrix[i][j] == ALIVE) {
                al_draw_filled_rectangle(j * 10, i * 10, j * 10 + 10, i * 10 + 10, al_map_rgb(33, 150, 243));
            }
        }
    }
}

void LifeScreen::Destroy() {
    al_destroy_bitmap(screen_buffer);
}


void LifeScreen::exit() {
    GEngine->Quit();
}

void LifeScreen::nextGeneration() {
    apmatrix<char> newGrid(20, 50);
    int neighbourCount = 0;
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 50; ++j) {
            //Counts all the live neighbours in the 8 surrounding cells
            if (i > 0 && lifeMatrix[i - 1][j] == ALIVE) neighbourCount++;
            if (i > 0 && j > 0 && lifeMatrix[i - 1][j - 1] == ALIVE) neighbourCount++;
            if (i > 0 && j < 49 && lifeMatrix[i - 1][j + 1] == ALIVE) neighbourCount++;
            if (j > 0 && lifeMatrix[i][j - 1] == ALIVE) neighbourCount++;
            if (j < 49 && lifeMatrix[i][j + 1] == ALIVE) neighbourCount++;
            if (i < 19 && j > 0 && lifeMatrix[i + 1][j - 1] == ALIVE) neighbourCount++;
            if (i < 19 && lifeMatrix[i + 1][j] == ALIVE) neighbourCount++;
            if (i < 19 && j < 49 && lifeMatrix[i + 1][j + 1] == ALIVE) neighbourCount++;

            if (lifeMatrix[i][j] == ALIVE && (neighbourCount < 2 || neighbourCount > 3)) {
                newGrid[i][j] = DEAD;
            } else if (lifeMatrix[i][j] == DEAD && neighbourCount == 3) {
                newGrid[i][j] = ALIVE;
            } else {
                newGrid[i][j] = lifeMatrix[i][j];
            }

            //Reset the number of live neighbours
            neighbourCount = 0;
        }
    }

    currentGeneration++;

    lifeMatrix = newGrid;
}

void LifeScreen::toggleDebugs() {
    GEngine->ToggleEngineDebugFlag(Engine::ENGINE_DEBUG_DRAW_FPS | Engine::ENGINE_DEBUG_DRAW_DEBUG_STRINGS);
}

