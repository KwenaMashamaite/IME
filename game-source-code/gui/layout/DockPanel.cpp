#include "DockPanel.h"
#include <cassert>

using PanelsContainer = std::map<Gui::DockPanel::DockPosition, std::unique_ptr<Gui::Panel>>;

Gui::DockPanel::DockPanel(float x, float y)
    : Panel(x, y),
      defaultPanelPos_(DockPosition::LeftEdge)
{
    addEventListener("newPanelAdded", Callback<DockPosition, bool>(
        [this](DockPosition dockPosition, bool isLastPanelToBeDocked){
            auto& newPanel = getPanelAt(dockPosition);
            const auto& leftEdgePanel = getPanelAt(DockPosition::LeftEdge);
            const auto& rightEdgePanel = getPanelAt(DockPosition::RightEdge);
            const auto& topEdgePanel = getPanelAt(DockPosition::TopEdge);
            const auto& bottomEdgePanel = getPanelAt(DockPosition::BottomEdge);

            //Get the panel on the opposite edge of the newly docked panel
            const auto& panelOnOpposite = [&dockPosition, this]() -> const std::unique_ptr<Panel>&{
                switch (dockPosition) {
                    case DockPosition::LeftEdge:
                        return getPanelAt(DockPosition::RightEdge);
                    case DockPosition::RightEdge:
                        return getPanelAt(DockPosition::LeftEdge);
                    case DockPosition::TopEdge:
                        return getPanelAt(DockPosition::BottomEdge);
                    case DockPosition::BottomEdge:
                        return getPanelAt(DockPosition::TopEdge);
                }
            }();

            //Set the position of the new panel
            [&]{
                auto newPosition = Position{-999, -999}; //Random position outside screen
                switch (dockPosition) {
                    case DockPosition::LeftEdge:
                    case DockPosition::RightEdge:
                        newPosition.y = topEdgePanel ? topEdgePanel->getPosition().y
                            + topEdgePanel->getDimensions().height
                            - topEdgePanel->getOutlineThickness(): 0;

                        if (dockPosition == DockPosition::LeftEdge)
                            newPosition.x = 0;
                        else
                            newPosition.x = isLastPanelToBeDocked ? leftEdgePanel->getPosition().x
                                + leftEdgePanel->getDimensions().width - leftEdgePanel->getOutlineThickness()
                                : Window::getDimensions().width - (newPanel->getDimensions().width
                                    + 2 * newPanel->getOutlineThickness());
                        break;
                    case DockPosition::TopEdge:
                    case DockPosition::BottomEdge:
                        newPosition.x = leftEdgePanel ? leftEdgePanel->getPosition().x
                            + leftEdgePanel->getDimensions().width - leftEdgePanel->getOutlineThickness(): 0;

                        if (dockPosition == DockPosition::TopEdge)
                            newPosition.y = 0;
                        else
                            newPosition.y = isLastPanelToBeDocked ? topEdgePanel->getPosition().y
                                + topEdgePanel->getDimensions().height - topEdgePanel->getOutlineThickness()
                                : Window::getDimensions().height - (newPanel->getDimensions().height
                                    + 2 * newPanel->getOutlineThickness());
                        break;
                }
                newPanel->setPosition(newPosition);
            }();

            //Set the new dimensions of the panel
            [&]{
                auto newPanelSize = newPanel->getDimensions();
                switch (dockPosition) {
                    case DockPosition::LeftEdge:
                    case DockPosition::RightEdge:
                        newPanelSize.height = Window::getDimensions().height
                            - 2 * newPanel->getOutlineThickness()
                            - (topEdgePanel ? topEdgePanel->getDimensions().height : 0)
                            - (bottomEdgePanel ? bottomEdgePanel->getDimensions().height : 0);

                        if (isLastPanelToBeDocked)
                            newPanelSize.width = Window::getDimensions().width
                                - 2 * newPanel->getOutlineThickness()
                                - panelOnOpposite->getDimensions().width;
                        break;
                    case DockPosition::TopEdge:
                    case DockPosition::BottomEdge:
                        newPanelSize.width = Window::getDimensions().width
                            - 2 * newPanel->getOutlineThickness()
                            - (leftEdgePanel ? leftEdgePanel->getDimensions().width : 0)
                            - (rightEdgePanel ? rightEdgePanel->getDimensions().width : 0);

                        if (isLastPanelToBeDocked)
                            newPanelSize.height = Window::getDimensions().height
                                - 2 * newPanel->getOutlineThickness()
                                - panelOnOpposite->getDimensions().height;
                        break;
                }
                newPanel->setDimensions(newPanelSize);
            }();
    }));
}

void Gui::DockPanel::addElement(const std::string &alias, std::unique_ptr<UIElement> uiElement) {
    if (getPanelAt(defaultPanelPos_))
        getPanelAt(defaultPanelPos_)->addElement(alias, std::move((uiElement)));
}

void Gui::DockPanel::dock(DockPosition dockPosition, std::unique_ptr<Panel> panel) {
    assert(panel && "Docked panel cannot be null");
    dockedPanels_.insert(std::pair(dockPosition, std::move(panel)));
    static const auto maxNumOfDockPositions = 4u;
    auto isLastPanelToBeDocked = dockedPanels_.size() == maxNumOfDockPositions;
    emit("newPanelAdded", dockPosition, isLastPanelToBeDocked);
}

void Gui::DockPanel::setDefaultPanelPos(Gui::DockPanel::DockPosition dockPosition) {
    defaultPanelPos_ = dockPosition;
}

void Gui::DockPanel::draw(Gui::Window &renderTarget) {
    std::for_each(dockedPanels_.begin(), dockedPanels_.end(), [&](auto& panel){
        if (panel.second)
            renderTarget.draw(*(panel.second));
    });
}

Gui::DockPanel::DockPosition Gui::DockPanel::getDefaultPanelPos() const {
    return defaultPanelPos_;
}

const std::unique_ptr<Gui::Panel>& Gui::DockPanel::getPanelAt(DockPosition dockPosition) {
    auto found = dockedPanels_.find(dockPosition);
    if (found != dockedPanels_.end())
        return found->second;
    return null_ptr;
}
