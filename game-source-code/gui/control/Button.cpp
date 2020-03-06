#include "Button.h"
#include "input/Mouse.h"

Gui::Button::Button(const std::string &buttonText)
    : UIElement(buttonText),
      isSelected_(false)
{}

Gui::Button::Button(const std::string &content, const std::string &font, unsigned int textCharSize)
    : UIElement(content, font, textCharSize),
      isSelected_(false)
{}

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