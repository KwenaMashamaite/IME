/**
 * @brief Tile map
 */

#ifndef TILEMAP_H
#define TILEMAP_H

#include "IME/common/Definitions.h"
#include "IME/common/IDrawable.h"
#include "Tile.h"
#include <vector>

namespace IME {
    using Definitions::Position;
    using Definitions::Dimensions;

    struct Index {
        int row;
        int colm;
    };

    //Alias for 2D vector
    using Map = std::vector<std::vector<char>>;

    class TileMap {
    public:
        /**
         * @brief Create a tile map
         * @param tileSet Tile set for constructing the map
         * @param tileWidth With of each tile in the map
         * @param tileHeight height of each tile in the map
         *
         * The tile map has the position (0, 0) by default
         *
         */
        TileMap(const std::string& tileSet, unsigned int tileWidth, unsigned int tileHeight);

        /**
         * @brief Set the position of the tile map
         * @param x X coordinate of the tile map
         * @param y Y coordinate of the tile map
         *
         * The position is (0, 0) by default
         */
        void setPosition(int x, int y);

        /**
         * @brief Get the position of the tile map
         * @return The position of the tile map
         */
        Position getPosition() const;

        /**
         * @brief Load map data from a file on the disk
         * @param filename Name of the file that contains the map data
         * @param separator Character used to separate map data
         */
        void loadFromFile(const std::string& filename, const char& separator = '\0');

        /**
         * @brief Load map data from a vector
         * @param map Vector to load data from
         */
        void loadFromVector(const Map& map);

        /**
         * @brief Replace a tile at a certain index
         * @param index Index of the tile to replace
         * @param tile Tile to replace old one with
         */
        void setTile(Index index, Tile&& tile);

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

    private:
        /**
         * @brief Check if the index is within bounds or not
         * @param index Index to check
         * @return True if the index is within bounds, otherwise false
         */
        bool isIndexValid(const Index &index) const;

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

    private:
        //Size of each tile in the tile map
        Dimensions tileSize_;
        //Size of the tile map
        Dimensions mapSizeInPixels_;
        //Position of the tile map in pixels
        Position mapPos_;
        //Number of tiles rows across
        unsigned int numOfRows_;
        //Number of tiles in columns across
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
        //First layer render state
        bool isBackgroundDrawable_;
        //Second layer render state
        bool isTilesDrawable_;
        //Third layer render state
        bool isObjectsDrawable_;
    };
}

#endif
