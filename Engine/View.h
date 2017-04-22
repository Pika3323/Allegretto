//
// Created by derek on 3/27/2017.
//

#pragma once

#include "Engine.h"

enum class ECursor : uint8_t;

/**
 * A View is a class that represents a "View" or user interface component that can be drawn on screen.
 * The View class is a general class for all User Interface component classes.
 */
class View {
    /**
     * The integer id of this View in the global layout.
     */
    int id;

    /**
     * The width of this View
     */
    float width = 0.f;

    /**
     * The height of this VIew
     */
    float height = 0.f;

    /**
     * The position of this view on screen
     */
    Vector2D position;

    /**
     * The internal top padding of the View.
     * Will be added to the height of the View.
     */
    float paddingTop = 0.f;

    /**
     * The internal right padding of the View.
     * Will be added to the width of the View.
     */
    float paddingRight = 0.f;

    /**
     * The internal bottom padding of the View.
     * Will be added to the height of the View.
     */
    float paddingBottom = 0.f;

    /**
     * The internal left padding of the View.
     * Will be added to the width of the View.
     */
    float paddingLeft = 0.f;

    /**
     * The radius of the rounded corners for the background of the View
     */
    float cornerRadius = 0.f;

    /**
     * The delegate to a method which should be called when this View is called
     */
    Delegate<void(class View*)>* onClickDelegate = nullptr;

    /**
     * The delegate to a method which should be called when the mouse hovers over this View
     */
    OtherMouseInputDelegate* onHoverDelegate = nullptr;

    /**
     * The underlying texture for the View
     */
    ALLEGRO_BITMAP* texture;

    /**
     * The background texture for the view.
     */
    ALLEGRO_BITMAP* background;

    /**
     * The colour of the background
     */
    Colour backgroundColour = Colour::TRANSPARENT;

    /**
     * The type of cursor to display when the user mouses over this view
     */
    ECursor cursor = ECursor(1);

    /**
     * Re-sizes the image textures handling the backgrounds
     */
    void ResizeTextures();

public:
    /**
     * Constructor
     * @param bounds The bounds of the view. Represents the size and position of the bound.
     */
    explicit View(Bound2D bounds);

    View(Vector2D position, float width, float height);

    /**
     * Copy constructor
     */
    View(const View& view);

    /**
     * Destructor
     */
    virtual ~View();

    /**
     * Copy assignment operator
     */
    View& operator=(const View& view);

    /**
     * Get the drawn height of the View
     * @version
     * @return Height of the View
     */
    float GetHeight();

    /**
     * Sets the drawing height of the View
     * @param The new height of the View
     */
    void SetHeight(float height);

    /**
     * Get the drawn width of the View
     * @return Width of the View
     */
    float GetWidth();

    /**
     * Sets the drawing width of the View
     * @param The new width of the View
     */
    void SetWidth(float width);

    /**
     * Sets the position on screen of the View
     * @param position The new position of the View
     */
    void SetPosition(Vector2D position);

    /**
     * Gets the position of this View on the screen
     * @return The position of the view
     */
    Vector2D GetPosition();

    /**
     * Gets the bounds of the View on the screen
     * @return The View's bounds
     */
    Bound2D GetBounds();

    /**
     * Gets a constant reference to the View's texture
     * @return The View's texture
     */
    ALLEGRO_BITMAP* const GetTexture();

    /**
     * Binds the OnClick event of this view to an object's method
     * @tparam T The type of object being bound (automatically deduced
     * @param object The object to bind the method for
     * @param ptr The pointer to the object's method
     */
    template <typename T>
    void BindOnClickDelegate(T* object, void (T::*ptr)(View*)) {
        onClickDelegate = new Delegate<void(class View*)>(object, ptr);
    }

    template<typename T>
    void BindOnHoverDelegate(T* object, void (T::*ptr)(EMouseEvent, int, int)) {
        onHoverDelegate = new OtherMouseInputDelegate(object, ptr, GetBounds());
    }

    /**
     * Draws the View onto the underlying texture so that it can be then drawn to the screen
     */
    virtual void Draw();

    /**
     * Sets the background of this view to a predefined texture
     * @param background The new background texture
     */
    void SetBackground(ALLEGRO_BITMAP* background);

    /**
     * Sets the background of this view to a solid colour
     * @param colour The colour to set the background to
     */
    void SetBackgroundColour(Colour colour);

    /**
     * Get the integer id for this View
     * @return The id of the View
     */
    int GetId();

    /**
     * Sets the id for the view
     * @param id The id to be set
     */
    void SetId(int id);

    /**
     * Dispatch the method bound in onClickDelegate
     */
    void OnClick();

    /**
     * Dispatch the method bound in onHoverDelegate
     */
     void OnHover(EMouseEvent event, int x, int y);

    /**
     * Sets the padding of the View
     * @param top The top padding
     * @param right The right padding
     * @param bottom The bottom padding
     * @param left The left padding
     */
    void SetPadding(float top, float right, float bottom, float left);

    /**
     * Sets the padding for all sides of the View
     * @param padding The padding to assign to all sides
     */
    void SetPadding(float padding);

    /**
     * Sets the padding for the top side of the View
     * @param paddingTop The padding to set the top of the View
     */
    void SetPaddingTop(float paddingTop);

    /**
     * Sets the padding for the right side of the View
     * @param paddingRight The padding to set the right of the View
     */
    void SetPaddingRight(float paddingRight);

    /**
     * Sets the padding for the bottom side of the View
     * @param paddingBottom The padding to set the bottom of the View
     */
    void SetPaddingBottom(float paddingBottom);

    /**
     * Sets the padding for the left side of the View
     * @param paddingLeft The padding to set the left of the View
     */
    void SetPaddingLeft(float paddingLeft);

    /**
     * Gets the padding for the top of the View
     * @return The padding on the top of the View
     */
    float GetPaddingTop();

    /**
     * Gets the padding for the right of the View
     * @return The padding on the right of the View
     */
    float GetPaddingRight();

    /**
     * Gets the padding for the bottom of the View
     * @return The padding on the bottom of the View
     */
    float GetPaddingBottom();

    /**
     * Gets the padding for the left of the View
     * @return The padding on the left of the View
     */
    float GetPaddingLeft();

    /**
     * Gets the rounded corner radius of the view's background
     * @return The radius of the corners
     */
    float GetCornerRadius();

    /**
     * Sets the radius of the corners of the View
     * @param cornerRadius The radius to set it to
     */
    void SetCornerRadius(float cornerRadius);

    /**
     * Gets the cursor for the view
     * @return The view's cursor
     */
    ECursor GetCursor();

    /**
     * Sets the cursor to be displayed when the user mouses over thisv  iew
     * @param cursor The type of cursor
     */
    void SetCursor(ECursor cursor);
};

