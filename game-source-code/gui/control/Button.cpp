#include "Button.h"
#include "input/Mouse.h"

Gui::Button::Button(const std::string &buttonText)
    : UIElement(buttonText),
      isSelected_(false)
{
    initDefaultBehavior();
}

Gui::Button::Button(const std::string &content, const std::string &font, unsigned int textCharSize)
    : UIElement(content, font, textCharSize),
      isSelected_(false)
{
    initDefaultBehavior();
}

void Gui::Button::initialize(SystemEventEmitter &systemEventEmitter) {
    systemEventEmitter.addListener("mouseMoved", Callback<int, int>([this](int x, int y) {
        if (contains(x, y) && !isSelected_) {
            isSelected_ = true;
            eventEmitter_.emit("mouseEnter");
        } else if (!contains(x, y) && isSelected_) {
            isSelected_ = false;
            eventEmitter_.emit("mouseLeave");
        }
    }));

    systemEventEmitter.addListener("mouseButtonReleased", Callback<Mouse::Button>(
        [this](Mouse::Button button) {
            if (isSelected_ && button == Mouse::Button::LMouseButton)
                eventEmitter_.emit("click");
        })
    );
}

void Gui::Button::on(std::string &&eventName, Callback<> callbackFunc) {
    eventEmitter_.addListener(std::forward<std::string&&>(eventName), std::move(callbackFunc));
}

void Gui::Button::initDefaultBehavior() {
    auto onHoverButtonColour = Gui::Colour{12, 241, 252};
    auto onHoverButtonTextColour = Gui::Colour{88, 175, 232};

    mouseEnterCallbackId_ = eventEmitter_.addListener("mouseEnter", Callback<>([=](){
        setFillColour(onHoverButtonColour);
        setTextFillColour(onHoverButtonTextColour);
    }));

    mouseLeaveCallbackId_ = eventEmitter_.addListener("mouseLeave",Callback<>([=](){
        setFillColour(getFillColour());
        setTextFillColour(getTextFillColour());
    }));
}

void Gui::Button::clearDefaultBehavior() {
    eventEmitter_.removeListener("mouseEnter", mouseEnterCallbackId_);
    eventEmitter_.removeListener("mouseLeave", mouseLeaveCallbackId_);
}
