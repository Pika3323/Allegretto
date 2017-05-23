//
// Created by derek on 4/20/2017.
//

#pragma once

#include "Engine/Engine.h"
#include "Engine/Screen.h"
#include "Peg.h"
#include "Engine/Transform.h"
#include "Engine/Mesh.h"
#include "allegro5/transformations.h"

class HanoiScreen : public Screen{
    Peg* pegs[3];

    ALLEGRO_TRANSFORM cameraTransform;

    Mesh* mesh;

    void setupTransform(ALLEGRO_TRANSFORM* transform);
public:
    HanoiScreen(int screenWidth, int screenHeight);

    void Init(InputController *input) override;

    void Tick(float delta) override;

    void Destroy() override;

protected:
    void Draw() override;

private:

    void Hanoi(int rings, Peg* start, Peg* end, Peg* intermediate);
};


