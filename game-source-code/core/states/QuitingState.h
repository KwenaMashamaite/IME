/**
 * @brief
 */

#ifndef QUITINGSTATE_H
#define QUITINGSTATE_H

#include "../State.h"
#include "gui/menu/WindowClosePopUpMenu.h"

class QuitingState : public State {
public:
    /**
     * @brief Constructor
     */
    QuitingState();

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

private:
    //
    Gui::WindowClosePopUpMenu windowCloseConfirmationMenu_;
};

#endif
