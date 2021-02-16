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

/////////////////////////////////////////////////////////////////
// All of the functions in this file are meant for internal use
// and should never be called externally (i.e You should never
// include this header if your externally linking to IME)
////////////////////////////////////////////////////////////////

#ifndef IME_UTILITY_H
#define IME_UTILITY_H

#include "IME/graphics/Colour.h"
#include "IME/common/Vector2.h"
#include "IME/core/event/Event.h"
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <memory>

namespace tgui {
    class Font;
    class Color;
}

namespace sf {
    class Event;
    class Color;
}

namespace ime {
    namespace ui {
        class Widget;
    }

    namespace utility {
        /**
        * @internal
        * @brief Convert SFML system event to own system Event
        * @param SFML_Event SFML event to convert to own event
        * @return Own event initialized with the corresponding system event if
        *         it is supported otherwise initialized with Event::Type::Unknown
        */
        extern Event convertToOwnEvent(const sf::Event& SFML_Event);

        /**
        * @internal
        * @brief Convert own system event to SFML system event
        * @param IME_Event Event to be converted
        * @return SFML system event
        */
        extern sf::Event convertToSFMLEvent(const Event& IME_Event);

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
        extern sf::Color convertToSFMLColour(Colour colour);

        /**
        * @internal
        * @brief Convert own Colour object to TGUI colour object
        * @param color colour Colour to be converted to TGUI colour object
        * @return TGUI colour object
        */
        extern tgui::Color convertToTGUIColour(Colour color);

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
        extern Colour convertFrom3rdPartyColour(sf::Color thirdPartyColour);

        /**
        * @internal
        * @brief Convert pixels to metres
        * @param pixels The pixel value to be converted to metres
        * @return @a pixels in metres
        *
        * The conversion ratio is as follows:
        *  1 m = 30 pixels
        */
        extern float pixelsToMetres(float pixels);

        /**
        * @internal
        * @brief Convert pixels to metres
        * @param pixels The pixel value to be converted to metres
        * @return @a pixels in metres
        *
        * The conversion ratio is as follows:
        *  1 m = 30 pixels
        */
        extern Vector2f pixelsToMetres(Vector2f pixels);

        /**
        * @internal
        * @brief Convert metres to pixels
        * @param metres The metre value to be converted to pixels
        * @return @a metres in pixels
        *
        * The conversion ratio is as follows:
        *  1 m = 30 pixels
        */
        extern float metresToPixels(float metres);

        /**
        * @internal
        * @brief Convert metres to pixels
        * @param metres The metre value to be converted to pixels
        * @return @a metres in pixels
        *
        * The conversion ratio is as follows:
        *  1 m = 30 pixels
        */
        extern Vector2f metresToPixels(Vector2f metres);

        /**
        * @internal
        * @brief Convert radians to degrees
        * @param rad The radian value to be converted to degrees
        * @return @a rad in degrees
        */
        extern float radToDeg(float rad);

        /**
        * @internal
        * @brief Convert degrees to radians
        * @param deg The degrees value to be converted to radians
        * @return @a deg in radians
        */
        extern float degToRad(float deg);

        /**
        * @internal
        * @brief Check if an item exists or not in an unordered map
        * @param unorderedMap Map to search for item in
        * @param item Item to search for
        * @return True if item exists in the unordered map, otherwise false
        */
        template <typename T, typename U, typename V>
        bool findIn(const std::unordered_map<T, U>& unorderedMap, const V& item);

        /**
        * @internal
        * @brief Erase an item from the map
        * @param unorderedMap Map to remove item from
        * @param item Item to be removed
        * @return True if was removed in the unordered map, otherwise false
        */
        template <typename T, typename U, typename V>
        bool eraseIn(std::unordered_map<T, U>& unorderedMap, const V& item);

        /**
        * @internal
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
        * @internal
        * @brief Erase an element from a vector
        * @param vector Vector to remove element from
        * @param element Element to be removed
        * @return True if element was removed or false if element doesn't exist
        *         in the vector
        */
        template <typename T, typename U>
        bool eraseIn(std::vector<T>& vector, const U& element);

        /**
        * @internal
        * @brief Get a TGUI font
        * @param filename Filename of the font
        * @throws FileNotFound If the font cannot be found on the disk
        * @return TGUI font
        */
        extern tgui::Font get_TGUI_Font(const std::string& filename);

        /**
        * @internal
        * @brief Recursively search for a widget
        * @param container Container to recursively search
        * @param widgetName Name of the widget to search for
        * @return Pointer to the widget if found, otherwise a nullptr
        */
        extern std::shared_ptr<ui::Widget> findRecursively(
            const std::unordered_map<std::string, std::shared_ptr<ui::Widget>>& container,
            const std::string& widgetName);

        #include "Helpers.inl"
    }
}

#endif // IME_UTILITY_H
