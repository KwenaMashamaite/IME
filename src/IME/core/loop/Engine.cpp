#include "IME/core/loop/Engine.h"
#include "IME/core/time/Clock.h"
#include "IME/utility/ConfigFileParser.h"
#include "IME/utility/ConsoleLogger.h"
#include <assert.h>
#include <cstdlib>

namespace IME {
    Engine::Engine(const std::string &gameName, const PropertyContainer &settings)
        : Engine(gameName, "")
    {
        srand(time(0));
        settings_ = settings;
    }

    Engine::Engine(const std::string &gameName, const std::string &settingsFile)
        : isSettingsLoadedFromFile_(!settingsFile.empty()),
          isRunning_{false},
          isInitialized_{false},
          appName_{gameName},
          settingFile_{settingsFile},
          shouldPop_{false},
          elapsedTime_{0.0f}
    {
        if (settingsFile.empty())
            isSettingsLoadedFromFile_ = false;
        else
            isSettingsLoadedFromFile_ = true;
    }

    void Engine::init() {
        if (isSettingsLoadedFromFile_)
            loadSettings();

        processSettings();
        initResourceManager();
        initRenderTarget();

        audioManager_ = std::make_unique<Audio::AudioManager>();
        eventDispatcher_ = EventDispatcher::instance();

        windowCloseHandler_ = [this]{quit();};
        isInitialized_ = true;
    }

    void Engine::loadSettings() {
        settings_ = Utility::ConfigFileParser().parse(settingFile_);
    }

    void Engine::processSettings() {
        static auto setDefaultValueIfNotSet = [this](const std::string& setting,
            const std::string& defaultValue) mutable {
                static auto consoleLogger = Utility::ConsoleLogger();
                if (!settings_.hasProperty(setting) && settings_.getValueFor(setting).empty()) {
                    consoleLogger.log(Utility::MessageType::Warning,
                        R"(Missing or invalid ")" + setting + R"(" entry in ")" + settingFile_
                        + R"(", using default value: ")" + setting + "=" + defaultValue + R"(")");
                    settings_.addProperty(setting, "string", defaultValue);
                }
        };

        setDefaultValueIfNotSet("windowTitle", "Infinite Motion Engine");
        setDefaultValueIfNotSet("windowWidth", "600.0f");
        setDefaultValueIfNotSet("windowHeight", "600.0f");
        setDefaultValueIfNotSet("fullscreen", "0");
        setDefaultValueIfNotSet("iconPath", "");
        setDefaultValueIfNotSet("fpsLimit", "60");
    }

    void Engine::initRenderTarget() {
        auto desktopWidth = sf::VideoMode::getDesktopMode().width;
        auto desktopHeight = sf::VideoMode::getDesktopMode().height;
        auto title = settings_.getValueFor("windowTitle");
        auto width = std::stof(settings_.getValueFor("windowWidth"));
        auto height = std::stof(settings_.getValueFor("windowHeight"));
        auto isFullscreen = static_cast<bool>(std::stoi(settings_.getValueFor("fullscreen")));
        if (isFullscreen || (width >= desktopWidth && height >= desktopHeight)){
            window_.create(title, desktopWidth, desktopHeight, Graphics::Window::Style::Fullscreen);
        } else {
            if (width > desktopWidth)
                width = desktopWidth;
            if (height > desktopHeight)
                height = desktopHeight;
            window_.create(title, width, height, Graphics::Window::Style::Close);
        }

        setFPSLimit(std::stoi(settings_.getValueFor("fpsLimit")));
        window_.setIcon(settings_.getValueFor("iconPath") + "icon.png");
    }

    void Engine::initResourceManager() {
        resourceManager_ = ResourceManager::getInstance();
        resourceManager_->setPathFor(ResourceType::Font, settings_.getValueFor("fontsPath"));
        resourceManager_->setPathFor(ResourceType::Texture, settings_.getValueFor("imagesPath"));
        resourceManager_->setPathFor(ResourceType::Image, settings_.getValueFor("imagesPath"));
        resourceManager_->setPathFor(ResourceType::SoundBuffer, settings_.getValueFor("sfxPath"));
        resourceManager_->setPathFor(ResourceType::Music, settings_.getValueFor("musicPath"));
    }

    void Engine::processEvents() {
        sf::Event event;
        while (window_.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                windowCloseHandler_();
            statesManager_.getActiveState()->handleEvent(event);
            globalInputManager_.handleEvent(event);
            inputManager_.handleEvent(event);
        }
    }

    void Engine::run() {
        assert(isInitialized_ && "ERROR: Failed to start engine because its not initialized");
        assert(!statesManager_.isEmpty() && "ERROR: Failed to start engine because it has no states");

        statesManager_.getActiveState()->initialize();
        isRunning_ = true;
        auto const frameTime = 1.0f / getFPSLimit();
        auto deltaTime = 0.0f, now = 0.0f, accumulator = 0.0f;
        auto clock = Time::Clock();
        auto prevTime = clock.getElapsedTimeInSeconds();
        while (window_.isOpen() && isRunning_ && !statesManager_.isEmpty()) {
            now = clock.getElapsedTimeInSeconds();
            deltaTime = now - prevTime;
            prevTime = now;
            accumulator += deltaTime;
            processEvents();
            while (accumulator >= frameTime) {
                statesManager_.getActiveState()->fixedUpdate(frameTime);
                accumulator -= frameTime;
            }
            update(deltaTime);
            clear();
            render();
            display();
            postFrameUpdate();
            elapsedTime_ += deltaTime;
        }
    }

    void Engine::quit() {
        isRunning_ = false;
    }

    void Engine::update(float deltaTime) {
        statesManager_.getActiveState()->update(deltaTime);
    }

    void Engine::clear() {
        window_.clear();
    }

    void Engine::render() {
        statesManager_.getActiveState()->render(window_);
    }

    void Engine::display() {
        window_.display();
    }

    void Engine::pushState(std::shared_ptr<State> state) {
        if (!isRunning_)
            statesManager_.pushState(std::move(state));
        else
            stateToPush_ = std::move(state);
    }

    void Engine::popState() {
        if (!isRunning_ && !statesManager_.isEmpty())
            statesManager_.popState();
        else
            shouldPop_ = true;
    }

    void Engine::postFrameUpdate() {
        // Don't use if-else because popping and pushing are not mutually exclusive
        if (shouldPop_) {
            shouldPop_ = false;
            inputManager_ = Input::InputManager(); //Clear current state input handlers
            statesManager_.popState();
            if (!statesManager_.isEmpty() && !statesManager_.getActiveState()->isInitialized())
                statesManager_.getActiveState()->initialize();
        }

        if (stateToPush_) {
            //@TODO - Remember input handlers on state push and only clear on state pop
            inputManager_ = Input::InputManager(); //Clear current state input handlers
            stateToPush_->initialize();
            statesManager_.pushState(std::move(stateToPush_));
        }

        if (!isRunning_) {
            window_.close();
            audioManager_->stopAllAudio();
            statesManager_.clear();
            isInitialized_ = false;
            elapsedTime_ = 0.0f;
        }
    }

    bool Engine::isRunning() const {
        return isRunning_;
    }

    void Engine::setFPSLimit(float fpsLimit) {
        window_.setFramerateLimit(fpsLimit);
        window_.setVsyncEnabled(fpsLimit >= 0);
    }

    float Engine::getElapsedTime() const {
        return elapsedTime_;
    }

    ResourceManager &Engine::getResourceManager() {
        return *resourceManager_;
    }

    const PropertyContainer &Engine::getSettings() const {
        return settings_;
    }

    float Engine::getFPSLimit() const {
        return window_.getFramerateLimit();
    }

    Audio::AudioManager &Engine::getAudioManager() {
        return *audioManager_;
    }

    Input::InputManager &Engine::getInputManager() {
        return inputManager_;
    }

    Input::InputManager &Engine::getGlobalInputManager() {
        return globalInputManager_;
    }

    Graphics::Window &Engine::getRenderTarget() {
        return window_;
    }

    void Engine::onWindowClose(Callback<> callback) {
        windowCloseHandler_ = callback;
    }
}
