#include "IME/core/engine/Engine.h"
#include "IME/utility/Clock.h"
#include "IME/utility/ConfigFileParser.h"
#include <assert.h>

namespace IME {
    std::shared_ptr<const GuiFactory> IME::Engine::guiFactory_(std::make_shared<GuiFactory>());

    Engine::Engine(const std::string &gameName, const std::string &settingsFilename)
        : isRunning_{false},
          isInitialized_{false},
          appName_{gameName},
          settingFile_{settingsFilename},
          shouldPop_{false}
    {}

    void Engine::init() {
        //Order is important!, some operations requires others to finish first
        loadSettings();
        initResourceManager();
        initRenderTarget();
        window_.setFramerateLimit(60);
        window_.setIcon("icon.png");

        auto musicPath = settings_.getValueFor("musicPath");
        auto sfxPath = settings_.getValueFor("sfxPath");
        audioManager_ = std::make_unique<Audio::AudioManager>(musicPath, sfxPath);
        isInitialized_ = true;
    }

    void Engine::loadSettings() {
        settings_ = Utility::ConfigFileParser().parse(settingFile_);
        verifySettings();
    }

    void Engine::verifySettings() const {
        auto mandatorySettings = {"title", "width", "height", "fullscreen"};
        std::for_each(mandatorySettings.begin(), mandatorySettings.end(),
            [this](const std::string setting) {
                if (!settings_.hasProperty(setting) && settings_.getValueFor(setting).empty())
                    throw InvalidArgument(R"(Missing mandatory setting ')"
                        + setting + R"(' in )" + settingFile_);
            }
        );
    }

    void Engine::initRenderTarget() {
        auto desktopWidth = sf::VideoMode::getDesktopMode().width;
        auto desktopHeight = sf::VideoMode::getDesktopMode().height;
        auto title = settings_.getValueFor("title");
        auto width = std::stof(settings_.getValueFor("width"));
        auto height = std::stof(settings_.getValueFor("height"));
        auto isFullscreen = static_cast<bool>(std::stoi(settings_.getValueFor("fullscreen")));
        if (isFullscreen || (width >= desktopWidth && height >= desktopHeight)){
            window_.create(title, desktopWidth, desktopHeight, Gui::Window::Style::Fullscreen);
        } else {
            if (width > desktopWidth)
                width = desktopWidth;
            if (height > desktopHeight)
                height = desktopHeight;
            window_.create(title, width, height, Gui::Window::Style::Close);
        }
    }

    void Engine::initResourceManager() {
        resourceManager_ = ResourceManager::getInstance();
        resourceManager_->setPath(ResourceType::Font, settings_.getValueFor("fontsPath"));
        resourceManager_->setPath(ResourceType::Texture, settings_.getValueFor("imagesPath"));
        resourceManager_->setPath(ResourceType::Image, settings_.getValueFor("imagesPath"));
        resourceManager_->setPath(ResourceType::SoundBuffer, settings_.getValueFor("sfxPath"));
        resourceManager_->setPath(ResourceType::Music, settings_.getValueFor("musicPath"));
    }

    void Engine::processEvents() {
        sf::Event event;
        while (window_.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window_.close();
            statesManager_.getActiveState()->handleEvent(event);
            inputManager_.handleEvent(event);
        }
    }

    void Engine::run() {
        assert(isInitialized_ && "ERROR: Failed to start engine because its not initialized");
        assert(!statesManager_.isEmpty() && "ERROR: Failed to start engine because it has no states");

        statesManager_.getActiveState()->initialize();
        isRunning_ = true;
        auto const frameTime = 1.0f / 60.0f;
        auto clock = Utility::Clock();
        auto deltaTime = clock.restart();
        while (window_.isOpen() && isRunning_ && !statesManager_.isEmpty()) {
            processEvents();
            if (deltaTime >= frameTime) {
                statesManager_.getActiveState()->fixedUpdate(deltaTime);
                deltaTime = 0.0;
            }
            window_.clear();
            update();
            render();
            display();
            postFrameUpdate();
            deltaTime += clock.restart();
        }
    }

    void Engine::quit() {
        isRunning_ = false;
    }

    void Engine::update() {
        statesManager_.getActiveState()->update();
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
        shouldPop_ = true;
    }

    Definitions::Dimensions Engine::getWindowSize() const {
        return window_.getDimensions();
    }

    const std::shared_ptr<const GuiFactory> & IME::Engine::getGuiFactory() const {
        return guiFactory_;
    }

    void Engine::postFrameUpdate() {
        // Don't use if-else because popping and pushing are not mutually exclusive
        if (shouldPop_) {
            shouldPop_ = false;
            statesManager_.popState();
            if (!statesManager_.isEmpty() && !statesManager_.getActiveState()->isInitialized())
                statesManager_.getActiveState()->initialize();
        }

        if (stateToPush_) { // A state push request has been made
            stateToPush_->initialize();
            statesManager_.pushState(std::move(stateToPush_));
        }

        if (!isRunning_) {
            window_.close();
            audioManager_->stopAllAudio();
            statesManager_.clear();
        }
    }

    bool Engine::isRunning() const {
        return isRunning_;
    }

    ResourceManager &Engine::getResourceManager() {
        return *resourceManager_;
    }

    const std::string &Engine::getGameName() const {
        return appName_;
    }

    Audio::AudioManager &Engine::getAudioManager() {
        return *audioManager_;
    }

    Input::InputManager &Engine::getInputManager() {
        return inputManager_;
    }

    Engine::~Engine() = default;
}
