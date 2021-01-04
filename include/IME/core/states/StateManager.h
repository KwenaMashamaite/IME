////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#ifndef IME_STATEMANAGER_H
#define IME_STATEMANAGER_H

#include "IME/Config.h"
#include "State.h"
#include <stack>
#include <memory>

namespace IME {
    /**
     * @brief Class for managing game states. The states are managed using a
     *        LIFO method
     */
    class IME_API StateManager {
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
         * manager. Such an event is undefined behavior
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
         * manager. Such an event is undefined behavior
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
        std::stack<std::shared_ptr<State>> states_; //!< States container
    };
}

#endif // IME_STATEMANAGER_H
