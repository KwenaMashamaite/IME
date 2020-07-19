#include "IMenu.h"

namespace IME::Gui {
    std::shared_ptr<const GuiFactory> IMenu::guiFactory_(std::make_shared<GuiFactory>());

    const std::shared_ptr<const GuiFactory>& IMenu::getGuiFactory() const {
        return guiFactory_;
    }
}
