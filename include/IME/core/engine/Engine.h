/**
 * @brief Runs the main loop
 */

#ifndef ENGINE_H
#define ENGINE_H

#include "IME/utility/GuiFactory.h"
#include "IME/gui/window/Window.h"
#include "IME/core/resources/ResourceManager.h"
#include "IME/core/audio/AudioManager.h"
#include "IME/core/input/InputManager.h"
#include "IME/utility/PropertiesContainer.h"
#include "StateManager.h"

namespace IME {
    class Engine {
    public:
        /**
         * @brief Constructor
         * @param gameName Name of the application
         * @param settingsFilename Name of the file (including the path) that
         *        contains the engines settings
         */
        Engine(const std::string &gameName, const std::string &settingsFilename);

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
         * @brief Get the name of the app the engine is running
         * @return Name of the game the engine is running
         */
        const std::string& getGameName() const;

        /**
         * @brief Add a state
         * @param name Name of the state
         * @param state State to be added
         * @return True if the state was added or false if a state with the
         *         same name already exists
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
         * @brief Get the size of the engines render target
         * @return The size of the engines render target
         */
        Definitions::Dimensions getWindowSize() const;

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
         * @brief Get a factory for creating gui components
         * @return Pointer to a gui factory
         */
        const std::shared_ptr<const GuiFactory>& getGuiFactory() const;

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
         * @throw InvalidArgument if at least one of the mandatory settings
         *        is missing
         *
         * These settings are the screen title, screen width, screen height and
         * fullscreen flag
         */
        void verifySettings() const;

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
         */
        void update();

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

    private:
        //Engines render target
        Gui::Window window_;
        //Name of the application
        std::string appName_;
        //Filename of the engine settings (including path)
        std::string settingFile_;
        //State of the engine
        bool isRunning_;
        //Initilization state
        bool isInitialized_;
        //Factory for instantiating GUI components
        static std::shared_ptr<const GuiFactory> guiFactory_;
        //Engine states
        StateManager statesManager_;
        //Engines audio manager
        std::unique_ptr<Audio::AudioManager> audioManager_;
        //Engines resource manager
        std::shared_ptr<ResourceManager> resourceManager_;
        //Engines input manager
        Input::InputManager inputManager_;
        //Engine settings
        Utility::PropertyContainer settings_;
        //Hold a state to be pushed to engine state
        std::shared_ptr<State> stateToPush_;
        //Flag for popping
        bool shouldPop_;
    };
} // namespace IME

#endif
