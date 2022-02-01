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

#ifndef IME_GRID2D_H
#define IME_GRID2D_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/common/Rect.h"
#include "IME/graphics/Tile.h"
#include "IME/core/grid/Index.h"
#include "IME/graphics/Sprite.h"
#include "IME/graphics/shapes/RectangleShape.h"
#include "IME/core/scene/GameObjectContainer.h"
#include "IME/core/grid/Grid2DRenderer.h"
#include <unordered_map>
#include <vector>
#include <unordered_set>

namespace ime {
    using Map = std::vector<std::vector<char>>; //!< Alias for 2D vector of chars

    class GridObject;

    /// @internal
    namespace priv {
        class RenderTarget;
    }

    /**
     * @brief A 2D visual grid
     */
    class IME_API Grid2D {
    public:
        /**
         * @internal
         * @brief Create an empty grid
         * @param tileWidth Width of each tile in the map
         * @param tileHeight height of each tile in the map
         * @param renderLayers The scenes render layer
         * @param scene The scene the grid belongs to
         *
         * The grid has the position (0, 0) by default
         *
         * This constructor is intended for internal use only
         */
        Grid2D(unsigned int tileWidth, unsigned int tileHeight, Scene& scene);

        /**
         * @internal
         * @brief Set the physics engine
         * @param engine The physics engine to be set
         *
         * @warning This function is intended for internal use only
         */
        void setPhysicsEngine(PhysicsEngine* engine);

        /**
         * @brief Get the scene the grid belongs to
         * @return The scene the grid belongs to
         */
        Scene& getScene();
        const Scene& getScene() const;

        /**
         * @brief Get the number of rows
         * @return The number of rows
         *
         * @see getColumnCount
         */
        unsigned int getRowCount() const;

        /**
         * @brief Get the number of columns
         * @return The number of columns
         *
         * @see getRowCount
         */
        unsigned int getColumnCount() const;

        /**
         * @brief Get the grids renderer
         * @return The grids renderer
         *
         * The renderer gives access to functions that determine how the
         * grid is displayed. It allows you to manipulate things such
         * as the tile colour, grid line colour etc...
         */
        Grid2DRenderer& getRenderer();
        const Grid2DRenderer& getRenderer() const;

        /**
         * @brief Set the position of the grid
         * @param x X coordinate of the grid
         * @param y Y coordinate of the grid
         *
         * The position is (0, 0) by default
         */
        void setPosition(int x, int y);

        /**
         * @brief Get the position of the grid in pixels
         * @return The position of the grid pixels
         */
        Vector2f getPosition() const;

        /**
        * @brief Check if the index is within bounds of the grid or not
        * @param index Index to check
        * @return True if the index is within bounds, otherwise false
        */
        bool isIndexValid(const Index &index) const;

        /**
         * @brief Construct a grid
         * @param id The id of each tile
         * @param size The size of the grid in tiles
         *
         * This function should be used when there are no special tiles
         * in the grid, that is, when all tiles have the same id. The
         * x component of @a size is the number of rows whilst the y
         * component is the number of columns
         *
         * @see loadFromFile and loadFromVector
         */
        void construct(const Vector2u& size, char id);

        /**
         * @brief Construct the grid from data located on a file on the disk
         * @param filename Name of the file that contains the map data
         * @param separator Character used to separate map data
         */
        void loadFromFile(const std::string& filename, const char& separator = '\0');

        /**
         * @brief Construct the grid form a vector that contains map data
         * @param map Vector to construct map from
         */
        void loadFromVector(Map map);

        /**
         * @brief Enable or disable collision for a tile at a certain location
         * @param index Location (in tiles) of the tile
         * @param isCollidable True to enable collision, otherwise false
         * @param attachCollider True to attach a Collider to the tile, otherwise
         *                       false
         *
         * Without a Collider, only game objects that are controlled by a
         * GridMover can collide with the tile. Attaching a collider makes
         * a GridObject with a RigidBody that has a Collider attached to it
         * able to collide with the tile. Note that a collider can only be
         * attached if the Scene this Grid2D belongs to has a PhysicsEngine
         */
        void setCollidableByIndex(const Index &index, bool isCollidable, bool attachCollider = false);

        /**
         * @brief Enable or disable collision for tiles at certain locations
         * @param locations Locations (in tiles) of the tiles
         * @param isCollidable True to enable collision, otherwise false
         * @param attachCollider True to attach a Collider to the tile, otherwise
         *                       false
         *
         * Without a Collider, only game objects that are controlled by a
         * GridMover can collide with the tile. Attaching a collider makes
         * a GridObject with a RigidBody that has a Collider attached to it
         * able to collide with the tile. Note that a collider can only be
         * attached if the Scene this Grid2D belongs to has a PhysicsEngine
         *
         * By default, tiles are not collidable
         *
         * All the tiles at specified indexes (if valid) will be set as solid
         * tiles if currently set as empty tiles
         */
        void setCollidableByIndex(const std::initializer_list<Index>& locations,
            bool isCollidable, bool attachCollider = false);

        /**
         * @brief Enable or disable collisions for tiles in a range
         * @param startPos The start position of the range
         * @param endPos The ending position of the range
         * @param isCollidable True to set collidable, otherwise false
         * @param attachCollider True to attach a Collider to the tile, otherwise
         *                       false
         *
         * Without a Collider, only game objects that are controlled by a
         * GridMover can collide with the tile. Attaching a collider makes
         * a GridObject with a RigidBody that has a Collider attached to it
         * able to collide with the tile. Note that a collider can only be
         * attached if the Scene this Grid2D belongs to has a PhysicsEngine
         *
         * By default, tiles are not collidable
         *
         * @warning Only horizontal ranges are supported. This means that
         * that the indexes in the range [startPos, endPos] must refer to
         * tiles that are valid and horizontally contiguous
         */
        void setCollidableByIndex(Index startPos, Index endPos, bool isCollidable, bool attachCollider = false);

        /**
         * @brief Enable or disable collisions for tiles with a certain id
         * @param id Id of the tiles to enable or disable collisions for
         * @param isCollidable True to enable collision, otherwise false
         * @param attachCollider True to attach a Collider to the tile, otherwise
         *                       false
         *
         * Without a Collider, only game objects that are controlled by a
         * GridMover can collide with the tile. Attaching a collider makes
         * a GridObject with a RigidBody that has a Collider attached to it
         * able to collide with the tile. Note that a collider can only be
         * attached if the Scene this Grid2D belongs to has a PhysicsEngine
         *
         * All the tiles with the specified id will be marked as solid tiles
         * if currently marked as empty tiles
         *
         * By default, tiles are not collidable
         */
        void setCollidableById(char id, bool isCollidable, bool attachCollider = false);

        /**
         * @brief Enable or disable collisions for all tiles except those with
         *        with a certain id
         * @param id Identification of the tiles to exclude
         * @param isCollidable True to enable collision, otherwise false
         * @param attachCollider True to attach a Collider to the tile, otherwise
         *                       false
         *
         * Without a Collider, only game objects that are controlled by a
         * GridMover can collide with the tile. Attaching a collider makes
         * a GridObject with a RigidBody that has a Collider attached to it
         * able to collide with the tile. Note that a collider can only be
         * attached if the Scene this Grid2D belongs to has a PhysicsEngine
         *
         * By default, tiles are not collidable
         */
        void setCollidableByExclusion(char id, bool isCollidable, bool attachCollider = false);

        /**
         * @brief Check if a tile is collidable or not
         * @param index Index of the tile to be checked
         * @return True if tile is collidable, or false if the tile is not
         *         collidable or the index is invalid
         */
        bool isCollidable(const Index& index) const;

        /**
         * @brief Get the size of the grid in pixels
         * @return Size of the grid in pixels
         */
        Vector2u getSize() const;

        /**
         * @brief Get the size of the grid in tiles
         * @return Size of the grid in tiles
         *
         * @warning The x component is the number of columns whilst the y
         * component is the number of rows
         */
        Vector2u getSizeInTiles() const;

        /**
         * @brief Get the size of each tile in the grid
         * @return The size of each tile in the grid
         *
         * All the tiles have the same size
         */
        Vector2u getTileSize() const;

        /**
         * @brief Get the spacing between tiles in all directions
         * @return The spacing between tiles
         *
         * The spacing is how far tiles are from one another. The default
         * space between tiles is 1
         */
        unsigned int getSpaceBetweenTiles() const;

        /**
         * @brief Get a tile at a certain index
         * @param index Index of the tile to get
         * @return The tile at the specified index or an invalid tile if the
         *         specified index is out of bounds of the grid
         *
         * A tile is invalid if it has a negative index
         */
        const Tile& getTile(const Index& index) const;

        /**
         * @brief Get the tile at at certain position
         * @param position Position of the tile to retrieve
         * @return The tile at the specified position or an invalid tile if
         *         the specified position does not lie within the grid
         *         bounds
         *
         * A tile is invalid if it has a negative index
         */
        const Tile& getTile(const Vector2f& position) const;

        /**
         * @brief Get the tile above a certain tile
         * @param tile Tile to get the tile above of
         * @return The tile above the specified tile or an invalid tile if
         *         there is no tile above the specified tile
         *
         * A tile is invalid if it has a negative index
         */
        const Tile& getTileAbove(const Tile& tile) const;

        /**
         * @brief Get the tile below a certain tile
         * @param tile Tile to get the tile below of
         * @return The tile below the specified tile or an invalid tile if
         *         there is no tile below the specified tile
         *
         * A tile is invalid if it has a negative index
         */
        const Tile& getTileBelow(const Tile& tile) const;

        /**
         * @brief Get the tile to the left of a certain tile
         * @param tile Tile to get the tile to the left of
         * @return The tile to the left of the specified tile or an invalid
         *         tile if there's no tile to the left of the specified tile
         *
         * A tile is invalid if it has a negative index
         */
        const Tile& getTileLeftOf(const Tile& tile) const;

        /**
         * @brief Get the tile to the right of a certain tile
         * @param tile Tile to get the tile to the right of
         * @return The tile to the right of the specified tile or an invalid
         *         tile if there's no tile to the left of the specified tile
         *
         * A tile is invalid if it has a negative index
         */
        const Tile& getTileRightOf(const Tile& tile) const;

        /**
         * @brief Execute a callback function on every tile with a certain id
         * @param id Id of the tile
         * @param callback Function to execute
         */
        void forEachTileWithId(char id, const Callback<const Tile&>& callback) const;

        /**
         * @brief Execute a callback on all tiles except tiles with a
         *        given id
         * @param id Id of the tiles to be ignored
         * @param callback Function to be executed
         */
        void forEachTileExcept(char id, const Callback<const Tile&>& callback) const;

        /**
         * @brief Execute a callback on all the tiles of the grid
         * @param callback Function to execute for each tile
         */
        void forEachTile(const Callback<const Tile&>& callback) const;

        /**
         * @brief Execute a callback function on each tile in a range
         * @param startPos The beginning of the range
         * @param endPos The end of the range
         * @param callback Function to execute for each tile
         *
         * @note Only horizontal ranges are supported
         */
        void forEachTileInRange(Index startPos, Index endPos,
            const Callback<const Tile&>& callback) const;

        /**
         * @internal
         * @brief Render grid on a render target
         * @param renderTarget Target to render grid on
         *
         * The grid's tiles do not belong to any render layer and are
         * always drawn behind everything. That is, they are drawn first
         * before the first render layer (layer at index 0) is drawn.
         *
         * @warning This function is intended for internal use only and
         * should never be called outside of IME
         */
        void draw(priv::RenderTarget &renderTarget) const;

        /**
         * @brief Add an entity to the grid
         * @param child GridObject to add to the grid
         * @param index Index of the tile to add the entity to
         * @return True if the entity has been added or false if the index is
         *         invalid or the entity already exists in the grid
         *
         * If the specified tile is already occupied, the child will be added
         * as a visitor of that tile. Note that @a child will always be placed
         * at the centre point of the tile.
         */
        bool addChild(GridObject* child, const Index& index);

        /**
         * @brief Get the child in the grid with a certain id
         * @param id Id of the child to get access to
         * @return The child with the specified id or a nullptr if the child
         *         with the specified id does not exist in the grid
         */
        GridObject* getChildWithId(std::size_t id) const;

        /**
         * @brief Check if the grid has a certain child or not
         * @param child Child to search for in the grid
         * @return True if the grid has the child, otherwise false
         */
        bool hasChild(const GridObject* child) const;

        /**
         * @brief Remove a child with a certain id from the grid
         * @param id Id of the child to be removed
         * @return True if the child was removed or false if the child with
         *         the specified id does not exist in the grid
         */
        bool removeChildWithId(std::size_t id);

        /**
         * @brief Remove a child from the grid
         * @param child Child to be removed
         * @return True if the child was removed or false if the child does
         *         not exist in the grid
         */
        bool removeChild(GridObject* child);

        /**
         * @brief Remove children from the grid using a condition
         * @param callback Function that determines if the condition is
         *        satisfied or not
         *
         * All children for which @a callback returns true are removed
         * from the grid
         */
        void removeChildIf(const std::function<bool(GridObject*)>& callback);

        /**
         * @brief Remove all children from the grid
         */
        void removeAllChildren();

        /**
         * @brief Move child to a different position in the grid
         * @param child Child to move
         * @param index New position of the child
         *
         * The child is ignored if it does not exist in the grid or the
         * specified index is invalid
         *
         * @see addChild
         */
        void changeTile(GridObject* child, const Index& index);

        /**
         * @brief Move child to a different tile
         * @param child Child to be moved
         * @param tile Tile to move child to
         *
         * The child is ignored if it does not exist in the grid or the
         * specified tile is invalid
         *
         * @see addChild
         */
        void changeTile(GridObject* child, const Tile& tile);

        /**
         * @brief Get the tile occupied by a child of the grid
         * @param child Child whose occupation tile is to be retrieved
         * @return The tile occupied by the specified child or an invalid tile
         *         if the child is not in the grid
         *
         * An invalid tile has a negative index
         */
        const Tile& getTileOccupiedByChild(const GridObject* child) const;

        /**
         * @brief Check if tile is occupied or not
         * @param tile Tile to be checked
         * @return True if the tile is occupied, otherwise false
         *
         * A tile is occupied if it has at least one child
         *
         * @see addChild
         */
        bool isTileOccupied(const Tile& tile) const;

        /**
         * @brief Check if a tile is occupied or not
         * @param index The position of the tile to be checked
         * @return True if the tile is occupied, otherwise false
         *
         * A tile is occupied if it has at least one child
         *
         * This function returns false if @a index is out of bounds
         *
         * @see addChild
         */
        bool isTileOccupied(const Index& index) const;

        /**
         * @brief Execute a callback for each child in the grid
         * @param callback Function to execute
         */
        void forEachChild(const Callback<GridObject*>& callback) const;

        /**
         * @brief Execute a callback for each child in a tile
         * @param tile Tile to execute callback on
         * @param callback Function to execute
         *
         * The callback will be passed the children of the tile, with the first
         * child being the occupant of the tile. The callback will be ignored
         * if the specified index is invalid or the tile is not occupied
         */
        void forEachChildInTile(const Tile& tile, const Callback<GridObject*>& callback) const;

        /**
         * @internal
         * @brief Update grid
         * @param deltaTime Time passed since last update
         *
         * @warning This function is intended for internal use only and should
         * never be called outside of IME
         */
        void update(Time deltaTime);

        /**
         * @brief Destructor
         */
        ~Grid2D();

    private:
        /**
         * @brief Create the visual gird
         */
        void createTiledMap();

        /**
         * @brief Calculate size related attributes
         *
         * This include map size, number of rows and columns, etc..
         */
        void computeDimensions();

        /**
         * @brief Get the tile above a tile at a given location
         * @param index Index of the tile to get the tile above
         * @return The tile at the specified index or an invalid tile if the
         *         specified index is out of bounds of the grid
         *
         * A tile is invalid if it has a negative index
         */
        const Tile& getTileAbove(const Index& index) const;

        /**
         * @brief Get the tile below a tile at a given location
         * @param index Location of the tile to get the tile below
         * @return The tile at the specified index or an invalid tile if the
         *         specified index is out of bounds of the grid
         *
         * A tile is invalid if it has a negative index
         */
        const Tile& getTileBelow(const Index& index) const;

        /**
         * @brief Get the tile to the left of a tile at a given location
         * @param index Location of the tile to get the tile to the left of
         * @return The tile at the specified index or an invalid tile if the
         *         specified index is out of bounds of the grid
         *
         * A tile is invalid if it has a negative index
         */
        const Tile& getTileLeftOf(const Index& index) const;

        /**
         * @brief Get the tile to the right of a tile at a given location
         * @param index Location of the tile to get the tile to the right of
         * @return The tile at the specified index or an invalid tile if the
         *         specified index is out of bounds of the grid
         *
         * A tile is invalid if it has a negative index
         */
        const Tile& getTileRightOf(const Index& index) const;

        /**
         * @brief Set whether or not a tile is collidable
         * @param tile The tile to enable or disable collisions for
         * @param collidable True to set collidable, otherwise false
         * @param attachCollider True to attach a Collider to the tile, otherwise
         *                       false
         *
         * Without a Collider, only game objects that are controlled by a
         * GridMover can collide with the tile. Attaching a collider makes
         * a GridObject with a RigidBody that has a Collider attached to it
         * able to collide with the tile. Note that a collider can only be
         * attached if the Scene this Grid2D belongs to has a PhysicsEngine
         *
         * By default, a tile is not collidable
         */
        void setCollidable(Tile& tile, bool collidable, bool attacheCollider = false);

        /**
         * @brief Execute a callback on all the tiles of the grid
         * @param callback Function to execute for each tile
         */
        void forEachTile_(const Callback<Tile&>& callback);

        /**
         * @brief Update the grid when a render property changes
         * @param property The render property that changed
         */
        void onRenderChange(const Property& property);

        /**
         * @brief Remove a destruction listener from a game object
         * @param child The game object to remove the destruction listener from
         */
        void unsubscribeDestructionListener(GridObject* child);

    private:
        Scene& scene_;                       //!< The scene the grid belongs to
        unsigned int tileSpacing_;           //!< Spacing between tiles in all directions
        Vector2u tileSize_;                  //!< The Size of each tile
        Vector2u mapSizeInPixels_;           //!< The Size of the grid in pixels
        Vector2f mapPos_;                    //!< The Position of the grid in pixels
        unsigned int numOfRows_;             //!< The width of the grid in tiles
        unsigned int numOfColms_;            //!< The height of the grid in tiles
        Map mapData_;                        //!< Map data used to identify different tiles
        Tile invalidTile_;                   //!< Tile returned when an invalid index is provided
        Grid2DRenderer renderer_;           //!< Determines the look of the grid
        RectangleShape backgroundTile_;      //!< Dictates the background colour of the grid

        std::unordered_set<GridObject*> children_; //!< Stores the id's of game objects that belong to the grid
        std::unordered_map<unsigned int, int> destructionIds_;         //!< Holds the id of the destruction listeners (key = object id, value = destruction id)
        std::vector<std::vector<Tile>> tiledMap_;                      //!< Tiles container
        PhysicsEngine* physicsSim_;                                     //!< The physics simulation

        friend class Scene;
    };
}

#endif // IME_GRID2D_H
