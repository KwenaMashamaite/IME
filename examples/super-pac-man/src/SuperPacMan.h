#ifndef SUPERPACMAN_H
#define SUPERPACMAN_H

#include "IME/core/engine/Engine.h"

namespace SuperPacMan {
class SuperPacMan : public IME::Engine {
    public:
        /**
         * @brief Construct game
         * @param settingsFilename Filename of the games settings
         */
        SuperPacMan(const std::string &settingsFilename);
    };
} //namespace SuperPacMan

#endif
