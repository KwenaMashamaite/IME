#include <iostream>
#include "QuitingState.h"
#include "core/Engine.h"

namespace IME {
    QuitingState::QuitingState(Engine &engine) : State(engine) {
        windowCloseConfirmationMenu_.onClick("yes-btn", [this] {
            getApp().stop();
        });

        windowCloseConfirmationMenu_.onClick("no-btn", [this] {
            auto prevState = getApp().getPreviousStateName();
            getApp().changeState(prevState);
        });
    }

    void QuitingState::render(Gui::Window &renderTarget) {
        renderTarget.draw(windowCloseConfirmationMenu_);
    }

    void QuitingState::update() {}

    void QuitingState::fixedUpdate(float deltaTime) {}

    void QuitingState::initialize() {

    }

    void QuitingState::pause() {

    }

    void QuitingState::resume() {

    }

    bool QuitingState::isInitialized() const {
        return false;
    }

    void QuitingState::reset() const {

    }
}
