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

#ifndef IME_TILE_H
#define IME_TILE_H

#include "IME/core/tilemap/Index.h"
#include "IME/common/Vector2.h"
#include "IME/graphics/shapes/RectangleShape.h"
#include "IME/graphics/IDrawable.h"
#include <unordered_map>
#include <memory>

namespace ime {
    /**
     * @brief A Tilemap tile
     */
    class IME_API Tile : public IDrawable {
    public:
        /**
         * @internal
         * @brief Controls access to some public member functions
         *
         * This is known as the Passkey idiom. It restricts the use of public
         * member functions to any class that can instantiate a Passkey. We
         * control which classes can instantiate a passkey by granting them
         * friendship to the Passkey class and not the class of interest. This
         * way the two classes (class that needs access to something from another
         * class and the class that contains the needed thing) are decoupled from
         * one another. Traditionally, you would make the member functions private
         * and grant friendship to the classes that need access to those functions.
         * However, this kind of friendship grants access to not only the information
         * of interest but to everything including private implementation
         */
        class TilePassKey final : utility::NonCopyable {
            TilePassKey(){};
            friend class TileMap;
            friend class Tile;
        };

        /**
         * @internal
         * @brief Construct a tile
         * @param size Size of the tile
         * @param position Position of the tile
         *
         * @warning This function is intended for internal use only
         */
        explicit Tile(Vector2u size, Vector2f position);

        /**
         * @brief Get the name of this class
         * @return The name of this class
         */
        std::string getClassName() const override;

        /**
         * @internal
         * @brief Set the fill colour of the tile
         * @param colour New fill colour of the tile
         *
         * @note This function is intended for internal use only
         */
        void setFillColour(const Colour& colour, TilePassKey);

        /**
         * @brief Get the tiles fill colour
         * @return The tiles fill colour
         */
        Colour getFillColour() const;

        /**
         * @internal
         * @brief Set the position of the tile
         * @param x X coordinate of the tile
         * @param y Y coordinate of the tile
         *
         * @note This function is intended for internal use only
         */
        void setPosition(float x, float y, TilePassKey);

        /**
         * @internal
         * @brief Set the position of the tile in coordinates
         * @param position Position to set
         *
         * @note This function is intended for internal use only
         */
        void setPosition(Vector2f position, TilePassKey);

        /**
         * @brief Get the position of the tile
         * @return The position of the tile
         */
        Vector2f getPosition() const;

        /**
         * @brief Get the tile's centre point in world coordinates
         * @return The tiles centre point in world coordinates
         */
        Vector2f getWorldCentre() const;

        /**
         * @brief Get the tile's centre point in local coordinates
         * @return The tiles centre point in local coordinates
         */
        Vector2f getLocalCentre() const;

        /**
         * @internal
         * @brief Set the size of the tile
         * @param width The horizontal size
         * @param height The vertical size
         *
         * @note This function is intended for internal use only
         */
        void setSize(unsigned int width, unsigned int height, TilePassKey);

        /**
         * @internal
         * @brief Set the size of the tile
         * @param size New tile size
         *
         * @note This function is intended for internal use only
         */
        void setSize(Vector2u size, TilePassKey);

        /**
         * @brief Get the size of the tile
         * @return The size of the tile
         */
        Vector2u getSize() const;

        /**
         * @internal
         * @brief Set the index of the tile in the tilemap
         * @param index The index of the tile in the tilemap
         *
         * The index corresponds to the position of the tile in the tilemap
         *
         * @note This function is intended for internal use only
         */
        void setIndex(Index index, TilePassKey);

        /**
         * @brief Get the index of the tile in the tilemap
         * @return The index of the tile in the tilemap
         */
        Index getIndex() const;

        /**
         * @internal
         * @brief Assign the tile an identification token
         * @param id Identification token to assign
         *
         * The id is an empty character by default
         *
         * @note This function is intended for internal use only
         */
        void setId(char id, TilePassKey);

        /**
         * @brief Get the tiles id
         * @return The tiles id
         */
        char getId() const;

        /**
         * @brief Set whether or not the tile is collidable
         * @param collidable True to set collidable. otherwise false
         *
         * The tile is collidable or not collidable on all sides depending on
         * the value of @a collidable
         */
        void setCollidable(bool collidable);

        /**
         * @brief Check if tile is collidable on all sides or not
         * @return True if tile is collidable on all sides, otherwise false
         *
         * @see setCollidable
         */
        bool isCollidable() const;

        /**
         * @internal
         * @brief Draw the tile on a render target
         * @param renderTarget Render target to draw tile on
         *
         * @warning This function is intended for internal use only and
         * should never be called outside of IME
         */
        void draw(Window &renderTarget) const override;

        /**
         * @internal
         * @brief Show or hide the tile
         * @param visible True to show or false to hide
         *
         * When hidden the tile will not be shown on the render target
         *
         * By default, the tile is visible
         *
         * @note This function is intended for internal use only
         */
        void setVisible(bool visible, TilePassKey);

        /**
         * @brief Check whether or not the tile is visible
         * @return True if visible, otherwise false
         */
        bool isVisible() const;

        /**
         * @internal
         * @brief Toggle the visibility of the tile
         *
         * This function will hide the tile if its currently
         * visible or show it if it is currently hidden
         *
         *  @note This function is intended for internal use only
         */
        void toggleVisibility(TilePassKey);

        /**
         * @brief Check if tile contains pixel coordinates
         * @param x X coordinate to be checked
         * @param y Y coordinate to be checked
         * @return True if the tile contains the pixel coordinates, otherwise
         *         false
         */
        bool contains(float x, float y) const;

    private:
        bool isCollidable_;     //!< A flag indicating whether or not the tile is collidable
        char id_;               //!< Tile id
        Index index_;           //!< Position of the tile in the tilemap
        RectangleShape tile_;   //!< Tile reset
        Colour prevFillColour_; //!< Tiles fill colour before it was hidden
    };
}

#endif // IME_TILE_H
