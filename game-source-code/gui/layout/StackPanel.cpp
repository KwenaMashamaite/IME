#include "StackPanel.h"
#include <algorithm>

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
    on("firstElement", Callback<>([this](){
        setDimensions(Dimensions{
            (*cBegin())->getDimensions().width,
            (*cBegin())->getDimensions().height
        });
        (*cBegin())->setPosition(getPosition().x, getPosition().y);
    }));
}

void Gui::StackPanel::addElement(std::shared_ptr<UIElement> guiElement) {
    if (cBegin() == cEnd())
        add(std::move(guiElement));
    else {
        setElemPosRelativeTo(guiElement, *(cEnd() - 1));
        auto getNewDimension = [](unsigned int newElemDimension, unsigned int prevElemDimension){
            return (newElemDimension > prevElemDimension? newElemDimension : prevElemDimension);
        };

        if (isOrientationVertical_) {
            setDimensions(Dimensions{
                getNewDimension(guiElement->getDimensions().width, (*(cEnd() - 1))->getDimensions().width),
                getDimensions().height + guiElement->getDimensions().height
            });
        }else{
            setDimensions(Dimensions{
                getDimensions().width + guiElement->getDimensions().width,
                getNewDimension(guiElement->getDimensions().height, (*(cEnd() - 1))->getDimensions().height)
            });
        }
        add(std::move(guiElement));
    }
}

void Gui::StackPanel::setElemPosRelativeTo(std::shared_ptr<UIElement> uiElem, std::shared_ptr<UIElement> refElem){
    uiElem->setPosition(
        refElem->getPosition().x + (isOrientationVertical_ ? 0.0f : refElem->getDimensions().width),
        refElem->getPosition().y + (isOrientationVertical_ ? refElem->getDimensions().height : 0.0f)
    );
}