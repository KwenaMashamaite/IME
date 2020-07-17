#include "IMenu.h"

std::shared_ptr<const GuiFactory> Gui::IMenu::guiFactory_(std::make_shared<GuiFactory>());

const std::shared_ptr<const GuiFactory>& Gui::IMenu::getGuiFactory() const {
    return guiFactory_;
}
