/**
 * @brief A Container for Tiles
 */

#ifndef TILEMAP_H
#define TILEMAP_H

#include "IME/common/Position.h"
#include "IME/common/Dimensions.h"
#include "IME/common/IDrawable.h"
#include "IME/event/EventEmitter.h"
#include "Tile.h"
#include <unordered_map>
#include <vector>

namespace IME {
    struct Index {
        int row;
        int colm;
    };

    //Alias for 2D vector
    using Map = std::vector<std::vector<char>>;

    class TileMap {
    public:
        /**
         * @brief Create an empty tilemap
         * @param tileWidth With of each tile in the map
         * @param tileHeight height of each tile in the map
         *
         * The tile map has the position (0, 0) by default
         */
        TileMap(unsigned int tileWidth, unsigned int tileHeight);

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
         * @param filename File name of the tileset image
         * @throw FileNotFound If the tileset cannot be loaded by the asset
         *        manager
         *
         * @note The tilemap can only use a single tileset at any given time
         */
        void setTileset(const std::string& filename);

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
        void setTile(Index index, Tile&& tile);

        /**
         * @brief Enable or disable collision for a tile at a certain location
         * @param index Location (in tiles) of the tile
         * @param isCollideable True to enable collision, otherwise false
         */
        void setCollideableByIndex(const Index &index, bool isCollideable);

        /**
         * @brief Enable or disable collision for tiles at certain locations
         * @param locations Locations (in tiles) of the tiles
         * @param isCollideable True to enable collision, otherwise false
         */
        void setCollideableByIndex(const std::initializer_list<Index>& locations,
            bool isCollideable);

        /**
         * @brief Enable or disable collisions for tiles in a range
         * @param startPos The start position of the range
         * @param endPos The ending position of the range
         *
         * @note Only horizontal ranges are supported
         */
        void setCollideableByIndex(Index startPos, Index endPos, bool isCollideable);

        /**
         * @brief Enable or disable collision for tiles with a certain id
         * @param id Id of the tiles to enable or disable collisions for
         * @param isCollideable True to enable collision, otherwise false
         */
        void setCollideableById(const char& id, bool isCollideable);

        /**
         * @brief Enable or disable collision for all tiles except those with
         *        with a certain id
         * @param id Identification of the tiles to exclude
         * @param isCollideable True to enable collision, otherwise false
         */
        void setCollideableByExclusion(const char& id, bool isCollideable);

        /**
         * @brief Add an object to the tile map
         * @param index Index of the tile to add the object to
         * @param object Object to add to the tile map
         * @return True if the object has been added or false if the index is
         *         invalid
         */
        bool addObject(Index index, Sprite& object);

        /**
         * @brief Get the tile at at certain position
         * @param position Position of the tile to retrieve
         * @return The tile at the specified position
         */
        Tile& getTile(const Position& position);

        /**
         * @brief Set the background of the tile amp
         * @param filename Name of the background image
         *
         * The image must be the same size as the tile set, otherwise it will
         * be cropped or stretched
         */
        void setBackground(const std::string& filename);

        /**
         * @brief Get a tile at a certain index
         * @param index Index of the tile to get
         * @return The tile at the specified index
         *
         * @warning The index must be within bounds of the tile map
         */
        Tile& getTile(const Index& index);

        /**
         * @brief Render tile map on a render target
         * @param renderTarget Target to render tile map on
         */
        void draw(Gui::Window &renderTarget);

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
         * @brief Check if a tile is collideable or not
         * @param index Index of the tile to be checked
         * @return True if tile is collideable, or false if the tile is not
         *         collideable, partially collideable (Some tile borders are
         *         collideable) or the position od the tile is invalid
         */
        bool isCollideable(const Index& index) const;

        /**
         * @brief Execute a callback function on every tile with a certain id
         * @param id Id of the tile
         * @param callback Function to execute
         */
        void forEachTile(const char& id, Callback<Tile&> callback);

        /**
         * @brief Execute a callback on each tile of the tilemap
         * @param callback Function to execute for each tile
         */
        void forEachTile(Callback<Tile&> callback);

        /**
         * @brief Execute a callback function on each tile in a range
         * @param index The beginning of the range
         * @param endPos The end of the range
         * @param callback Function to execute for each tile
         *
         * @note Only horizontal ranges are supported
         */
        void forEachTile(Index startPos, Index endPos, Callback<Tile&> callback);

    private:
        /**
         * @brief Check if the index is within bounds of the tilemap or not
         * @param index Index to check
         * @return True if the index is within bounds, otherwise false
         */
        bool isValidIndex(const Index &index) const;

        /**
         * @brief Check if a token is valid or not
         * @param token Token to check
         * @return True if token is valid, otherwise false
         *
         * A token is valid if it has been linked to a tile on the tilemap's
         * tileset
         */
        bool isValidToken(const char& token) const;

        /**
         * @brief Create the visual gird
         */
        void createTiledMap();

        /**
         * @brief Get the index of a tile from pixel coordinates
         * @param position Coordinates to get index from
         * @return Coordinates of the tile at the specified position or (-1,-1)
         *         if the position is out of tile map bounds
         */
        Index getIndexFromPosition(const Position& position) const;

        /**
         * @brief Get the pixel coordinates of a tile from its index
         * @param index The index of the tile to get the position for
         * @return The position of tile in pixels
         */
        Position getCoordinatesFromIndex(Index index) const;

        /**
         * @brief Calculate size related attributes
         *
         * This include map size, number of rows and columns, etc..
         */
        void computeDimensions();

        /**
         * @brief Get the tile above a tile at a given location
         * @param index Index of the tile to get the tile above
         * @returnThe tile above the specified position (in tiles)
         */
        Tile& getTileAbove(const Index& index);

        /**
         * @brief Get the tile below a tile at a given location
         * @param index Location of the tile to get the tile below
         * @return The tile below the tile at the specified coordinates
         */
        Tile& getTileBelow(const Index& index);

        /**
         * @brief Get the tile to the left of a tile at a given location
         * @param index Location of the tile to get the tile to the left of
         * @return The tile to the left of the tile at the specified coordinates
         */
        Tile & getTileLeftOf(const Index& index);

        /**
         * @brief Get the tile to the right of a tile at a given location
         * @param index Location of the tile to get the tile to the right of
         * @return The tile to the right of the tile at the specified coordinates
         */
        Tile& getTileRightOf(const Index& index);

        /**
         * @brief Execute a callback on each object int the tile map
         * @param callback Function to execute for each object
         */
        void forEachObject(Callback<Sprite&> callback);

        /**
         * @brief Add an event listener to a tilemap collision event
         * @param callback Function to execute when the event is raised
         * @return The event listeners identification number
         *
         * A tilemap collision event occurs when an object tries to enter a
         * tile that has been marked as collideable. The callback will be
         * passed the object that caused the collision and the tile the object
         * collided with respectively
         */
        int onTileMapCollision(Callback<Sprite&, Tile&> callback);

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
        std::string background_;
        //Visual grid (second layer)
        std::vector<std::vector<Tile>> tiledMap_;
        //References to objects (third layer)
        std::vector<std::reference_wrapper<Sprite>> objects_;
        //Holds the tileset image properties associated with a tile id
        std::unordered_map<char, std::pair<Position, Dimensions>> imagesData_;
        //First layer render state
        bool isBackgroundDrawable_;
        //Second layer render state
        bool isTilesDrawable_;
        //Third layer render state
        bool isObjectsDrawable_;
        //Tile returned when an invalid index is provided
        Tile invalidTile_;
        //Publishes the tile maps events
        EventEmitter eventEmitter_;
    };
}

#endif
