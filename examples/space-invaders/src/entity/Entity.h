/**
 * @brief Intermediate Abstract Base Class (ABC) for game entities
 *
 * This class implements the domain object interface (IEntity). All methods
 * that are the same for all game entities (such as getters and setters) are
 * implemented by this class. Those that are entity specific are passed down
 * to derived classes to implement. As a result, the class itself is an ABC.
 * All game entities inherit directly from this class instead of IEntity to
 * avoid code duplication within derived classes (DRY).
 *
 * @note All methods implemented by this class are not final. This means that they
 * can be overridden by derived classes.
 */

#ifndef ENTITY_H
#define ENTITY_H

#include "IME/core/IEntity.h"
#include <string>

namespace SI {
    class Entity : public IME::IEntity {
    public:
        /**
         * @brief Create a new entity object
         * @param position Position of the entity
         * @param direction Initial Direction of the entity
         * @param boundRect Dimensions of the entity's bounding box
         * @param texture Filename of the texture that graphically represents the entity
         * @param numOfLives Number of lives an entity must have
         */
        Entity(const IME::Position &position,
               Direction direction,
               const IME::Dimensions &boundRect,
               const std::string &texture,
               unsigned int numOfLives);

        /**
         * @brief Set the position of the entity
         * @param xPos New x coordinate of the entity
         * @param yPos New y coordinate of the entity
         */
        void setPosition(float xPos, float yPos) override;

        /**
         * @brief Set the direction of the entity
         * @param dir new direction of the entity
         */
        void setDirection(Direction dir) override;

        /**
         * @brief Set the texture of the entity
         * @param texture Texture to be set
         *
         * The texture is the name of the file that graphically
         * represents the entity
         */
        void setTexture(const std::string &texture) override;

        /**
         * @brief Get the texture of the entity
         * @return Texture of the entity
         */
        const std::string &getTexture() const override;

        /**
         * @brief Get the dimensions of the entity's bounding box
         * @return Dimensions of the entity's bounding box
         */
        IME::Dimensions getBoundingRect() const override;

        /**
         * @param Damage entity
         * @param amountOfDamage Amount of damage to inflict on enemy
         *
         * This function decreases the entity's life by the specified
         * amount of damage. If the life gets to zero the entity will die
         */
        void takeDamage(unsigned int amountOfDamage) override;

        /**
         * @brief Check if entity is alive or not
         * @return True if entity is alive, false if it's not alive
         */
        bool isAlive() const override;

        /**
         * @brief Get the direction of the entity
         * @return Direction of the entity
         */
        Direction getDirection() const override;

        /**
         * @brief Get the position of the entity
         * @return Position of the entity
         */
        IME::Position getPosition() const override;

        /**
         * @brief Get the remaining life of the entity
         * @return The remaining life of the entity
         */
        unsigned int getRemainingLives() const override;

        /**
         * @brief Destructor
         */
        virtual ~Entity() = 0;

    private:
        //Position of the entity
        IME::Position position_;
        //Bounding box dimensions
        IME::Dimensions boundingRect_;
        //Filename of entities texture
        std::string texture_;
        //Current direction of the entity
        Direction direction_;
        //Life of the entity
        unsigned int numOfLives_;
    };
}

#endif
