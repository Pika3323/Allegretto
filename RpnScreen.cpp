//
// Created by derek on 3/24/2017.
//

#include "RpnScreen.h"
#include "LifeScreen.h"
#include "Engine/Views/TextView.h"

void RpnScreen::Init(InputController *input) {
    input->RegisterKeyboardInput(ALLEGRO_KEY_K, this, &RpnScreen::switchScreens);

    // Adds all the text boxes and buttons for displaying the numbers and buttons
    for (int i = 9; i > 0; i--) {
        // Thanks John
        TextView* button = new TextView(Vector2D(52 * (((i - 1) % 3) + 1), 52 * ((9 - i) / 3)));
        button->SetId(i);
        button->SetFont(new Font("Roboto-Regular.ttf"));
        button->SetTextColour(Colour::BLACK);
        button->SetPadding(8);
        button->SetPaddingLeft(12);
        button->SetPaddingRight(12);
        button->SetCursor(ECursor::Link);
        button->SetText(std::to_string(i));
        button->BindOnClickDelegate(this, &RpnScreen::PressKey);
        button->SetBackgroundColour(Colour::WHITE);

        AddView(button);
    }

    TextView* addButton = new TextView(Vector2D(0, 0));
    addButton->SetId(RpnScreen::ADD_BUTTON);
    addButton->SetFont(new Font("Roboto-Regular.ttf"));
    addButton->SetTextColour(Colour::BLACK);
    addButton->SetPadding(8);
    addButton->SetPaddingLeft(12);
    addButton->SetPaddingRight(12);
    addButton->SetCursor(ECursor::Link);
    addButton->SetText("+");
    addButton->BindOnClickDelegate(this, &RpnScreen::PressKey);
    addButton->SetBackgroundColour(Colour::WHITE);
    AddView(addButton);

    TextView* subtractButton = new TextView(Vector2D(0, 52));
    subtractButton->SetId(RpnScreen::SUBTRACT_BUTTON);
    subtractButton->SetFont(new Font("Roboto-Regular.ttf"));
    subtractButton->SetTextColour(Colour::BLACK);
    subtractButton->SetPadding(8);
    subtractButton->SetPaddingLeft(12);
    subtractButton->SetPaddingRight(12);
    subtractButton->SetCursor(ECursor::Link);
    subtractButton->SetText("-");
    subtractButton->BindOnClickDelegate(this, &RpnScreen::PressKey);
    subtractButton->SetBackgroundColour(Colour::WHITE);
    AddView(subtractButton);

    TextView* multiplyButton = new TextView(Vector2D(0, 104));
    multiplyButton->SetId(RpnScreen::MULTIPLY_BUTTON);
    multiplyButton->SetFont(new Font("Roboto-Regular.ttf"));
    multiplyButton->SetTextColour(Colour::BLACK);
    multiplyButton->SetPadding(8);
    multiplyButton->SetPaddingLeft(12);
    multiplyButton->SetPaddingRight(12);
    multiplyButton->SetCursor(ECursor::Link);
    multiplyButton->SetText("X");
    multiplyButton->BindOnClickDelegate(this, &RpnScreen::PressKey);
    multiplyButton->SetBackgroundColour(Colour::WHITE);
    AddView(multiplyButton);

    TextView* divideButton = new TextView(Vector2D(0, 156));
    divideButton->SetId(RpnScreen::DIVIDE_BUTTON);
    divideButton->SetFont(new Font("Roboto-Regular.ttf"));
    divideButton->SetTextColour(Colour::BLACK);
    divideButton->SetPadding(8);
    divideButton->SetPaddingLeft(12);
    divideButton->SetPaddingRight(12);
    divideButton->SetCursor(ECursor::Link);
    divideButton->SetText("/");
    divideButton->BindOnClickDelegate(this, &RpnScreen::PressKey);
    divideButton->SetBackgroundColour(Colour::WHITE);
    AddView(divideButton);

    TextView* resultBox = new TextView(Vector2D(250, 52));
    resultBox->SetId(101);
    resultBox->SetFont(new Font("Roboto-Regular.ttf"));
    resultBox->SetTextColour(Colour::WHITE);
    resultBox->SetPadding(8);
    resultBox->SetPaddingLeft(12);
    resultBox->SetPaddingRight(12);
    resultBox->SetCursor(ECursor::Link);
    resultBox->BindOnClickDelegate(this, &RpnScreen::PressKey);
    AddView(resultBox);

    TextView* otherResultBox = new TextView(Vector2D(250, 0));
    otherResultBox->SetId(102);
    otherResultBox->SetFont(new Font("Roboto-Regular.ttf"));
    otherResultBox->SetTextColour(Colour::WHITE);
    otherResultBox->SetPadding(8);
    otherResultBox->SetPaddingLeft(12);
    otherResultBox->SetPaddingRight(12);
    otherResultBox->SetCursor(ECursor::Link);
    otherResultBox->BindOnClickDelegate(this, &RpnScreen::PressKey);
    AddView(otherResultBox);

    TextView* enterButton = new TextView(Vector2D(130, 156));
    enterButton->SetId(RpnScreen::ENTER_BUTTON);
    enterButton->SetFont(new Font("Roboto-Regular.ttf"));
    enterButton->SetTextColour(Colour::BLACK);
    enterButton->SetPadding(8);
    enterButton->SetText("Enter");
    enterButton->SetPaddingLeft(12);
    enterButton->SetPaddingRight(12);
    enterButton->SetBackgroundColour(Colour::WHITE);
    enterButton->SetCursor(ECursor::Link);
    enterButton->BindOnClickDelegate(this, &RpnScreen::PressKey);
    AddView(enterButton);

    TextView* zeroButton = new TextView(Vector2D(52, 156));
    zeroButton->SetId(0);
    zeroButton->SetFont(new Font("Roboto-Regular.ttf"));
    zeroButton->SetTextColour(Colour::BLACK);
    zeroButton->SetPadding(8);
    zeroButton->SetText("0");
    zeroButton->SetPaddingLeft(12);
    zeroButton->SetPaddingRight(12);
    zeroButton->SetBackgroundColour(Colour::WHITE);
    zeroButton->SetCursor(ECursor::Link);
    zeroButton->BindOnClickDelegate(this, &RpnScreen::PressKey);
    AddView(zeroButton);
}

void RpnScreen::switchScreens() {
    GEngine->SetActiveScreen(new LifeScreen(width, height));
}

void RpnScreen::PressKey(class View *view) {
    switch (view->GetId()) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            // Add the pressed button to the number
            currentInput *= 10;
            currentInput += view->GetId();
            ((TextView*) GetViewById(102))->SetText(std::to_string(stack.display()));
            ((TextView*) GetViewById(101))->SetText(std::to_string(currentInput));
            break;
        case RpnScreen::ADD_BUTTON:
            // Adds two values
            if (stack.getTopIndex() > 0) {
                stack.add();
                ((TextView*) GetViewById(102))->SetText(std::to_string(stack[stack.getTopIndex() - 1]));
                ((TextView*) GetViewById(101))->SetText(std::to_string(stack.display()));
            }
            break;
        case RpnScreen::SUBTRACT_BUTTON:
            // Subtracts two buttons
            if (stack.getTopIndex() > 0) {
                stack.subtract();
                ((TextView*) GetViewById(102))->SetText(std::to_string(stack[stack.getTopIndex() - 1]));
                ((TextView*) GetViewById(101))->SetText(std::to_string(stack.display()));
            }
            break;
        case RpnScreen::MULTIPLY_BUTTON:
            if (stack.getTopIndex() > 0) {
                stack.multiply();
                ((TextView*) GetViewById(102))->SetText(std::to_string(stack[stack.getTopIndex() - 1]));
                ((TextView*) GetViewById(101))->SetText(std::to_string(stack.display()));
            }
            break;
        case RpnScreen::DIVIDE_BUTTON:
            if (stack.getTopIndex() > 0) {
                stack.divide();
                ((TextView*) GetViewById(102))->SetText(std::to_string(stack[stack.getTopIndex() - 1]));
                ((TextView*) GetViewById(101))->SetText(std::to_string(stack.display()));
            }
            break;
        case RpnScreen::ENTER_BUTTON:
            if (stack.getTopIndex() < 19) {
                // Push the numerical value onto the stack
                stack.push(currentInput);
                ((TextView*) GetViewById(102))->SetText(std::to_string(stack[stack.getTopIndex() - 1]));
                ((TextView*) GetViewById(101))->SetText(std::to_string(stack.display()));
            }
            currentInput = 0;
        default:
            break;
    }
}

void RpnScreen::Draw() {
    Screen::Draw();
}
