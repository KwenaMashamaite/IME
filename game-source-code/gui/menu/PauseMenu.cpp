#include "PauseMenu.h"
#include "gui/window//Window.h"
#include "gui/control//Button.h"

Gui::PauseMenu::PauseMenu(Gui::Window &renderTarget)
    : renderTarget_(renderTarget), isCleared_(false)
{
    pauseMenuButtonsPanel_ = std::make_unique<StackPanel>(0.0f, 0.0f, Orientation::Vertical);
    pauseMenuButtonsPanel_->setFillColour({157, 15, 241});
    createButtons();
    auto centreOfScreen = Position{Window::getDimensions().width / 2.0f -
                                    pauseMenuButtonsPanel_->getDimensions().width / 2.0f,
                                    Window::getDimensions().height / 2.0f -
                                    pauseMenuButtonsPanel_->getDimensions().height / 2.0f};
    pauseMenuButtonsPanel_->setPosition(centreOfScreen);
}

void Gui::PauseMenu::createButtons() {
    auto unpauseButton = std::make_unique<Button>("UNPAUSE");
    unpauseButton->on("click", Callback<>([this](){
        clear();
        //Game::RequestStateChange(Game::State::Playing);
    }));
    auto exitButton = std::make_unique<Button>("EXIT");
    exitButton->on("click", Callback<>([this](){
        renderTarget_.close();
    }));

    auto distanceBetweenButtons = 50.0f;
    unpauseButton->setMargin({1.0f, 1.0f, 1.0f, distanceBetweenButtons});

    pauseMenuButtonsPanel_->addElement("unpauseButton", std::move(unpauseButton));
    pauseMenuButtonsPanel_->addElement("exitButton", std::move(exitButton));
}

void Gui::PauseMenu::draw() {
    if (isCleared_){
        isCleared_ = false;
        pauseMenuButtonsPanel_->show();
    }
    pauseMenuButtonsPanel_->draw(renderTarget_);
}

void Gui::PauseMenu::clear() {
    isCleared_ = true;
    pauseMenuButtonsPanel_->hide();
}
