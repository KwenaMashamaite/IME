#include "IME/core/tile/TileMapParser.h"
#include "IME/utility/DiskFileReader.h"
#include <sstream>

namespace IME {
    Map TileMapParser::parse(const std::string &filename, const char &separator) {
        auto map = Map();
        auto mapData = std::stringstream();
        Utility::DiskFileReader().readFileInto(filename, mapData);
        auto line = std::string("");
        while (std::getline(mapData, line)) {
            ////Skip lines that are empty or begin with a comment
            if (line.empty() || line[0] == '#')
                continue;

            auto row = std::vector<char>();
            for (const auto& character : line) {
                if (character != separator)
                    row.push_back(character);
            }
            map.push_back(row);
        }
        return map;
    }
}