#include "DockPanel.h"
#include "gui/window/Window.h"

Gui::DockPanel::DockPanel(float x, float y) : Panel(x, y){
    setDimensions(Window::getDimensions());
}

void Gui::DockPanel::addElement(std::unique_ptr<UIElement> guiElement) {
    if (lastDocked_)
        lastDocked_->addElement(std::move(guiElement));
}

void Gui::DockPanel::dock(Dock dockPosiion, std::unique_ptr<Panel> panel) {
    if(panel == nullptr)
        return;;
    switch (dockPosiion){
        case Dock::Left:
            dock(Dock::Left, leftDock_, panel, Position{0u, 0u});
            leftDock_ = std::move(panel);
            break;
        case Dock::Right:
            dock(Dock::Right, rightDock_, panel, Position{static_cast<float>(
                Window::getDimensions().width -
                panel->getDimensions().width), 0u
            });
            rightDock_ = std::move(panel);
            break;
        case Dock::Top:
            dock(Dock::Top, topDock_, panel, Position{0u, 0u});
            topDock_ = std::move(panel);
            break;
        case Dock::Bottom:
            dock(Dock::Bottom, bottomDock_, panel, Position{0u, static_cast<float>(
                    Window::getDimensions().height - panel->getDimensions().height)
            });
            bottomDock_ = std::move(panel);
            break;
    }
}

void Gui::DockPanel::dock(Dock dockPosition, const std::unique_ptr<Panel> &dockPanel,
        const std::unique_ptr<Panel> &panel,
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
}

void Gui::DockPanel::draw(Gui::Window &renderTarget) {
    if (topDock_) topDock_->draw(renderTarget);
    if (bottomDock_) bottomDock_->draw(renderTarget);
    if (leftDock_) leftDock_->draw(renderTarget);
    if (rightDock_) rightDock_->draw(renderTarget);
}