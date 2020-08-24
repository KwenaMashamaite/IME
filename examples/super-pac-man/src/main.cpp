#include "SuperPacMan.h"

int main() {
    auto superPacMan = SuperPacMan::SuperPacMan("files/settings.txt");
    superPacMan.init();
    superPacMan.run();
    return 0;
}