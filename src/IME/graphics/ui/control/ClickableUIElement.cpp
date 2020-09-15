#include "IME/graphics/ui/control/ClickableUIElement.h"
#include "IME/core/input/Mouse.h"

namespace IME::Graphics::UI {
    ClickableUIElement::ClickableUIElement()
        : ClickableUIElement("")
    {}

    ClickableUIElement::ClickableUIElement(const std::string &text)
        : UIElement(text), isMouseOverElement_(false), isEnabled_(true)
    {
        initEvents();
    }

    void ClickableUIElement::initEvents() {
        addEventListener("leftMouseUp", Callback<>([this] {
            if (isMouseOverElement_)
                emit("click");
        }));

        addEventListener("hidden", Callback<>([this] {
            isEnabled_ = false;
            emit("disabled");
        }));

        addEventListener("shown", Callback<>([this] {
            setEnabled(true);
        }));

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

    void ClickableUIElement::handleEvent(sf::Event event) {
        UIElement::handleEvent(event);

        switch (event.type) {
            case sf::Event::MouseButtonPressed:
                if (isMouseOverElement_) {
                    auto pressedButton = static_cast<Input::Mouse::Button>(
                            static_cast<unsigned int>(event.mouseButton.button));
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
                break;
            case sf::Event::MouseButtonReleased:
                if (isMouseOverElement_) {
                    auto releasedButton = static_cast<Input::Mouse::Button>(
                            static_cast<unsigned int>(event.mouseButton.button));
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
                break;
            case sf::Event::MouseMoved:
                //Check if mouse cursor has entered element or left element after entering it
                if (auto x = event.mouseMove.x, y = event.mouseMove.y; !isHidden() && isEnabled()) {
                    if (contains(x, y) && !isMouseOverElement_) {
                        isMouseOverElement_ = true;
                        emit("mouseEnter");
                    } else if (!contains(x, y) && isMouseOverElement_) {
                        isMouseOverElement_ = false;
                        emit("mouseLeave");
                    }
                }
                break;
            case sf::Event::MouseLeft:
                if (isMouseOverElement_) {
                    isMouseOverElement_ = false;
                    emit("mouseLeave");
                }
                break;
            default:
                break;
        }
    }

    ClickableUIElement::~ClickableUIElement() = default;
}
