#include "Engine.h"
#include "utility/Clock.h"
#include "State.h"
#include <cassert>
#include <iostream>

namespace IME {
    Engine::Engine(Gui::Window &window)
            : window_(window) {}

    void Engine::run() {
        if (!isRunning_) {
            isRunning_ = true;
            auto const frameTime = 1.0f / 60.0f;
            auto clock = Utility::Clock();
            auto deltaTime = clock.restart();
            while (window_.isOpen() && isRunning_) {
                window_.processEvents();
                if (deltaTime >= frameTime) { //Fixed time step update
                    if (getCurrentState())
                        states_[currentState_]->fixedUpdate(deltaTime);
                    deltaTime = 0.0;
                }
                update();
                render();
                window_.display();
                deltaTime += clock.restart();
            }
        }
    }

    void Engine::stop() {
        isRunning_ = false;
    }

    void
    Engine::addState(const std::string &name, std::shared_ptr<State> state) {
        assert(state && "A game state cannot be null");
        states_.insert(std::pair(name, std::move(state)));
    }

    bool Engine::removeState(const std::string &name) {
        auto found = states_.find(name);
        if (found != states_.end()) {
            states_.erase(found);
            return true;
        }
        return false;
    }

    bool Engine::changeState(const std::string &newState) {
        if (newState != currentState_) {
            auto found = states_.find(newState);
            if (found != states_.end()) {
                //states_[currentState_]->pause();
                if (states_[newState]->isInitialized())
                    states_[newState]->resume();
                else
                    states_[newState]->initialize();

                prevState_ = currentState_;
                currentState_ = newState;
                std::cout << "Changed state to" + newState << std::endl;
                return true;
            }
        }
        return false;
    }

    std::shared_ptr<State> Engine::getState(const std::string &name) {
        auto found = states_.find(name);
        if (found != states_.end())
            return found->second;
        return nullptr;
    }

    std::shared_ptr<State> Engine::getCurrentState() {
        return std::move(getState(currentState_));
    }

    bool Engine::stateExists(const std::string &name) {
        return getState(name) == nullptr;
    }

    void Engine::update() {
        if (!isRunning_)
            window_.close();
        else {
            if (getCurrentState()) {
                states_[currentState_]->update();
            }
        }
    }

    void Engine::render() {
        if (getCurrentState())
            states_[currentState_]->render(window_);
    }

    bool Engine::isRunning() {
        return isRunning_;
    }

    const std::string &Engine::getPreviousStateName() {
        return prevState_;
    }

    Engine::~Engine() = default;
}