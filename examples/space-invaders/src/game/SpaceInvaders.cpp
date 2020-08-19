#include "SpaceInvaders.h"
#include "states/MainMenuState.h"
#include "states/QuitingState.h"

namespace SI {
    SpaceInvaders::SpaceInvaders() : Engine("spaceInvaders", "files/settings.txt")
    {}

    void SpaceInvaders::initialize() {
        IME::Engine::init();
        getStateManager().addState("mainMenu", std::make_shared<MainMenuState>(*this));
        getStateManager().addState("quit", std::make_shared<QuitingState>(*this));
        getStateManager().changeState("mainMenu");

        getRenderTarget().addEventListener("closed", IME::Callback<>([this]{
            getStateManager().changeState("quit");
        }));
    }
}