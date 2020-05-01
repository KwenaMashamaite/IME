#include "StackPanel.h"
#include <algorithm>
#include <cassert>
#include <iostream>

Gui::StackPanel::StackPanel(float x, float y, Orientation orientation)
        : Panel(x, y)
{
    isOrientationVertical_ = orientation == Orientation::Vertical;
    //Reposition child elements when the panel changes position
    on("positionChanged", Callback<Position>([this](Position newPos){
        if (cBegin() != cEnd()) {
            (*(cBegin()->second)).setPosition(newPos.x, newPos.y);
            for (auto iter = ++cBegin(); iter != cEnd(); ++iter)
                setElemPosRelativeTo(iter->second, std::prev(iter,  1)->second);
        }
    }));
}

void Gui::StackPanel::addElement(const std::string &alias, std::unique_ptr<UIElement> guiElement) {
    assert(guiElement && "GUI elements added to stack panel cannot be null");
    if (isOrientationVertical_) {
        guiElement->setPadding({1.0f, guiElement->getPadding().right, guiElement->getPadding().top,
                                guiElement->getPadding().bottom});
        guiElement->setMargin({1.0f, 1.0f, guiElement->getMargin().top, guiElement->getMargin().bottom});
    }
    if (cBegin() == cEnd()) {
        guiElement->setPosition(getPosition().x, getPosition().y);
        setDimensions(guiElement->getDimensions());
    }else {
        const auto& lastAddedUIElement = std::prev(cEnd(),  1)->second;
        setElemPosRelativeTo(guiElement, lastAddedUIElement);
        adjustPanelDimensions(guiElement);
    }
    add(alias, std::move(guiElement));
}

void Gui::StackPanel::setElemPosRelativeTo(const std::unique_ptr<UIElement> &uiElem,
        const std::unique_ptr<UIElement> &refUIElem)
{
    uiElem->setPosition(
        refUIElem->getPosition().x + (isOrientationVertical_ ? 0.0f : refUIElem->getDimensions().width),
        refUIElem->getPosition().y + (isOrientationVertical_ ? refUIElem->getDimensions().height : 0.0f)
    );
}

void Gui::StackPanel::adjustPanelDimensions(const std::unique_ptr<UIElement> &uiElement) {
    const auto uiElemWidth = uiElement->getDimensions().width;
    const auto uiElemHeight = uiElement->getDimensions().height;
    const auto oldPanelWidth = getDimensions().width - 2 * getOutlineThickness();
    const auto oldPanelHeight = getDimensions().height - 2 * getOutlineThickness();
    const auto newPanelWidth = (uiElemWidth > oldPanelWidth ? uiElemWidth : oldPanelWidth);
    const auto newPanelHeight = (uiElemHeight > oldPanelHeight ? uiElemHeight : oldPanelHeight);

    if (isOrientationVertical_){
        setDimensions({newPanelWidth, oldPanelHeight + uiElemHeight});
        if (newPanelWidth > oldPanelWidth){
            std::for_each(cBegin(), cEnd(), [=](const auto& uiElem){
                auto& uiElemPtr = uiElem.second;
                auto newRightPadding = newPanelWidth - uiElemPtr->getDimensions().width;
                uiElemPtr->setPadding({uiElemPtr->getPadding().left, newRightPadding, uiElemPtr->getPadding().top,
                                      uiElemPtr->getPadding().bottom});
            });
        }else{
            auto newRightPadding = newPanelWidth - uiElement->getDimensions().width;
            uiElement->setPadding({uiElement->getPadding().left, newRightPadding, uiElement->getPadding().top,
                                   uiElement->getPadding().bottom});
        }
    }else
        setDimensions(Dimensions{oldPanelWidth + uiElemWidth, newPanelHeight});
}
