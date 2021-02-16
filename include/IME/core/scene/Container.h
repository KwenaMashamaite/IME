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
#include "IME/core/entity/Entity.h"
#include <memory>
#include <vector>

namespace ime {
    /**
     * @brief Base class for items contained in a Scene
     */
    template <typename T>
    class Container {
    public:
        using Item = std::shared_ptr<T>; //!< Shared item pointer
        using constIterator = typename std::vector<Item>::const_iterator;

        template <typename... Args>
        using Callback = std::function<void(Args...)>; //!< Event listener
        
        /**
         * @brief Add an item to the container
         * @param item Item to be added
         * 
         * @note This class does not check for duplicates
         */
        void add(Item item);
        
        /**
         * @brief Remove a item form the container
         * @param item The item to be removed
         * @return True if the item was removed or false if the item does
         *         not exist in the container
         */
        bool remove(Item item);

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
         * @brief Render all the items on a render target
         * @param window The window to render the items on
         * @param preRenderCallback Optional callback that is called before
         *        an item is rendered to the given render target
         *
         * You'll have to call this function yourself because we don't
         * know if the items should be rendered to the background or
         * foreground of the scene
         */
        void render(Window& window, Callback<Item> preRenderCallback = nullptr);

        /**
         * @brief Execute a callback function for each item in the container
         * @param callback The function to be executed
         */
        void forEach(Callback<Item> callback);

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
        std::vector<Item> items_;
    };

    #include "IME/core/scene/Container.inl"
}

#endif //IME_CONTAINER_H
