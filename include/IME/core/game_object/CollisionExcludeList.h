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

#ifndef IME_COLLISIONEXCLUDELIST_H
#define IME_COLLISIONEXCLUDELIST_H

#include "IME/Config.h"
#include <string>
#include <unordered_set>

namespace ime {
    /**
     * @brief A GameObject collision exclusion list
     *
     * This class allows a GameObject to select which other game objects
     * it should not collide with
     */
    class IME_API CollisionExcludeList {
    public:
        /**
         * @brief Add a group to the list
         * @param group The name of the group to be added
         */
        void add(const std::string& group);

        /**
         * @brief Remove a group from the list
         * @param group The name of the group to be removed
         * @return True if the group was removed from the list or false
         *         if it does not exist
         */
        bool remove(const std::string& group);

        /**
         * @brief Check if the list has a group or not
         * @param group The name of the group to be checked
         * @return True if the group exits in the list, otherwise false
         */
        bool contains(const std::string& group);

        /**
         * @brief Get the number of groups in the list
         * @return The number of groups in the list
         */
        std::size_t getCount() const;

        /**
         * @brief Remove all groups from the list
         */
        void clear();

    private:
        std::unordered_set<std::string> list_; //!< List container
    };
}

#endif //IME_COLLISIONEXCLUDELIST_H
