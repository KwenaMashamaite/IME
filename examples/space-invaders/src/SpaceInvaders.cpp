#include "SpaceInvaders.h"
#include "states/MainMenuState.h"
#include "states/QuitingState.h"

namespace SI {
    SpaceInvaders::SpaceInvaders() : Engine("Space Invaders", "files/settings.txt")
    {}

    void SpaceInvaders::initialize() {
        IME::Engine::init();
        pushState(std::make_shared<MainMenuState>(*this));
        pushState(std::make_shared<QuitingState>(*this));
    }
}