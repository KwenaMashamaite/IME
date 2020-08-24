/**
 * @brief Class for managing engine states
 */

#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "State.h"
#include <unordered_map>
#include <string>
#include <memory>

namespace IME {
    class StateManager {
    public:
        /**
         * @brief Add a state
         * @param name Name of the state
         * @param state State to be added
         * @return True if the state was added or false if a state with the
         *         same name already exists
         *
         * The name of the state must be unique. If a state with the same name
         * as the argument already exists, then the provided state will not be
         * added, In addition the state pointer must not be null.
         */
        bool addState(const std::string &name, std::shared_ptr<State> state);

        /**
         * @brief Remove a state
         * @param name Name of the state to remove
         * @return True if the state was removed or false is the state does
         *         not exist
         */
        bool removeState(const std::string &name);

        /**
         * @brief Check if a state exits or not
         * @param name Name of the state to check
         * @return True if state exists or false if state does not exist
         */
        bool hasState(const std::string &name) const;

        /**
         * @brief Change the current state
         * @param newStateName Name of the state to change to
         * @return True if the state was changed, false if the specified
         *         state does not exist
         */
        bool changeState(const std::string &newStateName);

        /**
         * @brief Get access to a state
         * @param name Name of the state to get access to
         * @return A pointer to the requested state if it exists, otherwise
         *         a nullptr
         */
        std::shared_ptr<State> getState(const std::string &name) const;

        /**
         * @brief Get the current number of states
         * @return The current number of states
         */
        int getSize() const;

        /**
         * @brief Get the current state
         * @return Pointer to the current state if any, otherwise a nullptr
         */
        std::shared_ptr<State> getCurrentState() const;

        /**
        * @brief Get the name of the state prior to the current state change
        * @return Name of the previous state
        */
        const std::string &getPreviousStateName() const;

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
        //Name of the current state
        std::string currentStateName_;
        //Name of the state before a state change
        std::string prevStateName_;
        //States
        std::unordered_map<std::string, std::shared_ptr<State>> states_;
    };
} // namespace IME
#endif
