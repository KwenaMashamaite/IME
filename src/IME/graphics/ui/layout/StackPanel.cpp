#include "IME/graphics/ui/layout/StackPanel.h"
#include <algorithm>
#include <cassert>

namespace IME::Graphics::UI {
    StackPanel::StackPanel(Orientation orientation)
     : StackPanel(0.0f, 0.0f, orientation){}

    StackPanel::StackPanel(float x, float y, Orientation orientation)
            : Panel(x, y) {
        orientation_ = orientation;
        initEvents();
    }

    void StackPanel::setTitle(const std::string &title) {
        title_.setText(title);
    }

    std::string StackPanel::getTitle() const {
        return title_.getText();
    }

    void StackPanel::initEvents() {
        //Move child elements with the panel when it changes position
        on("positionChanged", Callback<Position>([this](Position newPos){
            if (cBegin() != cEnd()) {
                title_.setPosition(newPos);
                (*(cBegin()->second)).setPosition(newPos.x, title_.getPosition().y + title_.getSize().height);
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

                fitElementToPanel(uiElem);
            });
        }));

        //This handler is composed of a group of Immediately Invoked Function Expressions (IIFEs). These functions
        // will be executed in the order in which they appear every time a new element is added to the Stack Panel
        on("newElementAdded", Callback<UIElementContainer::iterator>([this](auto newElemIter){
            auto &newUIElem = newElemIter->second;
            //Adjust the dimensions of the panel to accommodate the new element
            [this, &newUIElem] {
                if (getNumberOfElements() == 1){
                    setDimensions(newUIElem->getSize());
                    return;
                }

                auto currentPanelWidth = getDimensions().width - 2 * getOutlineThickness();
                auto currentPanelHeight = getDimensions().height - 2 * getOutlineThickness();
                auto newPanelWidth = 0.0f;
                auto newPanelHeight = 0.0f;

                if (orientation_ == Orientation::Vertical){
                    newPanelWidth = (newUIElem->getSize().width > currentPanelWidth
                        ? newUIElem->getSize().width : currentPanelWidth);
                    newPanelHeight = currentPanelHeight + newUIElem->getSize().height;
                }else {
                    newPanelWidth = currentPanelWidth + newUIElem->getSize().width;
                    newPanelHeight = (newUIElem->getSize().height > currentPanelHeight
                        ? newUIElem->getSize().height : currentPanelHeight);
                }
                setDimensions({newPanelWidth, newPanelHeight});
            }();

            //Place new element next to last added element (directly below it if the
            //orientation is vertical or directly on its right if orientation is horizontal
            [this, &newUIElem] {
                if (getNumberOfElements() == 1)
                    newUIElem->setPosition(getPosition().x, getPosition().y);
                else {
                    const auto &lastAddedUIElement = std::prev(cEnd(), 2)->second;
                    setElemPosRelativeTo(newUIElem, lastAddedUIElement);
                }
            }();
        }));
    }

    bool StackPanel::addElement(const std::string &alias, std::unique_ptr<UIElement> uiElement) {
        assert(uiElement && "GUI elements added to stack panel cannot be null");
        return add(alias, std::move(uiElement));
    }

    void StackPanel::setElemPosRelativeTo(const std::unique_ptr<UIElement> &uiElem,
            const std::unique_ptr<UIElement> &refUIElem) const
    {
        uiElem->setPosition(
            refUIElem->getPosition().x + ((orientation_ == Orientation::Vertical)
             ? 0.0f : refUIElem->getSize().width),
            refUIElem->getPosition().y + ((orientation_ == Orientation::Vertical)
             ? refUIElem->getSize().height : 0.0f)
        );
    }

    void StackPanel::fitElementToPanel(const std::unique_ptr<UIElement> &uiElem) {
        auto panelWidth = getDimensions().width - 2 * getOutlineThickness();
        auto panelHeight = getDimensions().height - 2 * getOutlineThickness();
        if (orientation_ == Orientation::Vertical) {
            auto rightPadding = panelWidth - uiElem->getSize().width;
            uiElem->setPadding({uiElem->getPadding().left, rightPadding,
                uiElem->getPadding().top, uiElem->getPadding().bottom
            });
        } else if (orientation_ == Orientation::Horizontal) {
            auto bottomPadding = panelHeight - uiElem->getSize().height;
            uiElem->setPadding({uiElem->getPadding().left,
                uiElem->getPadding().right, uiElem->getPadding().top, bottomPadding
            });
        }
    }

    void StackPanel::draw(Window &renderTarget) {
        renderTarget.draw(title_);
        Panel::draw(renderTarget);
    }
}
