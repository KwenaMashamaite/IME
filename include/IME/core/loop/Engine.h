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
#include "IME/graphics/Window.h"
#include "IME/core/resources/ResourceManager.h"
#include "IME/core/audio/AudioManager.h"
#include "IME/core/input/InputManager.h"
#include "IME/core/event/EventDispatcher.h"
#include "IME/core/time/TimerManager.h"
#include "IME/common/PropertyContainer.h"
#include "IME/core/scene/SceneManager.h"
#include "IME/core/scene/Scene.h"
#include "IME/core/time/Timer.h"
#include <queue>

namespace ime {
    /**
     * @brief Runs the main loop
     */
    class IME_API Engine {
    public:
        /**
         * @brief Constructor
         * @param gameTitle Name of the game run by the engine
         * @param settingsFile Filename of the file that contains the
         *        engines settings
         *
         * @a settingsFile must have the filename preceded by the path
         * to the file. The path must be relative to the directory that
         * contains the game executable. If @a settingsFile is left unspecified
         * the engine will be constructed from default settings
         */
        explicit Engine(const std::string &gameTitle, const std::string &settingsFile = "default");

        /**
         * @brief Constructor
         * @param gameName Name of the game to be run by the engine
         * @param settings Engine settings
         *
         * @warning This function is unstable at the moment, use the constructor
         * that loads the settings from the disk
         */
        Engine(const std::string& gameName, const PropertyContainer& settings);

        /**
         * @brief Copy constructor
         */
        Engine(const Engine&) = delete;

        /**
         * @brief Assignment operator
         */
        Engine& operator=(const Engine&) = delete;

        /**
         * @brief Initialize the engine
         *
         * This function will perform all the necessary initialization and
         * create the games render target, therefore calling the function
         * getRenderTarget() prior to this function is undefined behaviour
         *
         * @see getRenderTarget
         */
        void initialize();

        /**
         * @brief Start the main loop
         *
         * @warning The engine must be initialized before it is run. In
         * addition, there must be at least one scene added for the engine
         * to run
         *
         * @see initialize
         * @see pushScene
         */
        void run();

        /**
         * @brief Stop the engine
         *
         * This function will remove all scenes that have been added to the
         * engine and reset it's initialization state. Therefore, the engine
         * must be reinitialized before it is re-run
         */
        void quit();

        /**
         * @brief Check if the engine is running or not
         * @return True if the engine is running, otherwise false
         */
        bool isRunning() const;

        /**
         * @brief Get the engines settings
         * @return The engines settings
         *
         * @warning This function is experimental
         */
        const PropertyContainer& getSettings() const;

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
         * The scene will NOT be pushed immediately but rather at the end of
         * the current frame. Any operation performed on the engine before
         * the end of the current frame will reflect on the current scene and
         * not the scene to be pushed. A callback must be provided if the
         * need to perform an operation immediately after a scene is pushed
         * arises
         *
         * @warning If multiple scenes are pushed to the engine in the same
         * frame, the last scene to be received before the frame end will be
         * the active scene. All the other scenes will be pushed without
         * initialization. This means that only the optional callback attached
         * to the last scene will be invoked
         */
        void pushScene(Scene::sharedPtr scene, Callback<> callback = nullptr);

        /**
         * @brief Remove the current scene from the engine
         *
         * The scene will not be removed immediately but rather at the end
         * of the current frame
         */
        void popScene();

        /**
         * @brief Get the time passed since the engine was started
         * @return The time passed since the engine was started
         *
         * @note The elapsed time will reset to zero when the engine is
         * shutdown
         */
        Time getElapsedTime() const;

        /**
         * @brief Get the global resource manager
         * @return The global resource manager
         */
        ResourceManager& getResourceManager();

        /**
         * @brief Get the global audio manager
         * @return The global audio manager
         */
        audio::AudioManager& getAudioManager();

        /**
         * @brief Get the global input manager
         * @return The global input manager
         */
        input::InputManager& getInputManager();

        /**
         * @brief Get access to the engines render target
         * @return The engines render target
         *
         * @warning Don't call pollEvent(), on the instance as it will empty
         * the event queue and prevent the engine from properly dispatching
         * events. Also avoid drawing directly on the window because it will
         * be cleared by the engine before rendering the current scene.
         *
         * @warning This function must only be called after the engine has
         *          been initialized
         *
         * @see initialize
         */
        Window& getRenderTarget();

        /**
         * @brief Schedule a callback to be executed after a delay
         * @param delay Time to wait before executing the callback
         * @param callback Function to be executed
         *
         * This function will execute a callback function once after
         * @a delay seconds. To execute a callback repeatedly every
         * interval, checkout the setInterval function
         *
         * @note The callback is executed by a global timer
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
         * Unlike setTimeout, this function will execute a callback
         * every @a delay seconds for a specified number of times while
         * the engine is running. By default the repeat counter is -1,
         * this means that the callback will repeat forever. The repetition
         * can be also be cancelled by calling setRepeat(0) on the returned
         * timer
         *
         * @note The callback is executed by a global timer, therefore the
         * interval will continue to execute until the engine is shutdown
         * or the interval is stopped via the argument passed to the callback
         *
         * @warning The timer will be destroyed if the timer is externally
         * stopped or the repetition is cancelled
         *
         * @see setTimeout
         */
        void setInterval(Time delay, ime::Callback<Timer&> callback, int repeatCount = -1);

        /**
         * @brief Add an event lister to a window close event
         * @param callback Function to execute when a window close event is fired
         *
         * The callback function will be called by the engine when a request to
         * close the window is made by the user. The default behavior stops
         * the engine and closes the render window.
         *
         * @note Only one event listener may be registered to this event. This
         * means that when a new event listener is added, the previous one is
         * removed. As a result, adding a window close event listener overwrites
         * the default behavior
         */
        void onWindowClose(Callback<> callback);

        /**
         * @brief Execute a function at the start of a frame
         * @param callback Function to execute
         *
         * Only one callback may be registered at a time. Pass nullptr to
         * stop the callback from being invoked. By default no callback is
         * registered
         */
        void onFrameStart(Callback<> callback);

        /**
         * @brief Execute a function at the end of the current frame
         * @param callback Function to be executed
         *
         * @note Only one callback may be registered at a time. Pass nullptr
         * to stop the callback from being invoked.
         *
         * By default, no callback is registered
         */
        void onFrameEnd(Callback<> callback);

    private:
        /**
         * @brief Load engine settings from the hard drive
         * @throw InvalidArgument if the settings entries are invalid
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
        Window window_;                              //!< The engines render target
        std::string gameTitle_;                      //!< The name of the game run by the engine
        std::string settingFile_;                    //!< The filename of the file that contains the engines config entries
        PropertyContainer settings_;                 //!< The engines settings
        bool isSettingsLoadedFromFile_;              //!< A flag indicating whether or not config entries are loaded by the engine or are received during construction
        bool isInitialized_;                         //!< A flag indicating whether or not the engine has been initialized
        bool isRunning_;                             //!< A flag indicating whether or not the engine is running
        Time deltaTime_;                             //!< The time taken for each game frame to complete
        Time elapsedTime_;                           //!< The time passed since the engine started running
        SceneManager sceneManager_;                  //!< The games scene manager
        audio::AudioManager audioManager_;           //!< The games global audio manager
        input::InputManager inputManager_;           //!< The games global input manager
        ResourceManager::sharedPtr resourceManager_; //!< The games global resource manager
        EventDispatcher::sharedPtr eventDispatcher_; //!< Engines Event dispatcher
        PropertyContainer dataSaver_;                //!< Holds Data that persists across scenes
        bool pendingPop_;                            //!< A flag indicting whether or not the current scene should be popped
        Callback<> onWindowClose_;                   //!< A Function executed when a request to close the window is received
        Callback<> onFrameStart_;                    //!< A Function called at the start of the current frame
        Callback<> onFrameEnd_;                      //!< A Function called at the end of the current frame
        TimerManager timerManager_;                  //!< Manages global timers

        std::queue<std::pair<Scene::sharedPtr, Callback<>>> scenesPendingPush_; //!< Holds scenes to be pushed to the engine at the end of the current frame
    };
}

#endif // IME_ENGINE_H
