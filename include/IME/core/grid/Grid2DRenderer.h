////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#ifndef IME_GRID2DRENDERER_H
#define IME_GRID2DRENDERER_H

#include "IME/Config.h"
#include "IME/graphics/Colour.h"
#include "IME/common/Property.h"
#include <functional>

namespace ime {
    /**
     * @brief Defines the render properties of a Grid2D
     *
     * This class determines how a grid looks
     */
    class IME_API Grid2DRenderer {
    public:
        using Callback = std::function<void(const Property&)>; //!< Property change callback

        /**
         * @brief Default constructor
         */
        Grid2DRenderer();

        /**
         * @brief Set the colour of the grid tiles
         * @param colour The new colour of the grid tiles
         */
        void setTileColour(const Colour& colour);

        /**
         * @brief Get the colour of the grid tile
         * @return The colour of the grid tile
         */
        Colour getTileColour() const;

        /**
         * @brief Set the colour of a tile when it is collidable
         * @param colour The colour to set
         *
         * When the tile is no longer collidable, it will be set to the
         * normal tile colour
         *
         * @see setTileColour
         */
        void setCollidableTileColour(const Colour& colour);

        /**
         * @brief Get the colour of a grid tile when it is collidable
         * @return The colour of a collidable tile
         */
        Colour getCollidableTileColour() const;

        /**
         * @brief Set the colour of the
         * @param colour
         */
        void setGridLineColour(const Colour& colour);

        /**
         * @brief Get the colour of the grid lines colour
         * @return The colour of the grid lines
         */
        Colour getGridLineColour() const;

        /**
         * @brief Show or hide the grid
         * @param visible True to show it or false to hide it
         *
         * By default, the grid is visible
         */
        void setVisible(bool visible);

        /**
         * @brief Check if the grid is visible or not
         * @return True if the grid is visible, otherwise false
         */
        bool isVisible() const;

        /**
         * @brief Toggle the visibility of the grid
         *
         * This function will show the grid if it is currently visible
         * or hide it if its currently visible
         */
        void toggleVisibility();

        /**
         * @internal
         * @brief Get notified every time a property of the renderer changes
         * @param callback The function to be executed when a property changes
         *
         * Note that only one callback may be registered at a time. That is,
         * passing a new callback overwrites the previous callback. Pass
         * nullptr to remove the current callback
         *
         * @note This function is intended for internal use only
         */
        void onPropertyChange(const Callback& callback);

    private:
        /**
         * @brief Emit a property change event
         * @param property The property to emit
         */
        void emit(const Property& property);

    private:
        Colour tileColour_;           //!< The colour of each non-collidable tile in the grid
        Colour collidableTileColour_; //!< The colour of each collidable tile in the grid
        Colour gridLinesColour_;      //!< The colour of the grid lines of the grid
        bool isVisible_;              //!< A flag indicating whether or not the grid is visible
        Callback onPropertyChange_;   //!< Property change event emitter
    };
}

#endif //IME_GRID2DRENDERER_H
