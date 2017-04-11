//
// Created by Derek on 2/9/2017.
//

#include "LifeScreen.h"
#include <fstream>
#include "Engine/Views/TextView.h"

LifeScreen::LifeScreen(int screenWidth, int screenHeight) : Screen(screenWidth, screenHeight) {}


void LifeScreen::Init(InputController* inputController) {
    // Calculates the number of columns and rows that fit inside the screen
    matrixColumns = GEngine->GetDisplayWidth() / GRID_SIZE;
    matrixRows = GEngine->GetDisplayHeight() / GRID_SIZE;

    // Creates the matrix to be used in the game
    lifeMatrix = apmatrix<char>(matrixRows, matrixColumns, DEAD);

    // Setup keyboard input binding
    inputController->RegisterKeyboardInput(ALLEGRO_KEY_SPACE, this, &LifeScreen::nextGeneration);
    inputController->RegisterKeyboardInput(ALLEGRO_KEY_P, this, &LifeScreen::toggleAutoGenerate);
    inputController->RegisterKeyboardInput(ALLEGRO_KEY_C, this, &LifeScreen::clearMatrix);

    //inputController->RegisterKeyboardInput(ALLEGRO_KEY_L, this, +[](){ GEngine->PrintDebugText("Yoyoyoo"); });

    /*auto lambda = [this](){std::cout << a << std::endl; };
    LambdaDelegate* delegate = new LambdaDelegate(lambda);

    delegate->Call();*/

    // The number keys open different pre-made levels that can be viewed
    inputController->RegisterKeyboardInput(ALLEGRO_KEY_1, this, &LifeScreen::loadCat);
    inputController->RegisterKeyboardInput(ALLEGRO_KEY_2, this, &LifeScreen::loadGlider);
    inputController->RegisterKeyboardInput(ALLEGRO_KEY_4, this, &LifeScreen::loadHrv);

    // Setup mouse input binding
    inputController->RegisterMouseInput(EMouseEvent::ButtonDown, this, &LifeScreen::onClick);
    inputController->RegisterMouseInput(EMouseEvent::ButtonUp, this, &LifeScreen::onUnClick);
    inputController->RegisterMouseInput(EMouseEvent::AxesChange, this, &LifeScreen::onMouseMove);

    TextView* textView = new TextView(Vector2D(50, 70));
    textView->SetId(5);
    textView->SetFont(new Font("Roboto-Regular.ttf"));
    textView->SetText("Hello World!");
    textView->SetPadding(8);
    textView->SetTextColour(Colour(0x212121));
    textView->SetBackgroundColour(Colour::WHITE);
    textView->BindOnClickDelegate(this, &LifeScreen::TestClick);
    textView->BindOnHoverDelegate(this, &LifeScreen::TestHover);
    textView->SetCornerRadius(2.f);
    textView->SetCursor(ECursor::Link);

    AddView(textView);
}

void LifeScreen::Tick(float delta) {
    // Checks whether generations are being generated automatically
    if (bAutoGenerate) {
        elapsedSeconds += delta;

        // Creates a new generation every 0.1 elapsed seconds
        if (elapsedSeconds > 0.1f) {
            nextGeneration();
            elapsedSeconds = 0.f;
        }
    }

    // If the left mouse button is down, set the current cell to be alive
    if (bLeftMouseButtonDown) {
        ALLEGRO_MOUSE_STATE mouseState;
        al_get_mouse_state(&mouseState);

        setStateAtPosition(mouseState.x, mouseState.y, ALIVE);
    }

    // If the left mouse button is down, set the current cell to be dead
    if (bRightMouseButtonDown) {
        ALLEGRO_MOUSE_STATE mouseState;
        al_get_mouse_state(&mouseState);

        setStateAtPosition(mouseState.x, mouseState.y, DEAD);
    }

}

void LifeScreen::Draw() {


    // Alerts the user that the game is paused
    if (!bAutoGenerate) {
        std::string message = "Game is paused. Press P to unpause.";
        drawShadowedText(message, Colour::RED, GEngine->GetDisplayWidth() - 5, 55, ALLEGRO_ALIGN_RIGHT);
    }// Draws the grid lines for columns
    for (int i = 0; i < matrixColumns; ++i) {
        al_draw_line(GRID_SIZE * i, 0, GRID_SIZE * i, GEngine->GetDisplayHeight(), Colour(25, 25, 25), 1);
    }

    // Draws the grid lines for rows
    for (int k = 0; k < matrixRows; ++k) {
        al_draw_line(0, GRID_SIZE * k, GEngine->GetDisplayWidth(), GRID_SIZE * k, Colour(25, 25, 25), 1);
    }

    // Draws any live cells as a blue square
    for (int i = 0; i < matrixRows; ++i) {
        for (int j = 0; j < matrixColumns; ++j) {
            if (lifeMatrix[i][j] == ALIVE) {
                al_draw_filled_rectangle(j * GRID_SIZE, i * GRID_SIZE, j * GRID_SIZE + GRID_SIZE, i * GRID_SIZE + GRID_SIZE, Colour(33, 150, 243));
            }
        }
    }

    // Use the old-fashioned itoa number to string conversion since std::to_string doesn't work with most compilers
    char* generationNumber;
    itoa(currentGeneration, generationNumber, 10);

    // Draws the current generation number on screen
    std::string generationText = "Current Generation: " + std::string(generationNumber);
    drawShadowedText(generationText, Colour::CYAN, GEngine->GetDisplayWidth() - 5, 75, ALLEGRO_ALIGN_RIGHT);

    // Draws the options to open pre-set levels
    std::string text = "1: Cat      2: Glider       3: Glider Gun       4. HRV";
    drawShadowedText(text, Colour::CYAN, 5, GEngine->GetDisplayHeight() - 15, ALLEGRO_ALIGN_LEFT);

    // Draws the other game controls
    std::string otherInstructions = "C: Clear Level         P: Pause Game         Space Bar: Advance Generation         Esc: Close Game";
    drawShadowedText(otherInstructions, Colour::CYAN, GEngine->GetDisplayWidth() - 5, GEngine->GetDisplayHeight() - 15, ALLEGRO_ALIGN_RIGHT);
}

void LifeScreen::Destroy() {
    // Destroys the buffer for this screen
    al_destroy_bitmap(screenBuffer);
}

void LifeScreen::nextGeneration() {
    // Creates a matrix to store the new generation
    apmatrix<char> newGrid(matrixRows, matrixColumns, DEAD);

    int neighbourCount = 0;

    for (int i = 0; i < matrixRows; ++i) {
        for (int j = 0; j < matrixColumns; ++j) {
            //Counts all the live neighbours in the 8 cells surrounding the current cell (checking if they're in range first)
            if (i > 0 && lifeMatrix[i - 1][j] == ALIVE) neighbourCount++;
            if (i > 0 && j > 0 && lifeMatrix[i - 1][j - 1] == ALIVE) neighbourCount++;
            if (i > 0 && j < matrixColumns - 1 && lifeMatrix[i - 1][j + 1] == ALIVE) neighbourCount++;
            if (j > 0 && lifeMatrix[i][j - 1] == ALIVE) neighbourCount++;
            if (j < matrixColumns - 1 && lifeMatrix[i][j + 1] == ALIVE) neighbourCount++;
            if (i < matrixRows - 1 && j > 0 && lifeMatrix[i + 1][j - 1] == ALIVE) neighbourCount++;
            if (i < matrixRows - 1 && lifeMatrix[i + 1][j] == ALIVE) neighbourCount++;
            if (i < matrixRows - 1 && j < matrixColumns - 1 && lifeMatrix[i + 1][j + 1] == ALIVE) neighbourCount++;

            if (lifeMatrix[i][j] == ALIVE && (neighbourCount < 2 || neighbourCount > 3)) {
                // Kills the current cell if underpopulated or overpopulated
                newGrid[i][j] = DEAD;
            } else if (lifeMatrix[i][j] == DEAD && neighbourCount == 3) {
                // Gives birth to a new cell if the neighbouring population count is just right
                newGrid[i][j] = ALIVE;
            } else {
                // Leaves the current cell untouched
                newGrid[i][j] = lifeMatrix[i][j];
            }

            //Reset the number of live neighbours for the next cell to check
            neighbourCount = 0;
        }
    }

    currentGeneration++;

    // Swaps the old generation with the new generation
    lifeMatrix = newGrid;
}

void LifeScreen::toggleDebugs() {
    // Toggles some settings in the engine class that control whether to draw the frame rate on screen
    GEngine->ToggleEngineDebugFlag(Engine::ENGINE_DEBUG_DRAW_FPS | Engine::ENGINE_DEBUG_DRAW_DEBUG_STRINGS);
}

void LifeScreen::toggleAutoGenerate() {
    // Toggles the option to have the game automatically generate the next generation
    bAutoGenerate = !bAutoGenerate;
}

void LifeScreen::onClick(EMouseButton button, int x, int y) {
    switch (button) {
        case EMouseButton::Left:
            // Sets the clicked cell to alive
            setStateAtPosition(x, y, ALIVE);

            // Indicates that this button is now held down
            bLeftMouseButtonDown = true;
            break;
        case EMouseButton::Right:
            // Sets the clicked cell to dead
            setStateAtPosition(x, y, DEAD);

            // Indicates that this button is now held down
            bRightMouseButtonDown = true;
            break;
        case EMouseButton::Middle:break;
    }
}

void LifeScreen::onMouseMove(EMouseButton button, int x, int y) {
    if (bLeftMouseButtonDown) {
        setStateAtPosition(x, y, ALIVE);
    } else if (bRightMouseButtonDown) {
        setStateAtPosition(x, y, DEAD);
    }
}

void LifeScreen::onUnClick(EMouseButton button, int x, int y) {
    switch (button) {
        case EMouseButton::Left:
            // Indicates that this button is now longer held down
            bLeftMouseButtonDown = false;
            break;
        case EMouseButton::Right:
            // Indicates that this button is now longer held down
            bRightMouseButtonDown = false;
            break;
        case EMouseButton::Middle:break;
    }
}

void LifeScreen::setStateAtPosition(int x, int y, char state) {
    int matrixRow = y / GRID_SIZE;
    int matrixColumn = x / GRID_SIZE;

    // Checks for an out of range index and then sets that cell to be dead/alive
    if (matrixRow >= 0 && matrixColumn >= 0 && matrixRow < lifeMatrix.numrows() && matrixColumn < lifeMatrix.numcols()) {
        lifeMatrix[matrixRow][matrixColumn] = state;
    }
}

void LifeScreen::clearMatrix() {
    // Clears the current game (sets all cells to dead)
    lifeMatrix = apmatrix<char>(matrixRows, matrixColumns, DEAD);

    currentGeneration = 0;
}

void LifeScreen::openLevel(std::string file) {
    // Clears the current level
    clearMatrix();

    // Opens the new level file
    std::ifstream inFile(file);

    // Checks if the file is open
    if (inFile.is_open()) {
        //Reads the file into the matrix
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < 50; ++j) {
                char state;
                inFile >> state;
                lifeMatrix[i][j] = state;
            }
        }

        inFile.close();
    } else {
        // Notify the user that the file could not be opened
        GEngine->PrintDebugText("Could not open file '" + file + "'", Colour::RED);
    }
}

void LifeScreen::loadCat() {
    // Loads the cat level
    openLevel("LIFE_CAT.DAT");
}

void LifeScreen::loadGlider() {
    // Loads the glider level
    openLevel("LIFE_GLI.DAT");
}

void LifeScreen::loadGliderGun() {
    // Loads the glider gun level
    openLevel("LIFE_GUN.DAT");
}

void LifeScreen::loadHrv() {
    // Loads the hrv level
    openLevel("LIFE_HRV.DAT");
}

void LifeScreen::drawShadowedText(std::string message, Colour textColour, int x, int y, int justification) {
    // Draws an offset black version of the text as a "shadow"
    al_draw_text(GEngine->GetDefaultFont(), Colour::BLACK, x, y, justification, message.c_str());
    al_draw_text(GEngine->GetDefaultFont(), textColour, x - 1, y - 1, justification, message.c_str());
}

void LifeScreen::TestClick(View *view) {
    std::cout << "Click on view with id " << view->GetId() << std::endl;
}

void LifeScreen::TestHover(EMouseEvent event, int x, int y) {
    switch (event){
        case EMouseEvent::AxesChange:break;
        case EMouseEvent::ButtonDown:break;
        case EMouseEvent::ButtonUp:break;
        case EMouseEvent::EnterDisplay:break;
        case EMouseEvent::LeaveDisplay:break;
        case EMouseEvent::Hover:
            //GEngine->PrintDebugText("Hovering over the view!");
            break;
        case EMouseEvent::Enter:
            GEngine->PrintDebugText("Entered view!");
            break;
        case EMouseEvent::Exit:
            GEngine->PrintDebugText("Exited view!");
            break;
    }
}
