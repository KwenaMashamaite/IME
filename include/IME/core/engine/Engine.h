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
         * @param settingsFilename The name of the file that contains the engine
         *                     settings
         *
         * If the @a settingsFilename argument is left unspecified the engine
         * will be constructed with default settings
         */
        explicit Engine(const std::string &gameTitle, const std::string &settingsFilename = "default");

        /**
         * @brief Constructor
         * @param gameName The name of the game run by the engine
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
         * @warning This function must be called before the engine is run, otherwise
         * undefined behaviour
         *
         * @see run
         */
        void initialize();

        /**
         * @brief Start the main loop
         * @throws AccessViolationException If this function is called before
         *         the engine is initialized or before at least one Scene is
         *         pushed to the engine
         *
         * @warning The engine must be initialized before this function is
         * called. In addition, there must be at least one scene added to
         * the engine for it to run
         *
         * @see initialize and pushScene, pushCachedScene
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
         * Pausing the engine suspends all time based updates such as
         * animations, physics, movements, timers. The same effect can be
         * achieved by setting a scenes timescale to 0. The difference between
         * the two is that the latter invokes the scenes update functions with
         * a delta time of ime::Time::Zero whilst the former does not invoke
         * the update functions at all.
         *
         * By default, the engine is not paused
         *
         * @see isPaused
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
         * @brief Set the physics update frame rate
         * @param frameRate The new physics update frame rate
         * @throws InvalidArgumentException If the specified frame rate is 0
         *
         * Physics based components are updated using a fixed timestep defined
         * by the formula:
         *
         *  timestep = 1.0f / physicsUpdateFrameRate
         *
         * By default the physics update frame rate is 60 fps
         *
         * @see getPhysicsUpdateFrameRate
         */
        void setPhysicsUpdateFrameRate(unsigned int frameRate);

        /**
         * @brief Get the fixed update frame rate
         * @return The fixed update frame rate
         *
         * @see setPhysicsUpdateFrameRate
         */
        unsigned int getPhysicsUpdateFrameRate() const;

         /**
          * @brief Get the engines settings
          * @return The engines settings
          * @throws AccessViolationException If this function is called before
          *         the engine is initialized
          *
          * Note that this function returns the settings that were used during the
          * initialization of the engine. Modifying then after the engine has been
          * initialized has no effect
          *
          * @see initialize
          */
         PrefContainer& getConfigs();
         const PrefContainer& getConfigs() const;

        /**
         * @brief Get the engine level persistent data
         * @return The engine level persistent data
         *
         * Data stored in this object persists from scene to scene. This
         * means that the data is preserved during a scene push or a scene
         * pop operation. The data stored inside the cache can be of any type.
         *
         * For example, the code below saves the current level of the game in
         * the cache such that it can be accessed in any ime::Scene
         *
         * @code
         * // Saving data to the cache
         * engine.getCache().addProperty({"Current_Level", 1});
         *
         * // Accessing the cache within a ime::Scene
         * auto level = getEngine().getCache().getValue<int>("Current_Level");
         * @endcode
         *
         * @note Data in the cache is destroyed when the engine is shutdown,
         * see quit()
         *
         * @see getSavableCache
         */
        PropertyContainer& getCache();
        const PropertyContainer& getCache() const;

        /**
         * @brief Get the engine level savable persistent data
         * @return The engine level savable persistent data
         *
         * The savable cache behaves exactly the same way as the normal
         * cahce (see getCache()). The difference between them is that
         * the savable cache can only store data of a known type and can
         * be saved/read to/from the disk. Its main purpose is to save
         * player preferences. For example, you can use it to save the
         * players desired audio levels
         *
         * @warning The data is destroyed when the engine is shutdown
         *
         * @see getCache
         */
        PrefContainer& getSavableCache();
        const PrefContainer& getSavableCache() const;

        /**
         * @brief Get the name of the game run by the engine
         * @return The name of the game run by the engine
         *
         * This name is provided as an argument to the engines constructor(s)
         */
        const std::string& getGameName() const;

        /**
         * @brief Add a Scene to the engine
         * @param scene The scene to be added
         *
         * If the engine is running, the scene will @e not be pushed immediately
         * but rather at the end of the current frame. You can push multiple
         * scenes in the same frame, the last scene to be pushed will become
         * the active scene. All the other scenes will be pushed without being
         * entered
         *
         * To be notified when a scene becomes active, see onSceneActivate()
         *
         * @see popScene
         */
        void pushScene(Scene::Ptr scene);

        /**
         * @brief Add a cached scene to the engine
         * @param name The name of the scene to add
         * @return True if the scene was added or false if the scene with
         *         the given name does not exist in the cache list
         *
         * Note that after the push, the scene is removed from the cache and
         * will be added back once its popped (if its cache state is still true)
         *
         * @see cacheScene, ime::Scene::setCached and popScene
         */
        bool pushCachedScene(const std::string& name);

        /**
         * @brief Remove scenes from the engine
         * @param numScenes The number of scenes to remove
         *
         * If the engine is not running, the scene(s) will be removed immediately,
         * otherwise they will be removed at the end of the current frame.
         *
         * You can remove multiple scenes in the same frame by calling this
         * function as many times as the number of scenes to be removed or
         * by specifying the number of scenes to be removed. For example
         * the code below removes all scenes from the engine:
         *
         * @code
         * engine.popScene(engine.getSceneCount());
         *
         * // OR
         *
         * while (engine.getSceneCount() > 0)
         *      engine.popScene();
         *
         * @endcode
         *
         * Note that calling this function when the engine has no scenes
         * has no effect
         *
         * @see pushScene and pushCachedScene
         */
        void popScene(int numScenes = 1);

        /**
         * @brief Add a scene to the cache list
         * @param name The unique name of the scene for later access
         * @param scene The scene to be added
         *
         * A cached scene is not destroyed when popped from the Engine but
         * rather saved for reuse. This means that you can have a single
         * instance that you return to. For example, instead of instantiating
         * a new main menu scene every time the user wants to go to the main
         * menu, you can instantiate it once, cache it and use pushCachedScene()
         *
         * Unlike ime::Scene::setCached, this function will cache the scene
         * immediately
         *
         * @see pushCachedScene, uncacheScene, ime::Scene::setCached
         */
        void cacheScene(const std::string& name, Scene::Ptr scene);

        /**
         * @brief Remove a scene from the cache list
         * @param name The name of the scene to be removed
         * @return True if the scene was removed or false if it does not exist
         *
         * Unlike calling ime::Scene::setCached with a @a false argument, which
         * destroys the scene after it gets popped, this function will destroy
         * the scene immediately
         *
         * @see cacheScene
         */
        bool uncacheScene(const std::string& name);

        /**
         * @brief Check if a scene with a given name is cached or not
         * @param name The name of the scene to be checked
         * @return True if the scene is cached, otherwise false
         *
         * @see cacheScene
         */
        bool isSceneCached(const std::string& name) const;

        /**
         * @brief Remove all the scenes from the engine except the current
         *        active scene
         *
         * Note that if this function is called whilst the engine is @e not
         * running, then all the scenes will be removed from the engine.
         *
         * @note ime::Scene::onExit is not invoked on scenes that are removed
         * using this function
         *
         * @see removeAllScenes
         */
        void removeAllScenesExceptActive();

        /**
         * @brief Remove all the scenes from the engine
         *
         * If a scene is not pushed in the same frame as this function call,
         * then the engine will automatically shutdown since it must have
         * at least one scene to run.
         *
         * This function is an alias to the following code:
         *
         * @code
         * engine.popScene(engine.getSceneCount());
         * @endcode
         *
         * @see removeAllScenesExceptActive
         */
        void removeAllScenes();

        /**
         * @brief Get the number of scenes in the engine
         * @return The number of scenes in the engine
         */
        std::size_t getSceneCount() const;

        /**
         * @brief Get the active scene
         * @return A pointer to the active scene if it exists, otherwise a nullptr
         *
         * @see getBackgroundScene
         */
        Scene* getActiveScene();
        const Scene* getActiveScene() const;

        /**
         * @brief Get the background scene
         * @return A pointer to the background scene if it exists, otherwise
         *         a nullptr
         *
         * @see getActiveScene, ime::Scene::setOnPauseAction
         */
        Scene* getBackgroundScene();
        const Scene* getBackgroundScene() const;

        /**
         * @brief Get access to a scene in the cache list
         * @param name The name of the scene
         * @return A pointer to the scene is it exists, otherwise a nullptr
         */
        Scene* getCachedScene(const std::string& name);
        const Scene* getCachedScene(const std::string& name) const;

        /**
         * @brief Get the time passed since the engine was started
         * @return The time passed since the engine was started
         *
         * The elapsed time starts counting after run() is called.
         *
         * @note The elapsed time will reset to zero after the engine is
         * shutdown
         */
        Time getElapsedTime() const;

        /**
         * @brief Get the engines game window
         * @return The engines game window
         * @throws AccessViolationException If this function is called before
         *         the engine is initialized
         *
         * @see initialize
         */
        Window& getWindow();
        const Window& getWindow() const;

        /**
         * @brief Get the engine level gui
         * @return The engine level gui
         * @throws AccessViolationException If this function is called before
         *         the engine is initialized
         *
         * Unlike ime::Scene::getGui, this gui is not destroyed when the scene
         * is destroyed, but rather when the engine is shutdown. It may be
         * useful when the same UI is required across multiple scenes. Note
         * that this gui is rendered on top of the scene level gui
         *
         * @see initialize
         */
        ui::GuiContainer& getGui();
        const ui::GuiContainer& getGui() const;

        /**
         * @brief Get the engine level audio manager
         * @return The engine level audio manager
         *
         * Unlike ime::Scene::getAudio, this audio manager is not destroyed
         * when the scene is destroyed, but rather when the engine is
         * shutdown
         */
        audio::AudioManager& getAudioManager();
        const audio::AudioManager& getAudioManager() const;

        /**
         * @brief Get the engine level input manager
         * @return The engine level input manager
         *
         * Unlike ime::Scene::getInput, event listeners registered to this input
         * manager are executed regardless of which scene is active and are
         * only destroyed when the engine is shutdown
         */
        input::InputManager& getInputManager();
        const input::InputManager& getInputManager() const;

        /**
         * @brief Get the engine level timer manager
         * @return The engine level timer manager
         *
         * Unlike ime::Scene::getTimer, event listeners registered to this
         * timer manager are executed regardless of which scene is active
         * and are destroyed when the engine is shutdown
         */
        TimerManager& getTimer();
        const TimerManager& getTimer() const;

        /**
         * @brief Pause or resume execution of an event listener
         * @param id The event listeners unique identification number
         * @param suspend True to suspend/pause or false to unsuspend/resume
         *
         * @see isEventListenerSuspended
         */
        void suspendedEventListener(int id, bool suspend);

        /**
         * @brief Check if an event listener is suspended or not
         * @param id The identification number of the listener to be checked
         * @return True if suspended, otherwise false
         *
         * This function also returns false if the specified event listener
         * does not exist
         *
         * @see suspendedEventListener
         */
        bool isEventListenerSuspended(int id) const;

        /**
         * @brief Remove an event listener from an event
         * @param id The unique identification number of the event listener
         * @return True if the event listener was removed or false if no such
         *         event listener exists
         */
        bool removeEventListener(int id);

        /**
         * @brief Add an event listener to an initialize event
         * @param callback The function to be executed after the engine is
         *                 initialized
         * @return The event listener unique identification number
         *
         * You can add any number of event listeners to this event
         *
         * @see removeEventListener
         */
        int onInit(const Callback<>& callback);

        /**
         * @brief Add an event listener to a scene activation event
         * @param callback Function to be executed when a scene becomes active
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listener unique identification number
         *
         * This event is emitted when a scene becomes active. The callback is
         * passed a pointer to the scene that was activated.
         *
         * You can add any number of event listeners to this event
         */
        int onSceneActivate(const Callback<Scene*>& callback, bool oneTime = false);

        /**
         * @brief Add an event listener to a current frame start event
         * @param callback Function to executed when the current frame starts
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listener unique identification number
         *
         * You can add any number of event listeners to this event
         *
         * @see onFrameEnd
         */
        int onFrameStart(const Callback<>& callback, bool oneTime = false);

        /**
         * @brief Add an event listener to a current frame end event
         * @param callback Function to be executed when the current frame ends
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listener unique identification number
         *
         * You can add any number of event listeners to this event
         *
         * @see onFrameStart
         */
        int onFrameEnd(const Callback<>& callback, bool oneTime = false);

        /**
         * @brief Add an event listener to an engine start event
         * @param callback Function to be executed when the engine starts running
         * @return The event listener unique identification number
         *
         * You can add any number of event listeners to this event
         *
         * @see onShutdown
         */
        int onStart(const Callback<>& callback);

        /**
         * @brief Execute a callback when the engine is about to shut down
         * @param callback The function to be executed when the engine is
         *                 starts to shut down
         * @return The event listener unique identification number
         *
         * This event is emitted when the engine is about to begin its
         * shutdown sequence. To perform an action after the engine has
         * completed its shutdown sequence, use onShutdownComplete()
         *
         * You can add any number of event listeners to this event
         *
         * @see onShutdownComplete
         */
        int onShutDown(const Callback<>& callback);

        /**
         * @brief Add an event listener to a shutdown complete event
         * @param callback The function to be executed when the engine complete
         *                 its shutdown sequence
         *
         * @warning When this event is emitted, the engine will be in an
         * uninitialized state (see initialize())
         *
         * @note Only one event listener may registered to this event. Pass
         * @a nullptr to remove the callback
         *
         * @see onShutDown
         */
        void onShutdownComplete(const Callback<>& callback);

        /**
         * @internal
         * @brief Get access to the engines render target
         * @return The engines render target
         *
         * @warning This function must be called after the engine has been
         *          initialized, otherwise undefined behaviour
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
         * @throws InvalidArgumentException if anu of settings entries are invalid
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
        PrefContainer configs_;                            //!< The engines settings
        bool isSettingsLoadedFromFile_;                    //!< A flag indicating whether or not config entries are loaded by the engine or are received during construction
        bool isInitialized_;                               //!< A flag indicating whether or not the engine has been initialized
        bool isRunning_;                                   //!< A flag indicating whether or not the engine is running
        bool isPaused_;                                    //!< A flag indicating whether or not the engine is paused
        unsigned int fixedUpdateFPS_;                      //!< The frame rate of a fixed update
        Time elapsedTime_;                                 //!< The time passed since the engine started running
        EventEmitter eventEmitter_;                        //!< Emits engine events
        std::unique_ptr<priv::SceneManager> sceneManager_; //!< The scene manager
        audio::AudioManager audioManager_;                 //!< The engine level audio manager
        input::InputManager inputManager_;                 //!< The engine level input manager
        std::shared_ptr<ResourceManager> resourceManager_; //!< The engine level resource manager
        EventDispatcher::Ptr eventDispatcher_;             //!< System wide event emitter (Engine only keeps an instance alive for the application)
        PropertyContainer dataSaver_;                      //!< Holds Data that persists across scenes
        PrefContainer diskDataSaver_;                      //!< Holds data that persists across scenes and can be read/saved from/to a file on the disk
        int popCounter_;                                   //!< Holds the number of scenes to be removed from the engine at the end of the current frame
        TimerManager timerManager_;                        //!< Engine level timer manager
        ui::GuiContainer gui_;                             //!< Engine level gui
        Callback<> onShutdownComplete_;                    //!< An optional callback function executed after an engine shutdown

        std::queue<Scene::Ptr> scenesPendingPush_; //!< Holds scenes to be pushed to the engine at the end of the current frame
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
 *          void onEnter() override {}
 * };
 *
 * ime::Engine engine{"My awesome game"};
 * engine.initialize();
 * engine.pushScene(std::make_unique<TestScene>());
 * engine.run();
 * @endcode
 */

#endif // IME_ENGINE_H
