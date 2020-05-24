#include "StackPanel.h"
#include <algorithm>
#include <cassert>
#include <iostream>

Gui::StackPanel::StackPanel(Gui::Orientation orientation)
 : StackPanel(0.0f, 0.0f, orientation){}

Gui::StackPanel::StackPanel(float x, float y, Orientation orientation)
        : Panel(x, y) {
    orientation_ = orientation;
    initEvents();
}

void Gui::StackPanel::initEvents() {
    //Move child elements with the panel when it changes position
    on("positionChanged", Callback<Position>([this](Position newPos){
        if (cBegin() != cEnd()) {
            (*(cBegin()->second)).setPosition(newPos.x, newPos.y);
            for (auto iter = ++cBegin(); iter != cEnd(); ++iter)
                setElemPosRelativeTo(iter->second, std::prev(iter,  1)->second);
        }
    }));

    //Adjust the element such that it always has the dimensions of the panel
    //that is, same width as the panel when the orientation is vertical and
    //same height as the panel when the orientation is horizontal
    on("dimensionsChanged", Callback<Dimensions>([this](Dimensions newDim) {
        std::for_each(cBegin(), cEnd(), [=](const auto &uiElemIter) {
            auto& uiElem = uiElemIter.second;
            if (orientation_ == Orientation::Vertical)
                uiElem->setPadding({uiElem->getPadding().left, 0.0f,
                    uiElem->getPadding().top,uiElem->getPadding().bottom
                });
            else
                uiElem->setPadding({uiElem->getPadding().left,
                    uiElem->getPadding().right, uiElem->getPadding().top, 0.0f
                });

            fitElementToPanel(uiElemIter.second);
        });
    }));

    //This handler is composed of a group of Immediately Invoked Function Expressions (IIFEs). These functions
    // will be executed in the order in which they appear every time a new element is added to the Stack Panel
    on("newElementAdded", Callback<UIElementContainer::iterator>([this](auto newElemIter){
        auto &newUIElem = newElemIter->second;
        //Adjust the dimensions of the panel to accommodate the new element
        [this, &newUIElem] {
            if (size() == 1){
                setDimensions(newUIElem->getDimensions());
                return;
            }

            auto currentPanelWidth = getDimensions().width - 2 * getOutlineThickness();
            auto currentPanelHeight = getDimensions().height - 2 * getOutlineThickness();
            auto newPanelWidth = 0.0f;
            auto newPanelHeight = 0.0f;

            if (orientation_ == Orientation::Vertical){
                newPanelWidth = (newUIElem->getDimensions().width > currentPanelWidth
                                ? newUIElem->getDimensions().width : currentPanelWidth);
                newPanelHeight = currentPanelHeight + newUIElem->getDimensions().height;
            }else{
                newPanelWidth = currentPanelWidth + newUIElem->getDimensions().width;
                newPanelHeight = (newUIElem->getDimensions().height > currentPanelHeight
                                 ? newUIElem->getDimensions().height : currentPanelHeight);
            }
            setDimensions({newPanelWidth, newPanelHeight});
        }();

        //Place new element next to last added element (directly below it if the
        //orientation is vertical or directly on its right if orientation is horizontal
        [this, &newUIElem] {
            if (size() == 1)
                newUIElem->setPosition(getPosition().x, getPosition().y);
            else {
                const auto &lastAddedUIElement = std::prev(cEnd(), 2)->second;
                setElemPosRelativeTo(newUIElem, lastAddedUIElement);
            }
        }();

        //Adjust the stack panel dimensions when a child element's dimension change
        [this, &newElemIter] {
            auto childName = newElemIter->first;
            auto& targetElement = newElemIter->second;
            subscribeChildToEvent(childName, "dimensionsChanged",
                Callback<Dimensions>([this](Dimensions newElemDimensions) {
                    emit("dimensionsChanged");
                }));
        }();
    }));
}

void Gui::StackPanel::addElement(const std::string &alias, std::unique_ptr<UIElement> guiElement) {
    assert(guiElement && "GUI elements added to stack panel cannot be null");
    add(alias, std::move(guiElement));
}

void Gui::StackPanel::setElemPosRelativeTo(const std::unique_ptr<UIElement> &uiElem,
        const std::unique_ptr<UIElement> &refUIElem) const
{
    uiElem->setPosition(
        refUIElem->getPosition().x + ((orientation_ == Orientation::Vertical)
         ? 0.0f : refUIElem->getDimensions().width),
        refUIElem->getPosition().y + ((orientation_ == Orientation::Vertical)
         ? refUIElem->getDimensions().height : 0.0f)
    );
}

void Gui::StackPanel::fitElementToPanel(const std::unique_ptr<UIElement> &uiElem) {
    auto panelWidth = getDimensions().width - 2 * getOutlineThickness();
    auto panelHeight = getDimensions().height - 2 * getOutlineThickness();
    if (orientation_ == Orientation::Vertical) {
        auto rightPadding = panelWidth - uiElem->getDimensions().width;
        uiElem->setPadding({1.0f, rightPadding,
            uiElem->getPadding().top, uiElem->getPadding().bottom
        });
    } else if (orientation_ == Orientation::Horizontal) {
        auto bottomPadding = panelHeight - uiElem->getDimensions().height;
        uiElem->setPadding({uiElem->getPadding().left,
            uiElem->getPadding().right, 1.0f, bottomPadding
        });
    }
}
