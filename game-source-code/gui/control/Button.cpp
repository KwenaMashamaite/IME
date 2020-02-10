#include "Button.h"
#include "event/IdHolder.h"
#include "input/InputManager.h"
#include "globals/Globals.h"

using Utility::IdHolder;
using Globals::Events;

Gui::Button::Button(const std::string &buttonText)
    : UIElement(buttonText),
      isSelected_(false)
{
    subscribeToEvents();
}

Gui::Button::Button(const std::string &content, const std::string &font, unsigned int textCharSize)
    : UIElement(content, font, textCharSize),
      isSelected_(false)
{
    subscribeToEvents();
}

void Gui::Button::subscribeToEvents() {
    IdHolder::add("mouseMoved", Events::mouseMoved.addListener(
        [this](int x, int y) {
            if (contains(x, y) && !isSelected_) {
                isSelected_ = true;
                mouseEnterEvent.notifyListeners();
            }else if (!contains(x, y) && isSelected_) {
                isSelected_ = false;
                mouseLeaveEvent.notifyListeners();
            }
        }
    ));

    IdHolder::add("mouseButtonPressed", Events::mouseButtonReleased.addListener(
        [this](InputManager::MouseButton releasedMouseButton, int x, int y){
            if (isSelected_ && releasedMouseButton == InputManager::MouseButton::LMouseButton)
                clickEvent.notifyListeners();
        }
    ));
}

Gui::Button::~Button() {
    Events::mouseMoved.removeListener(IdHolder::getIdFor("mouseMoved"));
    Events::mouseButtonReleased.removeListener(IdHolder::getIdFor("mouseButtonPressed"));
}
