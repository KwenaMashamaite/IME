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

#ifndef IENTITY_H
#define IENTITY_H

#include "IME/common/Dimensions.h"
#include "IME/common/Position.h"
#include "IME/common/Direction.h"
#include "IME/core/event/EventEmitter.h"
#include <stack>
#include <string>
#include <memory>

namespace IME {
    class Entity {
    public:
        /**
         * @brief Construct entity
         * @param boundingRect Bounding rectangle of the entity
         *
         * The entity is alive, has the position (0, 0) and no direction
         * by default
         */
        explicit Entity(const Dimensions &boundingRect);

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
        Dimensions getSize() const;

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
        Position getPosition() const;

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
         * @brief Get the type of the entity
         * @return The type of the entity
         */
        virtual std::string getType() = 0;

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
        //The entities bounding rectangle
        Dimensions boundingRect_;
        //Vulnerability state state
        bool isVulnerable_;
        //The entities alive state
        bool isAlive_;
        //The entities collidable state
        bool isCollidable_;
        //The direction of the entity
        Direction direction_;
        //The position of the entity
        Position position_;
        //The event publisher of the entity
        EventEmitter eventEmitter_;
    };
}

#endif
