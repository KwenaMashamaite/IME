#include "GameLoseMenu.h"

namespace SI {
    GameLoseMenu::GameLoseMenu() {
        message_ = getGuiFactory()->getUIElement<IME::Gui::TextBlock>("You lost the game");
        message_->setTextCharSize(40);
        message_->setTextColour({151, 75, 105});
        message_->setBackgroundColour({0, 0, 0, 0});
        message_->setPosition(
            IME::Gui::Window::getDimensions().width / 2 - message_->getDimensions().width / 2,
            IME::Gui::Window::getDimensions().height / 2 - message_->getDimensions().height / 2
        );
    }

    void GameLoseMenu::draw(IME::Gui::Window &renderTarget) {
        renderTarget.draw(*message_);
    }

    void GameLoseMenu::hide() {

    }

    void GameLoseMenu::show() {

    }

    bool GameLoseMenu::isHidden() const {
        return false;
    }
}