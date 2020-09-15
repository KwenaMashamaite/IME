/**
 * @brief Interface for all game entities (players, projectiles, enemies etc...)
 */

#ifndef IENTITY_H
#define IENTITY_H

#include "IME/common/Dimensions.h"
#include "IME/common/Position.h"
#include "IME/core/IEntityState.h"
#include "IME/core/event/EventEmitter.h"
#include <stack>
#include <string>
#include <memory>

namespace IME {
    class IEntity {
    public:
        /**
         * @brief Directions in which an entity can face
         */
        enum class Direction {
            Left,
            Right,
            Up,
            Down
        };

        /**
         * @brief Set the position of the entity
         * @param xPos New x coordinate of the entity
         * @param yPos New y coordinate of the entity
         */
        virtual void setPosition(float xPos, float yPos) = 0;

        /**
         * @brief Set the direction of the entity
         * @param dir new direction of the entity
         */
        virtual void setDirection(Direction dir) = 0;

        /**
         * @brief Get the dimensions of the entity's bounding box
         * @return Dimensions of the entity's bounding box
         */
        virtual Dimensions getBoundingRect() const = 0;

        /**
         * @param Damage entity
         * @param amountOfDamage Amount of damage to inflict on entity
         *
         * This function decreases the entity's life by the specified amount
         * of damage. If the life gets to zero the entity will die
         */
        virtual void takeDamage(unsigned int amountOfDamage) = 0;

        /**
         * @brief Check if entity is alive or not
         * @return True if entity is alive, false if it's not alive
         */
        virtual bool isAlive() const = 0;

        /**
         * @brief Get the direction of the entity
         * @return Direction of the entity
         */
        virtual Direction getDirection() const = 0;

        /**
         * @brief Get the position of the entity
         * @return Position of the entity
         */
        virtual Position getPosition() const = 0;

        /**
         * @brief Get the type of the entity
         * @return The type of the entity
         */
        virtual std::string getType() = 0;

        /**
         * @brief Get the remaining life of the entity
         * @return The remaining life of the entity
         */
        virtual unsigned int getRemainingLives() const = 0;

        /**
         * @brief Check if entity is colliding with another entity
         * @param other Entity to check collision with
         * @return True if the entity is colliding with the specified entity or
         *         false if the two entities are not colliding with each other
         */
        bool isCollideWith(IEntity& other) const;

        void reset();

        void update();

        void pushState(std::shared_ptr<IEntityState> state);

        void popState();

        /**
         * @brief
         * @param entity
         */
        virtual void onCollide(Callback<IEntity&> callback) {

        };

        /**
         * @brief Destructor
         */
        virtual ~IEntity() = default;

    private:
        std::stack<std::shared_ptr<IEntityState>> states_;
    };
} // namespace IME

#endif
