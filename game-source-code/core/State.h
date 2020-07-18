/**
 * @brief Base class for states
 */

#ifndef STATE_H
#define STATE_H

#include <string>
#include "gui/window/Window.h"

class State{
public:
    /**
     * @brief Update the state
     */
    virtual void update() = 0;

    /**
     * @brief Update state in fixed time steps
     * @param deltaTime Time passed since last update
     */
    virtual void fixedUpdate(float deltaTime) = 0;

    /**
     * @brief Render the state on a render target
     * @param renderTarget Target to render state on
     */
    virtual void render(Gui::Window& renderTarget) = 0;

    /**
     * @brief Destructor
     */
    virtual ~State() = default;
};

#endif
