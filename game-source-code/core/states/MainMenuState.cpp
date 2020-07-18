#include "MainMenuState.h"

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
