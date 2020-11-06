/**
 * @brief Class that performs grid based movement on an entity using the keyboard
 *        as a movement trigger
 */

#ifndef KEYBOARDCONTROLLED_H
#define KEYBOARDCONTROLLED_H

#include "IME/core/input/Keyboard.h"
#include "IME/core/entity/Entity.h"
#include "GridMover.h"

namespace IME {
    enum class MovementTrigger {
        None,      // A key event does not trigger any movement
        OnKeyDown, // Continues to fire while key is held down
        OnKeyUp    // Only triggers when a key is released
    };

    class KeyboardControlledGridMover {
    public:
        using EntityPtr = std::shared_ptr<Entity>;

        /**
         * @brief Constructor
         * @param gridMover
         * @param trigger Set to onKeyDown to move entity whilst a key is held
         *        down or set to onKeyUp to move the entity only when a key is
         *
         * The movement trigger is MovementTrigger::None by default, which means
         * key events will be ignored and the target will not move @see setKeys()
         * and @see setTrigger()
         */
        explicit KeyboardControlledGridMover(TileMap &tileMap, std::shared_ptr<Entity> target = nullptr);

        /**
         * @brief Change the controlled entity
         * @param target New target
         *
         * Set to nullptr to remove the target from the grid mover
         */
        void setTarget(EntityPtr target);

        /**
         * @brief Get access to the controlled entity
         * @return The controlled entity, or a nullptr if there is no entity to
         *         control
         */
        EntityPtr getTarget() const;

        /**
         * @brief Set the key event that triggers the targets movement
         * @param trigger The targets movement trigger
         *
         * The actual keys that trigger the movements must be set, in order to
         * determine the direction of motion @see setKeys()
         */
        void setMovementTrigger(MovementTrigger trigger);

        /**
         * @brief Get the current movement trigger
         * @return Current movement trigger
         */
        MovementTrigger getMovementTrigger() const;

        /**
         * @brief Set the keys to move the target in all four directions
         * @param leftKey Key to move target left on trigger
         * @param rightKey Key to move target right on trigger
         * @param upKey Key to move target up on trigger
         * @param downKey Key to move target down on trigger
         *
         * In addition to setting the keys, the movement trigger must be set
         * @see setMovementTrigger(). There are no set keys by default
         */
        void setKeys(Input::Keyboard::Key leftKey, Input::Keyboard::Key rightKey,
             Input::Keyboard::Key upKey, Input::Keyboard::Key downKey);

        /**
         * @brief Check if target is moving or not
         * @return True if target is moving otherwise false
         *
         * @warning This function will return false if the target is not moving
         * or when there is no target set. Therefore, the existence of the
         * target should be checked first for accurate results. @see getTarget()
         */
        bool isTargetMoving() const;

        /**
         * @brief Handle an event
         * @param event Event to handle
         */
        void handleEvent(sf::Event event);

        /**
         * @brief Update the target entities movement in the grid
         * @param deltaTime Time passed since entity movement was last updated
         */
        void update(float deltaTime);

        /**
         * @brief Teleport target destination
         */
        void teleportTargetToDestination();

        /**
         * @brief Add an event listener to a grid/tilemap border collision
         * @param callback Function to execute when the target collides with
         *         the borders of the grid/tilemap
         * @return The event listeners identification number
         *
         * @note The target will be prevented from leaving the grid. That is,
         * it will occupy the same tile it occupied before the collision
         */
        int onGridBorderCollision(Callback<> callback);

        /**
         * @brief Add an event listener to a destination reached event
         * @param callback Function to execute when the target reaches its destination
         *
         * The destination is always the adjacent tile in the specified direction.
         * The callback function will be invoked only if the entity starts moving
         * and reaches its destination tile @see update()
         */
        int onDestinationReached(Callback<float, float> callback);

        /**
         * @brief Add an event listener to an obstacle collision
         * @param callback Function to execute when the collision takes place
         * @return The event listeners identification number
         *
         * This event is emitted when the target collides with an obstacle tile
         * in the grid. The target will be prevented from occupying the same tile
         * as an obstacle. @warning If a tile is marked as an obstacle and has
         * no obstacle object, the callback will be passed a nullptr for the
         * obstacle object
         */
        int onObstacleCollision(Callback<EntityPtr, EntityPtr> callback);

        /**
         * @brief Add an event listener to a collectable collision
         * @param callback Function to execute when the collision takes place
         * @return The event listeners identification number
         *
         * This event is emitted when the target collides with a collectable
         * object the grid. This event will be emitted when the target entity
         * and the collectable object occupy the same tile, not when they start
         * colliding with each other
         */
        int onCollectableCollision(Callback<EntityPtr, EntityPtr> callback);

        /**
         * @brief Add an event listener to an enemy collision
         * @param callback Function to execute when the collision takes place
         * @return The event listeners identification number
         *
         * This event is emitted when the target collides with an enemy object
         * in the grid. This event will be emitted when the target entity and
         * the enemy object occupy the same tile, not when they start colliding
         * with each other
         */
        int onEnemyCollision(Callback<EntityPtr, EntityPtr> callback);

        /**
         * @brief Add an event listener to a player collision
         * @param callback Function to execute when the collision takes place
         * @return The event listeners identification number
         *
         * This event is emitted when the target collides with a player object
         * in the grid. This event will be emitted when the target entity and
         * the player object occupy the same tile, not when they start colliding
         * with each other
         */
        int onPlayerCollision(Callback<EntityPtr, EntityPtr> callback);

    private:
        /**
         * @brief Move target in the grid
         * @param key pressed key (Helps Determine which direction to go)
         */
        void moveTarget(Input::Keyboard::Key key);

        /**
         * @brief Attach input event listeners to the set trigger
         */
        void attachInputEventListeners();

    private:
        //Moves entity in the grid
        GridMover gridMover_;
        //Key event that triggers target movement
        MovementTrigger trigger_;
        //Handler id
        int onTriggerHandlerId_;
        //Input detector
        Input::Keyboard keyboard_;
        //Flags if direction was changed during target movement
        std::pair<bool, Direction> newDir_;

        struct Keys {
            Input::Keyboard::Key left = Input::Keyboard::Key::Unknown;
            Input::Keyboard::Key right = Input::Keyboard::Key::Unknown;
            Input::Keyboard::Key up = Input::Keyboard::Key::Unknown;
            Input::Keyboard::Key down = Input::Keyboard::Key::Unknown;
        };

        //Keys which trigger the targets movement
        Keys movementKeys_;
    };
}

#endif
