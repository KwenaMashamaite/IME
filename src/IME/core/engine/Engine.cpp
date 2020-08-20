#include "IME/core/engine/Engine.h"
#include "IME/utility/Clock.h"
#include "IME/utility/ConfigFileParser.h"

namespace IME {
    std::shared_ptr<const GuiFactory> IME::Engine::guiFactory_(std::make_shared<GuiFactory>());

    Engine::Engine(const std::string &gameName, const std::string &settingsFilename)
        : isRunning_{false},
          appName_{gameName},
          settingFile_{settingsFilename}
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

    void Engine::run() {
        if (!isRunning_ && !statesManager_.isEmpty()) {
            isRunning_ = true;
            auto const frameTime = 1.0f / 60.0f;
            auto clock = Utility::Clock();
            auto deltaTime = clock.restart();
            while (window_.isOpen() && isRunning_ && !statesManager_.isEmpty()) {
                window_.processEvents();
                if (deltaTime >= frameTime) { //Fixed time step update
                    if (auto currentState = statesManager_.getCurrentState(); currentState)
                        currentState->fixedUpdate(deltaTime);
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

    const std::shared_ptr<const GuiFactory> & IME::Engine::getGuiFactory() const {
        return guiFactory_;
    }

    void Engine::update() {
        if (!isRunning_)
            window_.close();
        else
            statesManager_.getCurrentState()->update();
    }

    void Engine::render() {
        if (isRunning_)
            statesManager_.getCurrentState()->render(window_);
    }

    bool Engine::isRunning() const {
        return isRunning_;
    }

    const Gui::Window &Engine::getRenderTarget() const {
        return window_;
    }

    StateManager &Engine::getStateManager() {
        return statesManager_;
    }

    ResourceManager &Engine::getResourceManager() {
        return *resourceManager_;
    }

    const std::string &Engine::getAppName() const {
        return appName_;
    }

    Audio::AudioManager &Engine::getAudioManager() {
        return *audioManager_;
    }

    Engine::~Engine() = default;
}
