/**
 * @brief
 */

#ifndef QUITINGSTATE_H
#define QUITINGSTATE_H

#include "IME/gui/layout/Panel.h"
#include "IME/core/engine/State.h"

namespace SI {
    class QuitingState : public IME::State {
    public:
        /**
         * @brief Constructor
         */
        QuitingState(IME::Engine &engine);

        /**
         * @brief Update the state
         */
        void update() override;

        /**
         * @brief Update state in fixed time steps
         * @param deltaTime Time passed since last update
         */
        void fixedUpdate(float deltaTime) override;

        /**
         * @brief Render the state on a render target
         * @param renderTarget Target to render state on
         */
        void render(IME::Gui::Window &renderTarget) override;

        void initialize() override;

        void pause() override;

        void resume() override;

        bool isInitialized() const override;

        void reset() override;

    private:
        //Initialization state
        bool isInitialized_;
        //Menu panel
        std::unique_ptr<IME::Gui::Panel> panel_;
    };
}

#endif
