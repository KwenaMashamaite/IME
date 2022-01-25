////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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
#include "IME/utility/Helpers.h"

namespace ime {
    namespace {
        template <class T>
        void setDefaultValueIfNotSet(PrefContainer& settings, const std::string& preference,
             PrefType  prefType , T&& defaultValue, const std::string& description)
        {
            if (settings.hasPref(preference) && settings.getPref(preference).hasValue())
                return;
            else if (!settings.hasPref(preference)) {
                settings.addPref({preference, prefType, std::forward<T>(defaultValue), description});
                IME_PRINT_WARNING(R"(Missing config entry ")" + preference + R"(", using default value)")
            } else {
                settings.getPref(preference).setValue<T>(std::forward<T>(defaultValue));
                IME_PRINT_WARNING(R"(Config entry ")" + preference + R"(" defined but it is not assigned any value, using default value)")
            }
        }
    }

    Engine::Engine(const std::string &gameName, const PrefContainer &settings) :
        Engine(gameName, "")
    {
        configs_ = settings;
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

        eventEmitter_.emit("initialize");
    }

    void Engine::loadSettings() {
        configs_.load(settingFile_);
    }

    void Engine::processSettings() {
        setDefaultValueIfNotSet(configs_, "WINDOW_TITLE", PrefType::String, std::string("Untitled"), "The title of the render window");
        setDefaultValueIfNotSet(configs_, "WINDOW_ICON", PrefType::String, std::string("OS"), "The icon of the render window");
        setDefaultValueIfNotSet(configs_, "WINDOW_WIDTH", PrefType::Int, 600, "The width of the render window");
        setDefaultValueIfNotSet(configs_, "WINDOW_HEIGHT", PrefType::Int, 600, "The height of the render window");
        setDefaultValueIfNotSet(configs_, "FPS_LIMIT", PrefType::Int, 60, "The frames per second limit of the render window");
        setDefaultValueIfNotSet(configs_, "FULLSCREEN", PrefType::Bool, false, "Indicates whether or not the render window should be created in full screen mode");
        setDefaultValueIfNotSet(configs_, "V_SYNC", PrefType::Bool, false, "Indicates whether or not vertical synchronization should be enabled");
        setDefaultValueIfNotSet(configs_, "FONTS_DIR", PrefType::String, std::string(""), "The directory in which fonts can be found");
        setDefaultValueIfNotSet(configs_, "TEXTURES_DIR", PrefType::String, std::string(""), "The directory in which textures/images can be found");
        setDefaultValueIfNotSet(configs_, "SOUND_EFFECTS_DIR", PrefType::String, std::string(""), "The directory in which sound effects can be found");
        setDefaultValueIfNotSet(configs_, "MUSIC_DIR", PrefType::String, std::string(""), "The directory in which music can be found");
    }

    void Engine::initRenderTarget() {
        auto title = configs_.getPref("WINDOW_TITLE").getValue<std::string>();
        auto width = configs_.getPref("WINDOW_WIDTH").getValue<int>();
        auto height = configs_.getPref("WINDOW_HEIGHT").getValue<int>();

        IME_ASSERT(width > 0, "The width of the window cannot be negative")
        IME_ASSERT(height > 0, "The height of the window cannot be negative")

        // Create the window
        privWindow_->create(title, width, height, window_->getStyle());
        window_->setFullScreen(configs_.getPref("FULLSCREEN").getValue<bool>());
        window_->setFrameRateLimit(configs_.getPref("FPS_LIMIT").getValue<int>());
        window_->setVerticalSyncEnable(configs_.getPref("V_SYNC").getValue<bool>());

        // Set the window icon
        if (configs_.getPref("WINDOW_ICON").getValue<std::string>() != "OS")
            privWindow_->setIcon(configs_.getPref("WINDOW_ICON").getValue<std::string>());

        // Shutdown engine when window close event is triggered
        window_->defaultWinCloseHandlerId_ = window_->onClose([this] {
            quit();
        });

        // Because the window is destroyed and recreated when we enter full screen,
        // SFML does not generate a resized event. This cause some issues with
        // TGUI, so we associate a full screen toggle with a resize event
        window_->onFullScreenToggle([this] (bool) {
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
        resourceManager_->setPathFor(ResourceType::Font, configs_.getPref("FONTS_DIR").getValue<std::string>());
        resourceManager_->setPathFor(ResourceType::Texture, configs_.getPref("TEXTURES_DIR").getValue<std::string>());
        resourceManager_->setPathFor(ResourceType::Image, configs_.getPref("TEXTURES_DIR").getValue<std::string>());
        resourceManager_->setPathFor(ResourceType::SoundEffect, configs_.getPref("SOUND_EFFECTS_DIR").getValue<std::string>());
        resourceManager_->setPathFor(ResourceType::Music, configs_.getPref("MUSIC_DIR").getValue<std::string>());
    }

    void Engine::processEvents() {
        Event event;
        while (privWindow_->pollEvent(event)) {
            if (event.type == Event::Closed)
                window_->emitCloseEvent();
            else if (event.type == Event::Resized) {
                // A ime::Window may have a min and max size bounds
                window_->setSize(Vector2u{event.size.width, event.size.height});
                Vector2u newWinSize = window_->getSize();
                event.size.width = newWinSize.x;
                event.size.height = newWinSize.y;

                // Resize for bounds dimension is emitted by Window::setSize
                if (newWinSize != window_->getMinSize() && newWinSize != window_->getMaxSize())
                    window_->emitResize({event.size.width, event.size.height});

            } else if (event.type == Event::GainedFocus)
                window_->emitFocusChange(true);
            else if (event.type == Event::LostFocus)
                window_->emitFocusChange(false);
            else if (event.type == Event::MouseEntered)
                window_->emitMouseCursor(true);
            else if (event.type == Event::MouseLeft)
                window_->emitMouseCursor(false);

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
        Time deltaTime;
        Clock gameClock;
        eventEmitter_.emit("start");
        sceneManager_->enterTopScene();
        eventEmitter_.emit("sceneActivate", sceneManager_->getActiveScene());

        while (window_->isOpen() && isRunning_ && !sceneManager_->isEmpty()) {
            eventEmitter_.emit("frameStart");
            deltaTime = gameClock.restart();
            preUpdate(deltaTime);
            processEvents();
            update(deltaTime);
            clear();
            render();
            display();
            postFrameUpdate();
            elapsedTime_ += deltaTime;
            eventEmitter_.emit("frameEnd");
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

        const Time frameTime = seconds( 1.0f / window_->getFrameRateLimit());
        static Time accumulator = Time::Zero;

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

    void Engine::pushScene(Scene::Ptr scene) {
        IME_ASSERT(scene, "A scene pushed to the engine cannot be a nullptr")
        if (!isRunning_)
            sceneManager_->pushScene(std::move(scene));
        else
            scenesPendingPush_.push(std::move(scene));
    }

    bool Engine::pushCachedScene(const std::string &name) {
        Scene::Ptr scene = sceneManager_->popCached(name);

        if (scene) {
            pushScene(std::move(scene));
            return true;
        }

        return false;
    }

    void Engine::popScene() {
        if (!isRunning_)
            sceneManager_->popScene();
        else
            popCounter_++;
    }

    void Engine::cacheScene(const std::string &name, Scene::Ptr scene) {
        IME_ASSERT(scene, "A cached scene cannot be a nullptr")
        scene->init(*this);
        sceneManager_->cache(name, std::move(scene));
    }

    bool Engine::uncacheScene(const std::string &name) {
        return sceneManager_->removeCached(name);
    }

    bool Engine::isSceneCached(const std::string &name) const {
        return sceneManager_->isCached(name);
    }

    void Engine::removeAllScenesExceptActive() {
        sceneManager_->clearAllExceptActive();
        popCounter_ = 0;
    }

    std::size_t Engine::getSceneCount() const {
        return sceneManager_->getSceneCount();
    }

    Scene* Engine::getActiveScene() {
        return sceneManager_->getActiveScene();
    }

    const Scene* Engine::getActiveScene() const {
        return sceneManager_->getActiveScene();
    }

    Scene *Engine::getBackgroundScene() {
        return const_cast<Scene*>(std::as_const(*this).getBackgroundScene());
    }

    const Scene *Engine::getBackgroundScene() const {
        if (isRunning_)
            return sceneManager_->getBackgroundScene();
        else
            return nullptr;
    }

    Scene *Engine::getCachedScene(const std::string &name) {
        return sceneManager_->getCached(name);
    }

    const Scene *Engine::getCachedScene(const std::string &name) const {
        return sceneManager_->getCached(name);
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

            bool isPrevSceneResumed = popCounter_ == 1 && scenesPendingPush_.empty();
            sceneManager_->popScene(isPrevSceneResumed);
            popCounter_--;

            if (isPrevSceneResumed && !sceneManager_->isEmpty())
                eventEmitter_.emit("sceneActivate", sceneManager_->getActiveScene());
        }

        while (!scenesPendingPush_.empty()) {
            scenesPendingPush_.front()->init(*this);

            if (scenesPendingPush_.size() == 1) { // Add scene and immediately enter it
                sceneManager_->pushScene(std::move(scenesPendingPush_.front()), true);
                scenesPendingPush_.pop();
                eventEmitter_.emit("sceneActivate", sceneManager_->getActiveScene());
                break;
            } else {
                sceneManager_->pushScene(std::move(scenesPendingPush_.front()));
                scenesPendingPush_.pop();
            }
        }
    }

    void Engine::shutdown() {
        eventEmitter_.emit("shutdown");
        eventEmitter_.clear();
        audioManager_.stopAll();
        audioManager_.removePlayedAudio();
        isInitialized_ = false;
        isRunning_ = false;
        popCounter_ = 0;
        isSettingsLoadedFromFile_ = false;
        elapsedTime_ = Time::Zero;
        gameTitle_.clear();
        settingFile_.clear();
        configs_.clear();
        sceneManager_->clear();
        sceneManager_->clearCachedScenes();
        timerManager_.clear();
        dataSaver_.clear();
        diskDataSaver_.clear();
        resourceManager_.reset();
        inputManager_ = input::InputManager();
        eventDispatcher_.reset();

        while (!scenesPendingPush_.empty())
            scenesPendingPush_.pop();

        window_->close();

        if (onShutdownComplete_) {
            onShutdownComplete_();
            onShutdownComplete_ = nullptr;
        }
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

    const ui::GuiContainer &Engine::getGui() const {
        return gui_;
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

    const PropertyContainer &Engine::getPersistentData() const {
        return dataSaver_;
    }

    PrefContainer &Engine::getSavablePersistentData() {
        return diskDataSaver_;
    }

    const PrefContainer &Engine::getSavablePersistentData() const {
        return diskDataSaver_;
    }

    audio::AudioManager &Engine::getAudioManager() {
        return audioManager_;
    }

    const audio::AudioManager &Engine::getAudioManager() const {
        return audioManager_;
    }

    input::InputManager &Engine::getInputManager() {
        return inputManager_;
    }

    const input::InputManager &Engine::getInputManager() const {
        return inputManager_;
    }

    TimerManager &Engine::getTimer() {
        return timerManager_;
    }

    const TimerManager &Engine::getTimer() const {
        return timerManager_;
    }

    priv::RenderTarget &Engine::getRenderTarget() {
        return *privWindow_;
    }

    void Engine::suspendedEventListener(int id, bool suspend) {
        eventEmitter_.suspendEventListener(id, suspend);
    }

    bool Engine::isEventListenerSuspended(int id) const {
        return eventEmitter_.isEventListenerSuspended(id);
    }

    bool Engine::removeEventListener(int id) {
        return eventEmitter_.removeEventListener(id);
    }

    Window &Engine::getWindow() {
        return *window_;
    }

    const Window &Engine::getWindow() const {
        return *window_;
    }

    int Engine::onInit(const Callback<>& callback) {
        return eventEmitter_.addEventListener( "initialize", callback);
    }

    int Engine::onSceneActivate(const Callback<Scene*> &callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "sceneActivate", callback, oneTime);
    }

    int Engine::onFrameStart(const Callback<>& callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "frameStart", callback, oneTime);
    }

    int Engine::onFrameEnd(const Callback<>& callback, bool oneTime) {
        return utility::addEventListener(eventEmitter_, "frameEnd", callback, oneTime);
    }

    int Engine::onStart(const Callback<>& callback) {
        return eventEmitter_.addEventListener("start", callback);
    }

    int Engine::onShutDown(const Callback<>& callback) {
        return eventEmitter_.addEventListener("shutdown", callback);
    }

    void Engine::onShutdownComplete(const Callback<> &callback) {
        onShutdownComplete_ = callback;
    }

    Engine::~Engine() = default;
}
