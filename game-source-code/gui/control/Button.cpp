#include "Button.h"
#include "gui/window/Window.h"
#include "input/Mouse.h"
#include <utility>

Gui::Button::Button()
    : isSelected_(false),
      mouseEnterCallbackId_(-1),
      mouseLeaveCallbackId_(-1)
{
    subscribeToEvents();
    initDefaultBehavior();
}

Gui::Button::Button(const std::string& buttonText)
    : UIElement(buttonText),
      isSelected_(false),
      mouseEnterCallbackId_(-1),
      mouseLeaveCallbackId_(-1)
{
    subscribeToEvents();
    initDefaultBehavior();
}

void Gui::Button::subscribeToEvents() {
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

    Window::addListener("mouseButtonReleased", Callback<Mouse::Button>(
        [this](Mouse::Button button) {
            if (isSelected_ && button == Mouse::Button::LMouseButton && !isHidden())
                emit("click");
        })
    );
}

void Gui::Button::initDefaultBehavior() {
    auto defaultButtonColour = getFillColour();
    auto defaultButtonTextColour = getTextFillColour();
    auto onHoverButtonColour = Gui::Colour{12, 241, 252};
    auto onHoverButtonTextColour = Gui::Colour{88, 175, 232};

    mouseEnterCallbackId_ = addListener("mouseEnter", Callback<>([=](){
        setFillColour(onHoverButtonColour);
        setTextFillColour(onHoverButtonTextColour);
    }));

    mouseLeaveCallbackId_ = addListener("mouseLeave",Callback<>([=](){
        setFillColour(defaultButtonColour);
        setTextFillColour(defaultButtonTextColour);
    }));
}

void Gui::Button::removeDefaultBehavior() {
    removeListener("mouseEnter", mouseEnterCallbackId_);
    removeListener("mouseLeave", mouseLeaveCallbackId_);
}
