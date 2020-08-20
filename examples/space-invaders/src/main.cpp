#include "SpaceInvaders.h"

int main(){
    auto spaceInvaders = SI::SpaceInvaders();
    spaceInvaders.initialize();
    spaceInvaders.run();

    return 0;
}