//
// Created by derek on 3/27/2017.
//

#include "View.h"
#include "Engine.h"

View::View(Bound2D bounds)
        : position(bounds.upper), height(bounds.lower.y - bounds.upper.y), width(bounds.lower.x - bounds.upper.x){
    View(position, width, height);
}
View::View(Vector2D position, float width, float height) : position(position), width(width), height(height) {
    ResizeTextures();
}


float View::GetWidth() {
    return width + paddingLeft + paddingRight;
}

float View::GetHeight() {
    return height + paddingTop + paddingBottom;
}

void View::SetHeight(float height) {
    View::height = height;

    ResizeTextures();
}

void View::SetWidth(float width) {
    View::width = width;

    ResizeTextures();
}

void View::SetPosition(Vector2D position) {
    View::position = position;
}

void View::OnClick() {
    if (onClickDelegate) {
        onClickDelegate->Call(this);
    }
}

View::~View() {
    al_destroy_bitmap(texture);
    delete onClickDelegate;
    delete onHoverDelegate;
}

Vector2D View::GetPosition() {
    return position;
}

ALLEGRO_BITMAP* const View::GetTexture()  {
    return texture;
}

void View::Draw() {
    al_set_target_bitmap(texture);

    al_clear_to_color(Colour::TRANSPARENT);

    al_draw_bitmap(background, 0, 0, 0);
}

void View::SetBackground(ALLEGRO_BITMAP* background)  {
    al_set_target_bitmap(View::background);
    al_draw_bitmap(background, 0, 0, 0);
}

void View::SetBackgroundColour(Colour colour) {
    View::backgroundColour = colour;
    al_set_target_bitmap(View::background);

    al_clear_to_color(Colour::TRANSPARENT);

    al_draw_filled_rounded_rectangle(0, 0, GetWidth(), GetHeight(), cornerRadius, cornerRadius, backgroundColour);
}

int View::GetId() {
    return id;
}

void View::SetId(int id) {
    View::id = id;
}

Bound2D View::GetBounds() {
    return Bound2D(position, position + Vector2D(GetWidth(), GetHeight()));
}

void View::SetPaddingTop(float paddingTop) {
    View::paddingTop = paddingTop;
    ResizeTextures();
}

void View::SetPaddingRight(float paddingRight) {
    View::paddingRight = paddingRight;
    ResizeTextures();
}

void View::SetPaddingBottom(float paddingBottom) {
    View::paddingBottom = paddingBottom;
    ResizeTextures();
}

void View::SetPaddingLeft(float paddingLeft) {
    View::paddingLeft = paddingLeft;
    ResizeTextures();
}

void View::SetPadding(float top, float right, float bottom, float left) {
    paddingTop = top;
    paddingRight = right;
    paddingBottom = bottom;
    paddingLeft = left;

    ResizeTextures();
}

void View::ResizeTextures() {
    // Destroy the old textures
    if (!texture) {
        al_destroy_bitmap(texture);
    }

    if (!background) {
        al_destroy_bitmap(background);
    }

    // Create a new texture with the new size
    texture = al_create_bitmap((int) GetWidth(), (int) GetHeight());
    background = al_create_bitmap((int) GetWidth(), (int) GetHeight());
}

void View::SetPadding(float padding) {
    paddingTop = padding;
    paddingBottom = padding;
    paddingRight = padding;
    paddingLeft = padding;

    ResizeTextures();
}

float View::GetPaddingTop() {
    return paddingTop;
}

float View::GetPaddingRight() {
    return paddingRight;
}

float View::GetPaddingBottom() {
    return paddingBottom;
}

float View::GetPaddingLeft() {
    return paddingLeft;
}

float View::GetCornerRadius() {
    return cornerRadius;
}

void View::SetCornerRadius(float cornerRadius) {
    View::cornerRadius = cornerRadius;
    SetBackgroundColour(backgroundColour);
}

void View::OnHover(EMouseEvent event, int x, int y) {
    if (onHoverDelegate) {
        onHoverDelegate->Call(event, x, y);
    }

    if (GEngine) {
        if (event == EMouseEvent::Enter) {
            GEngine->SetCursor(cursor);
        } else if (event == EMouseEvent::Exit) {
            GEngine->SetCursor(ECursor::Default);
        }
    }
}

ECursor View::GetCursor() {
    return cursor;
}

void View::SetCursor(ECursor cursor) {
    View::cursor = cursor;
}
