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

#ifndef IME_TILEMAP_H
#define IME_TILEMAP_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/common/Rect.h"
#include "IME/graphics/Tile.h"
#include "IME/core/tilemap/Index.h"
#include "IME/core/game_object/GameObject.h"
#include "IME/graphics/Sprite.h"
#include "IME/graphics/shapes/RectangleShape.h"
#include "IME/core/scene/RenderLayerContainer.h"
#include "IME/core/scene/DrawableContainer.h"
#include <unordered_map>
#include <vector>
#include <tuple>
#include <map>

namespace ime {
    using Map = std::vector<std::vector<char>>; //!< Alias for 2D vector of chars

    /**
     * @brief Class for creating a visual 2D grid.
     *
     * The grid if made up of tiles for visual representation
     */
    class IME_API TileMap {
    public:
        using Ptr = std::shared_ptr<TileMap>; // Shared tilemap pointer

        /**
         * @internal
         * @brief Set the physics simulation
         * @param physicsSimulation The simulation to be set
         *
         * @warning This function is intednded for internal use only
         */
        void setPhysicsSimulation(std::shared_ptr<World> physicsSimulation);

        /**
         * @brief Show or hide the tilemap
         * @param visible True to show or false to hide the tilemap
         *
         * By default, the tilemap is visible
         */
        void setVisible(bool visible);

        /**
         * @brief Check if the tilemap is visible or not
         * @return True if the tilemap is visible, otherwise false
         */
        bool isVisible() const;

        /**
         * @brief Toggle the visibility of the tilemap
         *
         * This function will show the tilemap if it is currently visible
         * or hide it if its currently visible
         */
        void toggleVisibility();

        /**
         * @brief Set the position of the tile map
         * @param x X coordinate of the tile map
         * @param y Y coordinate of the tile map
         *
         * The position is (0, 0) by default
         */
        void setPosition(int x, int y);

        /**
         * @brief Get the position of the tilemap in pixels
         * @return The position of the tilemap pixels
         */
        Vector2f getPosition() const;

        /**
        * @brief Check if the index is within bounds of the tilemap or not
        * @param index Index to check
        * @return True if the index is within bounds, otherwise false
        */
        bool isIndexValid(const Index &index) const;

        /**
         * @brief Set the image to be used as the tileset
         * @param name Name of the tileset
         * @param filename Filename of the tileset image
         * @throws FileNotFound If the tileset cannot be loaded by the asset
         *        manager
         */
        void setTileset(const std::string& name, const std::string& filename);

        /**
         * @brief Set the current tileset
         * @param name Name of the tileset
         *
         * All tileset related operations are performed on the current tileset.
         * In order to tile the map from different tileset, the current tileset
         * must be alternated
         */
        void setCurrentTileset(const std::string& name);

        /**
         * @brief Construct a tilemap
         * @param id The id of each tile
         * @param size The size of the tilemap in tiles
         *
         * This function should be used when there are no special tiles
         * in the tilemap, that is, when all tiles have the same id. The
         * x component of @a size is the number of rows whilst the y
         * component is the number of columns
         *
         * @see loadFromFile and loadFromVector
         */
        void construct(Vector2u size, char id);

        /**
         * @brief Construct the tilemap from data located on a file on the disk
         * @param filename Name of the file that contains the map data
         * @param separator Character used to separate map data
         */
        void loadFromFile(const std::string& filename, const char& separator = '\0');

        /**
         * @brief Construct the tilemap form a vector that contains map data
         * @param map Vector to construct map from
         */
        void loadFromVector(Map map);

        /**
         * @brief Set whether or not a tile is collidable
         * @param tile The tile to enable or disable collisions for
         * @param collidable True to set collidable, otherwise false
         *
         * By default, a tile is not collidable
         */
        void setCollidable(Tile& tile, bool collidable);

        /**
         * @brief Enable or disable collision for a tile at a certain location
         * @param index Location (in tiles) of the tile
         * @param isCollidable True to enable collision, otherwise false
         *
         * The tile will be marked as a solid tile, if currently set as an
         * empty tile
         */
        void setCollidableByIndex(const Index &index, bool isCollidable);

        /**
         * @brief Enable or disable collision for tiles at certain locations
         * @param locations Locations (in tiles) of the tiles
         * @param isCollidable True to enable collision, otherwise false
         *
         * All the tiles at specified indexes (if valid) will be set as solid
         * tiles if currently set as empty tiles
         */
        void setCollidableByIndex(const std::initializer_list<Index>& locations,
            bool isCollidable);

        /**
         * @brief Enable or disable collisions for tiles in a range
         * @param startPos The start position of the range
         * @param endPos The ending position of the range
         * @param isCollidable True to set collidable, otherwise false
         *
         * @warning Only horizontal ranges are supported. This means that
         * that the indexes in the range [startPos, endPos] must refer to
         * tiles that are valid and horizontally contiguous
         */
        void setCollidableByIndex(Index startPos, Index endPos, bool isCollidable);

        /**
         * @brief Enable or disable collisions for tiles with a certain id
         * @param id Id of the tiles to enable or disable collisions for
         * @param isCollidable True to enable collision, otherwise false
         *
         * All the tiles with the specified id will be marked as solid tiles
         * if currently marked as empty tiles
         */
        void setCollidableById(char id, bool isCollidable);

        /**
         * @brief Enable or disable collisions for all tiles except those with
         *        with a certain id
         * @param id Identification of the tiles to exclude
         * @param isCollidable True to enable collision, otherwise false
         */
        void setCollidableByExclusion(char id, bool isCollidable);

        /**
         * @brief Check if a tile is collidable or not
         * @param index Index of the tile to be checked
         * @return True if tile is collidable, or false if the tile is not
         *         collidable or the index is invalid
         */
        bool isCollidable(const Index& index) const;

        /**
         * @brief Get the size of the tilemap in pixels
         * @return Size of the tilemap in pixels
         */
        Vector2u getSize() const;

        /**
         * @brief Get the size of the tilemap in tiles
         * @return Size of the tilemap in tiles
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
         *         specified index is out of bounds of the tilemap
         *
         * A tile is invalid if it has a negative index
         */
        Tile& getTile(const Index& index);

        /**
         * @brief Get the tile at at certain position
         * @param position Position of the tile to retrieve
         * @return The tile at the specified position or an invalid tile if
         *         the specified position does not lie within the tilemap
         *         bounds
         *
         * A tile is invalid if it has a negative index
         */
        Tile& getTile(const Vector2f& position);

        /**
         * @brief Get the tile above a certain tile
         * @param tile Tile to get the tile above of
         * @return The tile above the specified tile or an invalid tile if
         *         there is no tile above the specified tile
         *
         * A tile is invalid if it has a negative index
         */
        Tile& getTileAbove(const Tile& tile);

        /**
         * @brief Get the tile below a certain tile
         * @param tile Tile to get the tile below of
         * @return The tile below the specified tile or an invalid tile if
         *         there is no tile below the specified tile
         *
         * A tile is invalid if it has a negative index
         */
        Tile& getTileBelow(const Tile& tile);

        /**
         * @brief Get the tile to the left of a certain tile
         * @param tile Tile to get the tile to the left of
         * @return The tile to the left of the specified tile or an invalid
         *         tile if there's no tile to the left of the specified tile
         *
         * A tile is invalid if it has a negative index
         */
        Tile & getTileLeftOf(const Tile& tile);

        /**
         * @brief Get the tile to the right of a certain tile
         * @param tile Tile to get the tile to the right of
         * @return The tile to the right of the specified tile or an invalid
         *         tile if there's no tile to the left of the specified tile
         *
         * A tile is invalid if it has a negative index
         */
        Tile& getTileRightOf(const Tile& tile);

        /**
         * @brief Execute a callback function on every tile with a certain id
         * @param id Id of the tile
         * @param callback Function to execute
         */
        void forEachTileWithId(char id, Callback<Tile&> callback);

        /**
         * @brief Execute a callback on all tiles except tiles with a
         *        given id
         * @param id Id of the tiles to be ignored
         * @param callback Function to be executed
         */
        void forEachTileExcept(char id, Callback<Tile&> callback);

        /**
         * @brief Execute a callback on all the tiles of the tilemap
         * @param callback Function to execute for each tile
         */
        void forEachTile(Callback<Tile&> callback);

        /**
         * @brief Execute a callback function on each tile in a range
         * @param startPos The beginning of the range
         * @param endPos The end of the range
         * @param callback Function to execute for each tile
         *
         * @note Only horizontal ranges are supported
         */
        void forEachTileInRange(Index startPos, Index endPos, Callback<Tile&> callback);

        /**
         * @brief Get the tilemap render layers
         * @return The tilemap render layers
         *
         * Render layers allow the tilemap to be rendered in separate layers
         * which are then composed back together. By default the tilemap has
         * a "default" layer at index 0. When a drawable object is added to
         * the scene without an explicit layer, it will be added to the default
         * layer. You can add objects to the "default" layer or even remove
         * the "default" layer from the render layer container, however you
         * must not forget to reallocate the objects in the "default" layer to
         * another layer, otherwise they will not be drawn to the screen
         */
        RenderLayerContainer& renderLayers();

        /**
         * @brief Texture a tile at given index
         * @param index Index of the tile to apply a texture to
         * @param rect Texture to apply
         *
         * The current tileset image will be used to texture the tile.
         * The @a rect defines the sub-rectangle of the tileset to use
         * for texturing the tile
         */
        void textureTile(Index index, FloatRect rect);

        /**
         * @brief Apply a texture to all tiles with a certain id
         * @param id Id of the tile to apply texture to
         * @param rect Texture to apply
         *
         * The current tileset image will be used to texture the tile.
         * The @a rect defines the sub-rectangle of the tileset to use
         * for texturing the tile. The image will taken as is from the
         * tileset
         *
         * @see textureTilesById(char, const Sprite&)
         */
        void textureTilesById(char id, FloatRect rect);

        /**
         * @brief Apply a texture to all tiles with a certain id
         * @param id Id of the tile to apply texture to
         * @param sprite Texture to apply
         *
         * The texture will be applied as is (i.e the properties of the sprite
         * object (scaling, rotation, origin etc..) will no be altered. This
         * function is useful if the texture from the tileset must be transformed
         * first (scaled, rotated, etc...) before its applied to the tilemap
         */
        void textureTilesById(char id, const Sprite& sprite);

        /**
         * @internal
         * @brief Render tilemap on a render target
         * @param renderTarget Target to render tilemap on
         *
         * The tilemap's tiles do not belong to any render layer and are
         * always drawn behind everything. That is, they are drawn first
         * before the first render layer (layer at index 0) is drawn.
         *
         * @warning This function is intended for internal use only and
         * should never be called outside of IME
         */
        void draw(Window &renderTarget);

        /**
         * @brief Add a sprite to the tilemap
         * @param sprite The sprite to be added to the tilemap
         * @param index The index of the tile to add the sprite at
         * @param renderOrder The render order of the sprite in the layer
         * @param renderLayer The render layer to add the sprite to
         *
         * If @a renderLayer cannot be found, then sprite will be added to
         * the "default" layer. If the default layer cannot be found then
         * the behaviour is undefined. A tilemap without a "default" layer
         * is undefined behavior
         *
         * Note that the sprite is added at the centre of the the tile
         */
        void addSprite(Sprite::Ptr sprite, Index index, int renderOrder = 0,
            const std::string& renderLayer = "default");

        /**
         * @brief Add an entity to the tilemap
         * @param child GameObject to add to the tilemap
         * @param index Index of the tile to add the entity to
         * @return True if the entity has been added or false if the index is
         *         invalid or the entity already exists in the tilemap
         *
         * If the specified tile is already occupied, the child will be added
         * as a visitor of that tile. Note that @a child will always be placed
         * at the centre point of the tile
         */
        bool addChild(GameObject::Ptr child, Index index);

        /**
         * @brief Get the child in the tilemap with a certain id
         * @param id Id of the child to get access to
         * @return The child with the specified id or a nullptr if the child
         *         with the specified id does not exist in the tilemap
         */
        GameObject::Ptr getChildWithId(std::size_t id) const;

        /**
         * @brief Check if the tilemap has a certain child or not
         * @param child Child to search for in the tilemap
         * @return True if the tilemap has the child, otherwise false
         */
        bool hasChild(GameObject::Ptr child);

        /**
         * @brief Remove a child from a tile
         * @param tile Tile to remove child from
         * @param child Child to be removed
         * @return True if the child was removed or false if the child is not
         *         in the specified tile
         */
        bool removeChildFromTile(const Tile& tile, const GameObject::Ptr& child);

        /**
         * @brief Remove an occupant of a tile
         * @param tile Tile to remove occupant from
         * @return True if the occupant was removed or false if the tile is
         *         not occupied or it is invalid
         *
         * Recall, an occupant is the first child to occupy a tile, if removed,
         * the first visitor will become the new occupant. Subsequent calls to
         * this function will result in visitors taking turns as occupants until
         * the tile is no longer occupied
         */
        bool removeOccupant(const Tile &tile);

        /**
         * @brief Remove a child with a certain id from the tilemap
         * @param id Id of the child to be removed
         * @return True if the child was removed or false if the child with
         *         the specified id does not exist in the tilemap
         */
        bool removeChildWithId(std::size_t id);

        /**
         * @brief Remove a child from the grid
         * @param child Child to be removed
         * @return True if the child was removed or false if the child does
         *         not exist in the grid
         */
        bool removeChild(GameObject::Ptr child);

        /**
         * @brief Remove children from the grid using a condition
         * @param callback Function that determines if the condition is
         *        satisfied or not
         *
         * All children for which @a callback returns true are removed
         * from the grid
         */
        void removeChildrenIf(std::function<bool(GameObject::Ptr)> callback);

        /**
         * @brief Remove all the visitors of a tile
         * @param tile Tile whose visitors are to be removed
         * @return True if all visitors have been removed or false if the
         *         tile has no visitors
         *
         * This function will remove all children currently occupying a tile
         * except the occupant of the tile. In this context the occupant is
         * the child that got to the tile before other children
         *
         * @see tileHasVisitors
         */
        bool removeAllVisitors(const Tile& tile);

        /**
         * @brief Remove all children in a tile
         * @param tile Tile to remove all children from
         * @return True if all children were removed, or false if the
         *         tile is not occupied
         *
         * @see removeAllVisitors and removeOccupant
         */
        bool removeAllChildren(const Tile& tile);

        /**
         * @brief Move child to a different position in the tilemap
         * @param child Child to move
         * @param index New position of the child
         *
         * The child is ignored if it does not exist in the tilemap or the
         * specified index is invalid
         *
         * @see addChild
         */
        void moveChild(GameObject::Ptr child, Index index);

        /**
         * @brief Move child to a different tile
         * @param child Child to be moved
         * @param tile Tile to move child to
         *
         * The child is ignored if it does not exist in the tilemap or the
         * specified tile is invalid
         *
         * @see addChild
         */
        void moveChild(GameObject::Ptr child, const Tile& tile);

        /**
         * @brief Get the tile occupied by a child of the tilemap
         * @param child Child whose occupation tile is to be retrieved
         * @return The tile occupied by the specified child or an invalid tile
         *         if the child is not in the tilemap
         *
         * An invalid tile has a negative index
         */
        Tile& getTileOccupiedByChild(GameObject::Ptr child);

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
         * @brief Check if the tile at a specified index has visitors or not
         * @param tile Tile to be checked
         * @return True if the tile has visitors, otherwise false
         *
         * A tile has visitors if its currently occupied by more than one
         * child. The first child to occupy the tile is the occupant of
         * that tile whilst other entities are visitors
         */
        bool tileHasVisitors(const Tile& tile) const;

        /**
         * @brief Get the occupant of a tile
         * @param tile Tile to get the occupant of
         * @return The occupant of the specified tile if the tile is occupied,
         *         otherwise a nullptr
         *
         * An occupant is the first child to occupy a tile, subsequent children
         * are considered visitors
         *
         * @see forEachTile(Tile&, Callback)
         */
        GameObject::Ptr getOccupant(const Tile& tile);

        /**
         * @brief Execute a callback for each child in the tilemap
         * @param callback Function to execute
         */
        void forEachChild(Callback<GameObject::Ptr> callback);

        /**
         * @brief Execute a callback for each child in a tile
         * @param tile Tile to execute callback on
         * @param callback Function to execute
         *
         * The callback will be passed the children of the tile, with the first
         * child being the occupant of the tile. The callback will be ignored
         * if the specified index is invalid or the tile is not occupied
         */
        void forEachChildInTile(const Tile& tile, Callback<GameObject::Ptr> callback);

        /**
         * @brief Get the number of occupants in a tile
         * @param tile Tile to get the number of occupants for
         * @return The number of occupants in a tile
         */
        std::size_t getNumOfOccupants(const Tile& tile) const;

    private:
        /**
         * @brief Create an empty tilemap
         * @param tileWidth Width of each tile in the map
         * @param tileHeight height of each tile in the map
         *
         * The tile map has the position (0, 0) by default
         */
        TileMap(unsigned int tileWidth, unsigned int tileHeight);

        /**
         * @brief Create the visual gird
         */
        void createTiledMap();

        /**
         * @brief Create an empty vector of children for each tile of the
         *        tilemap
         *
         * This vector will store the children of that specific tile
         */
        void createObjectList();

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
         *         specified index is out of bounds of the tilemap
         *
         * A tile is invalid if it has a negative index
         */
        Tile& getTileAbove(const Index& index);

        /**
         * @brief Get the tile below a tile at a given location
         * @param index Location of the tile to get the tile below
         * @return The tile at the specified index or an invalid tile if the
         *         specified index is out of bounds of the tilemap
         *
         * A tile is invalid if it has a negative index
         */
        Tile& getTileBelow(const Index& index);

        /**
         * @brief Get the tile to the left of a tile at a given location
         * @param index Location of the tile to get the tile to the left of
         * @return The tile at the specified index or an invalid tile if the
         *         specified index is out of bounds of the tilemap
         *
         * A tile is invalid if it has a negative index
         */
        Tile& getTileLeftOf(const Index& index);

        /**
         * @brief Get the tile to the right of a tile at a given location
         * @param index Location of the tile to get the tile to the right of
         * @return The tile at the specified index or an invalid tile if the
         *         specified index is out of bounds of the tilemap
         *
         * A tile is invalid if it has a negative index
         */
        Tile& getTileRightOf(const Index& index);

    private:
        unsigned int tileSpacing_;   //!< Spacing between tiles in all directions
        Vector2u tileSize_;          //!< The Size of each tile
        Vector2u mapSizeInPixels_;   //!< The Size of the tilemap in pixels
        Vector2f mapPos_;            //!< The Position of the tilemap in pixels
        unsigned int numOfRows_;     //!< The width of the tilemap in tiles
        unsigned int numOfColms_;    //!< The height of the tilemap in tiles
        Map mapData_;                //!< Map data used to identify different tiles
        std::string tileSet_;        //!< Tileset the visual grid is constructed from
        bool isVisible_;             //!< A flag indicating whether or not the tilemap is visible
        Tile invalidTile_;           //!< Tile returned when an invalid index is provided
        RenderLayerContainer renderLayers_;   //!< Render layers for this scene
        SpriteContainer sprites_;    //!< Stores sprites that belong to the tilemap
        RectangleShape backgroundTile_; //!< Dictates the background colour of the tilemap
        std::unordered_map<Index, std::vector<GameObject::Ptr>> children_; //!< Children container
        std::unordered_map<std::string, std::string> tilesets_;              //!< Tilesets container
        std::vector<std::vector<Tile>> tiledMap_;//!< Tiles container
        std::shared_ptr<World> physicsSim_; //!< The physics simulation

        friend class Scene;
    };
}

#endif // IME_TILEMAP_H
