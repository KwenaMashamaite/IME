/**
 * @brief
 */

#ifndef QUITINGSTATE_H
#define QUITINGSTATE_H

#include "MenuState.h"

namespace IME {
    class QuitingState : public MenuState {
    public:
        /**
         * @brief Constructor
         */
        QuitingState(Engine &engine);

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
        void render(Gui::Window &renderTarget) override;

        void initialize() override;

        void pause() override;

        void resume() override;

        bool isInitialized() const override;

        void reset() const override;

    private:
        //Menu panel
        std::unique_ptr<Gui::Panel> panel_;
        //Visibility state
        bool isInitialized_;
    };
}

#endif
