
#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "IME/core/engine/State.h"
#include "gui/layout/DockPanel.h"
#include "scoreboard/Scoreboard.h"

namespace SI {
    class PlayingState : public State{
    public:
        PlayingState(Engine &engine);

        void initialize() override;

        void update() override;

        void fixedUpdate(float deltaTime) override;

        void render(Gui::Window &renderTarget) override;

        void pause() override;

        void resume() override;

        bool isInitialized() const override;

        void reset() override;

    private:
        std::unique_ptr<Gui::DockPanel> container_;
        Scoreboard scoreboard_;
        bool isInitialized_;
    };
}

#endif
