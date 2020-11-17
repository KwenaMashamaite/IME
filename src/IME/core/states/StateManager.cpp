////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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

#include "IME/core/states/StateManager.h"
#include <cassert>

namespace IME {
    void StateManager::pushState(std::shared_ptr<State> state) {
        assert(state && "A game state cannot be null");
        if (!states_.empty() && states_.top()->isInitialized())
            states_.top()->pause();
        states_.push(std::move(state));
    }

    void StateManager::popState() {
        assert(!states_.empty() && "Cannot pop a state from an empty state manager");
        if (states_.top()->isInitialized())
            states_.top()->exit();
        states_.pop();
        if (!states_.empty() && states_.top()->isInitialized())
            states_.top()->resume();
    }

    int StateManager::getSize() const {
        return states_.size();
    }

    void StateManager::clear() {
        while (!isEmpty())
            popState();
    }

    std::shared_ptr<State> StateManager::getActiveState() const {
        assert(!states_.empty() && "Cannot retrieve a state from an empty state manager");
        return states_.top();
    }

    bool StateManager::isEmpty() const {
        return states_.empty();
    }
}
