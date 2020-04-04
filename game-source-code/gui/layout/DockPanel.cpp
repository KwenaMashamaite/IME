#include "DockPanel.h"
#include <cassert>

Gui::DockPanel::DockPanel(float x, float y) : Panel(x, y), lastDockedPosition_(-1)
{}

void Gui::DockPanel::addElement(const std::string &alias, std::unique_ptr<UIElement> guiElement) {
    const static auto numOfDockPosition = 4u;
    if (lastDockedPosition_ >= 0 && lastDockedPosition_ < numOfDockPosition)
        getPanelAt(static_cast<DockPosition>(lastDockedPosition_))->addElement(alias, std::move(guiElement));
}

void Gui::DockPanel::dock(DockPosition dockPosition, std::unique_ptr<Panel> panel) {
    assert(panel && "nullptrs cannot be added to Dock Panel");
    switch (dockPosition){
        case DockPosition::LeftEdge:
            dock(DockPosition::LeftEdge, panel, Position{0u, 0u});
            leftEdgeDock_ = std::move(panel);
            break;
        case DockPosition::RightEdge:
            dock(DockPosition::RightEdge, panel, Position{static_cast<float>(
                getDimensions().width -
                panel->getDimensions().width), 0.0f
            });
            rightEdgeDock_ = std::move(panel);
            break;
        case DockPosition::TopEdge:
            dock(DockPosition::TopEdge, panel, Position{0u, 0u});
            topEdgeDock_ = std::move(panel);
            break;
        case DockPosition::BottomEdge:
            dock(DockPosition::BottomEdge, panel, Position{0u, static_cast<float>(
                    getDimensions().height - panel->getDimensions().height)
            });
            bottomEdgeDock_ = std::move(panel);
            break;
    }
    lastDockedPosition_ = static_cast<int>(dockPosition);
}

void Gui::DockPanel::dock(DockPosition dockPosition,const std::unique_ptr<Panel> &panel,
        Position defaultPos)
{
    if (dockPosition == DockPosition::LeftEdge || dockPosition == DockPosition::RightEdge){
        panel->setDimensions(Dimensions{
            panel->getDimensions().width,
            getDimensions().height
            - (topEdgeDock_ ? topEdgeDock_->getDimensions().height : 0)
            - (bottomEdgeDock_ ? bottomEdgeDock_->getDimensions().height : 0)
        });
        panel->setPosition({defaultPos.x, topEdgeDock_ ? topEdgeDock_->getDimensions().height : defaultPos.y});

        if (isLastToBeDocked(dockPosition)){
            if (dockPosition == DockPosition::RightEdge) {
                panel->setDimensions({getDimensions().width - leftEdgeDock_->getDimensions().width, getDimensions().height});
                panel->setPosition({leftEdgeDock_->getDimensions().width, topEdgeDock_->getDimensions().height});
            }else {
                panel->setDimensions({getDimensions().width - rightEdgeDock_->getDimensions().width, getDimensions().height});
                panel->setPosition({0.0f, topEdgeDock_->getDimensions().height});
            }
        }

    }else{
        panel->setDimensions(Dimensions{
            getDimensions().width
            - (leftEdgeDock_ ? leftEdgeDock_->getDimensions().width : 0)
            - (rightEdgeDock_ ? rightEdgeDock_->getDimensions().width : 0),
            panel->getDimensions().height
        });
        panel->setPosition({leftEdgeDock_ ? leftEdgeDock_->getDimensions().width : defaultPos.x, defaultPos.y});

        if (isLastToBeDocked(dockPosition)){
            if (dockPosition == DockPosition::TopEdge) {
                panel->setDimensions({getDimensions().width, getDimensions().height - bottomEdgeDock_->getDimensions().height});
                panel->setPosition({leftEdgeDock_->getDimensions().width, 0.0f});
            }else {
                panel->setDimensions({getDimensions().width, getDimensions().height - topEdgeDock_->getDimensions().height});
                panel->setPosition({leftEdgeDock_->getDimensions().width, topEdgeDock_->getDimensions().height});
            }
        }
    }
}

void Gui::DockPanel::draw(Gui::Window &renderTarget) {
    if (topEdgeDock_) topEdgeDock_->draw(renderTarget);
    if (bottomEdgeDock_) bottomEdgeDock_->draw(renderTarget);
    if (leftEdgeDock_) leftEdgeDock_->draw(renderTarget);
    if (rightEdgeDock_) rightEdgeDock_->draw(renderTarget);
}

const std::unique_ptr<Gui::Panel>& Gui::DockPanel::getPanelAt(DockPosition dockPosition) {
    switch (dockPosition){
        case DockPosition::LeftEdge:
            return leftEdgeDock_;
        case DockPosition::RightEdge:
            return rightEdgeDock_;
        case DockPosition::TopEdge:
            return topEdgeDock_;
        case DockPosition::BottomEdge:
            return bottomEdgeDock_;
    }
}

bool Gui::DockPanel::isLastToBeDocked(DockPosition dockPosition) const{
    switch (dockPosition){
        case DockPosition::LeftEdge:
            return (rightEdgeDock_ && topEdgeDock_ && bottomEdgeDock_);
        case DockPosition::RightEdge:
            return (leftEdgeDock_ && topEdgeDock_ && bottomEdgeDock_);
        case DockPosition::TopEdge:
            return (bottomEdgeDock_ && leftEdgeDock_ && rightEdgeDock_);
        case DockPosition::BottomEdge:
            return (topEdgeDock_ && leftEdgeDock_ && rightEdgeDock_);
    }
}
