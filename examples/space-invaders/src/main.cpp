#include "game/SpaceInvadersGame.h"

int main(){
    auto spaceInvaders = SI::SpaceInvadersGame();
    spaceInvaders.initialize();
    spaceInvaders.run();

    return 0;
}