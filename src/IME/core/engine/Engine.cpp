#include "IME/core/engine/Engine.h"
#include "IME/core/engine/State.h"
#include "IME/core/resources/FileReader.h"
#include "IME/core/exceptions/Exceptions.h"
#include "IME/utility/Clock.h"
#include <cassert>

namespace IME {
    std::shared_ptr<const GuiFactory> IME::Engine::guiFactory_(std::make_shared<GuiFactory>());

    Engine::Engine(const std::string &gameName, const std::string &settingsFilename)
        : isRunning_{false},
          appName_{gameName},
          settingFile_{settingsFilename}
    {}

    void Engine::init() {
        loadSettings();
        initRenderTarget();
    }

    void Engine::loadSettings() {
        auto settings = std::stringstream();
        Utility::FileReader().readFileInto(settings, settingFile_);
        std::string setting;
        while (std::getline(settings, setting)) {
            static auto errorMessage = [&](const std::string& errorMessage){
                return R"(The entry ')" + setting + R"(')" + " in " + settingFile_
                    + " is invalid because " + errorMessage;
            };

            ////Skip lines that are empty or begin with a comment or whitespaces
            if (setting.empty() || setting[0] == '#' || setting[0] == ' ')
                continue;

            auto separatorPos = setting.find_first_of('=');
            if (separatorPos != std::string::npos) {
                auto key = setting.substr(0, separatorPos);
                if (key.find_first_of(' ') != std::string::npos)
                    throw InvalidArgument(errorMessage("key contains whitespaces"));
                auto value = setting.substr(separatorPos + 1);
                settings_.insert(std::pair(key, value));
            } else
                throw InvalidArgument(errorMessage(R"("it's missing a separator '=')"));
        }
        verifySettings();
    }

    void Engine::verifySettings() const {
        auto mandatorySettings = {"title", "width", "height", "fullscreen"};
        std::for_each(mandatorySettings.begin(), mandatorySettings.end(),
            [this](const std::string setting){
                if (settings_.find(setting) == settings_.end())
                    throw InvalidArgument(R"(Missing mandatory setting ')"
                        + setting + R"(' in )" + settingFile_);
            }
        );
    }

    void Engine::initRenderTarget() {
        auto desktopWidth = sf::VideoMode::getDesktopMode().width;
        auto desktopHeight = sf::VideoMode::getDesktopMode().height;
        auto width = std::stof(settings_["width"]);
        auto height = std::stof(settings_["height"]);
        auto isFullscreen = static_cast<bool>(std::stoi(settings_["fullscreen"]));
        if (isFullscreen || (width >= desktopWidth && height >= desktopHeight)){
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

    const std::shared_ptr<State> Engine::getState(const std::string &name) const {
        auto found = states_.find(name);
        if (found != states_.end())
            return found->second;
        return nullptr;
    }

    const std::shared_ptr<State> Engine::getCurrentState() const {
        return std::move(getState(currentState_));
    }

    const std::shared_ptr<const GuiFactory> & IME::Engine::getGuiFactory() const {
        return guiFactory_;
    }

    bool Engine::stateExists(const std::string &name) const {
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

    bool Engine::isRunning() const {
        return isRunning_;
    }

    const std::string &Engine::getPreviousStateName() const {
        return prevState_;
    }

    const Gui::Window &Engine::getRenderTarget() const {
        return window_;
    }

    const std::string &Engine::getAppName() const {
        return appName_;
    }

    Engine::~Engine() = default;
}
