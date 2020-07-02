#include "ClickableUIElement.h"
#include "../input/Mouse.h"

Gui::ClickableUIElement::ClickableUIElement()
    : ClickableUIElement("")
{}

Gui::ClickableUIElement::ClickableUIElement(const std::string &text)
    : UIElement(text), isSelected_(false), isEnabled_(true)
{
    initEvents();
}

void Gui::ClickableUIElement::initEvents() {
    //Check if mouse cursor has entered element or not
    Window::addEventListener("mouseMoved",Callback<int, int>([this](int x, int y) {
        if (!isHidden() && isEnabled()) {
            if (contains(x, y) && !isSelected()) {
                setSelected(true);
                emit("mouseEnter");
            } else if (!contains(x, y) && isSelected()) {
                setSelected(false);
                emit("mouseLeave");
            }
        }
    }));

    //Notify event listeners when the element is pressed
    Window::addEventListener("mouseButtonPressed", Callback<Mouse::Button>(
        [this](Mouse::Button pressedButton) {
            if (isSelected() && isEnabled()) {
                switch (pressedButton) {
                    case Mouse::Button::Left:
                        emit("leftMouseDown");
                        break;
                    case Mouse::Button::Right:
                        emit("rightMouseDown");
                        break;
                    case Mouse::Button::Middle:
                        emit("middleMouseDown");
                        break;
                }
            }
        }
    ));

    //notify event listeners when the element is released
    Window::addEventListener("mouseButtonReleased", Callback<Mouse::Button>(
        [this](Mouse::Button releasedButton) {
            if (isSelected() && isEnabled()) {
                switch (releasedButton) {
                    case Mouse::Button::Left:
                        emit("leftMouseUp");
                        break;
                    case Mouse::Button::Right:
                        emit("rightMouseUp");
                        break;
                    case Mouse::Button::Middle:
                        emit("middleMouseUp");
                        break;
                }
            }
        }
    ));

    //Notify event listeners when the element is clicked. A click event always occurs
    //after a mouse up event, which occurs after a mouse down event
    //(mouseDown->mouseUp->click)
    addEventListener("leftMouseUp", Callback<>([this] {
        emit("click");
    }));


    //Automatically disable/enable the element when its visibility state changes.
    //A user must not interact with a hidden element
    addEventListener("visibilityChanged", Callback<bool>([this](bool isHidden) {
        setEnabled(!isHidden);
    }));
}

void Gui::ClickableUIElement::setEnabled(bool isEnable) {
    isEnabled_ = isEnable;
    emit("interactivityChanged", isEnabled_);
}

void Gui::ClickableUIElement::setSelected(bool isSelected) {
    isSelected_ = isSelected;
    emit("selectionChanged", isSelected_);
}

bool Gui::ClickableUIElement::isEnabled() const{
    return isEnabled_;
}

bool Gui::ClickableUIElement::isSelected() const {
    return isSelected_;
}

Gui::ClickableUIElement::~ClickableUIElement() = default;
