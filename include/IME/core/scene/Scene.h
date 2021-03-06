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
#include "IME/core/scene/GameObjectContainer.h"
#include "IME/core/scene/RenderLayerContainer.h"
#include "IME/core/scene/DrawableContainer.h"
#include "IME/core/scene/GridMoverContainer.h"
#include "IME/ui/GuiContainer.h"
#include "IME/utility/NonCopyable.h"
#include "IME/graphics/Camera.h"
#include "IME/core/tilemap/TileMap.h"
#include "IME/core/physics/PhysicsIterations.h"
#include <string>
#include <memory>
#include <vector>

namespace ime {
    class Engine;
    class PhysicsWorld;

    /// @internal
    namespace priv {
       class SceneManager;
    }

    /**
     * @brief An Abstract Base Class (ABC) for game scenes
     */
    class IME_API Scene : public Object {
    public:
        using Ptr = std::unique_ptr<Scene>; //!< Unique Scene pointer

        /**
         * @brief Defines what happens to the scene when it is paused
         */
        enum OnPauseAction {
            Default      = 0,      //!< The scene is hidden and does not receive time and system updates
            Show         = 1 << 0, //!< The scene is rendered behind the current active scene but does not receives time and system updates
            UpdateTime   = 1 << 1, //!< The scene is hidden and receives time updates only (timer, physics, animation updates, etc ...)
            UpdateSystem = 1 << 2, //!< The scene is hidden and receives system updates only (Window events, Input updates, etc ...)
            UpdateAll    = 1 << 3  //!< The scene is hidden and receives both time and system updates
        };

        /**
         * @brief Default Constructor
         */
        Scene();

        /**
         * @brief Copy constructor
         */
        Scene(const Scene&) = delete;

        /**
         * @brief Copy assignment operator
         */
        Scene& operator=(const Scene&) = delete;

        /**
         * @brief Move constructor
         */
        Scene(Scene&&) noexcept ;

        /**
         * @brief Move assignment operator
         */
        Scene& operator=(Scene&&) noexcept ;

        /**
         * @internal
         * @brief Initialize the scene
         * @param engine The engine that runs the scene
         *
         * This function initializes all scene components that depend on the
         * engine for their functionality. This function is called before the
         * scene is entered
         *
         * @warning This function is intended for internal use and should
         * never be called outside of IME
         */
        void init(Engine& engine);

        /**
         * @brief Initialize scene
         *
         * This function is called by the game engine when the base scene is ready
         * to be used. It is called once after the constructor but before
         * onEnter(). Note that IME scene functions cannot be called in the
         * constructor, doing so is undefined behavior. Thus, this function is
         * intended for situation where IME scene functions need to be accessed
         * before the scene is entered. In addition, unlike onEnter(), this
         * function is called after the scene is pushed to the engine. This
         * means that it will be invoked regardless of the running state of
         * the engine
         *
         * Note that IME will never put anything inside this function,
         * therefore you don't have to call the base class method in your
         * implementation
         */
        virtual void onInit() {};

        /**
         * @brief Enter the scene
         *
         * This function will be called by the game engine when the scene
         * is entered for the first time. Note that a scene cannot be entered
         * more than once, in other words this function will only be called
         * once
         */
        virtual void onEnter() = 0;

        /**
         * @brief Handle a system event
         * @param event System event to be handled
         *
         * This function will be called by the game engine before the scene
         * is updated. Override this function if you want to handle a window
         * specific events such as window resize event. Do not use it to
         * handle input related events. Use the scenes input manager or the
         * global input manager found in the Engine. The function is called
         * once per frame
         *
         * Note that implementing this function is optional and must be overridden
         * if needed. IME will never put anything inside this function, therefore
         * you don't have to call the base class method in your implementation
         */
        virtual void handleEvent(Event event) {IME_UNUSED(event);};

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
         * this function, therefore you don't have to call the base class
         * method in your implementation
         *
         * @see fixedUpdate
         */
        virtual void update(Time deltaTime) {IME_UNUSED(deltaTime);}

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
         * function, therefore you don't have to call the base class method
         * in your implementation
         *
         * @see update
         */
        virtual void fixedUpdate(Time deltaTime) {IME_UNUSED(deltaTime);}

        /**
         * @brief Post update the scene
         * @param deltaTime Time passed since last update
         *
         * This function is called after fixed update and update but
         * before the scene is rendered. It may be useful if you want to do
         * something after all time updates (timer updates, physics updates,
         * animation updates, gui updates etc...) have completed.
         *
         * Note that implementing this function is optional and must be
         * overridden if needed. IME will never put anything inside this
         * function, therefore you don't have to call the base class method
         * in your implementation
         */
        virtual void postUpdate(Time deltaTime) {IME_UNUSED(deltaTime);}

        /**
         * @brief Pause the scene
         *
         * This function will be called by the game engine if another scene
         * is pushed while this scene is active
         *
         * Note that implementing this function is optional and must be
         * overridden if you want to do something when the scene is paused.
         * IME will never put anything inside this function, therefore you
         * don't have to call the base class method in your implementation
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
         * resumed. IME will never put anything inside this function,
         * therefore you don't have to call the base class method in
         * your implementation
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
         * IME will never put anything inside this function. therefore you
         * don't have to call the base class method in your implementation
         *
         * @warning This function is not a replacement for the destructor,
         * it will be called first, then the destructor immediately after
         */
        virtual void onExit() {};

        /**
         * @brief Get the name of this class
         * @return The name of this class
         */
        std::string getClassName() const override;

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
         * @internal
         * @brief Add an event listener to a scene event
         * @param event Event to add event listener to
         * @param callback Function to be execute when the event is fired
         * @return The callback id
         *
         * @warning This function is intended for internal use and should
         * never be called outside of IME
         */
        template<typename ...Args>
        int on_(const std::string& event, Callback<Args...> callback) {
            return internalEmitter_.on(event, callback);
        }

        /**
         * @internal
         * @brief Unsubscribe from a scene event
         * @param event The event to unsubscribe from
         * @param id The event listeners id
         * @return True if the event listener was unsubscribed or false if
         *         @a event does not have a listener with the @a id
         *
         * @warning This function is intended for internal use and should
         * never be called outside of IME
         */
        bool unsubscribe_(const std::string& event, int id);

        /**
         * @brief Destructor
         */
        ~Scene() override;

    protected:
        /**
         * @deprecated Since v2.1.0, will be removed in v2.2.0. Use
         *             ime::Scene::setOnPauseAction instead.
         *
         * @brief Set whether or not the scene is hidden or rendered
         *        when it is paused
         * @param show True to show or false to hide
         *
         * When the scene is shown on pause, it is rendered behind the
         * current active scene but it does not receive any events or
         * updates. Note that the scene will only be rendered if it has
         * been entered and it is the next scene (It is the scene that
         * will run if the current one is popped)
         *
         * By default the scene is hidden when it is paused
         *
         * @see setOnPauseAction
         */
        [[deprecated("Use 'void ime::Scene::setOnPauseAction(ime::Uint32)' instead.")]]
        void setVisibleOnPause(bool show);

        /**
         * @brief Set which action is taken when the scene is paused
         * @param action Action to be taken
         *
         * Mote that actions can be combined using bitwise OR combination
         * of ime::OnPauseAction enumerations. For example, to make the
         * scene shown behind the current active scene and receive updates,
         * you do as follows:
         *
         * @code
         * setOnPauseAction(ime::Scene::Show | ime::Scene::UpdateAll)
         * @endcode
         *
         * By default the scene is hidden when it is paused and it does
         * not receive time and system (Window events, Input, etc...)
         * updates
         *
         * @see onPause
         */
        void setOnPauseAction(Uint32 action);

        /**
         * @brief Enable or disable scene input (keyboard, mouse, etc...)
         * @param enable True to enable input or false to disable it
         *
         * Note that input handlers are not destroyed when input is disabled.
         * Upon input re-enable, input handlers will be invoked as before
         *
         * By default, input is enabled
         *
         * @see input
         */
        void setInputEnable(bool enable);

        /**
         * @brief Check whether or not input is enabled for this scene
         * @return True if input is enabled, otherwise false
         *
         * @see setInputEnable
         */
        bool isInputEnabled() const;

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
         * @brief Get the scene level camera
         * @return The scene level camera
         */
        Camera& camera();

        /**
         * @brief Get the scene level physics simulation
         * @return The scene level physics simulation
         *
         * The physics simulation is responsible for creating, managing,
         * colliding and updating all of the bodies within it.
         *
         * @warning The physics simulation must be created first before
         * calling this function. Calling it before creating the creating
         * teh simulation will lead to undefined behavior undefined behaviour
         *
         * @see createPhysWorld
         */
        PhysicsWorld& physWorld();

        /**
         * @brief Get the scenes grid mover container
         * @return The scenes grid mover container
         *
         * Note that you can use this container to store a GridMover or you
         * can use your own container. The advantage of using this container
         * is that the GridMover instance is updated on your behalf
         */
        GridMoverContainer& gridMovers();

        /**
         * @brief Get the scene level event event emitter
         * @return The scene level event event emitter
         *
         * The event emitter is local to the scene instance. This means
         * that events registered on it are only dispatched when the
         * scene is active and de-registered when the scene is destroyed.
         *
         * @see globalEventEmitter
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
         * @brief Get the scene level input manager
         * @return The scene level input manager
         *
         * The input manager is local to the scene instance. This means
         * that input listeners registered on it are only invoked when
         * the scene is active and de-registered when the scene is destroyed
         *
         * @see ime::Engine::getInputManager
         */
        input::InputManager& input();

        /**
         * @brief Get the scene level audio manager
         * @return The scene level audio manager
         *
         * The audio manager is local to the scene instance. All audio played
         * by it is destroyed when the scene is destroyed
         *
         * @see ime::Engine::getAudioManager
         */
        audio::AudioManager& audio();

        /**
         * @brief Get the scene level timer manager
         * @return The scene level timer manager
         *
         * The timer manager is local to the scene instance. This means that
         * callbacks scheduled on it will only be dispatched when the scene
         * is active
         *
         * @see ime::Engine::setTimeout and ime::Engine::setInterval
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
         * @brief Get the scene render layers
         * @return The scene render layers
         *
         * Render layers allow the scene to be rendered in separate layers
         * which are then composed back together. By default the scene has
         * a "default" layer at index 0. When a drawable object is added to
         * the scene without an explicit layer, it will be added to the default
         * layer. You can add objects to the "default" layer or even remove
         * the "default" layer from the render layer container, however you
         * mus not forget to reallocate the objects in the "default" layer to
         * another layer, otherwise they will not be drawn to the screen
         *
         * @note When the scene contains a tilemap (createTilemap called),
         * the scene uses the tilemap's render layers instead of its own.
         * This means that drawables added using this function will not
         * be rendered. Only use this function if the scene does not have
         * a tilemap
         */
        RenderLayerContainer& renderLayers();

        /**
         * @brief Get the scene level Tilemap
         * @return The scene level tilemap
         *
         * Note that only one tilemap can be created per scene
         *
         * @warning The tilemap must be created before it is used. Calling
         * this function before the tilemap is created is undefined behavior
         *
         * @see createTilemap
         */
        TileMap& tilemap();

        /**
         * @brief Get the scene level gui container
         * @return The scene level gui container
         *
         * The gui container is local to the scene. This means that all widgets
         * in it are destroyed when the scene is destroyed
         *
         * @see ime::Engine::getGui
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
         * @brief Get the scene level game object container
         * @return The scene level game object container
         *
         * This class stores game objects that belong to this scene. All
         * game objects in this container are automatically updated
         *
         * @warning Do not keep the returned reference
         */
        GameObjectContainer& gameObjects();

        /**
         * @brief Get the scene level sprite container
         * @return The scene level sprite container
         *
         * This class stores the sprites in the scene. The sprite's animator
         * will automatically be updated
         */
        SpriteContainer& sprites();

        /**
         * @brief Create a scene level physics simulation
         * @param gravity Acceleration of bodies in the simulation due to gravity
         * @param iterations Position and velocity iterations (see ime::PhysIterations)
         *
         * @note This function should only be called by scenes that require
         * a physic simulation. If the scene only makes use of grid-based
         * physics (see ime::GridMover) then set @a gravity and @a iterations
         * to zero for improved performance
         *
         * @see physWorld
         */
        void createPhysWorld(Vector2f gravity, const PhysIterations& iterations = {3, 8});

        /**
         * @brief Create the scene level tilemap instance
         * @param tileWidth The width of the tilemap
         * @param tileHeight The height of the tilemap
         *
         * Note that this function only creates a tilemap instance so that
         * it can be used. You still need to construct the tilemap using
         * the appropriate member function
         *
         * @warning Only a single tilemap can be created, therefore calling
         * this function will destroy the previous tilemap
         *
         * @see tilemap
         */
        void createTilemap(unsigned int tileWidth, unsigned int tileHeight);

    private:
        std::unique_ptr<Camera> camera_;      //!< Scene level camera
        std::unique_ptr<PhysicsWorld> world_; //!< Scene level physics simulation
        input::InputManager inputManager_;    //!< Scene level input manager
        audio::AudioManager audioManager_;    //!< Scene level audio manager
        EventEmitter eventEmitter_;           //!< scene level event dispatcher
        EventEmitter internalEmitter_;        //!< Emits internal scene events
        TimerManager timerManager_;           //!< Scene level timer manager
        ui::GuiContainer guiContainer_;       //!< Scene level gui container
        RenderLayerContainer renderLayers_;   //!< Render layers for this scene
        GridMoverContainer gridMovers_;       //!< Stores grid movers that belong to the scene
        std::unique_ptr<TileMap> tileMap_;    //!< Scene level tilemap
        float timescale_;                     //!< Controls the speed of the scene without affecting the render fps
        bool isInputEnabled_;                 //!< A flag indicating whether or not the scene receives input
        bool isEntered_;                      //!< A flag indicating whether or not the scene has been entered
        bool isVisibleWhenPaused_;            //!< A flag indicating whether or not the scene is rendered behind the active scene when it is paused
        bool isTimeUpdatedWhenPaused_;        //!< A flag indicating whether or not the scene receives time updates when it is paused
        bool isEventUpdatedWhenPaused_;       //!< A flag indicating whether or not the scene receives system events when it is paused
        bool hasPhysicsSim_;                  //!< A flag indicating whether or not the scene has a physics simulation
        bool hasTilemap_;                     //!< A flag indicating whether or not the scene has a tilemap
        friend class priv::SceneManager;      //!< Pre updates the scene

        std::unique_ptr<std::reference_wrapper<Engine>> engine_;           //!< A reference to the game engine
        std::unique_ptr<SpriteContainer> spriteContainer_;                 //!< Stores sprites that belong to the scene
        std::unique_ptr<GameObjectContainer> entityContainer_;             //!< Stores game objects that belong to the scene
        std::unique_ptr<ShapeContainer> shapeContainer_;                   //!< Stores shapes that belong to the scene
        std::unique_ptr<std::reference_wrapper<PropertyContainer>> cache_; //!< The engine level cache
    };
}

#endif // IME_SCENE_H

/**
 * @class ime::Scene
 * @ingroup core
 *
 * A ime::Scene represents a distinct state of your game, for example
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
 *
 * Usage example:
 * @code
 * class StartUpScene : public ime::Scene {
 *      void onEnter() override {
 *          ime::ui::Label::Ptr greeting = ime::ui::Label::create("Thank you for using Infinite Motion Engine");
 *          greeting->setOrigin(0.5f, 0.5f);
 *          greeting->setPosition("50%", "50%");
 *          gui().addWidget(std::move(greeting), "lblGreeting");
 *      }
 * }
 *
 * ...
 *
 * engine.pushScene(std::make_unique<StartUpScene>());
 * @endcode
 */
