//
// Created by Derek on 2/9/2017.
//

#pragma once

#include "Engine/Engine.h"
#include <APMATRIX.H>

class LifeScreen : public Screen{

    // Character to represent a live cell
    const char ALIVE = 'x';

    // Character to represent a dead cell
    const char DEAD = '.';

    // The width and height of each cell
    const int GRID_SIZE = 10;

public:

    int a = 16;

    // Constructor
    LifeScreen(int screenWidth, int screenHeight);

    // Called when the screen is initialized
    virtual void Init(InputController* inputController) override;

    // Called on every frame
    virtual void Tick(float delta) override;

    // Called when the engine asks the screen to draw something
    virtual void Draw() override;

    // Called when the screen is destroyed
    virtual void Destroy() override;

    // Generates the next generation
    void nextGeneration();

    // Toggles displaying of frame rate, and other debugging tools
    void toggleDebugs();

    // Toggles the automatic generation of generations
    void toggleAutoGenerate();

    // Clears the game matrix and resets it to all dead
    void clearMatrix();

    // Called when a mouse button is clicked down
    void onClick(EMouseButton button, int x, int y);

    // Called when the mouse moves
    void onMouseMove(EMouseButton button, int x, int y);

    // Called when a mouse button is let go
    void onUnClick(EMouseButton button, int x, int y);

    void drawShadowedText(std::string message, Colour textColour, int x, int y, int justification);

    // Opens the cat level
    void loadCat();

    // Opens the glider level
    void loadGlider();

    // Opens the glider gun level
    void loadGliderGun();

    // Opens the hrv level
    void loadHrv();

    void TestClick(View* view);

    void TestHover(EMouseEvent event, int x, int y);

private:
    // The number of current generation
    int currentGeneration = 0;

    // The number of rows and columns in the matrix
    int matrixRows, matrixColumns;

    // Controls whether the next generation is automatically generated
    bool bAutoGenerate = true;

    // The current matrix containing the current generation
    apmatrix<char> lifeMatrix;

    // The number of frames that
    float elapsedSeconds = 0.f;

    // Whether the left mouse button is currently down
    bool bLeftMouseButtonDown = false;

    // Whether the right mouse button is currently down
    bool bRightMouseButtonDown = false;

    // Sets the alive/dead state of a cell based on the screen position
    void setStateAtPosition(int x, int y, char state);

    void openLevel(std::string file);

};


