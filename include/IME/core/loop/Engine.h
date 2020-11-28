////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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

/**
 * @brief Runs the main loop
 */

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

namespace IME {
    class IME_API Engine {
    public:
        /**
         * @brief Constructor
         * @param gameName Name of the game run by the engine
         * @param settingsFile filename of the file that contains the
         *        engines settings
         *
         * @param settingsFile must have the filename preceded by the path
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
         * @brief Initialize engine
         *
         * This function will perform all the necessary initialization and
         * create the engines render target, therefore calling the function
         * @see getRenderTarget() prior to this function may lead to undefined
         * behaviour. @note The engine will not run without initialization
         */
        void init();

        /**
         * @brief Start the main loop
         *
         * There must be at least one state added for the engine to run. The
         * engine must also be initialized first before running it, @see init()
         */
        void run();

        /**
         * @brief Stop the engine
         *
         * This function will remove all states that have been added to the
         * engine. The initialization state will not be reset. Therefore the
         * engine may be restarted without re-initialization after it ha been
         * stopped
         */
        void quit();

        /**
         * @brief Check if engine is running or not
         * @return True if engine is running, otherwise false
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
         * Data stored in the this object persists from state to state,
         * this means that the data is preserved during a state push or
         * pop. This is useful if you want share data between states. For
         * example, a state may save data before its destroyed/paused and
         * the next state can access the data and update for the next state
         * or for the previous state when it is resumed
         *
         * @warning The data is destroyed if the engine is shutdown
         *
         * @see quit
         */
        PropertyContainer& getPersistentData();

        /**
         * @brief Get frames per second (FPS) limit
         * @return FPS limit
         */
        unsigned int getFPSLimit() const;

        /**
         * @brief Get the name of the game
         * @return The name of the game
         *
         * This is the name provided during construction of the engine
         * @see Engine()
         */
        const std::string& getGameName() const;

        /**
         * @brief Add a state
         * @param name Name of the state
         * @param state State to be added
         * @param callback Optional function to be executed after the state is
         *                 pushed
         *
         * The state will NOT be pushed immediately but rather at the end of the
         * current frame. @note Any operation performed on the engine before
         * the end of the current frame will reflect on the current state and
         * not the state to be pushed. A callback must be provided if the
         * need to perform an operation immediately after a state is pushed
         * arises
         *
         * @warning If multiple states are pushed to the engine in a single/same
         * frame, the last state to be received before the frame end will be the
         * active state. All the other states will be pushed without initialization
         * This means that only the optional callback attached to the last state
         * will be invoked
         */
        void pushState(std::shared_ptr<State> state, Callback<> callback = nullptr);

        /**
         * @brief Remove a state from the engine
         *
         * The state will not be popped immediately but rather at the end of
         * the current frame
         */
        void popState();

        /**
         * @brief Get the time passed since the engine was started/run
         * @return The time passed since the engine was started/run
         *
         * The elapsed time will reset to 0.0f when the engine is stopped. This
         * means that this function will return 0.0f if the engine is not running.
         * The time is in seconds
         */
        float getElapsedTime() const;

        /**
         * @brief Get access to the engines resource manager
         * @return Engines resource manager
         */
        ResourceManager& getResourceManager();

        /**
         * @brief Get access to the engines audio manager
         * @return Engines audio manager
         */
        Audio::AudioManager& getAudioManager();

        /**
         * @brief Get access to the engines local input manager
         * @return Engines local input manager
         *
         * This input manager is local to the current state. This means that
         * input listeners attached to it will only be notified during the
         * current state only. The input manager is cleared on a state change
         * (push or pop). For a push operation, input event listeners are
         * remembered and restored when the state is resumed
         *
         * @warning If the input handler has a reference or a pointer to a class
         * member, then caution must be taken to ensure that the input manager
         * does not try to invoke a member of a destroyed object. Doing so may
         * lead to undefined behavior or worse, crash the program
         */
        Input::InputManager& getInputManager();

        /**
         * @brief Get access to the engines global input manager
         * @return Engines global input manager
         *
         * Input event listeners attached to this input manager will be notified
         * when the corresponding event is fired regardless of state.
         *
         * @warning State specific input handlers must use @see getInputManager()
         * because this input manager will not check if a state is active, paused
         * or destroyed when notifying handlers. Therefore, if a state is popped
         * and the global handlers are not removed before the state is destroyed,
         * the program may crash or perform some undefined behaviour. In addition
         * If the handler has a reference or a pointer to a class member, then
         * caution must be taken to ensure that the input manager does not try
         * to invoke a member of a destroyed object. Doing so may lead to undefined
         * behavior or worse, crash the program
         */
        Input::InputManager& getGlobalInputManager();

        /**
         * @brief Get access to the engines render target
         * @return The engines render target
         *
         * @warning Don't call pollEvent(), on the instance as it will empty
         * the event queue and prevent the engine from properly dispatching
         * events. Also avoid drawing directly on the window because it will
         * be cleared by the engine before rendering a state. This function
         * must only be called after the engine has been initialized @see init()
         */
        Graphics::Window& getRenderTarget();

        /**
         * @brief Add an event lister to a window close event
         * @param callback Function to execute when a window close event is fired
         *
         * The callback function will be called by the engine when a request to
         * close the window is made by the user. The default behavior stops
         * the engine and closes the render window. @note Only one event listener
         * may be registered to this event. This means that when a new event
         * listener is added, the previous one is removed. As a result, adding
         * a window close event listener overwrites the default behavior
         */
        void onWindowClose(Callback<> callback);

        /**
         * @brief Execute a function at the start of a frame
         * @param callback Function to execute
         *
         * @note Only one callback  may be registered at a time. Pass nullptr to
         * stop the callback from being invoked. By default no callback is
         * registered
         */
        void onFrameStart(Callback<> callback);

        /**
         * @brief Execute a function at the end of the current frame
         * @param callback Function to execute
         *
         * The callback is invoked after all updates and rendering is completed,
         * That is, before the start of the next frame. @note Only one callback
         * may be registered at a time. Pass nullptr to stop the callback from
         * being invoked. By default no callback is registered
         */
        void onFrameEnd(Callback<> callback);

    private:
        /**
         * @brief Load engine settings from the hard drive
         * @throw InvalidArgument if the settings entry are invalid. That is,
         *        they do not follow the set out settings entry guidelines
         *        @see init(void)
         */
        void loadSettings();

        /**
         * @brief Check if all the mandatory settings have been loaded from
         *        the hard drive
         *
         * These settings are the screen title, screen width, screen height and
         * fullscreen flag
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
         * @brief Stops the engine and clears all data
         */
        void shutdown();

    private:
        //Engines render target
        Graphics::Window window_;
        //Name of the application
        std::string appName_;
        //Filename of the engine settings (including path)
        std::string settingFile_;
        //Engine settings
        PropertyContainer settings_;
        //lags whether settings are provided or loaded from file
        bool isSettingsLoadedFromFile_;
        //Initialization state
        bool isInitialized_;
        //Running state
        bool isRunning_;
        //Keeps track of how long the engine has been running
        float elapsedTime_;
        //Engine states
        StateManager statesManager_;
        //Engines audio manager
        std::unique_ptr<Audio::AudioManager> audioManager_;
        //Engines resource manager
        std::shared_ptr<ResourceManager> resourceManager_;
        //Engines local input manager
        Input::InputManager inputManager_;
        //Engines global input manager
        Input::InputManager globalInputManager_;
        //Remembers the prev state local input handlers on state push
        std::stack<Input::InputManager> prevStateInputManager_;
        //Engines Event dispatcher (This instance is kept alive for all states)
        std::shared_ptr<EventDispatcher> eventDispatcher_;
        //Data that persists across states
        PropertyContainer dataSaver_;
        //Holds states to be pushed to the engine at the end of the frame
        std::vector<std::pair<std::shared_ptr<State>, Callback<>>> statesToPush_;
        //Flag for popping
        bool shouldPop_;
        //Window close event listener
        Callback<> windowCloseHandler_;
        //Function called at the start of a frame
        Callback<> onFrameStart_;
        //Function called at the end of a frame
        Callback<> onFrameEnd_;
    };
}

#endif
