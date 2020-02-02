#include "StackPanel.h"

Gui::StackPanel::StackPanel(float x, float y, Orientation orientation)
        : Panel(x, y), orientation_(orientation)
{}

void Gui::StackPanel::addElement(std::shared_ptr<UIElement> guiElement) {
    auto inserted = add(guiElement);
    if (inserted) {
        if (size() == 1) { //Only one element in panel
            setDimensions({guiElement->getDimensions().width, guiElement->getDimensions().height});
            guiElement->setPosition(getPosition().x, getPosition().y);
        }else {
            switch (orientation_){
                case Orientation::Vertical:
                    guiElement->setPosition(lastInsertedElement()->getPosition().x, lastInsertedElement()->getPosition().y
                                            + lastInsertedElement()->getDimensions().height);
                    setDimensions({getDimensions().width, getDimensions().height + guiElement->getDimensions().height});
                    break;
                case Orientation::Horizontal:
                    guiElement->setPosition(lastInsertedElement()->getPosition().x + lastInsertedElement()->getDimensions().width,
                                            lastInsertedElement()->getPosition().y);
                    setDimensions({getDimensions().width + guiElement->getDimensions().width, getDimensions().height});
                    break;
            }
        }
    }
}