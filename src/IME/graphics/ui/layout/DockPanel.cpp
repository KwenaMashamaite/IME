#include "IME/graphics/ui/layout/DockPanel.h"
#include <cassert>

namespace IME::Graphics::UI {
    using PanelsContainer = std::map<DockPanel::DockPosition, std::unique_ptr<Panel>>;

    DockPanel::DockPanel(float x, float y)
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

    bool DockPanel::addElement(const std::string &alias, std::unique_ptr<UIElement> uiElement) {
        if (getPanelAt(defaultPanelPos_))
            return getPanelAt(defaultPanelPos_)->addElement(alias, std::move((uiElement)));
        return false;
    }

    void DockPanel::dock(DockPosition dockPosition, std::unique_ptr<Panel> panel) {
        assert(panel && "Docked panel cannot be null");
        dockedPanels_.insert({dockPosition, std::move(panel)});
        static const auto maxNumOfDockPositions = 4u;
        auto isLastPanelToBeDocked = dockedPanels_.size() == maxNumOfDockPositions;
        emit("newPanelAdded", dockPosition, isLastPanelToBeDocked);
    }

    void DockPanel::setDefaultPanelPos(DockPosition dockPosition) {
        defaultPanelPos_ = dockPosition;
    }

    void DockPanel::draw(Window &renderTarget) {
        std::for_each(dockedPanels_.begin(), dockedPanels_.end(), [&](auto& panel){
            if (panel.second)
                renderTarget.draw(*(panel.second));
        });
    }

    DockPanel::DockPosition DockPanel::getDefaultPanelPos() const {
        return defaultPanelPos_;
    }

    const std::unique_ptr<Panel>& DockPanel::getPanelAt(DockPosition dockPosition) {
        if (dockedPanels_.find(dockPosition) != dockedPanels_.end())
            return dockedPanels_.at(dockPosition);
        return null_ptr;
    }
}