#include "ClickableUIElement.h"
#include "globals/Globals.h"
#include "input/InputManager.h"
#include "event/IdHolder.h"

using Utility::IdHolder;
using Globals::Events;

Gui::ClickableUIElement::ClickableUIElement(const std::string &content) 
    : UIElement(content), isSelected_(false) 
{
    subscribeToEvents();
}

Gui::ClickableUIElement::ClickableUIElement(const std::string &content, 
    const std::string &font, 
    unsigned int textCharSize) 
    : UIElement(content, font, textCharSize), 
      isSelected_(false)
{
    subscribeToEvents();
}

void Gui::ClickableUIElement::subscribeToEvents() {
    IdHolder::add("mouseMoved", Events::mouseMoved.addListener(
        [this](int x, int y) {
            if (contains(x, y) && !isSelected_) {
                isSelected_ = true;
                mouseEnterEvent.notifyListeners();
            }else if (!contains(x, y) && isSelected_) {
                isSelected_ = false;
                mouseLeaveEvent.notifyListeners();
            }
        })
    );

    IdHolder::add("mouseButtonPressed", Events::mouseButtonReleased.addListener(
        [this](InputManager::MouseButton releasedMouseButton, int x, int y){
            if (isSelected_ && releasedMouseButton == InputManager::MouseButton::LMouseButton)
                clickEvent.notifyListeners();
        })
    );
}

Gui::ClickableUIElement::~ClickableUIElement(){
    Events::mouseMoved.removeListener(IdHolder::getIdFor("mouseMoved"));
    Events::mouseButtonReleased.removeListener(IdHolder::getIdFor("mouseButtonPressed"));
}