#include "Canvas.h"

Gui::Canvas::Canvas(float x, float y) : Panel(x, y) {}

void Gui::Canvas::addElement(std::shared_ptr<UIElement> guiElement) {
    auto elementOverlapsWithPanel = [=](){
        return guiElement->getPosition().x >= getPosition().x
               && guiElement->getPosition().x <= getPosition().x + getDimensions().width
               && guiElement->getPosition().y >= getPosition().y
               && guiElement->getPosition().y <= getPosition().y + getDimensions().height;
    };

    if (elementOverlapsWithPanel())
        add(std::move(guiElement));
}
