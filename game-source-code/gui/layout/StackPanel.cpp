#include "StackPanel.h"
#include <algorithm>
#include <cassert>

Gui::StackPanel::StackPanel(float x, float y, Orientation orientation)
        : Panel(x, y)
{
    isOrientationVertical_ = orientation == Orientation::Vertical;
    //Reposition child elements when the panel changes position
    on("positionChanged", Callback<Position>([this](Position newPos){
        if (cBegin() != cEnd()) {
            (*cBegin())->setPosition(newPos.x, newPos.y);
            for (auto iter = ++cBegin(); iter != cEnd(); ++iter)
                setElemPosRelativeTo(*iter, *(iter - 1));
        }
    }));
}

void Gui::StackPanel::addElement(std::unique_ptr<UIElement> guiElement) {
    assert(guiElement && "GUI elements added to stack panel cannot be null");
    if (cBegin() == cEnd()) {
        guiElement->setPosition(getPosition().x, getPosition().y);
        setDimensions(guiElement->getDimensions());
    }else {
        const auto& lastAddedUIElement = *(cEnd() - 1);
        setElemPosRelativeTo(guiElement, lastAddedUIElement);
        accomodate(guiElement);
    }
    add(std::move(guiElement));
}

void Gui::StackPanel::setElemPosRelativeTo(const std::unique_ptr<UIElement> &uiElem,
        const std::unique_ptr<UIElement> &refUIElem)
{
    uiElem->setPosition(
        refUIElem->getPosition().x + (isOrientationVertical_ ? 0.0f : refUIElem->getDimensions().width),
        refUIElem->getPosition().y + (isOrientationVertical_ ? refUIElem->getDimensions().height : 0.0f)
    );
}

void Gui::StackPanel::accomodate(const std::unique_ptr<UIElement> &uiElement) {
    const auto uiElemWidth = uiElement->getDimensions().width;
    const auto uiElemHeight = uiElement->getDimensions().height;
    const auto oldPanelWidth = getDimensions().width - 2 * getOutlineThickness();
    const auto oldPanelHeight = getDimensions().height - 2 * getOutlineThickness();
    const auto newPanelWidth = (uiElemWidth > oldPanelWidth ? uiElemWidth : oldPanelWidth);
    const auto newPanelHeight = (uiElemHeight > oldPanelHeight ? uiElemHeight : oldPanelHeight);

    if (isOrientationVertical_)
        setDimensions(Dimensions{newPanelWidth, oldPanelHeight + uiElemHeight});
    else
        setDimensions(Dimensions{oldPanelWidth + uiElemWidth, newPanelHeight});
}
