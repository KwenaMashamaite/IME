/**
 * @brief Runs the main loop
 */

#ifndef ENGINE_H
#define ENGINE_H

#include "IME/graphics/Window.h"
#include "IME/core/managers/ResourceManager.h"
#include "IME/core/managers/AudioManager.h"
#include "IME/core/managers/InputManager.h"
#include "IME/core/managers/EventManager.h"
#include "IME/common/PropertiesContainer.h"
#include "StateManager.h"

namespace IME {
    class Engine {
    public:
        /**
         * @brief Constructor
         * @param gameName Name of the application
         * @param settingsFile Name of the file (including the path) that
         *        contains the engines settings
         */
        Engine(const std::string &gameName, const std::string &settingsFile);

        /**
         * @brief Constructor
         * @param gameName Name of the game to be run by the engine
         * @param settings Engine settings
         */
        Engine(const std::string& gameName, const PropertyContainer& settings);

        /**
         * @brief Initialize base engine
         * @throw InvalidArgument if at least one of the mandatory settings
         *        is missing in the settings file provided during instantiation
         *        @see Engine(const std::string&, const std::string&)
         *
         * This function will perform all the necessary initialization and
         * create the engines render target, therefore calling the function
         * @see getRenderTarget() prior to this function may lead to undefined
         * behaviour. @note The engine will not run without initialization
         */
        void init();

        /**
         * @brief Limit the frame rate of the engines render target
         * @param fpsLimit The new frame limit
         *
         * By default the frame rate is not limited
         */
        void setFPSLimit(float fpsLimit);

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
         * @brief Get the engines configuration entries
         * @return The engines configuration entries
         *
         * This entries are used to initialize the engine
         */
        const PropertyContainer& getSettings() const;

        /**
         * @brief Get frames per second (FPS) limit
         * @return FPS limit
         */
        float getFPSLimit() const;

        /**
         * @brief Add a state
         * @param name Name of the state
         * @param state State to be added
         *
         * The state will be pushed at the end of the current frame
         */
        void pushState(std::shared_ptr<State> state);

        /**
         * @brief Remove a state from the engine
         *
         * The state will be popped at the end of the current frame
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
         * @brief Get access to the engines input manager
         * @return Engines input manager
         */
        Input::InputManager& getInputManager();

        /**
         * @brief Destructor
         */
        virtual ~Engine() = 0;

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

    protected:
        /**
         * @brief Handle window close event
         *
         * This function will be called by the engine when a request to
         * close the window is made by the user. The default behavior stops
         * the engine
         */
        virtual void onWindowClose();

    private:
        //Engines render target
        Graphics::Window window_;
        //Name of the application
        std::string appName_;
        //Filename of the engine settings (including path)
        std::string settingFile_;
        //lags whether settings are provided or loaded from file
        bool isSettingsLoadedFromFile_;
        //Running state
        bool isRunning_;
        //Initialization state
        bool isInitialized_;
        //Engine states
        StateManager statesManager_;
        //Engines audio manager
        std::unique_ptr<Audio::AudioManager> audioManager_;
        //Engines resource manager
        std::shared_ptr<ResourceManager> resourceManager_;
        //Engines input manager
        Input::InputManager inputManager_;
        //Engines Event manager
        std::shared_ptr<EventManager> eventManager_;
        //Engine settings
        PropertyContainer settings_;
        //Hold a state to be pushed to engine state
        std::shared_ptr<State> stateToPush_;
        //Flag for popping
        bool shouldPop_;
        //Keeps track of how long the engine has been running
        float elapsedTime_;
    };
} // namespace IME

#endif
