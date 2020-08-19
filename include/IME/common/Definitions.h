/**
 * @brief
 */

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <string>

namespace IME {
    namespace Definitions {
        /**
         * @brief Dimensions
         */
        struct Dimensions {
            float width;
            float height;
        };

        /**
         * @brief Position
         */
        struct Position {
            float x;
            float y;
        };


        /**
         * @brief Property
         */
        struct Property {
            std::string name;
            std::string type;
            std::string value;

            /**
             * @brief Equality comparison operator
             */
            bool operator==(const Property& other) {
                return name == other.name
                    && type == other.type
                    && value== other.value;
            }

            /**
             * @brief
             */
            bool operator!=(const Property& other) {
                return name != other.name;
            }
        };

        /**
         * @brief Object type
         */
        struct Type {
            std::string type;
        };

        // Resource file path
        struct FilePath {
            static constexpr auto TexturesPath = "resources/textures/";
            static constexpr auto SoundEffectsPath = "resources/soundEffects/";
            static constexpr auto MusicPath = "resources/music/";
            static constexpr auto FontsPath = "resources/fonts/";
            static constexpr auto ImagesPath = "resources/textures/";
            static constexpr auto SettingsPath = "files/";
        };
    }  // namespace IME
} // namespace IME

#endif
