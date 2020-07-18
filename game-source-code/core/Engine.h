/**
 * @brief Runs the main loop
 */

#ifndef ENGINE_H
#define ENGINE_H

#include "gui/window/Window.h"
#include "State.h"

class Engine final{
public:
    /**
     * @brief Initialize the engine
     * @param window
     */
    explicit Engine(Gui::Window& window);

    /**
     * @brief Start the main loop
     */
    void run();

    /**
     * @brief Stop the engine
     */
    static void stop();

    /**
     * @brief Check if engine is running or not
     * @return True if engine is running or false if the engine is not running
     */
    static bool isRunning();

    /**
     * @brief Add a state to the engine
     * @param name Name of the state
     * @param state State to be added
     *
     * The name of the state must be unique. If a state with the same name as
     * the argument already exists, then the provided state will not be added,
     * In addition the state pointer must not be null
     */
    static void addState(const std::string& name, std::shared_ptr<State> state);

    /**
     * @brief Remove a state
     * @param name Name of the state to remove
     * @return True if the state was removed or false is the state does not exist
     */
    static bool removeState(const std::string& name);

    /**
     * @brief Check if a state is added to the engine or not
     * @param name Name of the state to check
     * @return True if state exists or false if state does not exist
     */
    static bool stateExists(const std::string& name);

    /**
     * @brief Change the current state
     * @param name Name of the state to change to
     * @return True if the state was changed, false if the specified state does
     *         not exist
     */
    static bool changeState(const std::string& name);

    /**
     * @brief Get access to a state
     * @param name Name of the state to get access to
     * @return A pointer to the requested state if it exists, otherwise a nullptr
     */
    static std::shared_ptr<State> getState(const std::string& name);

    /**
     * @brief Get the current state
     * @return Pointer to the current state if any, otherwise a nullptr
     */
    static std::shared_ptr<State> getCurrentState();

    /**
     * @brief Get the name of the state prior to state state change
     * @return Name of the previous state
     */
    static const std::string& getPreviousStateName();

private:
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
    Gui::Window& window_;
    //State of the engine
    inline static bool isRunning_{false};
    //Engine states
    inline static std::unordered_map<std::string, std::shared_ptr<State>> states_;
    //Name of the current state
    inline static std::string currentState_{""};
    //Name of the previous state
    inline static std::string prevState_{""};
};

#endif
