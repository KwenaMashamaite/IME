////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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

/**
 * @brief Class for creating a visual 2D grid.
 *
 * The grid if made up of tiles for visual representation
 */

#ifndef IME_TILEMAP_H
#define IME_TILEMAP_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/common/Rect.h"
#include "IME/graphics/Tile.h"
#include "IME/core/entity/Entity.h"
#include <unordered_map>
#include <vector>
#include <tuple>

namespace IME {
    //Alias for 2D vector
    using Map = std::vector<std::vector<char>>;

    class IME_API TileMap {
    public:
        /**
         * @brief Create an empty tilemap
         * @param tileWidth Width of each tile in the map
         * @param tileHeight height of each tile in the map
         *
         * The tile map has the position (0, 0) by default
         */
        explicit TileMap(unsigned int tileWidth = 8, unsigned int tileHeight = 8);

        /**
         * @brief Set the position of the tile map
         * @param x X coordinate of the tile map
         * @param y Y coordinate of the tile map
         *
         * The position is (0, 0) by default
         */
        void setPosition(int x, int y);

        /**
         * @brief Set the image to be used as the tileset
         * @param name Name of the tileset
         * @param filename File name of the tileset image
         * @throw FileNotFound If the tileset cannot be loaded by the asset
         *        manager
         */
        void setTileset(const std::string& name, const std::string& filename);

        /**
         * @brief Set the current tileset
         * @param name Name of the tileset
         *
         * All tileset related operations are performed on the current tileset.
         * For instance texturing tilemap tiles
         */
        void setCurrentTileset(const std::string& name);

        /**
         * @brief Get the position of the tile map in pixels
         * @return The position of the tile map pixels
         */
        Vector2f getPosition() const;

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
         * @brief Texture a tile at given index
         * @param index Index of the tile to apply a texture to
         * @param rect Texture to apply
         *
         * The current tileset image will be used to texture the tile. The
         * @param rect defines the portion of the tileset to use for the
         * texturing the tile
         */
        void textureTile(Index index, FloatRect rect);

        /**
         * @brief Apply a texture to all tiles with a certain id
         * @param id Id of the tile to apply texture to
         * @param rect Texture to apply
         *
         * The current tileset image will be used to texture the tile. The
         * @param rect defines the portion of the tileset to use for the
         * texturing the tile. If you want to use a transformed texture,
         * (scaled, rotated, etc ...), you can use
         * @see textureTilesById(char id, const Graphics::Sprite& sprite)
         */
        void textureTilesById(char id, FloatRect rect);

        /**
         * @brief Apply a texture to all tiles with a certain id
         * @param id Id of the tile to apply texture to
         * @param sprite Texture to apply
         *
         * The texture will be applied as is. This function is useful if the
         * texture from the tileset must be transformed first (scaled,
         * rotated, etc...) before its applied to the tilemap
         */
        void textureTilesById(char id, const Graphics::Sprite& sprite);

        /**
         * @brief Replace a tile at a certain index
         * @param index Index of the tile to replace
         * @param tile Tile to replace old one with
         */
        void setTile(Index index, Graphics::Tile&& tile);

        /**
         * @brief Enable or disable collision for a tile at a certain location
         * @param index Location (in tiles) of the tile
         * @param isCollidable True to enable collision, otherwise false
         */
        void setCollidableByIndex(const Index &index, bool isCollidable);

        /**
         * @brief Enable or disable collision for tiles at certain locations
         * @param locations Locations (in tiles) of the tiles
         * @param isCollidable True to enable collision, otherwise false
         */
        void setCollidableByIndex(const std::initializer_list<Index>& locations,
                                  bool isCollidable);

        /**
         * @brief Enable or disable collisions for tiles in a range
         * @param startPos The start position of the range
         * @param endPos The ending position of the range
         *
         * @note Only horizontal ranges are supported
         */
        void setCollidableByIndex(Index startPos, Index endPos, bool isCollidable);

        /**
         * @brief Enable or disable collision for tiles with a certain id
         * @param id Id of the tiles to enable or disable collisions for
         * @param isCollidable True to enable collision, otherwise false
         */
        void setCollidableById(const char& id, bool isCollidable);

        /**
         * @brief Enable or disable collision for all tiles except those with
         *        with a certain id
         * @param id Identification of the tiles to exclude
         * @param isCollidable True to enable collision, otherwise false
         */
        void setCollidableByExclusion(const char& id, bool isCollidable);

        /**
         * @brief Add an object to the tile map
         * @param index Index of the tile to add the object to
         * @param child Object to add to the tile map
         * @return True if the object has been added or false if the index is
         *         invalid
         */
        bool addChild(Index index, std::shared_ptr<IME::Entity> child);

        /**
         * @brief Check if the tilemap has a certain child object
         * @param childPtr Child to search for in the tilemap
         * @return True if the tilemap has the child otherwise false
         */
        bool hasChild(std::shared_ptr<Entity> childPtr);

        /**
         * @brief Get the child occupying a certain tile
         * @param tilePos The position of the tile to get the occupant of
         * @return The child occupying a tile at the specified location or a
         *         nullptr if the tile is not occupied
         */
        std::shared_ptr<Entity> getChild(Index index) const;

        /**
         * @brief Get the child in the map with a certain id
         * @param id Id of the child to get access to
         * @return The child with the specified id or a nullptr if the child
         *          with the specified id does not exist in the tilemap
         */
        std::shared_ptr<Entity> getChildWithId(std::size_t id) const;

        /**
         * @brief Remove a child from the tilemap
         * @param child Child to be removed
         * @return True if the child was removed or false if the child is not
         *          in the tilemap
         */
        bool removeChild(const std::shared_ptr<Entity>& child);

        /**
         * @brief Remove an entity from the tilemap
         * @param index Index of the entity in the tilemap
         * @return True if the entity was removed or false if the entity does not
         *          exist at the specified index
         */
        bool removeChild(Index index);

        /**
         * @brief Remove a child with a certain id from the tilemap
         * @param id Id of the child to be removed
         * @return True if the child was removed or false if the child does not
         *          exist
         */
        bool removeChildWithId(std::size_t id);

        /**
         * @brief Move child to a different position in the tilemap
         * @param child Child to move
         * @param index New position of the child
         */
        void updateChild(std::shared_ptr<IME::Entity> child, Index index);

        /**
         * @brief Get the size of each tile in the grid
         * @return The size of each tile in the grid
         *
         * All the tiles have the same size
         */
        Vector2u getTileSize() const;

        /**
         * @brief Get the tile at at certain position
         * @param position Position of the tile to retrieve
         * @return The tile at the specified position or an invalid tile if
         *         the specified position does not lie within the tilemap bounds
         *
         * A tile is invalid if it has a negative index
         */
        Graphics::Tile& getTile(const Vector2f& position);

        /**
         * @brief Get the tile above a certain tile
         * @param tile Tile to get the tile above of
         * @return The tile above the specified tile or an invalid tile if
         *         there is no tile above the specified tile
         *
         * A tile is invalid if it has a negative index
         */
        Graphics::Tile& getTileAbove(const Graphics::Tile& tile);

        /**
         * @brief Get the tile below a certain tile
         * @param tile Tile to get the tile below of
         * @return The tile below the specified tile or an invalid tile if
         *         there is no tile below the specified tile
         *
         * A tile is invalid if it has a negative index
         */
        Graphics::Tile& getTileBelow(const Graphics::Tile& tile);

        /**
         * @brief Get the tile to the left of a certain tile
         * @param tile Tile to get the tile to the left of
         * @return The tile to the left of the specified tile or an invalid
         *         tile if there's no tile to the left of the specified tile
         *
         * A tile is invalid if it has a negative index
         */
        Graphics::Tile & getTileLeftOf(const Graphics::Tile& tile);

        /**
         * @brief Get the tile to the right of a certain tile
         * @param tile Tile to get the tile to the right of
         * @return The tile to the right of the specified tile or an invalid
         *         tile if there's no tile to the left of the specified tile
         *
         * A tile is invalid if it has a negative index
         */
        Graphics::Tile& getTileRightOf(const Graphics::Tile& tile);

        /**
         * @brief Get the tilemap background
         * @return The tilemap background
         *
         * The background of the tilemap may be manipulated through the
         * returned sprite. @note By default there is no background set,
         * if the background texture is set then @see showLayer must be
         * invoked with "background" as the argument in order for the
         * background to be rendered and displayed
         */
        Graphics::Sprite& getBackground();

        /**
         * @brief Show or hide the tilemap grid lines
         * @param isVisible True to show or false to hide the grid lines
         *
         * The grid lines are visible by default
         */
        void setGridVisible(bool isVisible);

        /**
         * @brief Get a tile at a certain index
         * @param index Index of the tile to get
         * @return The tile at the specified index or an invalid tile if the
         *         specified index is out of bounds of the tilemap
         *
         * A tile is invalid if it has a negative index
         */
        Graphics::Tile& getTile(const Index& index);

        /**
         * @brief Render tile map on a render target
         * @param renderTarget Target to render tile map on
         */
        void draw(Graphics::Window &renderTarget);

        /**
         * @brief Get the size of the tilemap in pixels
         * @return Size of the tilemap in pixels
         */
        Vector2u getSize() const;

        /**
         * @brief Get the spacing between tiles in all directions
         * @return The spacing between tiles
         *
         * The spacing is how far tiles are from one another. The default
         * space between tiles is 1
         */
        unsigned int getSpaceBetweenTiles() const;

        /**
         * @brief Get the size of the tilemap in tiles
         * @return Size of the tilemap in tiles
         *
         * The x component is the number of columns whilst the y component
         * is the number of rows
         */
        Vector2u getSizeInTiles() const;

        /**
         * @brief Hide a layer
         * @param layer Name of the layer to be hidden
         */
        void hideLayer(const std::string& layer);

        /**
         * @brief Show a hidden layer
         * @param layer Name of the layer to be shown
         */
        void showLayer(const std::string& layer);

        /**
         * @brief Check if a layer is hidden or not
         * @param layer Name of the layer to be checked
         * @return True if specified layer is hidden, otherwise false
         */
        bool isLayerHidden(const std::string& layer) const;

        /**
         * @brief Check if a tile is collidable or not
         * @param index Index of the tile to be checked
         * @return True if tile is collidable, or false if the tile is not
         *         collidable or the index is invalid
         */
        bool isCollidable(const Index& index) const;

        /**
         * @brief Execute a callback function on every tile with a certain id
         * @param id Id of the tile
         * @param callback Function to execute
         */
        void forEachTile(const char& id, Callback<Graphics::Tile&> callback);

        /**
         * @brief Execute a callback on each tile of the tilemap
         * @param callback Function to execute for each tile
         */
        void forEachTile(Callback<Graphics::Tile&> callback);

        /**
         * @brief Execute a callback function on each tile in a range
         * @param index The beginning of the range
         * @param endPos The end of the range
         * @param callback Function to execute for each tile
         *
         * @note Only horizontal ranges are supported
         */
        void forEachTile(Index startPos, Index endPos, Callback<Graphics::Tile&> callback);

        /**
         * @brief Execute a callback on each child of the tile map
         * @param childPtr Function to execute for each child
         */
        void forEachChild(Callback<Entity&> childPtr);

        /**
         * @brief Check if the index is within bounds of the tilemap or not
         * @param index Index to check
         * @return True if the index is within bounds, otherwise false
         */
        bool isIndexValid(const Index &index) const;

        /**
         * @brief Check if the grid is visible or not
         * @return True if grid is visible, otherwise false
         */
        bool isGridVisible() const;

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
         *         specified index is out of bounds of the tilemap
         *
         * A tile is invalid if it has a negative index
         */
        Graphics::Tile& getTileAbove(const Index& index);

        /**
         * @brief Get the tile below a tile at a given location
         * @param index Location of the tile to get the tile below
         * @return The tile at the specified index or an invalid tile if the
         *         specified index is out of bounds of the tilemap
         *
         * A tile is invalid if it has a negative index
         */
        Graphics::Tile& getTileBelow(const Index& index);

        /**
         * @brief Get the tile to the left of a tile at a given location
         * @param index Location of the tile to get the tile to the left of
         * @return The tile at the specified index or an invalid tile if the
         *         specified index is out of bounds of the tilemap
         *
         * A tile is invalid if it has a negative index
         */
        Graphics::Tile & getTileLeftOf(const Index& index);

        /**
         * @brief Get the tile to the right of a tile at a given location
         * @param index Location of the tile to get the tile to the right of
         * @return The tile at the specified index or an invalid tile if the
         *         specified index is out of bounds of the tilemap
         *
         * A tile is invalid if it has a negative index
         */
        Graphics::Tile& getTileRightOf(const Index& index);

    private:
        //Spacing between tiles in all directions
        unsigned int tileSpacing_;
        //The Size of each tile in the tilemap
        Vector2u tileSize_;
        //The Size of the tilemap in pixels
        Vector2u mapSizeInPixels_;
        //The Position of the tilemap in pixels
        Vector2f mapPos_;
        //The width of the tilemap in tiles
        unsigned int numOfRows_;
        //The height of the tilemap in tiles
        unsigned int numOfColms_;
        //Map data used to identify different tiles/objects
        Map mapData_;
        //Tile set the visual grid is constructed from
        std::string tileSet_;
        //Background image (first layer)
        Graphics::Sprite background_;
        //Visual grid (second layer)
        std::vector<std::vector<Graphics::Tile>> tiledMap_;
        //References to objects (third layer)
        std::vector<std::pair<Index, std::shared_ptr<Entity>>> children_;
        //Holds the tileset image properties associated with a tile id
        std::unordered_map<char, std::pair<std::string, FloatRect>> imagesData_;
        //The maps tileset image files
        std::unordered_map<std::string, std::string> tilesets_;
        //The visibility state of the grid
        bool isGridVisible_;
        //First layer render state
        bool isBackgroundDrawable_;
        //Second layer render state
        bool isTilesDrawable_;
        //Third layer render state
        bool isObjectsDrawable_;
        //Tile returned when an invalid index is provided
        Graphics::Tile invalidTile_;
    };
}

#endif
