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
#include "IME/core/object/Object.h"
#include "IME/graphics/Sprite.h"

namespace ime {
    class RigidBody;
    class Scene;

    /**
     * @brief Class for modelling game objects (players, enemies etc...)
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
         * @brief Create a new GameObject instance
         * @param scene The scene the object belongs to
         * @return The created instance
         */
        static GameObject::Ptr create(Scene& scene);

        /**
         * @brief Create a copy of the game object
         * @return A new game object
         */
        GameObject::Ptr copy() const;

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
         * By default, the object is active
         *
         * @see isActive
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
         * @brief Add an event listener to a rigid body collision begin event
         * @param callback The function to be executed when the event is fired
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listeners identification number
         *
         * The callback function is called when two game objects begin to
         * overlap. The callback is passed this game object and the game
         * object that collided with this game object respectively.
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
         * @see attachRigidBody, onCollisionStay and onCollisionEnd
         */
        int onRigidBodyCollisionStart(const CollisionCallback& callback, bool oneTime = false);

        /**
         * @brief Add an event listener to a rigid body collision end event
         * @param callback The function to be executed when the event is fired
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listeners identification number
         *
         * The callback function is called when two game objects stop
         * overlapping. The callback is passed this game object and the
         * game object that stopped overlapping with this game object
         * respectively.
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
         * @see attachRigidBody, onCollisionStart and onCollisionStay
         */
        int onRigidBodyCollisionEnd(const CollisionCallback& callback, bool oneTime = false);

        /**
         * @brief Add an event listener to a rigid body collision stay event
         * @param callback The function to be executed when the event is fired
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listeners identification number
         *
         * The callback function is called while this game object remains in
         * contact with another game object. The callback is passed this game
         * object and the game object that is currently in contact with this
         * game object respectively.
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
         * @see attachRigidBody, onCollisionStart and onCollisionEnd
         */
        int onRigidBodyCollisionStay(const CollisionCallback& callback, bool oneTime = false);

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
         * @brief Update the game object
         * @param deltaTime Time past since last update
         *
         * This function is automatically called by IME. @a deltaTime is synced
         * with the render FPS. In other words, it is frame-rate dependent.
         *
         * Note that this function is provided for external use only, IME will
         * never put anything inside it. This means that don't have to call
         * the base class version when overriding it
         */
        virtual void update(Time deltaTime) {IME_UNUSED(deltaTime);}

        /**
         * @internal
         * @brief Emit a rigid body collision event on the game object
         * @param event Collision event to be emitted
         * @param other The game object that triggered the event
         *
         * @warning This function is intended for internal use only and should
         * never be called outside of IME
         */
        void emitRigidBodyCollisionEvent(const std::string& event, GameObject* other);

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
        bool isActive_;                       //!< A flag indicating whether or not the game object is active
        Transform transform_;                 //!< The objects transform
        Sprite sprite_;                       //!< The objects visual representation
        BodyPtr body_;                        //!< The rigid body attached to this game object
        int postStepId_;                      //!< Scene post step handler id
        int destructionId_;                   //!< Scene destruction listener id
        PropertyContainer userData_;          //!< Used to store metadata about the object
    };
}

#endif // IME_IENTITY_H
