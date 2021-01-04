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

#ifndef IME_IENTITY_H
#define IME_IENTITY_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/common/Direction.h"
#include "IME/core/event/EventEmitter.h"
#include <stack>
#include <string>
#include <memory>

namespace IME {
    /**
     * @brief Abstract base class for all game entities (players, enemies etc...)
     */
    class IME_API Entity {
    public:
        /**
         * @brief The type of an entity
         */
        enum class Type {
            Unknown = -1, //!< Unknown object
            Player = 0,   //!< Player object
            Enemy,        //!< Enemy object
            Collectable,  //!< Collectable object
            Obstacle,     //!< Obstacle object
        };

        /**
         * @brief Construct entity
         *
         * The entity has a bounding box size of {0, 0} and Type::Unknown
         * by default
         */
        Entity();

        /**
         * @brief Copy constructor
         * @param other Object to be copied
         */
        Entity(const Entity& other);

        /**
         * @brief Assignment operator
         */
        Entity& operator=(const Entity&);

        /**
         * @brief Move constructor
         */
        Entity(Entity&&) = default;

        /**
         * @brief Move assignment operator
         */
        Entity& operator=(Entity&&) = default;

        /**
         * @brief Construct entity
         * @param boundingBoxSize Size of the entity's bounding box
         * @param type Type of the entity
         */
        explicit Entity(const Vector2u &boundingBoxSize, Type type = Type::Unknown);

        /**
         * @brief Set the type of the entity
         * @param type Type to set
         *
         * The new type will overwrite the previous type
         */
        void setType(Type type);

        /**
         * @brief Get the type of the entity
         * @return The type of the entity
         */
        Type getType() const;

        /**
         * @brief Set the position of the entity
         * @param x X coordinate of the entity
         * @param y Y coordinate of the entity
         */
        void setPosition(float x, float y);

        /**
         * @brief Set the position of the entity
         * @param position New position
         */
        void setPosition(Vector2f position);

        /**
         * @brief Get the position of the entity
         * @return The position of the entity
         */
        Vector2f getPosition() const;

        /**
         * @brief Set the direction of the entity
         * @param dir New direction of the entity
         */
        void setDirection(Direction dir);

        /**
         * @brief Get the direction of the entity
         * @return The direction of the entity
         */
        Direction getDirection() const;

        /**
         * @brief Set the size of the entities bounding box
         * @param size New bounding box size
         */
        void setSize(Vector2u size);

        /**
         * @brief Get the dimensions of the entity's bounding box
         * @return The dimensions of the entity's bounding box
         */
        Vector2u getSize() const;

        /**
         * @brief Set whether entity is active or inactive
         * @param isActive True to set active or false to set inactive
         *
         * An active entity in this context refers to an entity that is
         * in a good state, not killed or completely destroyed, whilst
         * an inactive entity refers to one that is killed or destroyed
         */
        void setActive(bool isActive);

        /**
         * @brief Check if entity is active or not
         * @return True if entity is active, otherwise false
         */
        bool isActive() const;

        /**
         * @brief Set whether entity is vulnerable or inVulnerable
         * @param isVulnerable True to set vulnerable or false to set
         *                     invulnerable
         *
         * A vulnerable entity can be deactivated whilst an invulnerable
         * entity cannot be deactivated. That is, setActive(false) on an
         * entity that is active and invulnerable will always fail.
         *
         * The entity is vulnerable by default
         */
        void setVulnerable(bool isVulnerable);

        /**
         * @brief Check if entity is vulnerable or not
         * @return True if entity is vulnerable or false if inVulnerable
         *
         * @see setVulnerable
         */
        bool isVulnerable() const;

        /**
         * @brief Set whether entity is collidable or not
         * @param isCollidable True to make collidable, otherwise false
         *
         * Entity is not collidable by default
         */
        void setCollidable(bool isCollidable);

        /**
         * @brief Check if entity is collidable or not
         * @return True if entity is collidable, otherwise false
         */
        bool isCollidable() const;

        /**
         * @brief Get concrete class type
         * @return Name of the concrete class the entity is instantiated from
         *
         * If a concrete class is derived further, this function must always
         * be overridden to reflect the new concrete class
         */
        virtual std::string getClassType() = 0;

        /**
         * @brief Get the entity's unique identifier
         * @return The entity's unique identifier
         *
         * Each entity instance has it's own unique identification number
         */
        std::size_t getObjectId() const;

        /**
         * @brief Add an event listener to an entity event
         * @param event Event to add event listener to
         * @param callback Function to execute when the event is published
         * @return The event listeners identification number
         */
        template<typename ...Args>
        int onEvent(const std::string& event, Callback<Args...> callback) {
            return eventEmitter_.on(event, std::move(callback));
        }

        /**
         * @brief Remove an event listener form an entity event
         * @param event Event to remove event listener from
         * @param id Identification number of the event listener
         * @return True if the event listener was removed or false if no such
         *         event listener exists for the specified event
         *
         * The identification number is the number issued when an event
         * listener is added to an entity event
         *
         * @see onEvent
         */
        bool unsubscribe(const std::string& event, int id);

        /**
         * @brief Check if two entity objects are the same object or not
         * @param rhs Object to compare against this object
         * @return True if the two entities are the same object
         *
         * Two entity objects are the same object if they have the same
         * object id
         *
         * @see getObjectId
         */
        bool operator==(const Entity& rhs);

        /**
         * @brief Check if this entity is not the same object as another object
         * @param rhs Object to compare against this object
         * @return True if the two objects are not the same object
         *
         * Two entity objects are not the same object if they don't have the
         * same object id
         *
         * @see getObjectId
         */
        bool operator!=(const Entity& rhs);

        /**
         * @brief Destructor
         */
        virtual ~Entity() = default;

    protected:
        /**
         * @brief Publish an entity event
         * @param event Event to publish
         * @param args Arguments passed to event listeners
         */
        template<typename...Args>
        void publishEvent(const std::string& event, Args&&...args) {
            eventEmitter_.emit(event, std::forward<Args>(args)...);
        }

    private:
        static std::size_t prevEntityId_; //!< Object id counter
        Type type_;                       //!< The type of the entity
        std::size_t id_;                  //!< Unique identifier
        Vector2u boundingRect_;           //!< Bounding box size
        bool isVulnerable_;               //!< Vulnerability state
        bool isActive_;                   //!< Active state
        bool isCollidable_;               //!< Collidable state
        Direction direction_;             //!< Current direction
        Vector2f position_;               //!< Current position
        EventEmitter eventEmitter_;       //!< Event publisher
    };
}

#endif // IME_IENTITY_H
