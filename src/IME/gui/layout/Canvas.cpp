#include "IME/gui/layout/Canvas.h"

namespace IME::Gui {
    Canvas::Canvas(float x, float y) : Panel(x, y) {}

    bool Canvas::addElement(const std::string &alias, std::unique_ptr<UIElement> guiElement) {
        auto isElementInsidePanel = [&]{
            return guiElement->getPosition().x >= getPosition().x
                   && guiElement->getPosition().x <= getPosition().x + getDimensions().width
                   && guiElement->getPosition().y >= getPosition().y
                   && guiElement->getPosition().y <= getPosition().y + getDimensions().height
                   && guiElement->getSize().width <= getDimensions().width
                   && guiElement->getSize().height <= getDimensions().height;
        }();

        if (isElementInsidePanel)
            return add(alias, std::move(guiElement));
        return false;
    }
}
