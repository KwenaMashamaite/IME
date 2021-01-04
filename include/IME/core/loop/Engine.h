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
#include "IME/core/managers/ResourceManager.h"
#include "IME/core/managers/AudioManager.h"
#include "IME/core/managers/InputManager.h"
#include "IME/core/event/EventDispatcher.h"
#include "IME/common/PropertyContainer.h"
#include "IME/core/states/StateManager.h"
#include <queue>

namespace IME {
    /**
     * @brief Runs the main loop
     */
    class IME_API Engine {
    public:
        /**
         * @brief Constructor
         * @param gameName Name of the game run by the engine
         * @param settingsFile Filename of the file that contains the
         *        engines settings
         *
         * @a settingsFile must have the filename preceded by the path
         * to the file. The path must be relative to the directory that
         * contains the game executable
         */
        Engine(const std::string &gameName, const std::string &settingsFile);

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
         * addition, there must be at least one state added for the engine
         * to run
         *
         * @see initialize
         * @see pushState
         */
        void run();

        /**
         * @brief Stop the engine
         *
         * This function will remove all states that have been added to the
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
         * Data stored in the this object persists from state to state.
         * This means that the data is preserved during a state push or
         * pop. This is useful if you want share data between states. For
         * example, a state may save data before its destroyed/paused and
         * the next state can access the data and update for the next state
         * or for the previous state when it is resumed
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
         * @brief Add a state to the engine
         * @param state State to add
         * @param callback Optional function to be executed after the state
         *                 is added
         *
         * The state will NOT be pushed immediately but rather at the end of
         * the current frame. Any operation performed on the engine before
         * the end of the current frame will reflect on the current state and
         * not the state to be pushed. A callback must be provided if the
         * need to perform an operation immediately after a state is pushed
         * arises
         *
         * @warning If multiple states are pushed to the engine in the same
         * frame, the last state to be received before the frame end will be
         * the active state. All the other states will be pushed without
         * initialization. This means that only the optional callback attached
         * to the last state will be invoked
         */
        void pushState(std::shared_ptr<State> state, Callback<> callback = nullptr);

        /**
         * @brief Remove a state from the engine
         *
         * The state will not be removed immediately but rather at the end of
         * the current frame
         */
        void popState();

        /**
         * @brief Get the time passed since the engine was started
         * @return The time passed since the engine was started
         *
         * @note The elapsed time will reset to zero when the engine is stopped
         */
        float getElapsedTime() const;

        /**
         * @brief Get access to the engines resource manager
         * @return The engines resource manager
         */
        ResourceManager& getResourceManager();

        /**
         * @brief Get access to the engines audio manager
         * @return The engines audio manager
         */
        Audio::AudioManager& getAudioManager();

        /**
         * @brief Get access to the engines local input manager
         * @return The engines local input manager
         *
         * This input manager is local to the current state. This means that
         * input listeners attached to it will only be notified during the
         * current state only. The input manager is cleared on a state change
         * (push or pop). For a push operation, input event listeners are
         * remembered and restored when the state is resumed
         */
        Input::InputManager& getInputManager();

        /**
         * @brief Get access to the engines global input manager
         * @return Engines global input manager
         *
         * Input event listeners attached to this input manager will be
         * notified when the corresponding event is fired regardless of
         * state. That is, they persist from state to state
         */
        Input::InputManager& getGlobalInputManager();

        /**
         * @brief Get access to the engines render target
         * @return The engines render target
         *
         * @warning Don't call pollEvent(), on the instance as it will empty
         * the event queue and prevent the engine from properly dispatching
         * events. Also avoid drawing directly on the window because it will
         * be cleared by the engine before rendering a state.
         *
         * @warning This function must only be called after the engine has
         *          been initialized
         *
         * @see initialize
         */
        Graphics::Window& getRenderTarget();

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
         * @param callback Function to execute
         *
         * The callback is invoked before the start of the next frame (When
         * event processing, state updates, rendering, state push and state
         * pop operations are complete)
         *
         * @note Only one callback may be registered at a time. Pass nullptr
         * to stop the callback from being invoked. By default no callback is
         * registered
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
        void update(float deltaTime);

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
        Graphics::Window window_;                               //!< Render target
        std::string appName_;                                   //!< Game name
        std::string settingFile_;                               //!< Engine settings filename
        PropertyContainer settings_;                            //!< Engine settings container
        bool isSettingsLoadedFromFile_;                         //!< Flags whether settings are provided or loaded from file
        bool isInitialized_;                                    //!< Engine's initialization state
        bool isRunning_;                                        //!< Engine's running state
        float elapsedTime_;                                     //!< How long the engine has been running
        StateManager statesManager_;                            //!< Engine states manager
        std::unique_ptr<Audio::AudioManager> audioManager_;     //!< Engines audio manager
        std::shared_ptr<ResourceManager> resourceManager_;      //!< Engines resource manager
        Input::InputManager inputManager_;                      //!< Engines local input manager
        Input::InputManager globalInputManager_;                //!< Engines global input manager
        std::stack<Input::InputManager> prevStateInputManager_; //!< Previous states local input handlers
        std::shared_ptr<EventDispatcher> eventDispatcher_;      //!< Engines Event dispatcher
        PropertyContainer dataSaver_;                           //!< Data that persists across states
        bool shouldPop_;                                        //!< Flags whether o not current state should be popped
        Callback<> windowCloseHandler_;                         //!< Window close event listener
        Callback<> onFrameStart_;                               //!< Function called at the start of a frame
        Callback<> onFrameEnd_;                                 //!< Function called at the end of a frame
        std::queue<std::pair<std::shared_ptr<State>, Callback<>>> statesToPush_; //!< Holds states to be pushed to the engine at the end of the current frame
    };
}

#endif // IME_ENGINE_H
