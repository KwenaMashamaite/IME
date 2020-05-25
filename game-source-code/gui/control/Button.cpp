#include "Button.h"
#include "input/Mouse.h"

Gui::Button::Button() : Button("")
{}

Gui::Button::Button(const std::string& buttonText)
    : UIElement(buttonText),
      isSelected_(false)
{
    //Colours of the button when the mouse cursor enters it (may be changed)
    onHoverColours_.fillColour = {105, 105, 105}; //Dim gray
    onHoverColours_.TextColour = {169, 169, 169}; //Dark grey
    onHoverColours_.OutlineColour = {135,206,250}; //light sky blue

    //Colours of the button when the mouse cursor leaves it (May be changed)
    defaultColours_.fillColour = getFillColour();
    defaultColours_.TextColour = getTextFillColour();
    defaultColours_.OutlineColour = getOutlineColour();

    initializeEvents();
    initializeDefaultBehavior();
}

void Gui::Button::initializeEvents() {
    Window::addListener("mouseMoved", Callback<int, int>([this](int x, int y) {
        if (!isHidden()) {
            if (contains(x, y) && !isSelected_) {
                isSelected_ = true;
                emit("mouseEnter");
            } else if (!contains(x, y) && isSelected_) {
                isSelected_ = false;
                emit("mouseLeave");
            }
        }
    }));

    Window::addListener("mouseButtonPressed",  Callback<Mouse::Button>(
        [this](Mouse::Button button) {
            if (isSelected_ && button == Mouse::Button::LMouseButton && !isHidden())
                emit("mouseDown");
        })
    );

    Window::addListener("mouseButtonReleased", Callback<Mouse::Button>(
        [this](Mouse::Button button) {
            if (isSelected_ && button == Mouse::Button::LMouseButton && !isHidden())
                emit("mouseUp");
            })
    );

    addListener("mouseUp", Callback<>([this] {
        emit("click");
    }));
}

void Gui::Button::initializeDefaultBehavior() {
    addListener("mouseDown", Callback<>([this] {
        setFillColour({0, 0, 0, 0}); //Transparent
        setTextFillColour({0, 0, 0}); //Black
    }));

    addListener("click", Callback<>([this] {
        setFillColour(onHoverColours_.fillColour); //Back to hover colour, button not exited
        setTextFillColour(onHoverColours_.TextColour);
    }));

    addListener("mouseEnter", Callback<>([this] {
        defaultColours_.fillColour = getFillColour();
        defaultColours_.TextColour = getTextFillColour();
        defaultColours_.OutlineColour = getOutlineColour();
        setFillColour(onHoverColours_.fillColour);
        setTextFillColour(onHoverColours_.TextColour);
        setOutlineColour(onHoverColours_.OutlineColour);
    }));

    addListener("mouseLeave",Callback<>([this] {
        setFillColour(defaultColours_.fillColour);
        setTextFillColour(defaultColours_.TextColour);
        setOutlineColour(defaultColours_.OutlineColour);
    }));
}

void Gui::Button::setHoverFillColour(Gui::Colour fillColour) {
    onHoverColours_.fillColour = fillColour;
}

void Gui::Button::setHoverTextFillColour(Gui::Colour textFillColour) {
    onHoverColours_.TextColour = textFillColour;
}

void Gui::Button::setHoverOutlineColour(Gui::Colour outlineColour) {
    onHoverColours_.OutlineColour = outlineColour;
}
