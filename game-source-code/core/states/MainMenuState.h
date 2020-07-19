#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "../State.h"
#include "audio/MusicPlayer.h"
#include "gui/menu/MainMenu.h"
#include "gui/drawer/Drawer.h"

namespace IME {
    class MainMenuState : public State {
    public:
        MainMenuState(Engine &engine);

        /**
         * @brief Update state
         */
        void update() override;

        /**
         * @brief Update menu animations
         * @param deltaTime Time passed since animations were last updated
         */
        void fixedUpdate(float deltaTime) override;

        /**
         * @brief
         * @param renderTarget
         */
        void render(Gui::Window &renderTarget) override;

        void initialize() override;

        void pause() override;

        void resume() override;

        bool isInitialized() const override;

        void reset() const override;

    private:
        Gui::MainMenu mainMenu_;
    };
}

#endif
