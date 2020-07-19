#include "ClickableUIElement.h"
#include "../input/Mouse.h"

namespace IME::Gui{
    ClickableUIElement::ClickableUIElement()
        : ClickableUIElement("")
    {}

    ClickableUIElement::ClickableUIElement(const std::string &text)
        : UIElement(text), isMouseOverElement_(false), isEnabled_(true)
    {
        initEvents();
    }

    void ClickableUIElement::initEvents() {
        //Check if mouse cursor has entered element or not
        Window::addEventListener("mouseMoved",Callback<int, int>([this](int x, int y) {
            if (!isHidden() && isEnabled()) {
                if (contains(x, y) && !isMouseOverElement_) {
                    isMouseOverElement_ = true;
                    emit("mouseEnter");
                } else if (!contains(x, y) && isMouseOverElement_) {
                    isMouseOverElement_ = false;
                    emit("mouseLeave");
                }
            }
        }));

        //Notify event listeners when the element is pressed
        Window::addEventListener("mouseButtonPressed", Callback<Input::Mouse::Button>(
            [this](Input::Mouse::Button pressedButton) {
                if (isMouseOverElement_) {
                    switch (pressedButton) {
                        case Input::Mouse::Button::Left:
                            emit("leftMouseDown");
                            break;
                        case Input::Mouse::Button::Right:
                            emit("rightMouseDown");
                            break;
                        case Input::Mouse::Button::Middle:
                            emit("middleMouseDown");
                            break;
                    }
                }
            }
        ));

        //notify event listeners when the element is released
        Window::addEventListener("mouseButtonReleased", Callback<Input::Mouse::Button>(
            [this](Input::Mouse::Button releasedButton) {
                if (isMouseOverElement_) {
                    switch (releasedButton) {
                        case Input::Mouse::Button::Left:
                            emit("leftMouseUp");
                            break;
                        case Input::Mouse::Button::Right:
                            emit("rightMouseUp");
                            break;
                        case Input::Mouse::Button::Middle:
                            emit("middleMouseUp");
                            break;
                    }
                }
            }
        ));

        //Deselect UI element if it's selected and mouse cursor leaves window
        Window::addEventListener("mouseLeft", Callback<>([this]{
            if (isMouseOverElement_) {
                isMouseOverElement_ = false;
                emit("mouseLeave");
            }
        }));

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

    void ClickableUIElement::setEnabled(bool isEnable) {
        if (isEnabled_ != isEnable) {
            if (!isEnable && isMouseOverElement_) {
                isMouseOverElement_ = false;
                emit("mouseLeave");
            }
            isEnabled_ = isEnable;
            emit("interactivityChanged", isEnabled_);
        }
    }

    void ClickableUIElement::toggleEnabled() {
        setEnabled(!isEnabled());
    }

    bool ClickableUIElement::isEnabled() const{
        return isEnabled_;
    }

    ClickableUIElement::~ClickableUIElement() = default;
}
