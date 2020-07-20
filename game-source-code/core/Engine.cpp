#include "Engine.h"
#include "utility/Clock.h"
#include "resources/FileReader.h"
#include "exceptions/Exceptions.h"
#include "State.h"
#include <cassert>

namespace IME {
    Engine::Engine() : isRunning_{false}
    {}

    void Engine::init() {
        loadSettings();
        initRenderTarget();
    }

    void Engine::loadSettings() {
        auto settings = std::stringstream();
        auto settingsPath = std::string("resources/textFiles/");
        Utility::FileReader().readFileInto(settings, settingsPath + "settings.txt");
        std::string setting;
        while (std::getline(settings, setting)) {
            auto separatorPos = setting.find_first_of('=');
            if (separatorPos != std::string::npos) {
                auto name = setting.substr(0, separatorPos);
                auto value = setting.substr(separatorPos + 1);
                settings_.insert(std::pair(name, value));
            } else {
                throw InvalidArgument(R"(The entry ')" + setting + R"(')" + " in " + settingsPath
                    + "settings.txt" + R"( is invalid because it's missing a separator '=')");
            }
        }
    }

    void Engine::initRenderTarget() {
        auto desktopWidth = sf::VideoMode::getDesktopMode().width;
        auto desktopHeight = sf::VideoMode::getDesktopMode().height;
        auto width = std::stof(settings_["width"]);
        auto height = std::stof(settings_["height"]);
        auto isFullscreen = static_cast<bool>(std::stoi(settings_["fullscreen"]));
        if (isFullscreen){
            window_.create(settings_["title"], desktopWidth, desktopHeight, Gui::Window::Style::Fullscreen);
        }else{
            if (width > desktopWidth)
                width = desktopWidth;
            if (height > desktopHeight)
                height = desktopHeight;
            window_.create(settings_["title"], width, height, Gui::Window::Style::Close);
        }
    }

    void Engine::run() {
        if (!isRunning_ && !states_.empty()) {
            isRunning_ = true;
            auto const frameTime = 1.0f / 60.0f;
            auto clock = Utility::Clock();
            auto deltaTime = clock.restart();
            while (window_.isOpen() && isRunning_ && !states_.empty()) {
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

    void Engine::addState(const std::string &newState, std::shared_ptr<State> state) {
        assert(state && "A game state cannot be null");
        states_.insert(std::pair(newState, std::move(state)));
        if (states_.size() == 1) {
            states_[newState]->initialize();
            currentState_ = newState;
        }
    }

    bool Engine::removeState(const std::string &stateName) {
        auto found = states_.find(stateName);
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
                states_[currentState_]->pause();
                if (states_[newState]->isInitialized())
                    states_[newState]->resume();
                else
                    states_[newState]->initialize();

                prevState_ = currentState_;
                currentState_ = newState;
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

    const Gui::Window &Engine::getRenderTarget() const {
        return window_;
    }

    Engine::~Engine() = default;
}
