#include "MenuState.h"

namespace IME {
    std::shared_ptr<const GuiFactory> IME::MenuState::guiFactory_(std::make_shared<GuiFactory>());

    MenuState::MenuState(Engine &engine) : State(engine)
    {}

    const std::shared_ptr<const GuiFactory> & IME::MenuState::getGuiFactory() const {
        return guiFactory_;
    }
}
