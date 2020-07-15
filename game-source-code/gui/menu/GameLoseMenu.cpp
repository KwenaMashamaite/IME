#include "GameLoseMenu.h"

Gui::GameLoseMenu::GameLoseMenu() {
    message_ = std::make_unique<TextBlock>("You lost the game");
    message_->setTextCharSize(40);
    message_->setTextColour({151, 75, 105});
    message_->setBackgroundColour({0, 0, 0, 0});
    message_->setPosition(
        Window::getDimensions().width / 2 - message_->getDimensions().width / 2,
        Window::getDimensions().height / 2 - message_->getDimensions().height / 2
    );
}

void Gui::GameLoseMenu::draw(Gui::Window &renderTarget) {
    renderTarget.draw(*message_);
}

void Gui::GameLoseMenu::hide() {

}

void Gui::GameLoseMenu::show() {

}

bool Gui::GameLoseMenu::isHidden() const {
    return false;
}
