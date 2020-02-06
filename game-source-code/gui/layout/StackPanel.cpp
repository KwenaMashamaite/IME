#include "StackPanel.h"

Gui::StackPanel::StackPanel(float x, float y, Orientation orientation)
        : Panel(x, y), orientation_(orientation)
{}

void Gui::StackPanel::addElement(std::shared_ptr<UIElement> guiElement) {
    auto inserted = add(guiElement);
    if (inserted) {
        if (size() == 1) {
            setDimensions({guiElement->getDimensions().width, guiElement->getDimensions().height});
            guiElement->setPosition(getPosition().x, getPosition().y);
        }else {
            auto newWidth = 0u, newHeight = 0u;
            switch (orientation_){
                case Orientation::Vertical:
                    guiElement->setPosition(lastInsertedElement_->getPosition().x, lastInsertedElement_->getPosition().y
                                            + lastInsertedElement_->getDimensions().height);
                    newWidth = guiElement->getDimensions().width > lastInsertedElement_->getDimensions().width
                               ? guiElement->getDimensions().width : lastInsertedElement_->getDimensions().width;
                    setDimensions({newWidth, getDimensions().height + guiElement->getDimensions().height});
                    break;
                case Orientation::Horizontal:
                    guiElement->setPosition(lastInsertedElement_->getPosition().x + lastInsertedElement_->getDimensions().width,
                                            lastInsertedElement_->getPosition().y);
                    newHeight = guiElement->getDimensions().height > lastInsertedElement_->getDimensions().height
                               ? guiElement->getDimensions().height : lastInsertedElement_->getDimensions().height;
                    setDimensions({getDimensions().width + guiElement->getDimensions().width, newHeight});
                    break;
            }
        }
        lastInsertedElement_ = std::move(guiElement);
    }
}