#include "MainMenuState.h"

namespace IME {
    MainMenuState::MainMenuState(Engine &engine) : State(engine)
    {}

    void MainMenuState::render(Gui::Window &renderTarget) {
        static auto drawer = Gui::Drawer(renderTarget);
        renderTarget.clear();
        drawer.drawBackground("mainMenuBackground.png");
        renderTarget.draw(mainMenu_);
    }

    void MainMenuState::update() {

    }

    void MainMenuState::fixedUpdate(float deltaTime) {

    }

    void MainMenuState::initialize() {

    }

    void MainMenuState::pause() {

    }

    void MainMenuState::resume() {

    }

    bool MainMenuState::isInitialized() const {
        return false;
    }

    void MainMenuState::reset() const {

    }
}
