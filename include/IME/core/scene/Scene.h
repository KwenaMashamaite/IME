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
#include "IME/core/input/InputManager.h"
#include "IME/core/audio/AudioManager.h"
#include "IME/core/time/TimerManager.h"
#include "IME/common/PropertyContainer.h"
#include <string>

namespace ime {
    class Engine; //!< Engine class forward declaration
    class Window; //!< Window class forward declaration

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
         * All updates that need a variable time step must be in this function
         *
         * @see fixedUpdate
         */
        virtual void update(Time deltaTime) = 0;

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
         * Updates that are frame-rate independent must be in this function
         *
         * This update function is optional and may be overridden if required
         *
         * @see update
         */
        virtual void fixedUpdate(Time deltaTime) {};

        /**
         * @brief Render the scene
         * @param renderTarget Target to render scene on
         *
         * This function will be called by the game engine after the scene
         * has handled all events and been updated. The function will be
         * called once per frame
         */
        virtual void render(Window &renderTarget) = 0;

        /**
         * @brief Pause the scene
         *
         * This function will be called by the game engine if another scene
         * is pushed while this scene is active
         *
         * The function is optional and may be overridden if you want to
         * do something when the scene is paused
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
         * The function is optional and may be overridden if you want to
         * do something when the scene is resumed
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
         * @warning This function is not a replacement for the destructor,
         * it will be called first, then the destructor immediately after
         */
        virtual void onExit() {};

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
         * @brief Get a reference to the game engine
         * @return A reference to the game engine
         */
        Engine &engine() const;

        /**
         * @brief Get the scenes event event emitter
         * @return The scenes event event emitter
         *
         * The event emitter is local to the scene instance. This means
         * that events registered on it are only dispatched when the
         * scene is active and de-registered when the scene is destroyed.
         * For global events use the global event event emitter in the
         * Engine class or the EventDispatcher
         */
        EventEmitter& eventEmitter();

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
         * @see engine
         */
        PropertyContainer& cache();

    private:
        Engine &engine_;                   //!< A reference to the game engine
        PropertyContainer& cache_;         //!< The global cache
        std::string name_;                 //!< The name of the scene (optional)
        input::InputManager inputManager_; //!< The local input manager for this scene
        audio::AudioManager audioManager_; //!< The local audio manager for this scene
        EventEmitter eventEmitter_;        //!< The local event dispatcher for this scene
        TimerManager timerManager_;        //!< The local timer manager for this scene
        bool isManaged_;                   //!< A flag indicating whether or not this scene has been added to a scene manager
        bool isEntered_;                   //!< A flag indicating whether or not the scene has been entered
        bool isVisibleWhenPaused_;         //!< A flag indicating whether or not the scene is rendered behind the active scene when it is paused
        friend class SceneManager;         //!< Pre updates the scene
    };
}

#endif // IME_SCENE_H
