////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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

/**
 * @brief Interface for all game entities (players, projectiles, enemies etc...)
 */

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
    class IME_API Entity {
    public:
        // The type of an entity
        enum class Type {
            Unknown = -1,
            Player = 0,
            Enemy,
            Collectable,
            Obstacle,
        };

        /**
         * @brief Construct entity
         * @param boundingRectSize Size of the entity's bounding rect
         *
         * The entity is alive, has the position (0, 0) and no direction
         * by default
         */
        explicit Entity(const Vector2u &boundingRectSize, Type type = Type::Unknown);

        /**
         * @brief Set the position of the entity
         * @param x New x coordinate of the entity
         * @param y New y coordinate of the entity
         */
        void setPosition(float x, float y);

        /**
         * @brief Set the direction of the entity
         * @param dir new direction of the entity
         */
        void setDirection(Direction dir);

        /**
         * @brief Get the dimensions of the entity's bounding box
         * @return Dimensions of the entity's bounding box
         */
        Vector2u getSize() const;

        /**
         * @brief Set the alive state of the entity
         * @param isAlive True to set alive or false to kill
         */
        void setAlive(bool isAlive);

        /**
         * @brief Set entity as vulnerable or inVulnerable
         * @param isVulnerable True to set vulnerable or false to set invulnerable
         *
         * A vulnerable entity can be killed whilst an invulnerable entity
         * cannot be killed. That is, @see setAlive(bool) on an entity that is
         * alive and invulnerable will always fail.
         *
         * The entity is vulnerable by default
         */
        void setVulnerable(bool isVulnerable);

        /**
         * @brief Enable or disable collision for this entity
         * @param isCollidable True to enable collision or false to disable collision
         *
         * Collisions are disabled by default
         */
        void setCollidable(bool isCollidable);

        /**
         * @brief Check if entity is alive or not
         * @return True if entity is alive, false if it's not alive
         */
         bool isAlive() const;

        /**
         * @brief Get the direction of the entity
         * @return Direction of the entity
         */
        Direction getDirection() const;

        /**
         * @brief Get the position of the entity
         * @return Position of the entity
         */
        Vector2f getPosition() const;

        /**
         * @brief Check if entity is vulnerable or not
         * @return True if entity is vulnerable or false if inVulnerable
         *
         * @see setVulnerable(bool)
         */
        bool isVulnerable() const;

        /**
         * @brief Check if entity is collidable or not
         * @return True if entity is collidable, otherwise false
         */
        bool isCollidable() const;

        /**
         * @brief Get concrete class the object belongs to
         * @return Name of the concrete class the objects belongs to
         */
        virtual std::string getClassType() = 0;

        /**
         * @brief Set the type of the entity
         * @param type Type to set
         */
        void setType(Type type);

        /**
         * @brief Get the type of the entity
         * @return The type of the entity
         */
        Type getType() const;

        /**
         * @brief Get the entities unique identifier
         * @return Entities unique identifier
         *
         * An entity object cannot have the same identifier as another
         * entity object
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
         */
        bool removeEventListener(const std::string& event, int id);

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
        //The type of this entity object
        Type type_;
        //Objects unique identifier
        std::size_t id_;
        //The entities bounding rectangle
        Vector2u boundingRect_;
        //Vulnerability state state
        bool isVulnerable_;
        //The entities alive state
        bool isAlive_;
        //The entities collidable state
        bool isCollidable_;
        //The direction of the entity
        Direction direction_;
        //The position of the entity
        Vector2f position_;
        //The event publisher of the entity
        EventEmitter eventEmitter_;
    };
}

#endif
