/**
 * @brief Abstract base class for game entities
 */

#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "globals/Globals.h"

using Globals::Position;
using Globals::Dimensions;

enum class Direction{
    Left,
    Right,
    Up,
    Down
};

class Entity {
public:
    /**
     * @brief Create a new entity object
     * @param position Position of the entity
     * @param boundRect Dimensions of the entity's bounding box
     * @param texture Filename of the texture that graphically represents the entity
     * @param life Amount of life of the entity
     *
     * The entity is not rotated, has a speed of zero and is facing upwards by default
     */
    Entity(const Position &position, const Dimensions &boundRect, const std::string &texture, float life);


    /**
     * @brief Set the position of the entity
     * @param xPos New x coordinate of the entity
     * @param yPos New y coordinate of the entity
     */
    void setPosition(float xPos, float yPos);

    /**
     * @brief Set the direction of the entity
     * @param dir new direction of the entity
     */
    void setDirection(Direction dir);

    /**
     * @brief Set the speed of the entity
     * @param speed New speed of the entity
     * 
     * This function overrides the previous velocity
     * of the entity
     */
    void setSpeed(float speed);
    
    /**
     * @brief Increase/decrease the speed of the entity
     * @param speed Speed to increase or decrease by
     */
    void adjustSpeed(float speed);

    /**
     * @brief Rotate entity
     * @param angle Angle of rotation
     */
    void rotateBy(float angle);

    /**
     * @brief Set the texture of the entity
     * @param texture Texture to be set
     *
     * The texture is the name of the file that graphically represents the entity
     * If the file is located in "executables/resources/textures/", then the file
     * path is not required, only the name of the file
     */
    void setTexture(const std::string& texture);

    /**
     * @brief Get the texture of the entity
     * @return Texture of the entity
     */
    const std::string& getTexture() const;

    /**
     * @brief Get the dimensions of the entity
     * @return Dimensions of the entity
     *
     * The dimensions refer to the bounding box that surround the entity
     * The bounding box has the same dimensions as the texture of the entity
     */
    Dimensions getBoundingRect() const;

    /**
     * @param Damage entity
     * @param amountOfDamage Amount of damage to inflict on enemy
     *
     * This function decreases the entity's life by the specified amount of damage.
     * If the life gets to zero the entity will die
     */
    void takeDamage(float amountOfDamage);

    /**
     * @brief move entity in current direction at current speed
     * @param deltaTime Amount of time passed since entity last moved
     */
    virtual void move(float deltaTime) = 0;

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
     * @brief Get the angle of rotation of the entity
     * @return Angle of rotation
     */
    float getAngleOfRotation() const;
    
    /**
     * @brief Get the remaining life of the entity
     * @return The remaining life of the entity
     */
    float getRemainingLife() const;

private:
    //Position of the entity
    Position position_;
    //Bounding box dimensions
    Dimensions boundingRect_;
    //Filename of entities texture
    std::string texture_;
    //Current direction of the entity
    Direction direction_;
    //Current velocity of the entity
    float speed_;
    //Life of the entity
    float life_;
    //Entities orientation
    float angleOfRotation_;
};

#endif
