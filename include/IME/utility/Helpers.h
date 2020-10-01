/**
 * @brief Helper functions
 */

#ifndef UTILITY_H
#define UTILITY_H

#include "IME/graphics/Colour.h"
#include <SFML/Graphics/Color.hpp>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <ctime>

namespace IME {
    namespace Utility {
        /**
         * @brief Convert own Colour object to graphics library colour object
         * @param colour Colour to be converted to graphics library colour object
         * @return Graphics library colour object
         *
         * This function only converts the object and not the actual
         * colour. This means that the colour after the conversion is
         * the same as the one before the conversion
         */
        static sf::Color convertTo3rdPartyColour(Graphics::Colour color) {
            return {static_cast<sf::Uint8>(color.red),
                    static_cast<sf::Uint8>(color.green),
                    static_cast<sf::Uint8>(color.blue),
                    static_cast<sf::Uint8>(color.opacity)};
        }

        /**
         * @brief Convert graphics library colour object to own colour object
         * @param thirdPartyColour Colour to be converted to own colour object
         * @return Own colour object
         *
         * This function only converts the object and not the actual
         * colour. This means that the colour after the conversion is
         * the same as the one before the conversion
         */
        static Graphics::Colour convertFrom3rdPartyColour(sf::Color thirdPartyColour) {
            return {thirdPartyColour.r, thirdPartyColour.g, thirdPartyColour.b, thirdPartyColour.a};
        }

        /**
         * @brief Check if an item exists or not in an unordered map
         * @param unorderedMap Map to search for item in
         * @param item Item to search for
         * @return True if item exists in the unordered map, otherwise false
         */
        template <typename T, typename U, typename V>
        bool findIn(const std::unordered_map<T, U>& unorderedMap, const V& item) {
            return unorderedMap.find(item) != unorderedMap.end();
        }

        /**
         * @brief Find an item in vector
         * @param vector Vector to search item in
         * @param item Item to search for
         * @return A pair, of which the first element is a bool that is true if
         *         the specified item exists in the vector ,otherwise false and
         *         the second is an int which is the index of the found item in
         *         the vector
         */
        template <typename T, typename U>
        std::pair<bool, int> findIn(const std::vector<T> vector, const U& item) {
            if (auto found = std::find(vector.begin(), vector.end(), item); found != vector.end())
                return {true, std::distance(vector.begin(), found)};
            return {false, -1};
        }

        /**
         * @brief Erase an element from a vector
         * @param vector Vector to remove element from
         * @param element Element to be removed
         * @return True if element was removed or false if element doesn't exist
         *         in the vector
         */
        template <typename T, typename U>
        bool eraseIn(std::vector<T>& vector, const U& element) {
            if (auto [found, index] = findIn(vector, element); found) {
                vector.erase(vector.begin() + index);
                return true;
            }
            return false;
        }

        /**
         * @brief Generate a random number in a range
         * @param min The start of the range
         * @param max The end of the range
         * @return A random number in the given range
         */
        static int generateRandomNum(int min, int max) {
            return min + (rand() % (max - min + 1));
        }
    }
}

#endif
