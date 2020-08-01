#include "IME/gui/control/ClickableUIElement.h"
#include "IME/gui/input/Mouse.h"

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
        //Check if mouse cursor has entered element or left element after entering it
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

        // Notify event listeners when the the mouse is depressed while the
        // mouse cursor is over the element
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

        // notify event listeners when the mouse is released while the mouse
        // cursor is over the element.
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

        // Deselect UI element if it's selected and mouse cursor leaves application window
        Window::addEventListener("mouseLeft", Callback<>([this]{
            if (isMouseOverElement_) {
                isMouseOverElement_ = false;
                emit("mouseLeave");
            }
        }));

        // Notify event listeners when the element is clicked. A click event
        // always occur after a mouse up event, which occurs after a mouse
        // down event (mouseDown->mouseUp->click)
        addEventListener("leftMouseUp", Callback<>([this] {
            emit("click");
        }));

        // Disable the element when its hidden. A hidden element must not be
        // interacted with using the mouse cursor. Disabling it prevents the
        // element from receiving events while it is hidden
        addEventListener("hidden", Callback<>([this] {
            isEnabled_ = false;
            emit("disabled");
        }));

        // Enable the element when its shown. This allows the element to
        // receive events, thus allowing interaction with the mouse cursor
        addEventListener("shown", Callback<>([this] {
            setEnabled(true);
        }));

        // Publish a mouse leave event when the element is disabled and the
        // mouse cursor is over the element. This forces the mouse to leave
        // the element even though graphically the mouse is still over the
        // element
        addEventListener("disabled", Callback<>([this] {
            if (isMouseOverElement_) {
                isMouseOverElement_ = false;
                emit("mouseLeave");
            }
        }));
    }

    void ClickableUIElement::setEnabled(bool isEnable) {
        if (isEnabled_ != isEnable && !isHidden()) {
            isEnabled_ = isEnable;
            if (isEnabled_)
                emit("enabled");
            else
                emit("disabled");
        }
    }

    void ClickableUIElement::toggleEnabled() {
        setEnabled(!isEnabled());
    }

    bool ClickableUIElement::isEnabled() const{
        return isEnabled_;
    }

    bool ClickableUIElement::isMouseOverElement() const {
        return isMouseOverElement_;
    }

    ClickableUIElement::~ClickableUIElement() = default;
}
