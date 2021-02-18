////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#ifndef IME_SCENE_H
#define IME_SCENE_H

#include "IME/Config.h"
#include "IME/core/time/Time.h"
#include "IME/core/event/Event.h"
#include "IME/core/event/EventDispatcher.h"
#include "IME/core/input/InputManager.h"
#include "IME/core/audio/AudioManager.h"
#include "IME/core/time/TimerManager.h"
#include "IME/common/PropertyContainer.h"
#include "IME/core/scene/ShapeContainer.h"
#include "IME/core/scene/EntityContainer.h"
#include "IME/ui/GuiContainer.h"
#include <string>
#include <memory>
#include <vector>

namespace ime {
    // Forward declarations
    class Engine;
    class Window;
    class World;

    /**
     * @brief Abstract base class for game scenes
     *
     * A scene represents a distinct state of your game, for example
     * loading, main menu, gameplay, paused and so on. All game scenes
     * exist in isolation and have no knowledge of each other. Only
     * one scene can be active at a time. For example, the game cannot
     * be in a main menu state and a gameplay state at the same time.
     *
     * The transition between scenes is managed using the Last In First
     * Out (LIFO) technique (The same way std::stack works). Therefore
     * you cannot transition between scenes at random. The order in which
     * scenes are added to the Engine is important.
     *
     * For example, if while in the "gameplay" scene, you push a "pause" scene
     * to the game engine, the "gameplay" scene will be paused (onPause called)
     * and the "pause" scene will be entered (onEnter called on the pause scene
     * instance) and the "pause" scene will become the active scene (gets system
     * events, updates and rendered). If you pop the "pause" scene, the engine
     * will destroy it (onExit called on the pause scene instance) and return
     * to the "gameplay" scene (onResume called on the gameplay scene instance).
     * However, if you push (transition to) another scene while in the "pause"
     * scene, the process repeats; the "pause" scene gets paused and the the new
     * scene becomes active)
     */
    class IME_API Scene {
    public:
        using sharedPtr = std::shared_ptr<Scene>; //!< Shared Scene pointer

        /**
         * @brief Constructor
         * @param engine A reference to the game engine
         */
        explicit Scene(Engine &engine);

        /**
         * @brief Enter the scene
         *
         * This function will be called by the game engine when the scene
         * is entered for the first time. Note that a scene cannot be entered
         * more than once
         */
        virtual void onEnter() = 0;

        /**
         * @brief Handle a system event
         * @param event System event to be handled
         *
         * This function will be called by the game engine before the
         * scene is updated. The function is called once per frame
         */
        virtual void handleEvent(Event event) = 0;

        /**
         * @brief Update the scene
         * @param deltaTime Time passed since last update
         *
         * This function will be called by the game engine after the scene
         * has handled system events and external inputs (Keyboard and mouse).
         * The function is called once per frame and the delta passed to it
         * is frame rate dependent. This means that it depends on how long the
         * previous frame took to complete.
         *
         * All updates that should be synced with the render fps must be
         * in this function. Note that implementing this function is optional
         * and must be overridden if needed. IME will never put anything inside
         * this function
         *
         * @see fixedUpdate
         */
        virtual void update(__attribute__((unused)) Time deltaTime) {}

        /**
         * @brief Update the scene in fixed time steps
         * @param deltaTime Time passed since last update
         *
         * This function will be called by the game engine after the scene
         * has handled system events and external inputs (Keyboard and mouse).
         * The function may be called once per frame, multiple times per frame
         * or not called at all. The delta passed to it is always the same and
         * is independent of the games frame rate. The delta time is always
         * 1.0f / FPS_LIMIT,  where FPS_LIMIT is the games Frames Per Second
         * limit
         *
         * Updates that are frame-rate independent must be in this function.
         * Note that implementing this function is optional and must be
         * overridden if needed. IME will never put anything inside this
         * function
         *
         * @see update
         */
        virtual void fixedUpdate(__attribute__((unused)) Time deltaTime) {}

        /**
         * @brief Render the scene
         * @param renderTarget Target to render scene on
         *
         * This function will be called by the game engine after the scene
         * has handled all events and been updated. The function will be
         * called once per frame.
         *
         * @note You should never render anything outside of this function
         * because the contents of the render window will be cleared before
         * this function is called meaning you won't be able to see what was
         * rendered prior. Always render in this function
         */
        virtual void render(Window &renderTarget) = 0;

        /**
         * @brief Pause the scene
         *
         * This function will be called by the game engine if another scene
         * is pushed while this scene is active
         *
         * Note that implementing this function is optional and must be
         * overridden if you want to do something when the scene is paused.
         * IME will never put anything inside this function
         *
         * @see onResume
         */
        virtual void onPause() {};

        /**
         * @brief Resume scene
         *
         * This function will be called by the game engine when the
         * current active scene is removed and this scene was paused
         *
         * Note that implementing this function is optional and must
         * be overridden if you want to do something when the scene is
         * resumed. IME will never put anything inside this function
         *
         * @see onPause
         */
        virtual void onResume() {};

        /**
         * @brief Exit a scene
         *
         * This function will be called by the game engine before the
         * scene is removed from the game. The function is optional and
         * may be overridden if you want to perform cleanup or something
         * before the scene is destroyed
         *
         * Note that implementing this function is optional and must be
         * overridden if you want to do something when the scene is resumed.
         * IME will never put anything inside this function
         *
         * @warning This function is not a replacement for the destructor,
         * it will be called first, then the destructor immediately after
         */
        virtual void onExit() {};

        /**
         * @brief Get the name of the scene
         * @return The name of the scene
         */
        const std::string& getName() const;

        /**
         * @brief Set whether or not the scene is hidden or rendered
         *        when it is paused
         * @param True to show or false to hide
         *
         * When the scene is shown on pause, it is rendered behind the
         * current active scene but it does not receive any events or
         * updates. Note that the scene will only be rendered if it has
         * been entered and it is the next scene (It is the scene that
         * will run if the current one is popped)
         *
         * By default the scene is hidden when it is paused
         *
         * @see onPause
         */
        void setVisibleOnPause(bool show);

        /**
         * @brief Check if the scene is visible when paused or not
         * @return True if visible, otherwise false
         *
         * @see setVisibleOnPause
         */
        bool isVisibleOnPause() const;

        /**
         * @brief Check if the scene has been entered or not
         * @return True if the scene has been entered, otherwise false
         *
         * @see onEnter
         */
        bool isEntered() const;

        /**
         * @brief Destructor
         */
        virtual ~Scene() = default;

    protected:
        /**
         * @brief Set the name of the scene
         * @param name The name of the scene
         *
         * The scene name is optional. By default it is empty
         *
         * This function may be useful if you want to distinguish scenes
         * by name in your own code:
         *
         * @code
         * using Keyboard = ime::input::Keyboard;
         *
         * input().onKeyUp([](Keyboard::Key key) {
         *     if (key == Keyboard::Key::Escape)
         *          engine().pushScene(scenes.get("quit");
         *     else if (key == Keyboard::Key::P)
         *          engine().pushScene(scenes.get("pause");
         * });
         * @endcode
         */
        void setName(const std::string& name);

        /**
         * @brief Set the scene timescale
         * @param timescale The new scene timescale
         *
         * The timescale can be used to speed up or slow down the scene
         * without changing the FPS limit. Values above 1.0f speed up the
         * scene whilst values below 1.0f slow it down  A timescale of
         * zero freezes the scene.
         *
         * @note A scenes timescale affects everything that requires a time
         * update. This includes timers, animations, dynamic bodies etc...
         * For example, if the timescale is set to 2.0f, then scene timers
         * will count twice as fast, animations will play twice as fast,
         * dynamic bodies will move twice as fast etc..
         *
         * By default the timescale is 1.0f (real-time)
         */
        void setTimescale(float timescale);

        /**
         * @brief Get the scenes timescale
         * @return The scenes timescale
         */
        float getTimescale() const;

        /**
         * @brief Get a reference to the game engine
         * @return A reference to the game engine
         *
         * @warning Do not keep the returned reference
         */
        Engine &engine() const;

        /**
         * @brief Get the physics simulation
         * @return The physics simulation
         *
         * The physics simulation is responsible for creating, managing,
         * colliding and updating all of the bodies within it.
         *
         * @warning The physics simulation must be created first before
         * calling this function. Calling it before creating the
         * simulation is undefined behaviour. In addition, do not attempt
         * to update the simulation, it will be updated automatically by
         * the scene
         *
         * @warning Do not keep the returned reference
         *
         * @see createWorld
         */
        World& physics();

        /**
         * @brief Get the scenes event event emitter
         * @return The scenes event event emitter
         *
         * The event emitter is local to the scene instance. This means
         * that events registered on it are only dispatched when the
         * scene is active and de-registered when the scene is destroyed.
         * For global events use the global event event emitter in the
         * Engine class or the EventDispatcher
         *
         * @warning Do not keep the returned reference
         */
        EventEmitter& eventEmitter();

        /**
         * @brief Get the global event emitter
         * @return The global event emitter
         *
         * The global event emitter is available to anything that needs it
         * (a class, function etc...). Events registered to it are always
         * dispatched regardless of the active scene. As a result you must
         * remove event listeners that are local to the scene when the
         * scene is destroyed. For example, a lambda that captures "this"
         * will result in undefined behavior if not removed after the scene
         * is destroyed
         *
         * @warning Always remove local event listeners
         */
        EventDispatcher& globalEventEmitter();

        /**
         * @brief Get the scenes input manager
         * @return The scenes input manager
         *
         * The input manager is local to the scene instance. This means
         * that input listeners registered on it are only invoked when
         * the scene is active and de-registered when the scene is destroyed
         * To register global inputs, use the global input manager in the
         * Engine class
         *
         * @warning Do not keep the returned reference
         *
         * @warning Do not try to update the input manager, it will be
         * updated internally
         */
        input::InputManager& input();

        /**
         * @brief Get the scenes audio manager
         * @return The scenes audio manager
         *
         * The audio manager is local the scene instance. For global audio,
         * use the global audio manager in the Engine class
         *
         * @warning Do not keep the returned reference
         * @warning Do not try to update the audio manager, it will be
         * updated internally
         */
        audio::AudioManager& audio();

        /**
         * @brief Get the scenes timer manager
         * @return The scenes timer manager
         *
         * The timer manager is local to the scene instance. This means that
         * callbacks scheduled on it will only be dispatched when the scene
         * is active
         *
         * @warning Do not keep the returned reference
         *
         * @warning Do not try to update the timer manager, it will be
         * updated internally
         */
        TimerManager& timer();

        /**
         * @brief Get the global cache
         * @return The global cache
         *
         * Data stored in the cache persists from scene to scene. This means
         * that another scene can access or modify data stored by another scene.
         * The data can also be accessed using the engine instance
         *
         * @note The cache only stores data, while the engine is running. When
         * the engine is shutdown, the data in the cache is destroyed
         *
         * @warning Do not keep the returned reference
         *
         * @see engine
         */
        PropertyContainer& cache();

        /**
         * @brief Get the scene gui container
         * @return The scene gui container
         *
         * The gui container is provided here for convenience, you can
         * manually instantiate as many gui containers as you desire.
         * Note that you don't have to update the returned gui container
         * or set the render target, it will done automatically by the
         * scene. However, you have to call the gui containers draw
         * function yourself because we don't know if the gui should
         * be rendered to the background or foreground
         */
        ui::GuiContainer& gui();

        /**
         * @brief Get the scene geometry shape container
         * @return The geometry shape container
         *
         * You may use this class to create geometry shape instead of using
         * their respective constructors. Consult the ShapeContainer class
         * definition for more info
         *
         * @warning Do not keep the returned reference
         */
        ShapeContainer& shapes();

        /**
         * @brief Get the scene entity container
         * @return The scene entity container
         *
         * This class stores entities that belong to this scene
         *
         * @warning Do not keep the returned reference
         */
        EntityContainer& entities();

        /**
         * @brief Create a physics simulation
         * @param gravity Acceleration of bodies in the simulation due to gravity
         *
         * This function should be called by scenes that require a physics
         * simulation
         *
         * @see physics
         */
        void createWorld(Vector2f gravity);

    private:
        Engine &engine_;                   //!< A reference to the game engine
        PropertyContainer& cache_;         //!< The global cache
        std::shared_ptr<World> world_;     //!< Physics simulation
        std::string name_;                 //!< The name of the scene (optional)
        input::InputManager inputManager_; //!< Scene level input manager
        audio::AudioManager audioManager_; //!< Scene level audio manager
        EventEmitter eventEmitter_;        //!< scene level event dispatcher
        TimerManager timerManager_;        //!< Scene level timer manager
        ui::GuiContainer guiContainer_;    //!< Scene level gui container
        ShapeContainer shapeContainer_;    //!< Stores shapes that belong to the scene
        EntityContainer entityContainer_;  //!< Stores entities that belong to the scene
        float timescale_;                  //!< Controls the speed of the scene without affecting the render fps
        bool isManaged_;                   //!< A flag indicating whether or not this scene has been added to a scene manager
        bool isEntered_;                   //!< A flag indicating whether or not the scene has been entered
        bool isVisibleWhenPaused_;         //!< A flag indicating whether or not the scene is rendered behind the active scene when it is paused
        bool hasPhysicsSim_;               //!< A flag indicating whether or not the scene has a physics simulation
        friend class SceneManager;         //!< Pre updates the scene
    };
}

#endif // IME_SCENE_H
