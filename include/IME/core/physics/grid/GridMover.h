////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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
#include "IME/core/grid/Grid2D.h"
#include "IME/core/object/GridObject.h"
#include "IME/core/event/EventEmitter.h"
#include "IME/core/time/Time.h"
#include "IME/core/object/Object.h"

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
     */
    class IME_API GridMover : public Object {
    public:
        using Ptr = std::unique_ptr<GridMover>; //!< Unique grid mover pointer

        /**
         * @brief Types of grid movers
         */
        enum class Type {
            Manual,             //!< Manually triggered grid mover
            Random,             //!< Moves a game object randomly in the grid
            Target,             //!< Moves a game object to a specific tile within the grid
            Cyclic,             //!< Moves a game object by following a closed path
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
         * @param grid The grid the game object is in
         * @param gameObject The game object to be controlled by the grid mover
         *
         * @warning If @a gameObject is left as @a nullptr, then setTarget()
         * must be called before the grid mover is used. If the @a gameObject
         * is given, it must be in the grid prior to constructor call and it
         * must not have a RigidBody attached to it, otherwise undefined
         * behavior
         *
         * @see setTarget
         */
        explicit GridMover(Grid2D& grid, GridObject* gameObject = nullptr);

        /**
         * @brief Copy constructor
         */
        GridMover(const GridMover&) = delete;

        /**
         * @brief Copy assignment operator
         */
        GridMover& operator=(const GridMover) = delete;

        /**
         * @brief Create the grid mover
         * @param grid The grid the game object is in
         * @param gameObject The game object to be controlled by the grid mover
         * @return The created grid mover
         *
         * @warning If @a gameObject is left as @a nullptr, then setTarget()
         * must be called before the grid mover is used. If the @a gameObject
         * is given, it must be in the grid prior to constructor call and it
         * must not have a RigidBody attached to it, otherwise undefined
         * behavior
         *
         * @see setTarget
         */
        static GridMover::Ptr create(Grid2D& grid, GridObject* gameObject = nullptr);

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
         * @brief Get the name of this class
         * @return The name of this class
         */
        std::string getClassName() const override;

        /**
         * @brief Sync this grid mover with another grid mover
         * @param other The grid mover to sync with this grid mover with
         *
         * In situations where you want to change a targets grid mover, you'll
         * have to synchronize the new grid mover with the current grid mover
         * to avoid misalignment with the grid. When misaligned, the target is
         * no longer confined to the grid and moves indefinitely in its current
         * direction. Note that misalignment does not occur when the target is
         * not moving, i.e when isMoving() returns false.
         *
         * @code
         * // Lets assume a player target was being moved by a ime::RandomGridMover
         * // and now we want it to be moved by a ime::CyclicGridMover
         * cyclicGridMover.sync(randomGridMover);
         * cyclicGridMover.setTarget(randomGridMover.getTarget());
         * randomGridMover.setTarget(nullptr);
         * cyclicGridMover.startMovement();
         * @endcode
         */
        void syncWith(const GridMover& other);

        /**
         * @brief Request a move in a given direction
         * @param dir The direction to move in
         * @return True if the move was granted or false if the target is
         *         currently moving to another tile
         *
         * The target can only move one tile at a time, as a result it
         * cannot be requested to move to a tile while it is currently moving
         * towards another tile (see isTargetMoving()). In addition, If a move
         * in the specified direction is possible, the adjacent tile in the
         * specified direction will be flagged as occupied by the target before
         * it moves to it
         */
        bool requestMove(const Direction& dir);

        /**
         * @brief Check if the target is blocked from moving in a direction
         * @param direction The direction to be checked
         * @return A pair, of which the first element is a bool that is @a true
         *         if the target is blocked or @a false if the target is not blocked
         *         and the second element is a pointer to an obstacle game object
         *         that is a @a nullptr when the first element is @a false or
         *         when the first element is @a true but the target is not blocked
         *         by a game object
         *
         * This function will return true if the target is blocked by a
         * collidable tile or an obstacle (see ime::GridObject::setObstacle),
         * or if a move in the given direction will place it outside the bounds
         * of the grid
         */
        std::pair<bool, GridObject*> isBlockedInDirection(const Direction& direction) const;

        /**
         * @brief Get the current direction of the game object
         * @return The current direction of the game object
         */
        Direction getDirection() const;

        /**
         * @brief Get the previous direction of the target
         * @return The previous direction of the target
         */
        Direction getPrevDirection() const;

        /**
         * @brief Change the controlled entity
         * @param target New target
         *
         * Provide nullptr as argument to remove current target
         *
         * @warning if the @a target is not a @a nullptr, then it must exist
         * in the Grid2D and must not have a RigidBody attached to it,
         * otherwise undefined behavior
         */
        void setTarget(GridObject* target);

        /**
         * @brief Get access to the controlled entity
         * @return The controlled entity, or a nullptr if there is no entity to
         *         control
         */
        GridObject* getTarget() const;

        /**
         * @brief Set the speed of the game object
         * @param speed The new speed
         *
         * If the game object is currently moving, the speed will be set
         * after it reaches its current target tile
         *
         * Note that for a ime::MoveRestriction::Diagonal or ime::MoveRestriction::None,
         * the speed must be the same for both the x and y axis, otherwise
         * undefined behaviour
         *
         * By default, the speed is ime::Vector2f{60, 60}
         *
         * @see getSpeed
         */
        void setSpeed(const Vector2f& speed);

        /**
         * @brief Get the speed of the target
         * @return The speed of the target
         *
         * @see setSpeed
         */
        const Vector2f& getSpeed() const;

        /**
         * @brief Set a speed multiplier
         * @param multiplier The new speed multiplier
         *
         * A speed multiplier increases or decreases the speed of the target
         * without affecting its default speed. For example,  A multiplier of
         * 2.0f makes the target move twice as fast, a multiplier of 0.5f makes
         * the target move at half its normal speed and a multiplier of 0.0f
         * stops the target from moving. Note that a negative multiplier will
         * be ignored
         *
         * By default, the multiplier is 1.0f (normal)
         *
         * @see getSpeedMultiplier
         */
        void setSpeedMultiplier(float multiplier);

        /**
         * @brief Get the speed multiplier
         * @return The speed multiplier
         *
         * @see setSpeedMultiplier
         */
        float getSpeedMultiplier() const;

        /**
         * @brief Restrict the movement of the game object to certain directions
         * @param moveRestriction Permitted direction of travel
         *
         * By default the movement restrictions is MovementRestriction::None
         *
         * @see setMovementFreeze
         */
        void setMovementRestriction(MoveRestriction moveRestriction);

        /**
         * @brief Get the current movement restriction of the game object
         * @return The current movement restriction
         */
        MoveRestriction getMovementRestriction() const;

        /**
         * @brief Freeze or unfreeze the targets movement
         * @param freeze True to freeze movement or false to unfreeze
         *
         * This function achieves the same thing as setMovementRestriction().
         * The difference is when the function is called while the target is
         * moving. setMovementRestriction(true) will prevent the target from
         * moving further after the targets gets to its targeted tile whilst
         * setMovementFreeze(true) will immediately prevent the target from
         * moving further. This means that the target can temporarily be in
         * between grid tiles
         *
         * By default, the targets movement is not frozen
         *
         * @see setMovementRestriction
         */
        void setMovementFreeze(bool freeze);

        /**
         * @brief Check if the targets movement is frozen or not
         * @return True if movement is frozen otherwise false
         *
         * @see setMovementFreeze
         */
        bool isMovementFrozen() const;

        /**
         * @brief Get the index of the tile currently occupied by the target
         * @return The position of the tile currently occupied by the target
         *         in tiles
         *
         * Recall that when moved, the target occupies a tile ahead of time
         * (see requestMove())
         *
         * @see getPrevTileIndex
         */
        Index getCurrentTileIndex() const;

        /**
         * @brief Get the index of the tile previously occupied by the target
         * @return The tile the target was on before moving to another tile
         *
         * If the target never moved, then this function will return the tile
         * currently occupied by the target
         *
         * @see getCurrentTileIndex
         */
        Index getPrevTileIndex() const;

        /**
         * @brief Get the type of the grid mover
         * @return The type of the grid mover
         */
        Type getType() const;

        /**
         * @brief Get access to the grid in which the target is moved in
         * @return The grid in which the target is being moved in
         */
        Grid2D& getGrid();
        const Grid2D& getGrid() const;

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
         * @brief Force the target to reach it's destination
         *
         * The destination in this context is always the adjacent tile the
         * target is headed towards. This function has no effect if the
         * target is not moving towards any tile
         */
        void teleportTargetToDestination();

        /**
         * @brief Add an event listener to a target direction change
         * @param callback The function to be executed when target direction changes
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listeners unique identifier
         *
         * The direction change event is triggered by a move request
         *
         * @see requestMove
         */
        int onDirectionChange(const Callback<Direction>& callback, bool oneTime = false);

        /**
         * @brief Reset the target tile to be the same as the entity tile
         *
         * @note This function must be called every time the target is
         * manually moved in the grid so that the grid mover can register
         * the new position of the target. If not called, the GridMover will
         * lose control of the target and the targets movement behavior is
         * undefined in such a case. In addition, note that the target tile
         * can only be reset when the target is not moving. Here's an example:
         *
         * @code
         * // Let the grid mover be responsible for moving the player object
         * grid.addChild(player, ime::Index{4, 5});
         * gridMover.setTarget(player);
         *
         * ...
         *
         * // Manually move the player to some desired position
         * if (!gridMover.isTargetMoving) {
         *     gridMover.getGrid().removeChild(player);
         *     gridMover.getGrid().addChild(player, ime::Index{11, 20});
         *
         *      // Let the grid mover know that the player is no longer where it
         *      // was registered to be (The grid mover will update itself accordingly)
         *      gridMover.resetTargetTile();
         * }
         * @endcode
         */
        void resetTargetTile();

        /**
         * @brief Add an event listener to target tile reset event
         * @param callback Function to execute when the target tile is reset
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listeners identification number
         *
         * @see resetTargetTile and unsubscribe
         */
        int onTargetTileReset(const Callback<Index>& callback, bool oneTime = false);

        /**
         * @internal
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
         * @warning The target will never move if this function is never called
         *
         * @warning This function is intended for internal use only and
         * should never be called outside of IME
         *
         * @see onAdjacentMoveEnd
         */
        virtual void update(Time deltaTime);

        /**
         * @brief Add an event listener to a move begin event
         * @param callback The function to be executed when the game object
         *                 starts moving
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listeners unique identification number
         *
         * This event is emitted when the game object starts moving from its
         * current tile to one of its adjacent tile. The callback is passed
         * the index of the tile that the game object is currently moving to
         *
         * @note When controlled by a grid mover, the game object will always
         * move one tile at a time, regardless of how fast it's moving
         *
         * @see onAdjacentMoveEnd
         */
        int onMoveBegin(const Callback<Index>& callback, bool oneTime = false);

        /**
         * @brief Add an event listener to an adjacent tile reached event
         * @param callback Function to execute when the target reaches its
         *        target tile
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listeners identification number
         *
         * This event is emitted when the target moves from its current tile
         * to any of its adjacent tiles.
         *
         * @note When controlled by a grid mover, the target will always move
         * one tile at a time, regardless of how fast the target is moving
         *
         * The callback is passed the index of the tile the target moved to
         *
         * @see onAdjacentMoveBegin
         */
        int onMoveEnd(const Callback<Index>& callback, bool oneTime = false);

         /**
          * @brief Add an event listener to a grid collision event event
          * @param callback The function to be executed when the target collides with
          *                 another game object
          * @param oneTime True to execute the callback one-time or false to
          *                execute it every time the event is triggered
          * @return The event listeners unique identification number
          */
         int onObjectCollision(const Callback<GridObject*, GridObject*>& callback, bool oneTime = false);

        /**
         * @brief Add an event listener to a grid border collision event
         * @param callback Function to execute when the collision takes place
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listeners identification number
         *
         * This event is emitted when the target tries to go beyond the bounds
         * of the grid. By default the event is handled internally before it's
         * emitted to the outside. The internal handler prevents the target
         * from leaving the grid. That is, the target will occupy the same tile
         * it occupied before the collision. This behaviour is not removable,
         * however, it may be overridden since the internal handler is called
         * first before alerting external handlers
         *
         * @see unsubscribe
         */
        int onBorderCollision(const Callback<>& callback, bool oneTime = false);

        /**
         * @brief Add an event listener to a tile collision event
         * @param callback Function to execute when the collision takes place
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listeners identification number
         *
         * This event is emitted when the target collides with a solid tile
         * in the grid (Solid tiles are always collidable). By default, the
         * event is handled internally before its emitted to the outside. The
         * internal handler prevents the target from occupying the solid tile
         * by moving it back to its previous tile after the collision
         *
         * The callback is passed the index of the tile the target collided with
         *
         * @see unsubscribe
         */
        int onTileCollision(const Callback<Index>& callback, bool oneTime = false);

        /**
         * @brief Destructor
         */
        ~GridMover() override;

    protected:
        /**
         * @brief Create a grid mover
         * @param type The type of the grid mover
         * @param grid Grid to move a target entity in
         * @param target GridObject to be moved in the grid
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
        GridMover(Type type, Grid2D &grid, GridObject* target);

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
         * This function will prevent the target from leaving the grid
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
         * @brief Get an obstacle in a tile
         * @param tile The tile to get an obstacle from
         * @return Pointer to the obstacle object or a nullptr if none exists
         */
        GridObject* getObstacleInTile(const Tile& tile) const;

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

        /**
         * @brief Check if a game object can collide with the target
         * @param other The game object to be checked
         * @return True if the two can collide, otherwise false
         */
        bool canCollide(GridObject* other) const;

    private:
        Type type_;                    //!< The type of the grid mover
        Grid2D& grid_;             //!< Grid to move entity in
        GridObject* target_;           //!< Target to be moved in the grid
        Vector2f maxSpeed_;            //!< The maximum speed of the game object
        float speedMultiplier_;        //!< A normal speed multiplier
        Direction targetDirection_;    //!< The direction in which the game object wishes to go in
        Direction currentDirection_;   //!< The current direction of the game object
        Direction prevDirection_;      //!< The previous direction of the game object
        const Tile* targetTile_;       //!< The grid tile the target wishes to reach
        const Tile* prevTile_;         //!< Tile target was in before moving to adjacent tile
        bool isMoving_;                //!< A flag indicating whether or not the game object is moving
        bool isMoveFrozen_;            //!< A flag indicating whether or not the targets movement is frozen
        MoveRestriction moveRestrict_; //!< Specified permitted directions of travel for the game object
        int targetDestructionId_;      //!< Target destruction handler id
        int targetPropertyChangeId_;   //!< Target property change listener id
        bool isInternalHandler_;       //!< A flag indicating whether or not an event handler is internal
    };
}

#endif // IME_GRIDMOVER_H
