//
// Created by Derek on 2/9/2017.
//

#pragma once

#include "Engine.h"
#include "InputController.h"
#include "View.h"

class View;

class Screen : public GameObject {
    std::map<int, View*> viewList;

protected:
    int width;

    int height;

    ALLEGRO_BITMAP* screenBuffer;

    virtual void Draw();

    virtual void DrawViews();

public:
    Screen(int screenWidth, int screenHeight);

    virtual void Init(InputController* input) override = 0 ;

    virtual void Tick(float delta) override = 0;

    virtual void Destroy() override = 0;

    virtual void DrawToBuffer();

    virtual void Resize(int newX, int newY);

    ALLEGRO_BITMAP* const GetBuffer();

    void AddView(View* view);

    View* GetViewById(int id);
};


