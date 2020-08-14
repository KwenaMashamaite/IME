/**
 * @brief Interface for all game entities (players, projectiles, enemies etc...)
 */

#ifndef IENTITY_H
#define IENTITY_H

#include "IME/common/Definitions.h"
#include <string>

namespace IME {
    using Definitions::Position;
    using Definitions::Dimensions;

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
         * @brief Set the texture of the entity
         * @param texture Texture to be set
         *
         * The texture is the name of the file that graphically
         * represents the entity
         */
        virtual void setTexture(const std::string& texture) = 0;

        /**
         * @brief Get the texture of the entity
         * @return Texture of the entity
         */
        virtual const std::string& getTexture() const = 0;

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
        virtual std::string getEntityType() = 0;

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

        /**
         * @brief Destructor
         */
        virtual ~IEntity() = default;
    };
} // namespace IME

#endif
