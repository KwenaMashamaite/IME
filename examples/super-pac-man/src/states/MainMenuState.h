/**
 * @brief
 */

#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "IME/core/engine/State.h"

namespace SuperPacMan {
    class MainMenuState : public IME::State {
    public:
        void initialize() override;

        void update() override;

        void fixedUpdate(float deltaTime) override;

        void render(IME::Gui::Window &renderTarget) override;

        void pause() override;

        void handleEvent(sf::Event event) override;

        void resume() override;

        bool isInitialized() const override;

        void reset() override;

    private:
    };
} // namespace SuperPacMan

#endif
