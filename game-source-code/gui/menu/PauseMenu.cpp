#include <iostream>
#include "PauseMenu.h"
#include "gui/control//Button.h"

Gui::PauseMenu::PauseMenu(Gui::Window &renderTarget, SystemEventEmitter& systemEventEmitter)
    : renderTarget_(renderTarget), isCleared_(false)
{
    pauseMenuButtonsPanel_ = std::make_unique<StackPanel>(0.0f, 0.0f, Orientation::Vertical);
    pauseMenuButtonsPanel_->setFillColour({157, 15, 241});

    auto unpauseButton = std::make_unique<Button>("UNPAUSE");
    unpauseButton->on("click", Callback<>([this](){
        //Game::RequestStateChange(Game::State::Playing);
        clear();
    }));

    auto exitButton = std::make_unique<Button>("EXIT");
    exitButton->on("click", Callback<>([this](){
        renderTarget_.close();
    }));

    auto distanceBetweenButtons = 50.0f;
    unpauseButton->setMargin({0.0f, 0.0f, 0.0f, distanceBetweenButtons});

    unpauseButton->initialize(systemEventEmitter);
    exitButton->initialize(systemEventEmitter);

    pauseMenuButtonsPanel_->addElement("unpauseButton", std::move(unpauseButton));
    pauseMenuButtonsPanel_->addElement("exitButton", std::move(exitButton));
    auto centreOfScreen = Position{Window::getDimensions().width / 2.0f -
                                    pauseMenuButtonsPanel_->getDimensions().width / 2.0f,
                                    Window::getDimensions().height / 2.0f -
                                    pauseMenuButtonsPanel_->getDimensions().height / 2.0f};
    pauseMenuButtonsPanel_->setPosition(centreOfScreen);
}

void Gui::PauseMenu::draw() {
    if (isCleared_){
        isCleared_ = false;
        pauseMenuButtonsPanel_->unhide();
    }
    pauseMenuButtonsPanel_->draw(renderTarget_);
}

void Gui::PauseMenu::clear() {
    isCleared_ = true;
    pauseMenuButtonsPanel_->hide();
}


