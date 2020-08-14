/**
 * @brief Runs the main loop
 */

#ifndef ENGINE_H
#define ENGINE_H

#include "IME/factory/GuiFactory.h"
#include "IME/gui/window/Window.h"

namespace IME {
    class State; //Forward declaration

    class Engine {
    public:
        /**
         * @brief Constructor
         * @param gameName Name of the application
         * @param settingsFilename Name of the file (including the path) that
         *        contains the engines settings
         *
         * The settings file must contain at least the following mandatory
         * settings:
         *     "title"      - Title of the render window
         *     "width"      - Width of the render window
         *     "height"     - Height of the render window
         *     "fullscreen" - Whether the render window should be constructed
         *                    in fullscreen mode or not,
         *
         * otherwise the initialization of the base engine will fail @see init(void)
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
         * @note There must be at least one state added for the engine to run
         */
        void run();

        /**
         * @brief Stop the engine
         */
        void stop();

        /**
         * @brief Check if engine is running or not
         * @return True if engine is running or false if the engine is not
         *         running
         */
        bool isRunning() const;

        /**
         * @brief Add a state to the engine
         * @param name Name of the state
         * @param state State to be added
         * @return True if the state was added or false if a state with the
         *         same name already exists
         *
         * The name of the state must be unique. If a state with the same name
         * as the argument already exists, then the provided state will not be
         * added, In addition the state pointer must not be null.
         */
        bool addState(const std::string &name, std::shared_ptr<State> state);

        /**
         * @brief Remove a state from the engine
         * @param name Name of the state to remove
         * @return True if the state was removed or false is the state does
         *         not exist
         */
        bool removeState(const std::string &name);

        /**
         * @brief Check if a state is added to the engine or not
         * @param name Name of the state to check
         * @return True if state exists or false if state does not exist
         */
        bool stateExists(const std::string &name) const;

        /**
         * @brief Change the current state
         * @param newStateName Name of the state to change to
         * @return True if the state was changed, false if the specified
         *         state does not exist
         */
        bool changeState(const std::string &newStateName);

        /**
         * @brief Get window used by the engine to render objects
         * @return Window used by engine as a render target
         */
        const Gui::Window& getRenderTarget() const;

        /**
         * @brief Get access to a state
         * @param name Name of the state to get access to
         * @return A pointer to the requested state if it exists, otherwise
         *         a nullptr
         */
        const std::shared_ptr<State> getState(const std::string &name) const;

        /**
         * @brief Get the current state
         * @return Pointer to the current state if any, otherwise a nullptr
         */
        const std::shared_ptr<State> getCurrentState() const;

        /**
         * @brief Get the name of the state prior to the current state change
         * @return Name of the previous state
         */
        const std::string &getPreviousStateName() const;

        /**
         * @brief Get the name of the game
         * @return Name of the game
         */
        const std::string& getAppName() const;

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
         * @brief Update current frame
         */
        void update();

        /**
         * @brief Render current frame
         */
        void render();

    private:
        //Engines render target
        Gui::Window window_;
        //Name of the application
        std::string appName_;
        //Filename of the engine settings (including path)
        std::string settingFile_;
        //State of the engine
        bool isRunning_;
        //Factory for instantiating GUI components
        static std::shared_ptr<const GuiFactory> guiFactory_;
        //Engine states
        std::unordered_map<std::string, std::shared_ptr<State>> states_;
        //Engine settings
        std::unordered_map<std::string, std::string> settings_;
        //Name of the current state
        std::string currentStateName_;
        //Name of the previous state
        std::string prevStateName_;
    };
} // namespace IME

#endif
