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
    instantiationNum_ = std::to_string(numOfInstantiations_++);
    subscribeToEvents();
}

Gui::Button::Button(const std::string &content, const std::string &font, unsigned int textCharSize)
    : UIElement(content, font, textCharSize),
      isSelected_(false)
{
    instantiationNum_ = std::to_string(numOfInstantiations_++);
    subscribeToEvents();
}

void Gui::Button::subscribeToEvents() {
    IdHolder::add(
        "mouseMoved-BtnClass" + instantiationNum_,
        Events::mouseMoved.addListener(
            [this](int x, int y) {
                if (contains(x, y) && !isSelected_) {
                    isSelected_ = true;
                    mouseEnterEvent.notifyListeners();
                }else if (!contains(x, y) && isSelected_) {
                    isSelected_ = false;
                    mouseLeaveEvent.notifyListeners();
                }
            }
        )
    );

    IdHolder::add(
        "mouseBtnPressed-BtnClass" + instantiationNum_,
        Events::mouseButtonReleased.addListener(
            [this](InputManager::MouseButton releasedMouseButton, int x, int y){
                if (isSelected_ && releasedMouseButton == InputManager::MouseButton::LMouseButton)
                    clickEvent.notifyListeners();
            }
        )
    );
}

void Gui::Button::setActive(bool isActive) {
    isSelected_ = false;
    Events::mouseMoved.setNotificationPause(
        isActive, 
        IdHolder::getIdFor("mouseMoved-BtnClass" + instantiationNum_)
    );
    Events::mouseButtonReleased.setNotificationPause(
        isActive, 
        IdHolder::getIdFor("mouseBtnPressed-BtnClass" + instantiationNum_)
    );
}

Gui::Button::~Button() {
    Events::mouseMoved.removeListener(
        IdHolder::getIdFor("mouseMoved-BtnClass" + instantiationNum_)
    );
    Events::mouseButtonReleased.removeListener(
        IdHolder::getIdFor("mouseBtnPressed-BtnClass" + instantiationNum_)
    );
}