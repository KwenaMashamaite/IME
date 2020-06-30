#include "GameWinMenu.h"
#include "../window/Window.h"
#include "../control/TextBlock.h"

void Gui::GameWinMenu::draw(Gui::Window &renderTarget) {
    static auto message = TextBlock("You won the game!!");
    message.setTextCharSize(40);
    message.setTextFillColour({151, 75, 105});
    message.setFillColour({0, 0, 0, 0});
    message.setPosition(
        Window::getDimensions().width / 2 - message.getDimensions().width / 2,
        Window::getDimensions().height / 2 - message.getDimensions().height / 2
    );

    renderTarget.draw(message);
}

void Gui::GameWinMenu::hide() {

}

void Gui::GameWinMenu::show() {

}

bool Gui::GameWinMenu::isHidden() const {
    return false;
}
