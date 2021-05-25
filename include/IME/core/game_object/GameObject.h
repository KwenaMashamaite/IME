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

#ifndef IME_GAMEOBJECT_H
#define IME_GAMEOBJECT_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/common/Transform.h"
#include "IME/common/PropertyContainer.h"
#include "IME/common/Object.h"
#include "IME/core/event/EventEmitter.h"
#include "IME/graphics/Sprite.h"
#include <stack>

namespace ime {
    class RigidBody;
    class Scene;

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
         * Note that this property only affects grid based physics (see GridMover)
         * When an object is an obstacle and its collidable state is true, then
         * other game objects cannot overlap with it. A collision event will be
         * raised when another game object attempts to occupy the same cell as
         * the obstacle. However, the two object will not visually overlap
         *
         * By default, the game object is not an obstacle
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
         * @brief Set whether the game object is active or inactive
         * @param isActive True to set active or false to set inactive
         */
        void setActive(bool isActive);

        /**
         * @brief Check if the game object is active or not
         * @return True if the game object is active, otherwise false
         */
        bool isActive() const;

        /**
         * @brief Set whether the game object is collidable or not
         * @param collidable True to make collidable, otherwise false
         *
         * This function has no effect if the game object does not have a
         * physics body attached to it or if the attached physics body
         * does not have a collider.
         *
         * When @a collidable is true, this function will reset the collision
         * filter to all collisions and when @a collidable is false the function
         * will reset the collision filter to no collisions. If the game object
         * must collide with some game objects and ignore other game objects
         * then it is advised to use the game objects Collider to enable or
         * disable collisions as it gives you great flexibility
         */
        void setCollidable(bool collidable);

        /**
         * @brief Check if the game object is collidable or not
         * @return True if the game object is collidable, otherwise false
         */
        bool isCollidable() const;

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
         */
        Transform& getTransform();
        const Transform& getTransform() const;

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
         * @brief Update the game object
         * @param deltaTime Time past since last update
         *
         * @warning When overriding this function make sure to call the base
         * class version first in your implementation. In addition, don't
         * invoke the overridden function, it will be called by the engine
         */
        virtual void update(Time deltaTime);

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
        bool isCollidable_;                   //!< A flag indicating whether or not the game object is collidable
        Transform transform_;                 //!< The objects transform
        Sprite sprite_;                       //!< The objects visual representation
        BodyPtr body_;                        //!< The rigid body attached to this game object
        int postStepId_;                      //!< Scene post step handler id
        int destructionId_;                   //!< Scene destruction listener id
        PropertyContainer userData_;          //!< Used to store metadata about the object
        CollisionCallback onContactBegin_;    //!< Called when this game object starts colliding with another game object or vice versa
        CollisionCallback onContactStay_;     //!< Called when this game object remains in collision with another game object or vice versa
        CollisionCallback onContactEnd_;      //!< Called when this game object stops colliding with another game object or vice versa
    };
}

#endif // IME_IENTITY_H
