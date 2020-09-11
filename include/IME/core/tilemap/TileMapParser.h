#ifndef TILEMAPPARSER_H
#define TILEMAPPARSER_H

#include "IME/core/tilemap/TileMap.h"

namespace IME {
    class TileMapParser {
    public:
        /**
         * @brief Parse a map file
         * @param filename Name of the map file
         * @param separator Character used to separate column entries
         * @return Tile map data
         *
         * This function parses a map file and returns a map object created
         * form the parsed date
         */
        Map parse(const std::string& filename, const char& separator = ',');
    };
}

#endif
