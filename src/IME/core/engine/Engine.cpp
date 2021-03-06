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

#include "IME/core/engine/Engine.h"
#include "IME/core/time/Clock.h"
#include "IME/core/scene/SceneManager.h"
#include "IME/core/resources/ResourceManager.h"
#include "IME/graphics/RenderTarget.h"

namespace ime {
    namespace {
        template <class T>
        void setDefaultValueIfNotSet(PropertyContainer& settings,
            const std::string& setting, T&& defaultValue)
        {
            if (settings.hasProperty(setting) && settings.propertyHasValue(setting))
                return;
            else if (!settings.hasProperty(setting)) {
                settings.addProperty({setting, std::forward<T>(defaultValue)});
                IME_PRINT_WARNING(R"(Missing config entry ")" + setting + R"(", using default value)")
            } else {
                settings.setValue<T>(setting, std::forward<T>(defaultValue));
                IME_PRINT_WARNING(R"(Config entry ")" + setting + R"(" defined but it is not assigned any value, using default value)")
            }
        }
    }

    Engine::Engine(const std::string &gameName, const PropertyContainer& settings) :
        Engine(gameName, "")
    {
        settings_ = settings;
    }

    Engine::Engine(const std::string &gameName, const PrefContainer &settings) :
        Engine(gameName, "")
    {
        configs_ = settings;
        settings_ = settings.asPropertyContainer();
    }

    Engine::Engine(const std::string &gameTitle, const std::string &settingsFile) :
        privWindow_{std::make_unique<priv::RenderTarget>()},
        window_{new Window(*privWindow_)},
        gameTitle_{gameTitle},
        settingFile_{settingsFile},
        isSettingsLoadedFromFile_(!settingsFile.empty() && settingsFile != "default"),
        isInitialized_{false},
        isRunning_{false},
        isPaused_{false},
        sceneManager_{std::make_unique<priv::SceneManager>()},
        popCounter_{0}
    {}

    void Engine::initialize() {
        if (isSettingsLoadedFromFile_)
            loadSettings();

        processSettings();
        initResourceManager();
        initRenderTarget();
        gui_.setTarget(*privWindow_);

        eventDispatcher_ = EventDispatcher::instance();
        isInitialized_ = true;
    }

    void Engine::loadSettings() {
        configs_.load(settingFile_);
        settings_ = configs_.asPropertyContainer();
    }

    void Engine::processSettings() {
        setDefaultValueIfNotSet(settings_, "WINDOW_TITLE", std::string("Untitled"));
        setDefaultValueIfNotSet(settings_, "WINDOW_ICON", std::string(""));
        if (settings_.getValue<std::string>("WINDOW_ICON").empty())
            settings_.setValue<std::string>("WINDOW_ICON", "OS"); //Operating System icon

        setDefaultValueIfNotSet(settings_, "WINDOW_WIDTH",  600);
        setDefaultValueIfNotSet(settings_, "WINDOW_HEIGHT", 600);
        setDefaultValueIfNotSet(settings_, "FPS_LIMIT", 60);
        setDefaultValueIfNotSet(settings_, "FULLSCREEN", false);
        setDefaultValueIfNotSet(settings_, "V_SYNC",  false);
        setDefaultValueIfNotSet(settings_, "FONTS_DIR", std::string("")); // Same directory as the executable
        setDefaultValueIfNotSet(settings_, "TEXTURES_DIR", std::string(""));
        setDefaultValueIfNotSet(settings_, "SOUND_EFFECTS_DIR", std::string(""));
        setDefaultValueIfNotSet(settings_, "MUSIC_DIR", std::string(""));
    }

    void Engine::initRenderTarget() {
        auto title = settings_.getValue<std::string>("WINDOW_TITLE");
        auto width = settings_.getValue<int>("WINDOW_WIDTH");
        auto height = settings_.getValue<int>("WINDOW_HEIGHT");

        IME_ASSERT(width > 0, "The width of the window cannot be negative")
        IME_ASSERT(height > 0, "The height of the window cannot be negative")

        // Create the window
        privWindow_->create(title, width, height, window_->getStyle());
        window_->setFullScreen(settings_.getValue<bool>("FULLSCREEN"));
        window_->setFrameRateLimit(settings_.getValue<int>("FPS_LIMIT"));
        window_->setVerticalSyncEnable(settings_.getValue<bool>("V_SYNC"));

        // Set the window icon
        if (settings_.getValue<std::string>("WINDOW_ICON") != "OS")
            privWindow_->setIcon(settings_.getValue<std::string>("WINDOW_ICON"));

        // Shutdown engine when window close event is triggered
        window_->onClose([this] {
            quit();
        });

        // Because the window is destroyed and recreated when we enter full screen,
        // SFML does not generate a resized event. This cause some issues with
        // TGUI, so we associate a full screen toggle with a resize event
        window_->onFullScreenToggle([this] {
            Event event;
            event.type = Event::Resized;
            event.size.width = window_->getSize().x;
            event.size.height = window_->getSize().y;
            gui_.handleEvent(event);
            sceneManager_->handleEvent(event);
        });
    }

    void Engine::initResourceManager() {
        resourceManager_ = ResourceManager::getInstance();
        resourceManager_->setPathFor(ResourceType::Font, settings_.getValue<std::string>("FONTS_DIR"));
        resourceManager_->setPathFor(ResourceType::Texture, settings_.getValue<std::string>("TEXTURES_DIR"));
        resourceManager_->setPathFor(ResourceType::Image, settings_.getValue<std::string>("TEXTURES_DIR"));
        resourceManager_->setPathFor(ResourceType::SoundBuffer, settings_.getValue<std::string>("SOUND_EFFECTS_DIR"));
        resourceManager_->setPathFor(ResourceType::Music, settings_.getValue<std::string>("MUSIC_DIR"));
    }

    void Engine::processEvents() {
        Event event;
        while (privWindow_->pollEvent(event)) {
            if (event.type == Event::Closed)
                window_->emitCloseEvent();

            gui_.handleEvent(event);
            inputManager_.handleEvent(event);
            sceneManager_->handleEvent(event);
        }
    }

    void Engine::run() {
        if (isRunning_) {
            IME_PRINT_WARNING("Engine cannot be rerun while it is running, stop it first then call 'run' again")
            return;
        }

        IME_ASSERT(isInitialized_, "Failed to start engine because its not initialized")
        IME_ASSERT(!sceneManager_->isEmpty(), "Failed to start engine because it has no states")

        // Initialize scenes that were added to the engine before it was ran. Scenes
        // that are added while the engine is running are initialized before they are
        // pushed to the scene manager whilst scenes that are added before the engine
        // ran are immediately added to the scene manager and await late initialization
        sceneManager_->forEachScene([this](const Scene::Ptr& scene) {
            scene->init(*this);
        });

        isRunning_ = true;
        sceneManager_->enterTopScene();
        Time deltaTime;
        Clock gameClock;
        while (window_->isOpen() && isRunning_ && !sceneManager_->isEmpty()) {
            deltaTime = gameClock.restart();
            if (onFrameStart_)
                onFrameStart_();

            preUpdate(deltaTime);
            processEvents();
            update(deltaTime);
            clear();
            render();
            display();
            postFrameUpdate();
            elapsedTime_ += deltaTime;
        }

        shutdown();
    }

    void Engine::quit() {
        isRunning_ = false;
    }

    void Engine::preUpdate(Time deltaTime) {
        if (isPaused_)
            return;

        sceneManager_->preUpdate(deltaTime);
    }

    void Engine::update(Time deltaTime) {
        if (isPaused_)
            return;

        auto const frameTime = seconds( 1.0f / window_->getFrameRateLimit());
        auto static accumulator = Time::Zero;

        // Fixed update
        accumulator += deltaTime;
        while (accumulator >= frameTime) {
            sceneManager_->fixedUpdate(frameTime);
            accumulator -= frameTime;
        }

        // Normal update
        timerManager_.update(deltaTime);
        sceneManager_->update(deltaTime);
    }

    void Engine::clear() {
        privWindow_->clear(window_->getClearColour());
    }

    void Engine::render() {
        sceneManager_->render(*privWindow_);
        gui_.draw();
    }

    void Engine::display() {
        privWindow_->display();
    }

    void Engine::pushScene(Scene::Ptr scene, Callback<> callback) {
        IME_ASSERT(scene, "A scene pushed to the engine cannot be a nullptr")
        if (!isRunning_)
            sceneManager_->pushScene(std::move(scene));
        else
            scenesPendingPush_.push({std::move(scene), std::move(callback)});
    }

    void Engine::popScene() {
        if (!isRunning_)
            sceneManager_->popScene();
        else
            popCounter_++;
    }

    void Engine::removeAllScenesExceptActive() {
        sceneManager_->clearAllExceptActive();
        popCounter_ = 0;
    }

    std::size_t Engine::getSceneCount() const {
        return sceneManager_->getSceneCount();
    }

    void Engine::postFrameUpdate() {
        audioManager_.removePlayedAudio();
        timerManager_.preUpdate();

        // Note: Always check pending pop first before pending pushes
        while (popCounter_ > 0) {
            if (sceneManager_->isEmpty()) { // Engine::PopScene called more than the number of scenes
                popCounter_ = 0;
                break;
            }
            sceneManager_->popScene();
            popCounter_--;
        }

        while (!scenesPendingPush_.empty()) {
            scenesPendingPush_.front().first->init(*this);

            if (scenesPendingPush_.size() == 1) { // Add scene and immediately enter it
                sceneManager_->pushScene(std::move(scenesPendingPush_.front().first), true);
                if (auto& callback = scenesPendingPush_.front().second; callback)
                    callback();

                scenesPendingPush_.pop();
                break;
            } else {
                sceneManager_->pushScene(std::move(scenesPendingPush_.front().first));
                scenesPendingPush_.pop();
            }
        }

        // Execute frame end listener
        if (onFrameEnd_)
            onFrameEnd_();
    }

    void Engine::shutdown() {
        eventEmitter_.emit("shutdown");
        audioManager_.stopAll();
        audioManager_.removePlayedAudio();
        window_->close();
        isInitialized_ = false;
        isRunning_ = false;
        popCounter_ = 0;
        isSettingsLoadedFromFile_ = false;
        elapsedTime_ = Time::Zero;
        gameTitle_.clear();
        settingFile_.clear();
        settings_.clear();
        sceneManager_->clear();
        timerManager_.clear();
        dataSaver_.clear();
        resourceManager_.reset();
        inputManager_ = input::InputManager();
        eventDispatcher_.reset();
        onFrameEnd_ = nullptr;
        onFrameStart_ = nullptr;

        while (!scenesPendingPush_.empty())
            scenesPendingPush_.pop();
    }

    bool Engine::isRunning() const {
        return isRunning_;
    }

    void Engine::setPause(bool pause) {
        isPaused_ = pause;
    }

    bool Engine::isPaused() const {
        return isPaused_;
    }

    Time Engine::getElapsedTime() const {
        return elapsedTime_;
    }

    ui::GuiContainer &Engine::getGui() {
        return gui_;
    }

    const PropertyContainer &Engine::getSettings() const {
        return settings_;
    }

    PrefContainer &Engine::getConfigs() {
        return configs_;
    }

    const PrefContainer &Engine::getConfigs() const {
        return configs_;
    }

    const std::string &Engine::getGameName() const {
        return gameTitle_;
    }

    PropertyContainer &Engine::getPersistentData() {
        return dataSaver_;
    }

    audio::AudioManager &Engine::getAudioManager() {
        return audioManager_;
    }

    input::InputManager &Engine::getInputManager() {
        return inputManager_;
    }

    priv::RenderTarget &Engine::getRenderTarget() {
        return *privWindow_;
    }

    void Engine::setTimeout(Time delay, ime::Callback<Timer&> callback) {
        timerManager_.setTimeout(delay, std::move(callback));
    }

    void Engine::setInterval(Time delay, ime::Callback<Timer&> callback, int repeatCount) {
        timerManager_.setInterval(delay, std::move(callback), repeatCount);
    }

    Window &Engine::getWindow() {
        return *window_;
    }

    const Window &Engine::getWindow() const {
        return *window_;
    }

    void Engine::onWindowClose(Callback<> callback) {
        window_->onClose(callback);
    }

    void Engine::onFrameStart(Callback<> callback) {
        onFrameStart_ = std::move(callback);
    }

    void Engine::onFrameEnd(Callback<> callback) {
        onFrameEnd_ = std::move(callback);
    }

    void Engine::onShutDown(Callback<> callback) {
        eventEmitter_.addEventListener("shutdown", std::move(callback));
    }

    Engine::~Engine() = default;
}
