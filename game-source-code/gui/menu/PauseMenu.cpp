#include "PauseMenu.h"
#include "gui/control/Button.h"

Gui::PauseMenu::PauseMenu(){
    pauseMenuButtonsPanel_ = std::move(getGuiFactory()->getPanel<StackPanel>( 0, 0, StackPanel::Orientation::Vertical));
    pauseMenuButtonsPanel_->setFillColour({0, 0, 0, 0});
    createButtons();
}

void Gui::PauseMenu::createButtons() {
    auto unpauseButton = getGuiFactory()->getUIElement<Button>("UNPAUSE");
    unpauseButton->on("click", Callback<>([]{
        //@TODO - Return to game
    }));
    auto exitButton = getGuiFactory()->getUIElement<Button>("EXIT");
    exitButton->on("click", Callback<>([]{
        //@todo close window
    }));

    pauseMenuButtonsPanel_->addElement("unpauseButton", std::move(unpauseButton));
    pauseMenuButtonsPanel_->addElement("exitButton", std::move(exitButton));

    pauseMenuButtonsPanel_->setPosition({
        Window::getDimensions().width / 2.0f - pauseMenuButtonsPanel_->getDimensions().width / 2.0f,
        Window::getDimensions().height / 2.0f - pauseMenuButtonsPanel_->getDimensions().height / 2.0f
    });
}

void Gui::PauseMenu::draw(Window &renderTarget) {
    renderTarget.draw(*pauseMenuButtonsPanel_);
}

void Gui::PauseMenu::hide() {

}

void Gui::PauseMenu::show() {

}

bool Gui::PauseMenu::isHidden() const {
    return false;
}
