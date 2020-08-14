#include "SpaceInvaders.h"
#include "states/MainMenuState.h"
#include "states/QuitingState.h"

namespace SI {
    SpaceInvaders::SpaceInvaders() : Engine("spaceInvaders", "files/settings.txt")
    {}

    void SpaceInvaders::initialize() {
        IME::Engine::init();
        addState("mainMenu", std::make_shared<MainMenuState>(*this));
        addState("quit", std::make_shared<QuitingState>(*this));
        changeState("mainMenu");

        getRenderTarget().addEventListener("closed", IME::Callback<>([this]{
            changeState("quit");
        }));
    }
}