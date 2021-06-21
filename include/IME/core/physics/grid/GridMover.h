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
        using Ptr = std::unique_ptr<GridMover>; //!< Unique grid mover pointer
        using CollisionCallback = Callback<GameObject*, GameObject*>; //!< Called when collision takes place

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
         * @warning If @a gameObject is left as @a nullptr, then setTarget()
         * must be called before the grid mover is used. If the @a gameObject
         * is given, it must be in the grid prior to constructor call, otherwise
         * the grid mover construction will fail
         *
         * @see setTarget
         */
        explicit GridMover(TileMap& tilemap, GameObject* gameObject = nullptr);

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
         * @warning if the @a target is not a @a nullptr, then it must exist
         * in the grid and have a rigid Body of time Body::Type::Kinematic
         * attached to it prior to function call
         */
        void setTarget(GameObject* target);

        /**
         * @brief Get access to the controlled entity
         * @return The controlled entity, or a nullptr if there is no entity to
         *         control
         */
        GameObject* getTarget() const;

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
         * @see setMovementFreeze and isTargetMoving
         */
        bool isMovementFrozen() const;

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
        const TileMap& getGrid() const;

        /**
         * @brief Check if target is moving or not
         * @return True if target is moving otherwise false
         *
         * @warning This function must not be called when there is no
         * target, otherwise undefined behavior
         *
         * @see setTarget, getTarget and setMovementFreeze
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
         * @brief Add an event listener to a move begin event
         * @param callback The function to be executed when the game object
         *                 starts moving
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
        int onAdjacentMoveBegin(const Callback<Index>& callback);

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
         * The callback is passed the index of the tile the target moved to
         *
         * @see onAdjacentMoveBegin
         */
        int onAdjacentMoveEnd(const Callback<Index>& callback);

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
         *
         * @see unsubscribe
         */
        int onGridBorderCollision(const Callback<>& callback);

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
         * The callback is passed the index of the tile the target collided with
         *
         * @see unsubscribe
         */
        int onTileCollision(const Callback<Index>& callback);

        /**
         * @brief Add an event listener to a game object collision
         * @param callback The function to be executed when the collision take place
         * @return The event listeners unique identifier
         *
         * The callback is invoked when the target collides with another game
         * object. On invocation, the callback it is passed the target and
         * the game object it collided with respectively. In addition, note
         * that the callback is invoked only if the target is active and its
         * collision group and collision id are configured such that it can
         * collide with other game objects (see ime::GameObject::setActive,
         * ime::GameObject::setCollisionGroup and ime::GameObject::setCollisionId)
         *
         * @note A grid mover registers a collision between two game objects
         * only when they occupy the same tile. That is, a collision will not
         * be raised when the two game objects start overlapping. For contact
         * based collision detection use ime::RigidBody physics
         *
         * @see unsubscribe
         */
        int onGameObjectCollision(const CollisionCallback& callback);

        /**
         * @brief Remove an event listener from the grid movers event list
         * @param handlerId The unique identification number of the listener
         * @return True if the event listener was removed or false if no such
         *         listener exist in the grid movers event list
         */
        bool unsubscribe(int handlerId);

        /**
         * @brief Reset the target tile to be the same as the entity tile
         *
         * @note This function must be called every time the target is
         * manually moved in the Tilemap so that the grid mover can register
         * the new position of the target. If not called, the GridMover will
         * lose control of the target and the targets movement behavior is
         * undefined in such a case. In addition, note that the target tile
         * can only be reset when the target is not moving. Here's an example:
         *
         * @code
         * // Let the grid mover be responsible for moving the player object
         * tilemap.addChild(player, ime::Index{4, 5});
         * gridMover.setTarget(player);
         *
         * ...
         *
         * // Manually move the player to some desired position
         * tilemap.removeChild(player);
         * tilemap.addChild(player, ime::Index{11, 20});
         *
         * // Let the grid mover know that the player is no longer where it
         * // was registered to be (The grid mover will update itself accordingly)
         * gridMover.setMovementFreeze(true);
         * gridMover.resetTargetTile();
         * gridMover.setMovementFreeze(false);
         * @endcode
         *
         * @see setMovementFreeze
         */
        void resetTargetTile();

        /**
         * @brief Add an event listener to target tile reset event
         * @param callback Function to execute when the target tile is reset
         * @return The event listeners identification number
         *
         * @see resetTargetTile and unsubscribe
         */
        int onTargetTileReset(const Callback<Index>& callback);

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
         * @see onAdjacentMoveEnd and requestDirectionChange
         */
        virtual void update(Time deltaTime);

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
         * @return Pointer to the obstacle object or a nullptr if none exists
         */
        GameObject* getObstacleInTargetTile();

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
        GridMover(Type type, TileMap &tileMap, GameObject* target);

    private:
        Type type_;                    //!< The type of the grid mover
        TileMap& tileMap_;             //!< Grid to move entity in
        GameObject* target_;           //!< Target to be moved in the grid
        Vector2f maxSpeed_;            //!< The maximum speed of the game object
        Direction targetDirection_;    //!< The direction in which the game object wishes to go in
        Direction currentDirection_;   //!< The current direction of the game object
        const Tile* targetTile_;       //!< The grid tile the target wishes to reach
        const Tile* prevTile_;         //!< Tile target was in before moving to adjacent tile
        EventEmitter eventEmitter_;    //!< Collision event publisher
        bool isMoveFrozen_;            //!< A flag indicating whether or not the targets movement is frozen
        MoveRestriction moveRestrict_; //!< Specified permitted directions of travel for the game object
        int targetDestructionId_;      //!< Target destruction handler id
    };
}

#endif // IME_GRIDMOVER_H
