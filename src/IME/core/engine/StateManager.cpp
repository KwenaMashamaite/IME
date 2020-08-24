#include "IME/core/engine/StateManager.h"
#include <cassert>

namespace IME {
    bool StateManager::addState(const std::string &name, std::shared_ptr<State> state) {
        assert(state && "A game state cannot be null");
        return states_.insert({name, std::move(state)}).second;
    }

    bool StateManager::removeState(const std::string &name) {
        return states_.erase(name);
    }

    bool StateManager::changeState(const std::string &newStateName) {
        if (newStateName != currentStateName_) {
            if (auto newState = getState(newStateName); newState) {
                if (getCurrentState())
                    getCurrentState()->pause();
                if (newState->isInitialized())
                    newState->resume();
                else
                    newState->initialize();

                prevStateName_ = currentStateName_;
                currentStateName_ = newStateName;
                return true;
            }
        }
        return false;
    }

    std::shared_ptr<State> StateManager::getState(const std::string &name) const {
        if (auto found = states_.find(name); found != states_.end())
            return found->second;
        return nullptr;
    }

    int StateManager::getSize() const {
        return states_.size();
    }

    const std::string &StateManager::getPreviousStateName() const {
        return prevStateName_;
    }

    void StateManager::clear() {
        states_.clear();
    }

    std::shared_ptr<State> StateManager::getCurrentState() const {
        return std::move(getState(currentStateName_));
    }

    bool StateManager::isEmpty() const {
        return states_.empty();
    }

    bool StateManager::hasState(const std::string &name) const {
        return getState(name) != nullptr;;
    }
}
