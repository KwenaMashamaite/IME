/**
 * @brief Base class for states
 */

#ifndef STATE_H
#define STATE_H

#include "IME/graphics/Window.h"
#include <SFML/Window/Event.hpp>
#include <string>

namespace IME {
    class Engine;

    class State {
    public:
        /**
         * @brief Constructor
         * @param engine Reference to the game
         */
        State(Engine &engine);

        /**
         * @brief Initialize state
         *
         * This function will be called by the engine before the state is entered
         * for the first time
         */
        virtual void initialize() = 0;

        /**
         * @brief Update the state
         * @param deltaTime Time passed since last update
         *
         * This function will be called once per frame by the engine. The delta
         * passed to it is frame rate dependent. This means that it depends on
         * how long the current frames takes to complete. All updates that need
         * a variable timestep must be defined in this function
         */
        virtual void update(float deltaTime) = 0;

        /**
         * @brief Update state in fixed time steps
         * @param deltaTime Time passed since last update
         *
         * This function will be called multiple times per frame by the engine.
         * The delta passed to it is always the same. All update that require a
         * fixed timestep must be defined in this function. This function allows
         * updates to be the same regardless of how fast or slow the computer is
         */
        virtual void fixedUpdate(float deltaTime) = 0;

        /**
         * @brief Render the state on a render target
         * @param renderTarget Target to render state on
         *
         * This function will be called once per frame by the engine after all
         * events have been handled and all updates have performed for the
         * current frame
         */
        virtual void render(Graphics::Window &renderTarget) = 0;

        /**
         * @brief Pause the state
         *
         * This function will be called by the game engine on the current state
         * when a state change is requested. This function allows a state to pause
         * itself such that when it is returned to, it can resume where it left of
         * instead of being reinitialized
         */
        virtual void pause() = 0;

        /**
         * @brief Handle an event
         * @param event Event to handle
         *
         * This function wil be called by the engine at the start of the current
         * frame
         */
        virtual void handleEvent(sf::Event event) = 0;

        /**
         * @brief Resume a paused state
         *
         * This function will be called by the game engine when a previously
         * initialised state is returned to @see initialize() and pause()
         */
        virtual void resume() = 0;

        /**
         * @brief Check if a state is initialized or not
         * @return True if state is initialized or false if state is not initialized
         *
         * This function will be called by the engine when a state push or a state
         * pop was requested in the previous frame. This ensures that a previously
         * initialized state is resumed instead of being reinitialized and vice
         * versa @see initialize(), resume() and pause()
         */
        virtual bool isInitialized() const = 0;

        /**
         * @brief Reset state without re-initialization
         */
        virtual void reset() = 0;

        /**
         * @brief Exit a state
         *
         * This function will be called by the engine before the state
         * is destroyed. It may be useful if there are some cleanup
         * procedures that need to be taken care of before the object
         * is destroyed
         */
        virtual void exit() = 0;

        /**
         * @brief Destructor
         */
        virtual ~State() = default;

    protected:
        /**
         * @brief Get a reference to the game engine
         * @return Reference to a game engine
         */
        Engine &engine() const;

    private:
        //Reference to the game engine
        Engine &app_;
    };
} // namespace IME

#endif
