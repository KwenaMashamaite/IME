////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#ifndef IME_ENGINE_H
#define IME_ENGINE_H

#include "IME/Config.h"
#include "IME/core/audio/AudioManager.h"
#include "IME/ui/GuiContainer.h"
#include "IME/core/input/InputManager.h"
#include "IME/core/event/EventDispatcher.h"
#include "IME/core/time/TimerManager.h"
#include "IME/common/PrefContainer.h"
#include "IME/core/scene/Scene.h"
#include "IME/core/time/Timer.h"
#include "IME/graphics/WindowStyles.h"
#include "IME/graphics/Window.h"
#include <queue>

namespace ime {

    /// @internal
    namespace priv {
        class SceneManager;
        class RenderTarget;
    }

    /// @internal
    class ResourceManager;

    /**
     * @brief Runs the main game loop
     */
    class IME_API Engine {
    public:
        /**
         * @brief Constructor
         * @param gameTitle The name of the game run by the engine
         * @param settingsFile Filename of the file that contains the engines
         *                     settings
         *
         * @a settingsFile must have the filename preceded by the path to the
         * file. The path must be relative to the directory that contains the
         * game executable. If @a settingsFile is left unspecified the engine
         * will be constructed with default settings
         */
        explicit Engine(const std::string &gameTitle, const std::string &settingsFile = "default");

        /**
         * @deprecated Since v2.1.0, will be removed in v2.2.0. Use
         *             ime::Engine::Engine(const std::string&, const ime::PrefContainer&) instead.
         *
         * @brief Constructor
         * @param gameName The name of the game to be run by the engine
         * @param settings Settings to construct engine with
         */
         [[deprecated("Use 'ime::Engine::Engine(const std::string&, const ime::PrefContainer&)' instead.")]]
        Engine(const std::string& gameName, const PropertyContainer& settings);

        /**
         * @brief Constructor
         * @param gameName The name of the game
         * @param settings Settings to construct the engine with
         */
        Engine(const std::string& gameName, const PrefContainer& settings);

        /**
         * @brief Copy constructor
         */
        Engine(const Engine&) = delete;

        /**
         * @brief Copy assignment operator
         */
        Engine& operator=(const Engine&) = delete;

        /**
         * @brief Move constructor
         */
        Engine(Engine&&) = delete;

        /**
         * @brief Move Assignment operator
         */
        Engine& operator=(Engine&&) = delete;

        /**
         * @brief Initialize the engine
         *
         * @warning This function must be called before the engine is run()
         */
        void initialize();

        /**
         * @brief Start the main loop
         *
         * @warning The engine must be initialized this function is called. In
         * addition, there must be at least one scene added to the engine for
         * the it to run
         *
         * @see initialize and pushScene
         */
        void run();

        /**
         * @brief Check if the engine is running or not
         * @return True if the engine is running, otherwise false
         */
        bool isRunning() const;

        /**
         * @brief Stop the engine
         *
         * This function will remove all scenes that have been added to the
         * engine and reset it's initialization state. Therefore, the engine
         * must be reinitialized before it is re-run
         *
         * @see initialize and run
         */
        void quit();

        /**
         * @brief Pause or resume the engine
         * @param pause True to pause the engine or false to resume it
         *
         * When the engine is paused, it keeps running, this means that the
         * isRunning() function will return true if the engine was started.
         * However, the current scene will not receive time updates. This
         * effectively pauses all time dependent operations such as animations,
         * physics, movements, time-based callbacks and so on... The same
         * effect can be achieved by setting the scenes timescale to 0. The
         * difference between the two is that the latter invokes the scenes
         * update functions with a delta time of ime::Time::Zero whilst the
         * former does not invoke the update functions at all.
         *
         * Note that events are dispatched when the engine is paused, thus
         * user input is not blocked
         *
         * By default the engine is not paused
         */
        void setPause(bool pause);

        /**
         * @brief Check if then engine is paused or not
         * @return True if paused, otherwise false
         *
         * @see setPause
         */
        bool isPaused() const;

        /**
         * @deprecated Since v2.1.0, will be removed in v2.2.0. Use
         *             ime::Engine::getConfigs instead.
         *
         * @brief Get the engines settings
         * @return The engines settings
         */
         [[deprecated("Use 'ime::PrefContainer& ime::Engine::getConfigs()' instead.")]]
        const PropertyContainer& getSettings() const;

         /**
          * @brief Get the engines settings
          * @return The engines settings
          */
         PrefContainer& getConfigs();
         const PrefContainer& getConfigs() const;

        /**
         * @brief Get persistent data
         * @return Persistent data
         *
         * Data stored in the this object persists from scene to scene.
         * This means that the data is preserved during a scene push or
         * pop. This is useful if you want share data between scenes. For
         * example, a scene may save data before its destroyed/paused and
         * the next scene can access the data and update for the next scene
         * or for the previous scene when it is resumed
         *
         * @warning The data is destroyed when the engine is shutdown
         *
         * @see quit
         */
        PropertyContainer& getPersistentData();

        /**
         * @brief Get the name of the game run by the engine
         * @return The name of the game run by the engine
         *
         * This is the name provided during construction of the engine
         */
        const std::string& getGameName() const;

        /**
         * @brief Add a scene to the engine
         * @param scene Scene to be added
         * @param callback Optional function to be executed after the scene
         *                 is added
         *
         * If the engine is running, then the scene will NOT be pushed immediately
         * but rather at the end of the current frame. Any operation performed
         * on the engine before the end of the current frame will reflect on
         * the current scene and not the scene to be pushed. A callback must
         * be provided if the need to perform an operation immediately after
         * a scene is pushed arises. If the engine is NOT running, then the
         * scene will be pushed immediately and the callback function is
         * ignored
         *
         * @warning If multiple scenes are pushed to the engine in the same
         * frame, the last scene to be received before the frame end will be
         * the active scene. All the other scenes will be pushed without
         * initialization. This means that only the optional callback attached
         * to the last scene will be invoked
         */
        void pushScene(Scene::Ptr scene, Callback<> callback = nullptr);

        /**
         * @brief Remove the current scene from the engine
         *
         * If the engine is not running, the scene will be removed immediately,
         * otherwise the scene will be removed at the end of the current frame.
         * Note that multiple scenes may be removed in the same frame by calling
         * this function as many times as the number of scenes to be removed.
         * In addition, Calling this function when the engine has no scenes
         * has no effect
         *
         * @see pushScene
         */
        void popScene();

        /**
         * @brief Remove all the scenes from the engine except the current
         *        active scene
         *
         * Note that if this function is called whilst the engine is NOT
         * running, then all the scenes will be removed from the engine.
         * Since the engine must always have at least one scene to run,
         * scenes cannot be removed all at once while the engine is running.
         * However you can use the following workaround to do so:
         *
         * @code
         * engine.removeAllScenesExceptActive();
         * engine.popScene(); // Remove remaining active scene at the end of the frame
         * @endcode
         *
         * @see pushScene, popScene, run and quit
         */
        void removeAllScenesExceptActive();

        /**
         * @brief Get the number of scenes in the engine
         * @return The number of scenes in the engine
         */
        std::size_t getSceneCount() const;

        /**
         * @brief Get the time passed since the engine was started
         * @return The time passed since the engine was started
         *
         * @note The elapsed time will reset to zero when the engine is
         * shutdown
         */
        Time getElapsedTime() const;

        /**
         * @brief Get access to the engines game window
         * @return The engines game window
         *
         * @see initialize
         */
        Window& getWindow();
        const Window& getWindow() const;

        /**
         * @brief Get the engine level gui
         * @return The engine level gui
         *
         * Unlike ime::Scene::gui, this gui is not destroyed when the scene
         * is destroyed, but rather when the engine is shutdown. It may be
         * useful when the same UI is required across multiple scenes. Note
         * that this gui is rendered on top of the scene level gui
         */
        ui::GuiContainer& getGui();

        /**
         * @brief Get the engine level audio manager
         * @return The engine level audio manager
         *
         * Unlike ime::Scene::audio, this audio manager is not destroyed
         * when the scene is destroyed, but rather when the engine is
         * shutdown
         */
        audio::AudioManager& getAudioManager();

        /**
         * @brief Get the engine level input manager
         * @return The engine level input manager
         *
         * Unlike ime::Scene::input, event listeners registered to this input
         * manager are executed regardless of which scene is active and are
         * only destroyed when the engine is shutdown
         */
        input::InputManager& getInputManager();

        /**
         * @brief Schedule a callback to be executed after a delay
         * @param delay Time to wait before executing the callback
         * @param callback Function to be executed when the delay expires
         *
         * This function will execute a callback function once after
         * @a delay seconds. To execute a callback repeatedly every
         * interval, use the setInterval() function
         *
         * Unlike ime::Scene::timer, callbacks registered to this timer
         * are executed regardless of which scene is active and are only
         * destroyed when the engine is shutdown or the timer has expired
         *
         * @warning The timer will be destroyed after the callback is invoked
         * or if it is externally stopped before the callback is invoked
         *
         * @see setInterval
         */
        void setTimeout(Time delay, ime::Callback<Timer&> callback);

        /**
         * @brief Schedule a callback to be executed every interval
         * @param delay Time to wait before executing the callback
         * @param callback Function to be executed
         * @param repeatCount The number of times to repeat the interval
         *
         * Unlike setTimeout(), this function will execute a callback
         * every @a delay seconds for a specified number of times while
         * the engine is running. By default the repeat counter is -1,
         * this means that the callback will repeat forever. The repetition
         * can be also be cancelled by calling setRepeat(0) on the returned
         * timer
         *
         * Unlike ime::Scene::timer, callbacks registered to this timer
         * are executed regardless of which scene is active and are only
         * destroyed when the engine is shutdown or the timer has expired
         *
         * @warning The timer will be destroyed if the timer is externally
         * stopped or the repetition is cancelled
         *
         * @see setTimeout
         */
        void setInterval(Time delay, ime::Callback<Timer&> callback, int repeatCount = -1);

        /**
         * @deprecated Since v2.1.0, will be removed in v2.2.0. Use
         *             ime::Window::onClose instead.
         *
         * @brief Add an event lister to a window close event
         * @param callback Function to execute when a window close event is fired
         *
         * The callback function will be called by the engine when a request
         * to close the window is made by the user. The default behavior stops
         * the engine and closes the render window.
         *
         * @note Only one event listener may be registered to this event. This
         * means that when a new event listener is added, the previous one is
         * removed. As a result, adding a window close event listener overwrites
         * the default behavior. Pass nullptr to stop the callback from being
         * invoked
         */
         [[deprecated("use 'void ime::Window::onClose(const Callback&)' instead.")]]
        void onWindowClose(Callback<> callback);

        /**
         * @brief Execute a function at the start of a frame
         * @param callback Function to executed when a frame starts
         *
         * @note Only one callback may be registered at a time. Pass nullptr
         * to stop the callback from being invoked.
         *
         * By default no callback is registered to this event
         */
        void onFrameStart(Callback<> callback);

        /**
         * @brief Execute a function at the end of the current frame
         * @param callback Function to be executed
         *
         * @note Only one callback may be registered at a time. Pass nullptr
         * to stop the callback from being invoked.
         *
         * By default, no callback is registered to this event
         */
        void onFrameEnd(Callback<> callback);

        /**
         * @brief Execute a callback when the engine is shut down
         * @param callback The function to be executed
         *
         * This callback is called before the engine executes its shutdown
         * sequence
         */
        void onShutDown(Callback<> callback);

        /**
         * @internal
         * @brief Get access to the engines render target
         * @return The engines render target
         *
         * @warning This function must be called after the engine has been
         *          initialized
         *
         * Note that this function is intended for internal use only
         *
         * @see getWindow
         */
        priv::RenderTarget& getRenderTarget();

        /**
         * @brief Destructor
         */
        ~Engine();

    private:
        /**
         * @brief Load engine settings from the disk
         * @throws InvalidArgument if anu of settings entries are invalid
         */
        void loadSettings();

        /**
         * @brief Check if all the mandatory settings have been declared
         *
         * If any of the mandatory setting is missing, a default value will
         * be used
         */
        void processSettings();

        /**
         * @brief Initialize the render target
         */
        void initRenderTarget();

        /**
         * @brief Initialize the resource manager
         */
        void initResourceManager();

        /**
         * @brief Process events for the current frame
         */
        void processEvents();

        /**
         * @brief Pre-update current frame
         * @param deltaTime Time passed since last pre-update
         */
        void preUpdate(Time deltaTime);

        /**
         * @brief Update current frame
         * @param deltaTime Time passed since last frame update
         */
        void update(Time deltaTime);

        /**
         * @brief Clear contents of the previous frame from the render window
         */
        void clear();

        /**
         * @brief Render current frame
         */
        void render();

        /**
         * @brief Display current frame
         */
        void display();

        /**
         * @brief Update the engine after rendering the current frame
         */
        void postFrameUpdate();

        /**
         * @brief Stop the engine and clear all data
         */
        void shutdown();

    private:
        std::unique_ptr<priv::RenderTarget> privWindow_;   //!< The engines render target
        std::unique_ptr<Window> window_;                   //!< Exposes parts of priv::RenderTarget through its public interface
        std::string gameTitle_;                            //!< The name of the game run by the engine
        std::string settingFile_;                          //!< The filename of the file that contains the engines config entries
        PropertyContainer settings_;                       ///@deprecated since v2.1.0, Replace with configs_ v2.2.0
        PrefContainer configs_;                            //!< The engines settings
        bool isSettingsLoadedFromFile_;                    //!< A flag indicating whether or not config entries are loaded by the engine or are received during construction
        bool isInitialized_;                               //!< A flag indicating whether or not the engine has been initialized
        bool isRunning_;                                   //!< A flag indicating whether or not the engine is running
        bool isPaused_;                                    //!< A flag indicating whether or not the engine is paused
        Time elapsedTime_;                                 //!< The time passed since the engine started running
        std::unique_ptr<priv::SceneManager> sceneManager_; //!< The scene manager
        audio::AudioManager audioManager_;                 //!< The engine level audio manager
        input::InputManager inputManager_;                 //!< The engine level input manager
        std::shared_ptr<ResourceManager> resourceManager_; //!< The engine level resource manager
        EventDispatcher::Ptr eventDispatcher_;             //!< System wide event emitter (Engine only keeps an instance alive for the application)
        PropertyContainer dataSaver_;                      //!< Holds Data that persists across scenes
        int popCounter_;                                   //!< Holds the number of scenes to be removed from the engine at the end of the current frame
        Callback<> onFrameStart_;                          //!< Optional function called at the start of the current frame
        Callback<> onFrameEnd_;                            //!< Optional function called at the end of the current frame
        EventEmitter eventEmitter_;                        //!< Emits engine events
        TimerManager timerManager_;                        //!< Engine level timer manager
        ui::GuiContainer gui_;                             //!< Engine level gui

        std::queue<std::pair<Scene::Ptr, Callback<>>> scenesPendingPush_; //!< Holds scenes to be pushed to the engine at the end of the current frame
    };
}

/**
 * @class ime::Engine
 * @ingroup core
 *
 * ime::Engine is the entry point of Infinite Motion Engine. It is responsible
 * for running, updating and rendering the game world. External code interacts
 * with the engine by pushing and popping ime::Scene at appropriate times
 *
 * Usage example:
 * @code
 * // The engine needs at least one scene in order to run
 * class TestScene : public ime::Scene {
 *      public:
 *          void onEnter() override {//Init scene}
 * };
 *
 * ime::Engine engine{"My awesome game"};
 * engine.initialize();
 * engine.pushScene(std::make_unique<TestScene>());
 * engine.run();
 * @endcode
 */

#endif // IME_ENGINE_H
