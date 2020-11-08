/**
 * @brief Class for managing game states. The states are managed using a LIFO method
 */

#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "State.h"
#include <stack>
#include <memory>

namespace IME {
    class StateManager {
    public:
        /**
         * @brief Add a state
         * @param state State to be added
         *
         * @warning The pointer must not be null
         */
        void pushState(std::shared_ptr<State> state);

        /**
         * @brief Remove a state
         *
         * @warning This function must not be called on an empty state
         * manager. Such an event will result in a program crash
         */
        void popState();

        /**
         * @brief Get the current number of states
         * @return The current number of states
         */
        int getSize() const;

        /**
         * @brief Get the current state
         * @return Pointer to the current state
         *
         * @warning This function must not be called on an empty state
         * manager. Such an event will result in a program crash
         */
        std::shared_ptr<State> getActiveState() const;

        /**
         * @brief Destroy all states
         */
        void clear();

        /**
         * @brief Check if state manager is empty or not
         * @return True of state manager is empty, otherwise false
         */
        bool isEmpty() const;

    private:
        //States container
        std::stack<std::shared_ptr<State>> states_;
    };
}

#endif
