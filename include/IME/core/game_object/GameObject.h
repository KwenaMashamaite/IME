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
#include "IME/common/Direction.h"
#include "IME/common/Transform.h"
#include "IME/core/event/EventEmitter.h"
#include "IME/graphics/Sprite.h"
#include <stack>
#include <string>
#include <memory>

namespace ime {
    class Body;  //!< Rigid body class forward declaration
    class Scene; //!< Scene class forward declaration

    /**
     * @brief Abstract base class for game objects (players, enemies etc...)
     */
    class IME_API GameObject {
    public:
        using sharedPtr = std::shared_ptr<GameObject>; //!< Shared GameObject pointer
        using BodyPtr = std::shared_ptr<Body>;     //!< Shared Body pointer

        /**
         * @brief The type of the GameObject
         */
        enum class Type {
            Unknown = -1, //!< Unknown object
            Player = 0,   //!< Player object
            Enemy,        //!< Enemy object
            Collectable,  //!< Collectable object
            Obstacle,     //!< Obstacle object
        };

        /**
         * @brief Construct the game object
         * @param scene The scene this game object belongs to
         * @param type Type of the game object
         */
        explicit GameObject(Scene& scene, Type type = Type::Unknown);

        /**
         * @brief Copy constructor
         * @param other Object to be copied
         */
        GameObject(const GameObject& other);

        /**
         * @brief Assignment operator
         */
        GameObject& operator=(const GameObject&);

        /**
         * @brief Move constructor
         */
        GameObject(GameObject&&) = default;

        /**
         * @brief Move assignment operator
         */
        GameObject& operator=(GameObject&&) = default;

        /**
         * @brief Check if two game objects are the same object or not
         * @param rhs Object to compare against this object
         * @return True if the two entities are the same object
         *
         * Two game objects are the same object if they have the same
         * object id
         *
         * @see getObjectId
         */
        bool operator==(const GameObject& rhs);

        /**
         * @brief Check if this game object is not the same object as another object
         * @param rhs Object to compare against this object
         * @return True if the two objects are not the same object
         *
         * Two game objects are not the same object if they don't have the
         * same object id
         *
         * @see getObjectId
         */
        bool operator!=(const GameObject& rhs);

        /**
         * @brief Set the type of the game object
         * @param type Type to set
         *
         * The new type will overwrite the previous type
         */
        void setType(Type type);

        /**
         * @brief Get the type of the game object
         * @return The type of the game object
         */
        Type getType() const;

        /**
         * @brief Set current state
         * @param state The current state
         *
         * The state is number that should be associated with something
         * (maybe an enum) in your game.
         *
         * Be default, the state is -1, which is supposed to indicate
         * that there is no state. The state property is optional and
         * may be used if needs be. It is not used internally
         */
        void setState(int state);

        /**
         * @brief Get the current state of the game object
         * @return The current state of the game object
         */
        int getState() const;

        /**
         * @brief Set the name of the game object (optional)
         * @param name The name to set
         *
         * By default, the name is an empty string
         */
        void setName(const std::string& name);

        /**
         * @brief Get the name of the game object
         * @return The name of the game object
         */
        const std::string& getName() const;

        /**
         * @brief Set the direction of the game object
         * @param dir New direction of the game object
         */
        void setDirection(Direction dir);

        /**
         * @brief Get the direction of the game object
         * @return The direction of the game object
         */
        Direction getDirection() const;

        /**
         * @brief Set whether the game object is active or inactive
         * @param isActive True to set active or false to set inactive
         *
         * An active game object in this context refers to a game object that is
         * in a good state, not killed or completely destroyed, whilst
         * an inactive game object refers to one that is killed or destroyed
         */
        void setActive(bool isActive);

        /**
         * @brief Check if the game object is active or not
         * @return True if the game object is active, otherwise false
         */
        bool isActive() const;

        /**
         * @brief Set whether the game object is vulnerable or inVulnerable
         * @param isVulnerable True to set vulnerable or false to set
         *                     invulnerable
         *
         * A vulnerable game object can be deactivated whilst an invulnerable
         * game object cannot be deactivated. That is, setActive(false) on a
         * game object that is active and invulnerable will always fail.
         *
         * The game object is vulnerable by default
         */
        void setVulnerable(bool isVulnerable);

        /**
         * @brief Check if the game object is vulnerable or not
         * @return True if the game object is vulnerable or false if inVulnerable
         *
         * @see setVulnerable
         */
        bool isVulnerable() const;

        /**
         * @brief Set whether the game object is collidable or not
         * @param isCollidable True to make collidable, otherwise false
         *
         * The game object is not collidable by default
         */
        void setCollidable(bool isCollidable);

        /**
         * @brief Check if the game object is collidable or not
         * @return True if the game object is collidable, otherwise false
         */
        bool isCollidable() const;

        /**
         * @brief Get concrete class type
         * @return Name of the concrete class the game object is instantiated from
         *
         * If a concrete class is derived further, this function must always
         * be overridden to reflect the new concrete class
         */
        virtual std::string getClassType() = 0;

        /**
         * @brief Get the game object's unique identifier
         * @return The game object's unique identifier
         *
         * Each game object instance has it's own unique identification number
         */
        std::size_t getObjectId() const;

        /**
         * @brief Attach a physics Body to the game object
         * @param body Physics body to be attached
         *
         * Attaching a rigid Body to a game object enables physics for that
         * game object. This means that you should refrain from calling
         * functions that MODIFY the game objects transform (position,
         * rotation and origin). Note that the physics simulation does not
         * account for scaling, that should be handles by you
         *
         * @note Attaching a rigid body will alter the origin of the game objects
         * sprite to match the centre of mass of the body. In addition, the
         * transform of the game object will be reset to that of the rigid body
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
        BodyPtr& getRigidBody();
        const BodyPtr& getRigidBody() const;

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
         * class version first in your implementation
         */
        virtual void update(Time deltaTime);

        /**
         * @brief Add an event listener to a game object event
         * @param event Event to add event listener to
         * @param callback Function to execute when the event is published
         * @return The event listeners identification number
         */
        template<typename ...Args>
        int onEvent(const std::string& event, Callback<Args...> callback) {
            return eventEmitter_.on(event, std::move(callback));
        }

        /**
         * @brief Remove an event listener form a game object event
         * @param event Event to remove event listener from
         * @param id Identification number of the event listener
         * @return True if the event listener was removed or false if no such
         *         event listener exists for the specified event
         *
         * The identification number is the number issued when an event
         * listener is added to a game object event
         *
         * @see onEvent
         */
        bool unsubscribe(const std::string& event, int id);

        /**
         * @brief Destructor
         */
        virtual ~GameObject();

    private:
        /**
         * @brief Subscribe interested parties to a transform property change
         */
        void initTransformEvents();

    protected:
        /**
         * @brief Dispatch a game object event
         * @param event Event to publish
         * @param args Arguments passed to event listeners
         */
        template<typename...Args>
        void dispatchEvent(const std::string& event, Args&&...args) {
            eventEmitter_.emit(event, std::forward<Args>(args)...);
        }

    private:
        std::reference_wrapper<Scene> scene_; //!< The scene this game object belongs to
        static std::size_t prevEntityId_;     //!< Object id counter
        Type type_;                           //!< The type of the game object
        std::size_t id_;                      //!< Unique identifier
        int state_;                           //!< The current state of the game object
        std::string name_;                    //!< The name of the game object
        bool isVulnerable_;                   //!< Vulnerability state
        bool isActive_;                       //!< Active state
        bool isCollidable_;                   //!< Collidable state
        Direction direction_;                 //!< Current direction
        EventEmitter eventEmitter_;           //!< Event publisher
        Transform transform_;                 //!< The objects transform
        Sprite sprite_;                       //!< The objects visual representation
        BodyPtr body_;                        //!< The rigid body attached to this game object
        int postStepId_;                      //!< Scene post step handler id
    };
}

#endif // IME_IENTITY_H
