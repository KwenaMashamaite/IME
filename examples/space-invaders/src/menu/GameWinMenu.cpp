#include "GameWinMenu.h"
#include "../window/Window.h"
#include "../control/TextBlock.h"

namespace IME::Gui {
    void GameWinMenu::draw(Window &renderTarget) {
        static auto message = getGuiFactory()->getUIElement<IME::Gui::TextBlock>("You won the game!!");
        message->setTextCharSize(40);
        message->setTextColour({151, 75, 105});
        message->setBackgroundColour({0, 0, 0, 0});
        message->setPosition(
            Window::getDimensions().width / 2 - message->getDimensions().width / 2,
            Window::getDimensions().height / 2 - message->getDimensions().height / 2
        );

        renderTarget.draw(*message);
    }

    void GameWinMenu::hide() {

    }

    void GameWinMenu::show() {

    }

    bool GameWinMenu::isHidden() const {
        return false;
    }
}
