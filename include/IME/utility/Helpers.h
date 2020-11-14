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
 * @brief Helper functions
 */

#ifndef IME_UTILITY_H
#define IME_UTILITY_H

#include "IME/graphics/Colour.h"
#include <SFML/Graphics/Color.hpp>
#include <TGUI/Color.hpp>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <ctime>
#include <random>
#include <SFML/Window/Keyboard.hpp>
#include <TGUI/Event.hpp>
#include <SFML/Window/Event.hpp>
#include <TGUI/Font.hpp>

namespace IME::Utility {
    /**
     * @internal
     * @brief Convert own Colour object to SFML colour object
     * @param colour Colour to be converted to SFML colour object
     * @return SFML colour object
     *
     * This function only converts the object and not the actual
     * colour. This means that the colour after the conversion is
     * the same as the one before the conversion
     */
    extern sf::Color convertToSFMLColour(Graphics::Colour colour);

    /**
     * @internal
     * @brief Convert own Colour object to TGUI colour object
     * @param color colour Colour to be converted to TGUI colour object
     * @return TGUI colour object
     */
    extern tgui::Color convertToTGUIColour(Graphics::Colour color);

    /**
     * @internal
     * @brief Convert graphics library colour object to own colour object
     * @param thirdPartyColour Colour to be converted to own colour object
     * @return Own colour object
     *
     * This function only converts the object and not the actual
     * colour. This means that the colour after the conversion is
     * the same as the one before the conversion
     */
    extern Graphics::Colour convertFrom3rdPartyColour(sf::Color thirdPartyColour);

    /**
     * @brief Check if an item exists or not in an unordered map
     * @param unorderedMap Map to search for item in
     * @param item Item to search for
     * @return True if item exists in the unordered map, otherwise false
     */
    template <typename T, typename U, typename V>
    bool findIn(const std::unordered_map<T, U>& unorderedMap, const V& item);

    /**
     * @brief Erase an item from the map
     * @param unorderedMap Map to remove item from
     * @param item Item to be removed
     * @return True if was removed in the unordered map, otherwise false
     */
    template <typename T, typename U, typename V>
    bool eraseIn(std::unordered_map<T, U>& unorderedMap, const V& item);

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
    std::pair<bool, int> findIn(const std::vector<T> vector, const U& item);

    /**
     * @brief Erase an element from a vector
     * @param vector Vector to remove element from
     * @param element Element to be removed
     * @return True if element was removed or false if element doesn't exist
     *         in the vector
     */
    template <typename T, typename U>
    bool eraseIn(std::vector<T>& vector, const U& element);

    /**
     * @brief Generate a random number in a range
     * @param min The start of the range
     * @param max The end of the range
     * @return A random number in the given range
     */
    extern int generateRandomNum(int min, int max);

    /**
     * @brief Create a callable that generates random numbers in a range
     * @param min The start of the range
     * @param max The end of the range
     * @return A callable object, when called returns a random number in the
     *         specified range
     */
    static auto createRandomNumGenerator(int min, int max);

    /**
     * @brief Create a random colour
     * @return A random colour
     */
    extern Graphics::Colour generateRandomColour();

    /**
     * @internal
     * @brief Get a TGUI font
     * @param filename Filename of the font
     * @throws FileNotFound If the font cannot be found on the disk
     * @return TGUI font
     */
    extern tgui::Font get_TGUI_Font(const std::string& filename);

    #include "Helpers.inl"
}

#endif
