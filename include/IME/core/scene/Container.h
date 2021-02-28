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

#ifndef IME_CONTAINER_H
#define IME_CONTAINER_H

#include "IME/graphics/Window.h"
#include "IME/core/game_object/GameObject.h"
#include <memory>
#include <vector>
#include <algorithm>

namespace ime {
    /**
     * @brief Base class for items contained in a Scene
     */
    template <typename T>
    class Container {
    public:
        using ItemPtr = std::shared_ptr<T>;
        using constItemPtr = std::shared_ptr<const T>;
        using constIterator = typename std::vector<ItemPtr>::const_iterator;

        template <typename... Args>
        using Callback = std::function<void(Args...)>;
        using Predicate = std::function<bool(const constItemPtr)>;
        
        /**
         * @brief Add an item to the container
         * @param item Item to be added
         * 
         * @note This class does not check for duplicates
         */
        void add(ItemPtr item);

        /**
         * @brief Conditionally find an item in the container
         * @param predicate A function which returns true if the item should
         *                  be returned or false if the search should continue
         * @return The item that matches the found condition or a nullptr if
         *         an item that matches the success condition could not be
         *         found in the container
         */
        ItemPtr findIf(Predicate predicate);
        const ItemPtr findIf(Predicate predicate) const;

        /**
         * @brief Remove a item form the container
         * @param item The item to be removed
         * @return True if the item was removed or false if the item does
         *         not exist in the container
         */
        bool remove(ItemPtr item);

        /**
         * @brief Conditionally remove items from the container
         * @param predicate A function which returns true if the object should
         *                 be removed or false if it should not be removed
         *                 from the container
         * @return True if the items were removed from the container or false
         *         if no items matched the remove condition
         */
        bool removeIf(Predicate predicate);

        /**
         * @brief Remove all items from the container
         */
        void removeAll();

        /**
         * @brief Get the number of items in the container
         * @return The number of items in the container
         */
        std::size_t getCount() const;

        /**
         * @brief Execute a callback function for each item in the container
         * @param callback The function to be executed
         */
        void forEach(Callback<ItemPtr> callback);

        /**
         * @brief Get a constant iterator that points to the first element in
         *         the container
         * @return A constant iterator to the first element
         */
        constIterator cbegin() const;

        /**
         * @brief Get a constant iterator that points one past the last element
         *         in the container
         * @return A constant iterator one past the last element
         *
         *
         */
        constIterator cend() const;

        /**
         * @brief Destructor
         */
        virtual ~Container() = default;

    private:
        std::vector<ItemPtr> items_;
    };

    #include "IME/core/scene/Container.inl"
}

#endif //IME_CONTAINER_H
