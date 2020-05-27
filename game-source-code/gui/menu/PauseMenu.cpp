#include "PauseMenu.h"
#include "gui/control/Button.h"

Gui::PauseMenu::PauseMenu(Gui::Window &renderTarget)
    : renderTarget_(renderTarget), isCleared_(false)
{
    pauseMenuButtonsPanel_ = std::make_unique<StackPanel>(0.0f, 0.0f, StackPanel::Orientation::Vertical);
    pauseMenuButtonsPanel_->setFillColour({0, 0, 0});

    createButtons();
    auto centreOfScreen = Position{
        Window::getDimensions().width / 2.0f - pauseMenuButtonsPanel_->getDimensions().width / 2.0f,
        Window::getDimensions().height / 2.0f - pauseMenuButtonsPanel_->getDimensions().height / 2.0f
    };
    pauseMenuButtonsPanel_->setPosition(centreOfScreen);
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
}

void Gui::PauseMenu::draw(Window &renderTarget) {
    renderTarget.draw(*pauseMenuButtonsPanel_);
}
