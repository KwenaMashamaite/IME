#include "MenuState.h"

namespace SI {
    std::shared_ptr<const GuiFactory> IME::MenuState::guiFactory_(std::make_shared<GuiFactory>());

    MenuState::MenuState(IME::Engine &engine) : State(engine)
    {}

    const std::shared_ptr<const GuiFactory> & IME::MenuState::getGuiFactory() const {
        return guiFactory_;
    }
}
