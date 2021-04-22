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

#ifndef IME_GRIDMOVER_H
#define IME_GRIDMOVER_H

#include "IME/Config.h"
#include "IME/core/tilemap/TileMap.h"
#include "IME/core/game_object/GameObject.h"
#include "IME/core/event/EventEmitter.h"
#include "IME/core/time/Time.h"
#include "IME/common/Object.h"

namespace ime {

    using Direction = Vector2i;                //!< Direction of a game object
    static const Direction Left = {-1, 0};     //!< West direction
    static const Direction UpLeft = {-1, -1};  //!< North-West direction
    static const Direction Up = {0, -1};       //!< North direction
    static const Direction UpRight = {1, -1};  //!< North-East direction
    static const Direction Right = {1, 0};     //!< East direction
    static const Direction DownRight = {1, 1}; //!< South-East direction
    static const Direction Down = {0, 1};      //!< South direction
    static const Direction DownLeft = {-1, 1}; //!< South-West direction
    static const Direction Unknown = {0, 0};   //!< Unknown direction

    /**
     * @brief Class for performing grid based movement on an entity in a grid
     *
     * This class monitors the movement of an entity in a grid and ensures that
     * it always moves from one cell to the next and never between grid cells.
     * The entities direction cannot be changed until it has completed it's
     * current movement.
     *
     * Note that the grid mover only supports orthogonal movement (left, right,
     * up and down)
     */
    class IME_API GridMover : public Object {
    public:
        using Ptr = std::shared_ptr<GridMover>; //!< Shared grid mover pointer

        /**
         * @brief Types of grid movers
         */
        enum class Type {
            Manual,             //!< Manually triggered grid mover
            Random,             //!< Moves a game object randomly in the grid
            Target,             //!< Moves a game object to a specific tile within the grid
            KeyboardControlled, //!< Moves a game object within the grid using the keyboard as a trigger
            Custom              //!< For classes that extend the grid mover outside of IME
        };

        /**
         * @brief Restricts the movement of the target along axes
         */
        enum class MoveRestriction {
            None,       //!< Target can move in all in all 8 directions (W, NW, N, NE, E, SE, S, SW)
            All,        //!< Target cannot move in any direction
            Vertical,   //!< Target can only move vertically (N or S)
            Horizontal, //!< Target can only move horizontally (W or E)
            Diagonal,   //!< Target can only move diagonally (NW, NE, SE, SW)
            NonDiagonal //!< Target can only move non-diagonally (W, N, E, S)
        };

        /**
         * @brief Create a manually controlled grid mover
         * @param tilemap The grid the game object is in
         * @param gameObject The game object to be controlled by the grid mover
         *
         * @warning You may omit the game object if you want to set it later,
         * However if the target is provided @a gameObject != nullptr, then
         * it must be placed in the grid prior to instantiation of this class
         *
         * @see setTarget
         */
        explicit GridMover(TileMap& tilemap, GameObject::Ptr gameObject = nullptr);

        /**
         * @brief Get the name of this class
         * @return The name of this class
         *
         * Note that this function is only implemented by child classes
         * of Object which also serve as a base class for other classes
         *
         * @see Object::getClassType and Object::getClassName
         */
        std::string getClassType() const override;

        /**
         * @brief Change the direction of the game object
         * @param newDir The new direction of the game object
         * @return True if the direction was changed or false if the game
         *         object is in motion or the grid mover is not in control
         *         of any game object
         *
         * Note that the direction of the game object cannot be changed while
         * it is moving to another tile. This function only works with predefined
         * directions. In addition to returning @b true for successful direction
         * change, the function will emit a "direction" property change event.
         * Usually property change events are only emitted by setters (functions
         * that begin with a "set" prefix)
         *
         * @code
         * gridMover.onPropertyChange("direction", [](const ime::Property& p) {
         *      auto dir = p.getValue<ime::Direction>();
         *     // Do something - Maybe rotate the game object in the new direction
         * });
         * @endcode
         *
         * @see update
         */
        bool requestDirectionChange(const Direction& newDir);

        /**
         * @brief Get the current direction of the game object
         * @return The current direction of the game object
         */
        Direction getDirection() const;

        /**
         * @brief Change the controlled entity
         * @param target New target
         *
         * Provide nullptr as argument to remove current target
         *
         * @warning if the target is not a nullptr, then it must exist in
         * the grid prior to function call
         */
        void setTarget(GameObject::Ptr target);

        /**
         * @brief Get access to the controlled entity
         * @return The controlled entity, or a nullptr if there is no entity to
         *         control
         */
        GameObject::Ptr getTarget() const;

        /**
         * @brief Set the maximum linear speed of the game object
         * @param speed The new maximum speed
         *
         * If the game object is currently moving, the speed will be set
         * after it reaches its current target tile
         *
         * @warning When using a grid mover the velocity of the game object
         * must not be set directly but rather through this function. Setting
         * the velocity directly will transfer movement management of the game
         * object from the grid mover to the physics engine
         */
        void setMaxLinearSpeed(Vector2f speed);

        /**
         * @brief Get the maximum speed of the game object
         * @return The maximum speed of the game object
         */
        Vector2f getMaxLinearSpeed() const;

        /**
         * @brief Restrict the movement of the game object to certain directions
         * @param moveRestriction Permitted direction of travel
         *
         * By default the movement restrictions is MovementRestriction::None
         */
        void setMovementRestriction(MoveRestriction moveRestriction);

        /**
         * @brief Get the current movement restriction of the game object
         * @return The current movement restriction
         */
        MoveRestriction getMovementRestriction() const;

        /**
         * @brief Get the index of the adjacent tile the target is trying to reach
         * @return The index of the adjacent tile the target is trying to reach
         *
         * If the target it not moving towards any tiles, this function
         * will return the index of the tile currently occupied by the
         * target
         */
        virtual Index getTargetTileIndex() const;

        /**
         * @brief Get the type of the grid mover
         * @return The type of the grid mover
         */
        Type getType() const;

        /**
         * @brief Get access to the grid in which the target is moved in
         * @return The grid in which the target is being moved in
         */
        TileMap& getGrid();

        /**
         * @brief Check if target is moving or not
         * @return True if target is moving otherwise false
         *
         * @warning This function will return false if the target is not moving
         * or there is no target set. Therefore, the existence of the
         * target should be checked first for accurate results
         *
         * @see getTarget
         */
        bool isTargetMoving() const;

        /**
         * @brief Update entity movement in the grid
         * @param deltaTime Time passed since movement was last updated
         *
         * The target can only move one tile at a time and cannot be instructed
         * to move to another tile while it is currently moving to one of its
         * adjacent tiles. After it reaching it's target tile it stops moving
         * until instructed to move again. Therefore if the target is to be
         * moved multiple tiles, the request to change direction must be made
         * immediately after the target reaches its destination
         *
         * @see onAdjacentTileReached and requestDirectionChange
         *
         * @warning The target will never move if this function is never called
         */
        virtual void update(Time deltaTime);

        /**
         * @brief Force the target to reach it's destination
         *
         * The destination in this context is always the adjacent tile the
         * target is headed towards. This function has no effect if the
         * target is not moving towards any tile
         */
        void teleportTargetToDestination();

        /**
         * @brief Add an event listener to a target change event
         * @param callback Function to execute when the target changes
         * @return The event listeners identification number
         */
        int onTargetChanged(Callback<GameObject::Ptr> callback);

        /**
         * @brief Add an event listener to a move begin event
         * @param callback The function to be executed when the game object
         *                 starts moving
         * @return The event listeners unique identification number
         *
         * This event is emitted when the game object starts moving from its
         * current tile to one of its adjacent tile. The callback is passed
         * the tile that the game object is currently moving to
         *
         * @note When controlled by a grid mover, the game object will always
         * move one tile at a time, regardless of how fast it's moving
         *
         * @see onAdjacentTileReached
         */
        int onMoveBegin(Callback<Tile> callback);

        /**
         * @brief Add an event listener to an adjacent tile reached event
         * @param callback Function to execute when the target reaches its
         *        target tile
         * @return The event listeners identification number
         *
         * This event is emitted when the target moves from its current tile
         * to any of its adjacent tiles.
         *
         * @note When controlled by a grid mover, the target will always move
         * one tile at a time, regardless of how fast the target is moving
         *
         * The callback is passed the tile the target moved to
         *
         * @see onMoveBegin
         */
        int onAdjacentTileReached(Callback<Tile> callback);

        /**
         * @brief Add an event listener to a tilemap border collision event
         * @param callback Function to execute when the collision takes place
         * @return The event listeners identification number
         *
         * This event is emitted when the target tries to go beyond the bounds
         * of the grid. By default the event is handled internally before it's
         * emitted to the outside. The internal handler prevents the target
         * from leaving the grid. That is, the target will occupy the same tile
         * it occupied before the collision. This behaviour is not removable,
         * however, it may be overridden since the internal handler is called
         * first before alerting external handlers
         */
        int onGridBorderCollision(Callback<> callback);

        /**
         * @brief Add an event listener to a tile collision event
         * @param callback Function to execute when the collision takes place
         * @return The event listeners identification number
         *
         * This event is emitted when the target collides with a solid tile
         * in the grid (Solid tiles are always collidable). By default, the
         * event is handled internally before its emitted to the outside. The
         * internal handler prevents the target from occupying the solid tile
         * by moving it back to its previous tile after the collision
         *
         * The callback is passed the tile the target collided with
         */
        int onSolidTileCollision(Callback<Tile> callback);

        /**
         * @brief Add an event listener to an obstacle collision
         * @param callback Function to execute when the collision takes place
         * @return The event listeners identification number
         *
         * This event is emitted when the target collides with an obstacle
         * in the grid. By default the event is handled internally before
         * its emitted to the outside. The internal handler prevents the
         * target from occupying the same tile as the obstacle by moving it
         * back to its previous tile after the collision
         *
         * The callback is passed the target as the first argument and the
         * obstacle it collided with as the second argument
         */
        int onObstacleCollision(Callback<GameObject::Ptr, GameObject::Ptr> callback);

        /**
         * @brief Add an event listener to a collectable collision event
         * @param callback Function to execute when the collision takes place
         * @return The event listeners identification number
         *
         * This event is emitted when the target collides with a collectable
         * in the grid. The callback is passed the target as the first argument
         * and the collectable it collided with as the second argument
         */
        int onCollectableCollision(Callback<GameObject::Ptr, GameObject::Ptr> callback);

        /**
         * @brief Add an event listener to an enemy collision event
         * @param callback Function to execute when the collision takes place
         * @return The event listeners identification number
         *
         * This event is emitted when the target collides with an enemy in the
         * grid. The callback is passed the target as the first argument and
         * the enemy it collided with as the second argument
         */
        int onEnemyCollision(Callback<GameObject::Ptr, GameObject::Ptr> callback);

        /**
         * @brief Add an event listener to a player collision event
         * @param callback Function to execute when the collision takes place
         * @return The event listeners identification number
         *
         * This event is emitted when the target collides with a player in the
         * grid. The callback is passed the target as the first argument and
         * the player it collided with as the second argument
         */
        int onPlayerCollision(Callback<GameObject::Ptr, GameObject::Ptr> callback);

        /**
         * @brief Remove a collision handler
         * @param id Identification number of the handler
         * @return True if the handler was removed or false if no such handler
         *         exits
         *
         * The identification number is the number returned when an event
         * listener was added to a collision event
         */
        bool removeCollisionHandler(int id);

        /**
         * @brief Remove an event listener from an event
         * @param event Name of the event to remove event listener from
         * @param id Identification number of the event listener
         * @return True if the event listener was removed or false if the
         *         given event does not have an event listener with the
         *         given id
         *
         * The identification number is the number returned when an event
         * listener was added to an events
         */
        bool removeEventListener(const std::string& event, int id);

        /**
         * @internal
         * @brief Reset the target tile to be the same as the entity tile
         *
         * The tile can only be rest if the entity is not moving
         */
        void resetTargetTile();

        /**
         * @internal
         * @brief Add an event listener to target tile reset event
         * @param callback Function to execute when the target tile is reset
         */
        void onTargetTileReset(Callback<Tile> callback);

        /**
         * @brief Destructor
         */
        ~GridMover() override;

    private:
        /**
         * @brief Set the targets target tile
         *
         * This tile is the tile the target wishes to occupy
         */
        void setTargetTile();

        /**
         * @brief Resolve a solid tile collision
         * * @return True if the collision was resolved or false if such a
         *         collision is not taking place
         *
         * This function will prevent the target from occupying a solid tile.
         * (Solid tiles are considered collidable)
         */
        bool handleSolidTileCollision();

        /**
         * @brief Resolve a grid border collision
         * @return True if the collision was resolved or false if such a
         *         collision is not taking place
         *
         * This function will prevent the target from leaving the tilemap
         */
        bool handleGridBorderCollision();

        /**
         * @brief Resolve an obstacle collision
         * @return True if the collision was resolved or false if such a
         *         collision is not taking place
         *
         * This function will prevent the target from occupying a tile which
         * has obstacles
         */
        bool handleObstacleCollision();

        /**
         * @brief Check whether or not target has reached its adjacent tile
         * @param deltaTime Time passed since last check
         * @return True if target has reached its adjacent tile, otherwise false
         */
        bool isTargetTileReached(Time deltaTime);

        /**
         * @brief Stop target and notify event listeners
         */
        void onDestinationReached();

        /**
         * @brief Check if the target tile has any obstacle objects or not
         * @return A pair, of which the first element is a bool that is true if
         *         the target tile is occupied by an obstacle, otherwise false
         *         and the second is a pointer to the first encountered obstacle
         *         in the target tile or a nullptr if the first element is false
         */
        std::pair<bool, GameObject::Ptr> targetTileHasObstacle();

        /**
         * @brief Perfectly align target with the target destination
         */
        void snapTargetToTargetTile();

        /**
         * @brief Check whether or not the target can move in a given direction
         * @param targetDir The direction to be checked
         * @return True if the target can make a move in the given direction,
         *         otherwise false
         */
        bool isMoveValid(Direction targetDir) const;

    protected:
        /**
         * @brief Create a grid mover
         * @param type The type of the grid mover
         * @param tileMap Grid to move a target entity in
         * @param target GameObject to be moved in the grid
         *
         * Note that this constructor is intended to be used by derived
         * classes such that the user cannot change the type of the grid
         * mover during instantiation. The public constructor sets the
         * type to Type::Manual and it cannot be changed once set. Since
         * derived classes must set their own type, they use this constructor
         * to initialize the base class
         *
         * @warning if the target is not a nullptr, then it must be placed
         * in the grid prior to instantiation of this class
         */
        GridMover(Type type, TileMap &tileMap, GameObject::Ptr target);

    private:
        Type type_;                    //!< The type of the grid mover
        TileMap& tileMap_;             //!< Grid to move entity in
        GameObject::Ptr target_;       //!< Target to be moved in the grid
        Vector2f maxSpeed_;            //!< The maximum speed of the game object
        Direction targetDirection_;    //!< The direction in which the game object wishes to go in
        Direction currentDirection_;   //!< The current direction of the game object
        Tile targetTile_;              //!< The grid tile the target wishes to reach
        Tile prevTile_;                //!< Tile target was in before moving to adjacent tile
        EventEmitter eventEmitter_;    //!< Collision event publisher
        bool isMoving_;                //!< A flag indicating whether or not the game object is moving
        MoveRestriction moveRestrict_; //!< Specified permitted directions of travel for the game object
    };
}

#endif // IME_GRIDMOVER_H
