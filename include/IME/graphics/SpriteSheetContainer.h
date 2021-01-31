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

#ifndef IME_SPRITESHEETCONTAINER_H
#define IME_SPRITESHEETCONTAINER_H

#include "IME/Config.h"
#include "IME/graphics/SpriteSheet.h"
#include <unordered_map>
#include <string>

namespace ime {
    /**
     * @brief Container for spritesheets
     */
    class IME_API SpriteSheetContainer {
    public:
        /**
         * @brief Add a spritesheet
         * @param spritesheet Sprite to be added
         * @return True if the spritesheet was added or false if a
         *         spritesheet with the same name as the given
         *         spritesheet already exists
         *
         * @warning The spritesheet must be created first
         */
        bool add(SpriteSheet spritesheet);

        /**
         * @brief Get a spritesheet
         * @param name Name of the spritesheet
         * @return The spritesheet with the specified name
         *
         * @warning The spritesheet must exist in the container before
         * this function is called, otherwise the behavior is undefined
         *
         * @see contains
         */
        const SpriteSheet& get(const std::string& name) const;

        /**
         * @brief Check whether or not the container has a spritesheet
         * @param name Name of the spritesheet to be checked
         * @return True if the spritesheet exists, otherwise false
         */
        bool contains(const std::string& name) const;

        /**
         * @brief Remove a spritesheet
         * @param name Name of the spritesheet to be removed
         * @return True if the spritesheet was removed, or false if the
         *         spritesheet does not exist
         */
        bool remove(const std::string& name);

    private:
        std::unordered_map<std::string, SpriteSheet> spritesheets_;
    };
}

#endif //IME_SPRITESHEETCONTAINER_H
