#include "DockPanel.h"
#include "gui/window/Window.h"

Gui::DockPanel::DockPanel(float x, float y) : Panel(x, y){
    setDimensions(Window::getDimensions());
}

void Gui::DockPanel::addElement(std::shared_ptr<UIElement> guiElement) {
    if (lastDocked_)
        lastDocked_->addElement(std::move(guiElement));
}

void Gui::DockPanel::dock(Dock dockPosition, std::shared_ptr<Panel> panel) {
    if(panel == nullptr)
        return;;
    switch (dockPosition){
        case Dock::Left:
            dock(Dock ::Left, leftDock_, std::move(panel), Position{0u, 0u});
            break;
        case Dock::Right:
            dock(Dock::Right, rightDock_, panel, Position{static_cast<float>(
                Window::getDimensions().width -
                panel->getDimensions().width), 0u
            });
            break;
        case Dock::Top:
            dock(Dock::Top, topDock_, std::move(panel), Position{0u, 0u});
            break;
        case Dock::Bottom:
            dock(Dock::Bottom, bottomDock_, panel, Position{0u, static_cast<float>(
                    Window::getDimensions().height - panel->getDimensions().height)
            });
            break;
    }
}

void Gui::DockPanel::dock(Dock dockPosition, std::shared_ptr<Panel> &dockPanel, std::shared_ptr<Panel> panel,
                          Position defaultPos) {
    if (dockPosition == Dock::Left || dockPosition == Dock::Right){
        panel->setDimensions(Dimensions{
            panel->getDimensions().width,
            Window::getDimensions().height
            - (topDock_ ? topDock_->getDimensions().height : 0)
            - (bottomDock_ ? bottomDock_->getDimensions().height : 0)
        });
        panel->setPosition({defaultPos.x, topDock_ ? topDock_->getDimensions().height : defaultPos.y});
    }else{
        panel->setDimensions(Dimensions{
            Window::getDimensions().width
            - (leftDock_ ? leftDock_->getDimensions().width : 0)
            - (rightDock_ ? rightDock_->getDimensions().width : 0),
            panel->getDimensions().height
        });
        panel->setPosition({leftDock_ ? leftDock_->getDimensions().width : defaultPos.x, defaultPos.y});
    }
    lastDocked_ = dockPanel = std::move(panel);
}

void Gui::DockPanel::draw(Gui::Window &renderTarget) {
    for (const auto& dock : {topDock_, bottomDock_, leftDock_, rightDock_})
        if (dock)
            dock->draw(renderTarget);
}