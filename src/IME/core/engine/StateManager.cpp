#include "IME/core/engine/StateManager.h"
#include <cassert>

namespace IME {
    void StateManager::pushState(std::shared_ptr<State> state) {
        assert(state && "A game state cannot be null");
        if (!states_.empty())
            states_.top()->pause();
        states_.push(std::move(state));
    }

    void StateManager::popState() {
        assert(!states_.empty() && "Cannot pop a state from an empty state manager");
        states_.top()->exit();
        states_.pop();
        if (!states_.empty())
            states_.top()->resume();
    }

    int StateManager::getSize() const {
        return states_.size();
    }

    void StateManager::clear() {
        for (auto i = 0; i < states_.size(); i++)
            states_.pop();
    }

    std::shared_ptr<State> StateManager::getActiveState() const {
        assert(!states_.empty() && "Cannot retrieve a state from an empty state manager");
        return states_.top();
    }

    bool StateManager::isEmpty() const {
        return states_.empty();
    }
}
