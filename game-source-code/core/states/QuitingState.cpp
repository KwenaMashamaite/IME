#include <iostream>
#include "QuitingState.h"
#include "core/Engine.h"

QuitingState::QuitingState() {
    windowCloseConfirmationMenu_.onClick("yes-btn", []{
        Engine::stop();
    });

    windowCloseConfirmationMenu_.onClick("no-btn", [this]{
        auto prevState = Engine::getPreviousStateName();
        Engine::changeState(prevState);
    });
}

void QuitingState::render(Gui::Window &renderTarget) {
    renderTarget.draw(windowCloseConfirmationMenu_);
}

void QuitingState::update() {}

void QuitingState::fixedUpdate(float deltaTime) {}
