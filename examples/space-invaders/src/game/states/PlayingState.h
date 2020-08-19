
#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "IME/core/engine/State.h"
#include "IME/gui/layout/DockPanel.h"
#include "IME/core/Scoreboard.h"

namespace SI {
    class PlayingState : public IME::State{
    public:
        PlayingState(IME::Engine &engine);

        void initialize() override;

        void update() override;

        void fixedUpdate(float deltaTime) override;

        void render(IME::Gui::Window &renderTarget) override;

        void pause() override;

        void resume() override;

        bool isInitialized() const override;

        void reset() override;

    private:
        bool isInitialized_;
        std::unique_ptr<IME::Gui::Panel> container_;
        IME::Scoreboard scoreboard_;
    };
}

#endif
