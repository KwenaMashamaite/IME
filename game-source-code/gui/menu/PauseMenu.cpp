#include "PauseMenu.h"
#include "gui/control/Button.h"

Gui::PauseMenu::PauseMenu(Gui::Window &renderTarget)
    : renderTarget_(renderTarget)
{
    pauseMenuButtonsPanel_ = std::make_unique<StackPanel>(StackPanel::Orientation::Vertical);
    pauseMenuButtonsPanel_->setFillColour({0, 0, 0, 0});
    createButtons();
}

void Gui::PauseMenu::createButtons() {
    auto unpauseButton = std::make_unique<Button>("UNPAUSE");
    unpauseButton->on("click", Callback<>([this](){
        //@TODO - Return to game
    }));
    auto exitButton = std::make_unique<Button>("EXIT");
    exitButton->on("click", Callback<>([this](){
        renderTarget_.close();
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
