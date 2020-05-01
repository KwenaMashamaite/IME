#include "Button.h"
#include "input/Mouse.h"
#include <utility>

Gui::Button::Button() : Button("")
{}

Gui::Button::Button(const std::string& buttonText)
    : UIElement(buttonText),
      isSelected_(false),
      onHoverColour_({105, 105, 105}), //Dim gray
      onHoverTextColour_({169, 169, 169}), //Dark grey
      onHoverOutlineColour_({135,206,250}) //light sky blue
{
    initializeEvents();
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
                setFillColour({0, 0, 0, 0}); //Transparent
        })
    );

    Window::addListener("mouseButtonReleased", Callback<Mouse::Button>(
        [this](Mouse::Button button) {
            if (isSelected_ && button == Mouse::Button::LMouseButton && !isHidden()) {
                setFillColour(onHoverColour_);
                emit("click");
            }
        })
    );

    addListener("mouseEnter", Callback<>([this] {
        setFillColour(onHoverColour_);
        setTextFillColour(onHoverTextColour_);
        setOutlineColour(onHoverOutlineColour_);
    }));

    auto defaultFillColour = getFillColour();
    auto defaultTextColour = getTextFillColour();
    auto defaultOutlineColour = getOutlineColour();

    addListener("mouseLeave",Callback<>([=] {
        setFillColour(defaultFillColour);
        setTextFillColour(defaultTextColour);
        setOutlineColour(defaultOutlineColour);
    }));
}

void Gui::Button::setHoverFillColour(Gui::Colour fillColour) {
    onHoverColour_ = fillColour;
}

void Gui::Button::setHoverTextFillColour(Gui::Colour textFillColour) {
    onHoverTextColour_ = textFillColour;
}

void Gui::Button::setHoverOutlineColour(Gui::Colour outlineColour) {
    onHoverOutlineColour_ = outlineColour;
}
