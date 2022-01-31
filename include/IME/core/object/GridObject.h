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

#ifndef IME_GRIDOBJECT_H
#define IME_GRIDOBJECT_H

#include "IME/Config.h"
#include "IME/core/object/GridObject.h"
#include "IME/core/object/ExcludeList.h"
#include "IME/core/tilemap/TileMap.h"
#include <memory>

namespace ime {
    class GridMover;

    /**
     * @brief An object that can be placed in a TileMap
     */
    class IME_API GridObject : public GameObject {
    public:
        using Ptr = std::unique_ptr<GridObject>;     //!< Unique game object pointer

        /**
         * @brief Constructor
         * @param scene The scene this game object belongs to
         */
        explicit GridObject(Scene& scene);

        /**
         * @brief Copy constructor
         */
        GridObject(const GridObject&);

        /**
         * @brief Copy assignment operator
         */
        GridObject& operator=(const GridObject&);

        /**
         * @brief Move constructor
         */
        GridObject(GridObject&&) noexcept = default;

        /**
         * @brief Move assignment operator
         */
        GridObject& operator=(GridObject&&) noexcept = default;

        /**
         * @brief Create a new GridObject instance
         * @return The created instance
         */
        static GridObject::Ptr create(Scene& scene);

        /**
         * @brief Create a copy of the game object
         * @return A new game object
         */
        GridObject::Ptr copy() const;

        /**
         * @brief Swap the object with another game object
         * @param other The object to swap with this game object
         */
        void swap(GridObject& other);

        /**
         * @brief Get the name of the class the game object is instantiated from
         * @return The name of the concrete class the game object is instantiated
         *         from
         *
         * Note that this function must be overridden further if this class
         * is extended, otherwise it will return the name of this class
         * instead of your class name
         *
         * @see getClassType
         */
        std::string getClassName() const override;

        /**
         * @brief Set the direction of the object
         * @param dir The direction to be set
         *
         * By default the direction is Vector2i{0, 0}
         *
         * @see getDirection
         */
        void setDirection(const Vector2i& dir);

        /**
         * @brief Get the objects current direction
         * @return The objects direction
         */
        const Vector2i& getDirection() const;

        /**
         * @brief Set whether or not the game object is an obstacle
         * @param isObstacle True if it is an obstacle, otherwise false
         *
         * When the object is an obstacle and its active state is @a true
         * (see ime::GameObject::setActive), then other game objects cannot
         * overlap with it. A collision event will be raised when another
         * game object attempts to occupy the same cell as the obstacle.
         * However, the two objects will never overlap
         *
         * By default, the game object is not an obstacle
         *
         * @see isObstacle
         */
        void setObstacle(bool isObstacle);

        /**
         * @brief Check if the object is an obstacle or not
         * @return True if the object is an obstacle, otherwise false
         *
         * @see setObstacle
         */
        bool isObstacle() const;

        /**
         * @brief Set the game objects collision id
         * @param id The id to be set
         *
         * A collision id allows game objects to selectively collide with
         * each other within colliding groups (see setCollisionGroup()).
         * Game objects with the same collision id will collide with each
         * other, whilst game objects with different collision id's do not
         * collide with each other.
         *
         * Note that "collision group" filtering takes higher precedence
         * than "collision id" filtering. This means that regardless of
         * how collision id's are configured, a collision will never take
         * place if the collision group of one game object is added to the
         * other game objects collision group exclude list (see getCollisionExcludeList())
         *
         * By default, the collision id is 0. This means that this game
         * object will collide with any other game object that is not in
         * its collision group exclude list
         *
         * @see setCollisionGroup and getCollisionExcludeList
         */
        void setCollisionId(int id);

        /**
         * @brief Get the collision id
         * @return The objects collision id
         *
         * @see setCollisionId
         */
        int getCollisionId() const;

        /**
         * @brief Set the objects collision group
         * @param name The collision group to be set
         *
         * A collision group allows certain game objects to always collide
         * or never collide with each other. When a collision group is added
         * to the object's collision exclusion list (see getCollisionExcludeList()),
         * the game object will never collide with game objects in that group
         * (they will pass through each other without generating a collision
         * event), whereas when not added, the game object will always collide
         * with game objects whose collision group does not appear in its
         * exclusion list
         *
         * Note that the @em active state (see ime::GameObject::setActive())
         * takes higher precedence than "collision group" filtering. This means
         * that, regardless of how the collision groups are configured, a collision
         * will never take place if the game object is not active
         *
         * For example, the following code makes objects in the "Enemies"
         * collision group to never collide with each other:
         *
         * @code
         * // Assume 'enemies' is a collection of 'ime::GridObject' objects
         * for (auto& enemy : enemies) {
         *      enemy.setCollisionGroup("Enemies");
         *      enemy.getCollisionExcludeList().add("Enemies");
         * }
         * @endcode
         *
         * By default, the collision group is am empty string. This means that
         * the object does not belong to any collision group. Therefore, it will
         * collide with any other game object whose collision id is the same as
         * theirs
         *
         * @see getCollisionGroup, setCollisionId and getCollisionExcludeList
         */
        void setCollisionGroup(const std::string& name);

        /**
         * @brief Get the objects collision group
         * @return The game objects collision group
         *
         * @see setCollisionGroup
         */
        const std::string& getCollisionGroup() const;

        /**
         * @brief Set the speed of the game object
         * @param speed The new speed
         *
         * By default, the speed is ime::Vector2f{0, 0}
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
         * @brief Check if target is moving or not
         * @return True if target is moving otherwise false
         *
         * @see getTarget
         */
        bool isMoving() const;

        /**
         * @brief Get the index of the grid tile currently occupied by the object
         * @return The index of the grid tile currently occupied by the object
         *
         * Note that when the object is moved by a GridMover, it occupies a tile
         * ahead of time, see ime::GridMover::requestMove()
         *
         * This function returns ime::Index{-1, -1} if the object is not in a Grid
         *
         * @see getPrevTileIndex
         */
        Index getGridIndex() const;

        /**
         * @brief Get access to the grid in which the target is moved in
         * @return The grid in which the target is being moved in
         */
        TileMap* getGrid();
        const TileMap* getGrid() const;

        /**
         * @brief Get the game objects collision exclude list
         * @return The game objects collision exclude list
         *
         * This list allows you to specify which game objects this game
         * object can collide with
         *
         * By default, the game object collides with all other objects
         *
         * @see getObstacleCollisionFilter
         */
        ExcludeList& getCollisionExcludeList();
        const ExcludeList& getCollisionExcludeList() const;

        /**
         * @brief Get the game objects obstacle collision filter
         * @return The game objects obstacle collision filter
         *
         * By default, any object that @e cannot collide with an obstacle game
         * object will pass through it without generating a collision event
         * whereas if they @e can collide, the two objects will never overlap.
         * Sometimes you may want an obstacle object to exhibit the default
         * behavior for some objects but allow others to pass through it and
         * still generate a collision event. This list helps you achieve that.
         * The collision groups of game objects added to this list will pass
         * over an obstacle game object but generate a collision event
         *
         * @note This function is useful only if the game object is an obstacle
         * (see setObstacle()).
         *
         * @see getCollisionExcludeList
         */
        ExcludeList& getObstacleCollisionFilter();
        const ExcludeList& getObstacleCollisionFilter() const;

        /**
         * @brief Get the objects grid mover
         * @return The objects grid mover or a nullptr if the object is not
         *         being controlled by a grid mover
         *
         * @see ime::GridMover
         */
        GridMover* getGridMover();
        const GridMover* getGridMover() const;

        /**
         * @brief Add an event listener to a grid enter event
         * @param callback The function to be executed when the game object
         *                 is added to a TileMap
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listeners unique identification number
         *
         * The callback is passed this game object on invocation
         *
         * @see onGridExit
         */
        int onGridEnter(const Callback<ime::GridObject*>& callback, bool oneTime = false);

        /**
         * @brief Add an event listener to a grid exit event
         * @param callback The function to be executed when the game object
         *                 is removed from a TileMap
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listeners unique identification number
         *
         * The callback is passed this game object on invocation
         *
         * @see onGridEnter
         */
        int onGridExit(const Callback<GridObject*>& callback, bool oneTime = false);

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
         * The callback is passed this game object on invocation
         *
         * @see onGridMoveEnd
         */
        int onGridMoveBegin(const Callback<GridObject*>& callback, bool oneTime = false);

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
         * The callback is passed this game object on invocation
         *
         * @see onGridMoveBegin
         */
        int onGridMoveEnd(const Callback<GridObject*>& callback, bool oneTime = false);

        /**
         * @brief Add an event listener to a grid object collision event
         * @param callback Function to be executed when this game object
         *                 collides with another game object in a TileMap
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listeners unique identification number
         *
         * This event is triggered when this grid object collides with another
         * grid object or vice versa. A collision is registered between two
         * grid objects when the occupy the same TileMap tile
         *
         * The callback is passed this game object and the game object it is
         * in collision with respectively.
         *
         * @see removeCollisionListener
         */
        int onGridObjectCollision(const Callback<GridObject*, GridObject*>& callback, bool onetime = false);

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
         * The callback is passed this object on invocation
         *
         * @see unsubscribe
         */
        int onGridBorderCollision(const Callback<GridObject*>& callback, bool oneTime = false);

        /**
         * @brief Add an event listener to a grid tile collision event
         * @param callback Function to execute when the collision takes place
         * @param oneTime True to execute the callback one-time or false to
         *                execute it every time the event is triggered
         * @return The event listeners identification number
         *
         * This event is emitted when the object collides with a grid tile
         * By default, the event is handled internally before its emitted. The
         * internal handler prevents the object from occupying the tile by moving
         * it back to its previous tile. This behaviour is not removable, however,
         * it may be overridden since the internal handler is called first before
         * alerting external handlers
         *
         * The callback is passed this object and the index of the tile it tried to
         * occupy on invocation
         *
         * @see unsubscribe
         */
        int onGridTileCollision(const Callback<GridObject*, Index>& callback, bool oneTime = false);

        /**
         * @internal
         * @brief Set the game object's grid mover
         * @param gridMover The grid mover to be set
         *
         * @warning This function is intended for internal use only and should
         * never be called outside of IME
         */
        void setGridMover(GridMover* gridMover);

        /**
         * @internal
         * @brief Set the grid
         * @param grid The grid the object is in
         *
         * @warning This function is intended for internal use only and should
         * never be called outside of IME
         */
        void setGrid(TileMap* grid);

        /**
         * @internal
         * @brief Emit a collision event
         * @param property Event arguments
         *
         * @warning This function is intended for internal use only and should
         * never be called outside of IME
         */
        void emitGridEvent(const Property& property);

        /**
         * @brief Destructor
         */
        ~GridObject() override;

    private:
        TileMap* grid_;                     //!< The grid the object is in
        bool isObstacle_;                   //!< A flag indicating whether or not the object is an obstacle
        Vector2i direction_;                //!< The current direction of the object
        Vector2f speed_;                    //!< The speed of the game object
        ExcludeList excludeList_;           //!< Stores the collision groups of game objects this game object should not collide with
        ExcludeList obstacleColFilter_;     //!< Stores the collision groups of game objects that can collide with an obstacle without being blocked
        std::string collisionGroup_;        //!< The objects collision group (collision filtering)
        int collisionId_;                   //!< The objects collision id (collision filtering)
        GridMover* gridMover_;              //!< The objects grid mover
    };
}

#endif //IME_GRIDOBJECT_H
