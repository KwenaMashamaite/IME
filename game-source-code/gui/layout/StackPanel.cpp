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

    //The stack panel initially takes on the dimensions of the first element
    on("firstElementAdded", Callback<>([this](){
        setDimensions(Dimensions{
            (*cBegin())->getDimensions().width,
            (*cBegin())->getDimensions().height
        });
        (*cBegin())->setPosition(getPosition().x, getPosition().y);
    }));
}

void Gui::StackPanel::addElement(std::shared_ptr<UIElement> guiElement) {
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

void Gui::StackPanel::setElemPosRelativeTo(std::shared_ptr<UIElement> uiElem,
        const std::shared_ptr<UIElement>& refElem)
{
    uiElem->setPosition(
        refElem->getPosition().x + (isOrientationVertical_ ? 0.0f : refElem->getDimensions().width),
        refElem->getPosition().y + (isOrientationVertical_ ? refElem->getDimensions().height : 0.0f)
    );
}

void Gui::StackPanel::accomodate(const std::shared_ptr<UIElement>& uiElement) {
    const auto uiElemWidth = uiElement->getDimensions().width;
    const auto uiElemHeight = uiElement->getDimensions().height;
    const auto oldPanelWidth = getDimensions().width;
    const auto oldPanelHeight = getDimensions().height;
    const auto newPanelWidth = (uiElemWidth > oldPanelWidth ? uiElemWidth : oldPanelWidth);
    const auto newPanelHeight = (uiElemHeight > oldPanelHeight ? uiElemHeight : oldPanelHeight);

    if (isOrientationVertical_)
        setDimensions(Dimensions{newPanelWidth, oldPanelHeight + uiElemHeight});
    else
        setDimensions(Dimensions{oldPanelWidth + uiElemWidth, newPanelHeight});
}
