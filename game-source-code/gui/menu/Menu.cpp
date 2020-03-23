#include "Menu.h"

Gui::Menu::Menu(Gui::Window &renderTarget) : renderTarget_(renderTarget)
{}

Gui::Window &Gui::Menu::getRenderTarget() {
    return renderTarget_;
}

void Gui::Menu::addPanel(const std::string &panelName, std::shared_ptr<IPanel> panel) {
    panels_.insert(std::pair(panelName, std::move(panel)));
}

std::shared_ptr<IPanel> Gui::Menu::getPanel(const std::string &panel) const {
    auto found = panels_.find(panel);
    if (found != panels_.end())
        return found->second;
    return nullptr;
}

void Gui::Menu::removePanel(const std::string &panel) {
    auto found = panels_.find(panel);
    if (found != panels_.end())
        panels_.erase(found);
}
