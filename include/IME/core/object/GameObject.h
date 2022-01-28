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

#ifndef IME_GAMEOBJECT_H
#define IME_GAMEOBJECT_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/common/Transform.h"
#include "IME/common/PropertyContainer.h"
#include "IME/common/Object.h"
#include "IME/core/event/EventEmitter.h"
#include "IME/graphics/Sprite.h"
#include "IME/core/object/ExcludeList.h"
#include <stack>

namespace ime {
    class RigidBody;
    class Scene;
    class GridMover;

    /**
     * @brief Abstract base class for game objects (players, enemies etc...)
     */
    class IME_API GameObject : public Object {
    public:
        using Ptr = std::unique_ptr<GameObject>;                      //!< Unique game object pointer
        using BodyPtr = std::unique_ptr<RigidBody>;                   //!< Unique Body pointer
        using CollisionCallback = Callback<GameObject*, GameObject*>; //!< Collision callback

        /**
         * @brief Constructor
         * @param scene The scene this game object belongs to
         */
        explicit GameObject(Scene& scene);

        /**
         * @brief Copy constructor
         */
        GameObject(const GameObject&);

        /**
         * @brief Copy assignment operator
         */
        GameObject& operator=(const GameObject&);

        /**
         * @brief Move constructor
         */
        GameObject(GameObject&&) noexcept;

        /**
         * @brief Move assignment operator
         */
        GameObject& operator=(GameObject&&) noexcept;

        /**
         * @brief Swap the game object with another game object
         * @param other The game object to swap with this game object
         */
        void swap(GameObject& other);

        /**
         * @brief Create a game object
         * @return The created game object
         */
        static GameObject::Ptr create(Scene& scene);

        /**
         * @brief Create a copy of the game object
         * @return A new game object
         */
        GameObject::Ptr copy() const;

        /**
         * @brief Set whether or not the game object is an obstacle
         * @param isObstacle True if it is an obstacle, otherwise false
         *
         * When the object is an obstacle and its active state is @a true
         * (see setActive()), then other game objects cannot overlap with
         * it. A collision event will be raised when another game object
         * attempts to occupy the same cell as the obstacle. However, the
         * two objects will never overlap
         *
         * By default, the game object is not an obstacle
         *
         * @note This function is only applicable to grid-based physics
         * (see ime::GridMover). For ime::RigidBody physics, use
         * ime::Collider::setSensor to toggle overlapping
         */
        void setAsObstacle(bool isObstacle);

        /**
         * @brief Check if the object is an obstacle or not
         * @return True if object is an obstacle, otherwise false
         *
         * @see setAsObstacle
         */
        bool isObstacle() const;

        /**
         * @brief Set current state
         * @param state The current state
         *
         * The state is number that should be associated with something
         * (maybe an enum) in your game.
         *
         * Be default, the state is -1, which is supposed to indicate
         * that there is no state. The state property is optional and
         * may be used if needs be. It is not used by IME
         */
        void setState(int state);

        /**
         * @brief Get the current state of the game object
         * @return The current state of the game object
         */
        int getState() const;

        /**
         * @brief Set whether or not the game object is active
         * @param isActive True to set as active or false to set as inactive
         *
         * Note that an inactive game object does not participate in
         * collision detection. In addition the game object's update()
         * method will not be invoked.
         *
         * For grid-based physics you can also disable collisions for the
         * game object without deactivating it by simply setting its collision
         * group or collision id to one that is not collidable with any other.
         * The same can also be done for ime::RigidBody physics by using
         * ime::Collider::setCollisionFilter
         *
         * By default, the object is active
         *
         * @see setCollisionGroup and setCollisionId
         */
        void setActive(bool isActive);

        /**
         * @brief Check if the game object is active or not
         * @return True if the game object is active, otherwise false
         *
         * @see setActive
         */
        bool isActive() const;

        /**
         * @brief Set the game objects collision id
         * @param id The id to be set
         *
         * A collision id allows game objects to selectively collide with
         * each other within colliding groups. Game objects with the same
         * collision id will collide with each other, whilst game objects
         * with different collision id's do not collide with each other.
         *
         * Note that "collision group" filtering takes higher precedence
         * than "collision id" filtering. This means that regardless of
         * how collision id's are configured, a collision will never take
         * place if the collision group of one game object is added to the
         * other game objects collision group exclude list (see getCollisionExcludeList())
         *
         * By default, the collision id is 0. This means that this game
         * object will collide with any other game object that is not in
         * its collision group exclude list
         *
         * @note This function is only applicable to grid-based physics
         * (see ime::GridMover). For ime::RigidBody collision filtering
         * use ime::Collider::setCollisionFilter
         *
         * @see setCollisionGroup and getCollisionExcludeList
         */
        void setCollisionId(int id);

        /**
         * @brief Get the collision id
         * @return The collision id
         *
         * @see setCollisionId
         */
        int getCollisionId() const;

        /**
         * @brief Set the collision group this game object belongs to
         * @param name The collision group to be set
         *
         * A collision group allows certain game objects to always collide
         * or never collide with each other. When a collision group is added
         * to the object's collision exclusion list (see getCollisionExcludeList()),
         * the game object will never collide with game objects in that group
         * (they will pass through each other), whereas when not added, the
         * game object will always collide with game objects whose collision
         * group does not appear in its exclusion list.
         *
         * Note that the @em active state (see setActive()) takes higher
         * precedence than "collision group" filtering. This means that,
         * regardless of how the collision groups are configured, a collision
         * will never take place if the game object is inactive
         *
         * For example, the following code makes objects in the "Enemies"
         * collision group to never collide with each other:
         *
         * @code
         * for (auto& enemy : enemies) {
         *      enemy.setCollisionGroup("Enemies");
         *      enemy.getCollisionExcludeList().add("Enemies");
         * }
         * @endcode
         *
         * By default, the object does not belong to any collision group
         * (empty sting). Therefore, it will collide with any other game
         * object whose collision id is the same as theirs
         *
         * @note This function is only applicable to grid-based physics
         * (see ime::GridMover). For ime::RigidBody physics collision
         * filtering, use ime::Collider::setCollisionFilter
         *
         * @see setActive, setCollisionId and getCollisionExcludeList
         */
        void setCollisionGroup(const std::string& name);

        /**
         * @brief Get the collision group this object belongs to
         * @return The game objects collision group
         *
         * @see setCollisionGroup
         */
        const std::string& getCollisionGroup() const;

        /**
         * @brief Get access to the game object's collision exclude list
         * @return The game object's collision exclude list
         *
         * This list allows you to specify which game objects this game
         * object should or should not collide with
         *
         * By default, the game object collides with all other objects
         *
         * @note This function is only applicable to grid-based physics
         * (see ime::GridMover). For ime::RigidBody physics collision
         * filtering use ime::Collider::setCollisionFilter
         *
         * @see getObstacleCollisionFilter
         */
        ExcludeList& getCollisionExcludeList();
        const ExcludeList& getCollisionExcludeList() const;

        /**
         * @brief Get access to the game object's obstacle collision filter
         * @return The game objects obstacle collision filter
         *
         * @note This function is only applicable to obstacle game objects
         * (see setAsObstacle()).
         *
         * By default, any object that @e cannot collide with an obstacle game
         * object will pass through it without generating a collision event
         * whereas if they @e can collide, the two objects will never overlap.
         *
         * Sometimes you may want an obstacle object to exhibit the default
         * behavior for some objects but allow others to pass through it and
         * still generate a collision event. This list helps you achieve that.
         * The collision groups of game objects added to this list will pass
         * over an obstacle game object but generate a collision event
         *
         * @see getCollisionExcludeList
         */
        ExcludeList& getObstacleCollisionFilter();
        const ExcludeList& getObstacleCollisionFilter() const;

        /**
         * @brief Get the user data added to game object
         * @return The user data
         *
         * The user data object can be used to store additional information
         * about the game object. For example, you may store a profile associated
         * with the game object or when the game object was instantiated etc...
         * You can store any type and any number of data in the user date object
         *
         * Note that IME does not store anything inside the user data object,
         * it is reserved for external use only
         */
        PropertyContainer& getUserData();
        const PropertyContainer& getUserData() const;

        /**
         * @brief Get the name of the class the game object is instantiated from
         * @return The name of the concrete class the game object is instantiated
         *         from
         *
         * Note that this function must be overridden further if this class
         * is extended, otherwise it will return the name of this class
         * instead of your class name
         *
         * @see getClassType
         */
        std::string getClassName() const override;

        /**
         * @brief Get the name of this class
         * @return The name of this class
         *
         * Note that this function is only implemented by child classes
         * of Object which also serve as a base class for other classes
         *
         * @see getClassName
         */
        std::string getClassType() const override;

        /**
         * @brief Attach a physics Body to the game object
         * @param body Physics body to be attached to the game object
         *
         * When a rigid body is attached to a game object, the game object
         * becomes enabled for physics. This means that it will react to
         * gravity, friction, applies forces, impulses etc. The position
         * and rotation of the game object will be controlled by the physics
         * engine therefore you should refrain from calling functions that
         * MODIFY the game objects transform (position, rotation and origin).
         * A result of doing so is inconsistency. Note that the physics engine
         * does not account for scaling. This means that scaling the objects
         * sprite will NOT scale the objects body or the body's collider. If
         * you want the body to scale with the objects sprite, you should
         * remove the old collider and attach a new one with the appropriate
         * size.
         *
         * @warning The pointer must not be a nullptr. Also, you cannot attach
         * a rigid body to a game object that already has a rigid body attached
         * to it, the current rigid body must be removed first
         *
         * @see removeRigidBody
         */
        void attachRigidBody(BodyPtr body);

        /**
         * @brief Get the game objects physics body
         * @return The game objects physics body if any, otherwise a nullptr
         */
        RigidBody* getRigidBody();
        const RigidBody* getRigidBody() const;

        /**
         * @brief Remove a rigid body from the game object
         *
         * Removing a rigid Body from an game object disables all physics
         * applied to it
         *
         * @see attachRigidBody
         */
        void removeRigidBody();

        /**
         * @brief Check if the the game object has a rigid body attached to it
         * @return True if the game object has a rigid body attached to it,
         *         otherwise false
         */
        bool hasRigidBody() const;

        /**
         * @brief Add an event listener to a grid collision event
         * @param callback Function to be executed when this game object
         *                 collides with another game object in a TileMap
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listeners identification number
         *
         * @note This function is applicable to grid-based collisions only
         * (see ime::GridMover), as such it is called only when this game
         * object and another game object occupy the same tile. The callback
         * is passed this game object and the game object in collision with
         * respectively.
         *
         * Unlike ime::GridMover::onGameObjectCollision which is triggered
         * only when the game object collides with another game object, this
         * callback is called when the game object collides with another game
         * object or when another game object collides with it.
         *
         * For ime::RigidBody collision, see onCollisionStart, onCollisionStay
         * and onCollisionEnd
         *
         * @see removeCollisionListener
         */
        int onCollision(const CollisionCallback& callback, bool onetime = false);

        /**
         * @brief Remove a grid collision event listener
         * @param id The id of the collision listener to be removed
         * @return True if the event listener was removed or false if no
         *         such handler exists
         */
        bool removeCollisionListener(int id);

        /**
         * @brief Add an event listener to a collision begin event
         * @param callback The function to be executed when event is fired
         *
         * The callback function is called when two game objects begin to
         * overlap. The callback is passed this game object and the game
         * object that collided with this game object respectively. Pass
         * nullptr to remove the current callback
         *
         * A collision begin handler may be registered on the game object or on
         * the collider that is attached to the game objects rigid body or on
         * both. However, exercise caution as registering the same handler on
         * both objects will result in the handler being executed twice each
         * time the event is fired
         *
         * @note A collision begin event can only occur if the game object has a
         * rigid body attached to it and the rigid body has a Collider attached
         * to it
         *
         * @warning Don't keep the pointers passed to the callback, they are
         * invalidated when the callback execution terminates
         *
         * @see attachRigidBody, onCollisionStay and onCollisionEnd
         */
        void onCollisionStart(const CollisionCallback& callback);

        /**
         * @brief Add an event listener to a collision end event
         * @param callback The function to be executed when event is fired
         *
         * The callback function is called when two game objects stop
         * overlapping. The callback is passed this game object and the
         * game object that stopped overlapping with this game object
         * respectively. Pass nullptr to remove the current callback.
         *
         * A collision end handler may be registered on the game object or on
         * the collider that is attached to the game objects rigid body or on
         * both. However, exercise caution as registering the same handler on
         * both objects will result in the handler being executed twice each
         * time the event is fired
         *
         * @note A collision end event can only occur if the game object has a
         * rigid body attached to it and the rigid body has a Collider attached
         * to it
         *
         * @warning Don't keep the pointers passed to the callback, they are
         * invalidated when the callback execution terminates
         *
         * @see attachRigidBody, onCollisionStart and onCollisionStay
         */
        void onCollisionEnd(const CollisionCallback& callback);

        /**
         * @brief Add an event listener to a collision stay event
         * @param callback The function to be executed when event is fired
         *
         * The callback function is called while this game object remains in
         * contact with another game object. The callback is passed this game
         * object and the game object that is currently in contact with this
         * game object respectively. Pass nullptr to remove the current callback
         *
         * A collision stay handler may be registered on the game object or on
         * the collider that is attached to the game objects rigid body or on
         * both. However, exercise caution as registering the same handler on
         * both objects will result in the handler being executed twice each
         * time the event is fired
         *
         * @note A collision stay event can only occur if the game object has
         * a rigid body attached to it and the rigid body is awake and has a
         * Collider attached to it that is not a sensor
         *
         * @warning Don't keep the pointers passed to the callback, they are
         * invalidated when the callback execution terminates
         *
         * @see attachRigidBody, onCollisionStart and onCollisionEnd
         */
        void onCollisionStay(const CollisionCallback& callback);

        /**
         * @brief Get the game objects transform
         * @return The game objects transform
         *
         * The transform can be used to query or modify the game object
         * position, scale, rotation and origin
         *
         * @warning Do not use the ime::Transform::onPropertyChange function
         * of the returned object, It is used internally. Use ime::Object::onPropertyChange
         * instead, which in inherited.
         */
        Transform& getTransform();
        const Transform& getTransform() const;

        /**
         * @brief Get the scene the game object belongs to
         * @return The scene the game object belongs to
         */
        Scene& getScene();
        const Scene& getScene() const;

        /**
         * @brief Reset the origin of the sprite
         *
         * The origin is reset to the local centre of the sprite
         *
         * @note This function must be called everytime the sprites texture,
         * texture rectangle size or scale is changed
         */
        void resetSpriteOrigin();

        /**
         * @brief Get the game objects graphical representation
         * @return The game objects graphical representation
         *
         * By default, the sprite is empty
         */
        Sprite& getSprite();
        const Sprite& getSprite() const;

        /**
         * @brief Get the objects grid mover
         * @return The objects grid mover or a nullptr if the object is not
         *         being controlled by a grid mover
         *
         * @see ime::GridMover
         */
        GridMover* getGridMover();
        const GridMover* getGridMover() const;

        /**
         * @brief Update the game object
         * @param deltaTime Time past since last update
         *
         * @a deltaTime is synced with the render FPS. In other words, it is
         * frame-rate dependent.
         *
         * Note that this function is provided for external use only, IME will
         * never put anything inside it. This means that don't have to call
         * the base class version when overriding it
         */
        virtual void update(Time deltaTime) {IME_UNUSED(deltaTime);}

        /**
         * @internal
         * @brief Set the game object's grid mover
         * @param gridMover The grid mover to be set
         *
         * @warning This function is intended for internal use only and should
         * never be called outside of IME
         */
        void setGridMover(GridMover* gridMover);

        /**
         * @internal
         * @brief Emit a collision event on the game object
         * @param event Collision event to be emitted
         * @param other The game object that triggered the event
         *
         * @warning This function is intended for internal use only and should
         * never be called outside of IME
         */
        void emitCollisionEvent(const std::string& event, GameObject* other);

        /**
         * @internal
         * @brief Emit a collision event
         * @param other The game object in collision with this game object
         *
         * @warning This function is intended for internal use only and should
         * never be called outside of IME
         */
        void emitCollisionEvent(GameObject* other);

        /**
         * @brief Destructor
         */
        ~GameObject() override;

    private:
        /**
         * @brief Subscribe game object to events
         */
        void initEvents();

    private:
        std::reference_wrapper<Scene> scene_; //!< The scene this game object belongs to
        int state_;                           //!< The current state of the game object
        bool isObstacle_;                     //!< A flag indicating whether or not the object is an obstacle
        bool isActive_;                       //!< A flag indicating whether or not the game object is active
        Transform transform_;                 //!< The objects transform
        Sprite sprite_;                       //!< The objects visual representation
        BodyPtr body_;                        //!< The rigid body attached to this game object
        int postStepId_;                      //!< Scene post step handler id
        int destructionId_;                   //!< Scene destruction listener id
        PropertyContainer userData_;          //!< Used to store metadata about the object
        EventEmitter emitter_;                //!< Publishes events specific to GameObject
        CollisionCallback onContactBegin_;    //!< Called when this game object starts colliding with another game object or vice versa
        CollisionCallback onContactStay_;     //!< Called when this game object remains in collision with another game object or vice versa
        CollisionCallback onContactEnd_;      //!< Called when this game object stops colliding with another game object or vice versa
        ExcludeList excludeList_;             //!< Stores the collision groups of game objects this game object should not collide with
        ExcludeList obstacleColFilter_;       //!< Stores the collision groups of game objects that can collide with an obstacle without being blocked
        std::string collisionGroup_;          //!< The objects collision group (collision filtering)
        int collisionId_;                     //!< The objects collision id (collision filtering)
        GridMover* gridMover_;                //!< The objects grid mover
    };
}

#endif // IME_IENTITY_H
