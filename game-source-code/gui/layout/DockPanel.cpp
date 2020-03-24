#include "DockPanel.h"
#include "gui/window/Window.h"

Gui::DockPanel::DockPanel(float x, float y) : Panel(x, y){
    setDimensions(Window::getDimensions());
}

void Gui::DockPanel::addElement(std::shared_ptr<UIElement> guiElement) {
    if (lastDocked_)
        lastDocked_->addElement(std::move(guiElement));
}

void Gui::DockPanel::dock(DockPosition dockPosition, std::shared_ptr<Panel> panel) {
    if(panel == nullptr)
        return;;
    switch (dockPosition){
        case DockPosition::LeftEdge:
            dock(DockPosition ::LeftEdge, leftEdgeDock_, std::move(panel), Position{0u, 0u});
            break;
        case DockPosition::RightEdge:
            dock(DockPosition::RightEdge, rightEdgeDock_, panel, Position{static_cast<float>(
                Window::getDimensions().width -
                panel->getDimensions().width), 0u
            });
            break;
        case DockPosition::TopEdge:
            dock(DockPosition::TopEdge, topEdgeDock_, std::move(panel), Position{0u, 0u});
            break;
        case DockPosition::BottomEdge:
            dock(DockPosition::BottomEdge, bottomEdgeDock_, panel, Position{0u, static_cast<float>(
                    Window::getDimensions().height - panel->getDimensions().height)
            });
            break;
    }
}

void Gui::DockPanel::dock(DockPosition dockPosition, std::shared_ptr<Panel> &dockPanel, std::shared_ptr<Panel> panel,
                          Position defaultPos) {
    if (dockPosition == DockPosition::LeftEdge || dockPosition == DockPosition::RightEdge){
        panel->setDimensions(Dimensions{
            panel->getDimensions().width,
            Window::getDimensions().height
            - (topEdgeDock_ ? topEdgeDock_->getDimensions().height : 0)
            - (bottomEdgeDock_ ? bottomEdgeDock_->getDimensions().height : 0)
        });
        panel->setPosition({defaultPos.x, topEdgeDock_ ? topEdgeDock_->getDimensions().height : defaultPos.y});
    }else{
        panel->setDimensions(Dimensions{
            Window::getDimensions().width
            - (leftEdgeDock_ ? leftEdgeDock_->getDimensions().width : 0)
            - (rightEdgeDock_ ? rightEdgeDock_->getDimensions().width : 0),
            panel->getDimensions().height
        });
        panel->setPosition({leftEdgeDock_ ? leftEdgeDock_->getDimensions().width : defaultPos.x, defaultPos.y});
    }
    lastDocked_ = dockPanel = std::move(panel);
}

void Gui::DockPanel::draw(Gui::Window &renderTarget) {
    for (const auto& dock : {topEdgeDock_, bottomEdgeDock_, leftEdgeDock_, rightEdgeDock_})
        if (dock)
            dock->draw(renderTarget);
}