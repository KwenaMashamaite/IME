#include "Button.h"
#include "input/Mouse.h"
#include <utility>

using Utility::IdHolder;
using Globals::Events;

Gui::Button::Button(const std::string &buttonText)
    : UIElement(buttonText),
      isSelected_(false)
{
    init();
}

Gui::Button::Button(const std::string &content, const std::string &font, unsigned int textCharSize)
    : UIElement(content, font, textCharSize),
      isSelected_(false)
{
    init();
}

void Gui::Button::init(){
    eventEmitter_.addEventListener("mouseMoved", Callback<int, int>([this](int x, int y) {
        if (contains(x, y) && !isSelected_) {
            isSelected_ = true;
            eventEmitter_.emit("mouseEnter");
        }else if (!contains(x, y) && isSelected_) {
            isSelected_ = false;
            eventEmitter_.emit("mouseLeave");
        }
    }));

    eventEmitter_.addEventListener("mouseButtonReleased", Callback<Mouse::Button>(
        [this](Mouse::Button button){
            if (isSelected_ && button == Mouse::Button::LMouseButton)
                eventEmitter_.emit("clicked");
        })
    );
}

void Gui::Button::on(std::string &&eventName, Callback<> callbackFunc) {
    eventEmitter_.addEventListener(std::forward<std::string&&>(eventName), std::move(callbackFunc));
}

void Gui::Button::setActive(bool isActive) {
    isSelected_ = false;

}