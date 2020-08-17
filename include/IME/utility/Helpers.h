/**
 * @brief Helper functions
 */

#ifndef UTILITY_H
#define UTILITY_H

#include "IME/gui/common/Colour.h"
#include <SFML/Graphics/Color.hpp>
#include <unordered_map>

namespace IME {
    namespace Utility{
        /**
         * @brief Convert own Colour object to graphics library colour object
         * @param colour Colour to be converted to graphics library colour object
         * @return Graphics library colour object
         *
         * This function only converts the object and not the actual
         * colour. This means that the colour after the conversion is
         * the same as the one before the conversion
         */
        static sf::Color convertTo3rdPartyColour(Gui::Colour color){
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
        static Gui::Colour convertFrom3rdPartyColour(sf::Color thirdPartyColour){
            return {thirdPartyColour.r, thirdPartyColour.g, thirdPartyColour.b, thirdPartyColour.a};
        }

        template <typename T, typename U, typename V>
        bool findIn(const std::unordered_map<T, U>& unorderedMap, const V& item){
            return unorderedMap.find(item) != unorderedMap.end();
        }
    }
}

#endif
