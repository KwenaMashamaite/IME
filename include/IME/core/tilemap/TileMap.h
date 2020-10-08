/**
 * @brief Class for creating a visual 2D grid.
 *
 * The grid if made up of tiles for visual representation
 */

#ifndef TILEMAP_H
#define TILEMAP_H

#include "IME/common/Position.h"
#include "IME/common/Dimensions.h"
#include "IME/graphics/Tile.h"
#include "IME/core/entity/Entity.h"
#include <unordered_map>
#include <vector>
#include <tuple>

namespace IME {
    //Alias for 2D vector
    using Map = std::vector<std::vector<char>>;

    class TileMap {
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
        Position getPosition() const;

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
        void loadFromVector(const Map& map);

        /**
         * @brief Associate a tile id with a tileset image
         * @param id The tile id to associate with a tileset image
         * @param startPos The starting position of the tileset image
         * @param size The size of the tileset image
         *
         * Tiles in the tilemap will be textured with the image data corresponding
         * to their id's when textured @see applyImages()
         */
        void addTilesetImageData(const char& id, Position startPos, Dimensions size);

        /**
         * @brief Texture the tilemap
         *
         * This function will texture each tile in the tile map with an image
         * linked to the tile's id. Any tile whose id is not linked to an image
         * on the tilemap's tileset will be left empty
         *
         * @see addTilesetImageData(const char&, Position, Dimensions)
         */
        void applyImages();

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
         * @brief Remove an entity from the tilemap
         * @param index Index of the entity in the tilemap
         * @return True if the entity was removed or false if the entity does not
         *          exist at the specified index
         */
        bool removeChild(Index index);

        /**
         * @brief Move child to a different position in the tilemap
         * @param child Child to move
         * @param index New position of the child
         */
        void updateChild(std::shared_ptr<IME::Entity> child, Index index);

        /**
         * @brief Get the tile at at certain position
         * @param position Position of the tile to retrieve
         * @return The tile at the specified position or an invalid tile if
         *         the specified position does not lie within the tilemap bounds
         *
         * A tile is invalid if it has the id of '!' or a negative position
         */
        Graphics::Tile& getTile(const Position& position);

        /**
         * @brief Get the tile above a certain tile
         * @param tile Tile to get the tile above of
         * @return The tile above the specified tile or an invalid tile if
         *         there is no tile above the specified tile
         *
         * A tile is invalid if it has the id of '!' or a negative index
         */
        Graphics::Tile& getTileAbove(const Graphics::Tile& tile);

        /**
         * @brief Get the tile below a certain tile
         * @param tile Tile to get the tile below of
         * @return The tile below the specified tile or an invalid tile if
         *         there is no tile below the specified tile
         *
         * A tile is invalid if it has the id of '!' or a negative index
         */
        Graphics::Tile& getTileBelow(const Graphics::Tile& tile);

        /**
         * @brief Get the tile to the left of a certain tile
         * @param tile Tile to get the tile to the left of
         * @return The tile to the left of the specified tile or an invalid
         *         tile if there's no tile to the left of the specified tile
         *
         * A tile is invalid if it has the id of '!' or a negative index
         */
        Graphics::Tile & getTileLeftOf(const Graphics::Tile& tile);

        /**
         * @brief Get the tile to the right of a certain tile
         * @param tile Tile to get the tile to the right of
         * @return The tile to the right of the specified tile or an invalid
         *         tile if there's no tile to the left of the specified tile
         *
         * A tile is invalid if it has the id of '!' or a negative index
         */
        Graphics::Tile& getTileRightOf(const Graphics::Tile& tile);

        /**
         * @brief Set the background of the tile amp
         * @param filename Name of the background image
         *
         * The background image must
         */
        void setBackground(const std::string& filename, Position position);

        /**
         * @brief Scale the background image by an offset
         * @param xOffset Horizontal offset
         * @param yOffset Vertical offset
         *
         * The image will be cropped if the scaling goes beyond the tile borders
         */
        void scaleBackground(float xOffset, float yOffset);

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
         * A tile is invalid if it has the id of '!' or a negative position
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
        Dimensions getSize() const;

        /**
         * @brief Get the size of the tilemap in tiles
         * @return Size of the tilemap in tiles
         *
         * This function will return the number of rows and columns in the
         * tilemap as the width and height respectively
         */
        Dimensions getSizeInTiles() const;

        /**
         * @brief Hide a shown tile map
         */
        void hide(const std::string& layer);

        /**
         * @brief Show a hidden tile map
         */
        void show(const std::string& layer);

        /**
         * @brief Check if tile map is hidden or not
         * @return True if tile map is hidden, otherwise false
         */
        bool isHidden(const std::string& layer) const;

        /**
         * @brief Check if a tile is collidable or not
         * @param index Index of the tile to be checked
         * @return True if tile is collidable, or false if the tile is not
         *         collidable, partially collidable (Some tile borders are
         *         collidable) or the position od the tile is invalid
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
         * @return True if gird is visible, otherwise false
         */
        bool isGridVisible() const;

    private:
        /**
         * @brief Check if a tile id is linked to a tileset image or not
         * @param id Id to check
         * @return True if id is linked to tileset image, otherwise false
         */
        bool isIdLinkedToImage(const char& id) const;

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
         * A tile is invalid if it has the id of '!' or a negative position
         */
        Graphics::Tile& getTileAbove(const Index& index);

        /**
         * @brief Get the tile below a tile at a given location
         * @param index Location of the tile to get the tile below
         * @return The tile at the specified index or an invalid tile if the
         *         specified index is out of bounds of the tilemap
         *
         * A tile is invalid if it has the id of '!' or a negative position
         */
        Graphics::Tile& getTileBelow(const Index& index);

        /**
         * @brief Get the tile to the left of a tile at a given location
         * @param index Location of the tile to get the tile to the left of
         * @return The tile at the specified index or an invalid tile if the
         *         specified index is out of bounds of the tilemap
         *
         * A tile is invalid if it has the id of '!' or a negative position
         */
        Graphics::Tile & getTileLeftOf(const Index& index);

        /**
         * @brief Get the tile to the right of a tile at a given location
         * @param index Location of the tile to get the tile to the right of
         * @return The tile at the specified index or an invalid tile if the
         *         specified index is out of bounds of the tilemap
         *
         * A tile is invalid if it has the id of '!' or a negative position
         */
        Graphics::Tile& getTileRightOf(const Index& index);

    private:
        //The Size of each tile in the tilemap
        Dimensions tileSize_;
        //The Size of the tilemap in pixels
        Dimensions mapSizeInPixels_;
        //The Position of the tilemap in pixels
        Position mapPos_;
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
        std::unordered_map<char, std::tuple<std::string, Position, Dimensions>> imagesData_;
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

        friend class AdjacencyList;
    };
}

#endif
