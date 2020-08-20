#ifndef SPACEINVADERSGAME_H
#define SPACEINVADERSGAME_H

#include "IME/core/engine/Engine.h"

namespace SI {
    class SpaceInvaders : public IME::Engine {
    public:
        SpaceInvaders();

        void initialize();
    };
}
#endif
