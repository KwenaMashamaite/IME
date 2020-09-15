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
         * This function will be called by the engine when the game starts
         */
        virtual void initialize() = 0;

        /**
         * @brief Update the state
         * @param deltaTime Time passed since last update
         */
        virtual void update(float deltaTime) = 0;

        /**
         * @brief Update state in fixed time steps
         * @param deltaTime Time passed since last update
         */
        virtual void fixedUpdate(float deltaTime) = 0;

        /**
         * @brief Render the state on a render target
         * @param renderTarget Target to render state on
         */
        virtual void render(Graphics::Window &renderTarget) = 0;

        /**
         * @brief Pause the state
         *
         * This function will be called by the game engine when a state change is
         * requested and this object is the current state
         */
        virtual void pause() = 0;

        /**
         * @brief Handle an event
         * @param event Event to handle
         */
        virtual void handleEvent(sf::Event event) = 0;

        /**
         * @brief Resume a paused state
         *
         * This function will be called by the game engine when a state change
         */
        virtual void resume() = 0;

        /**
         * @brief Check if a state is initialized or not
         * @return True if state is initialized or false if state is not initialized
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
