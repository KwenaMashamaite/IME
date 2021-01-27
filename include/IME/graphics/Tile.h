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

#include "IME/core/event/EventEmitter.h"
#include "IME/core/tilemap/Index.h"
#include "IME/common/Vector2.h"
#include "IDrawable.h"
#include "Sprite.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <unordered_map>
#include <memory>

namespace ime {
    /**
     * @brief Represents a tile in the tilemap
     */
    class IME_API Tile : public IDrawable {
    public:
        /**
         * @brief Construct a tile
         * @param size Size of the tile
         * @param position Position of the tile
         */
        Tile(const Vector2u &size, const Vector2f &position);

        /**
         * @brief Copy constructor
         */
        Tile(const Tile &) = default;

        /**
         * @brief Assignment operator
         */
        Tile &operator=(const Tile &) = default;

        /**
         * @brief Move constructor
         */
        Tile(Tile &&) = default;

        /**
         * @brief Move assignment operator
         */
        Tile &operator=(Tile &&) = default;

        /**
         * @brief Add a sprite to the tile
         * @param sprite Sprite to be added
         *
         * The tile can only contain a single sprite. Therefore, subsequent
         * calls to this function will replace the previous sprite
         */
        void addSprite(Sprite sprite);

        /**
         * @brief Get the sprite set on the tile
         * @return Sprite on the tile
         */
        Sprite &getSprite();

        /**
         * @brief Set the fill colour of the tile
         * @param colour New fill colour of the tile
         */
        void setFillColour(const Colour& colour);

        /**
         * @brief Get the tiles fill colour
         * @return The tiles fill colour
         */
        Colour getFillColour() const;

        /**
         * @brief Set the position of the tile
         * @param x X coordinate of the tile
         * @param y Y coordinate of the tile
         */
        void setPosition(float x, float y);

        /**
         * @brief Set the position of the tile in coordinates
         * @param position Position to set
         */
        void setPosition(Vector2f position);

        /**
         * @brief Get the position of the tile
         * @return The position of the tile
         */
        Vector2f getPosition() const;

        /**
         * @brief Set the size of the tile
         * @param width The horizontal size
         * @param height The vertical size
         */
        void setSize(unsigned int width, unsigned int height);

        /**
         * @brief Set the size of the tile
         * @param size New tile size
         */
        void setSize(Vector2u size);

        /**
         * @brief Get the size of the tile
         * @return The size of the tile
         */
        Vector2u getSize() const;

        /**
         * @brief Set the visibility of the tile border
         * @param isVisible True to set visible, otherwise false
         */
        void setBorderVisible(bool isVisible);

        /**
         * @brief Set the index of the tile in the tilemap
         * @param index The index of the tile in the tilemap
         *
         * The index corresponds to the position of the tile in the tilemap
         *
         * @warning This function is called by the tilemap and should never
         * be called directly if the tile is part of a tilemap
         */
        void setIndex(Index index);

        /**
         * @brief Get the index of the tile in the tilemap
         * @return The index of the tile in the tilemap
         */
        Index getIndex() const;

        /**
         * @brief Assign the tile an identification token
         * @param id Identification token to assign
         *
         * The id is an empty character by default
         */
        void setId(char id);

        /**
         * @brief Get the tiles id
         * @return The tiles id
         */
        char getId() const;

        /**
         * @brief Set whether the tile is a solid or an empty tile
         * @param isSolid True to set solid or false to set empty
         *
         * Solid tiles are collidable while empty tiles are not collidable.
         * The tile is empty by default
         */
        void setSolid(bool isSolid);

        /**
         * @brief Check if tile is a solid or an empty tile
         * @return True if solid or false if empty
         */
        bool isSolid() const;

        /**
         * @brief Render tile
         * @param renderTarget Target to render tile on
         */
        void draw(Window &renderTarget) const override;

        /**
         * @brief Show or hide the tile
         * @param visible True to show or false to hide
         *
         * When hidden the tile will not be shown on the render target
         *
         * By default, the tile is visible
         */
        void setVisible(bool visible);

        /**
         * @brief Check whether or not the tile is visible
         * @return True if visible, otherwise false
         */
        bool isVisible() const;

        /**
         * @brief Toggle the visibility of the tile
         *
         * This function will hide the tile if its currently
         * visible or show it if it is currently hidden
         */
        void toggleVisibility();

        /**
         * @brief Check if tile is collidable on all sides or not
         * @return True if tile is collidable on all sides, otherwise false
         */
        bool isCollidable() const;

        /**
         * @brief Check if tile contains pixel coordinates
         * @param x X coordinate to be checked
         * @param y Y coordinate to be checked
         * @return True if the tile contains the pixel coordinates, otherwise
         *         false
         */
        bool contains(float x, float y) const;

        /**
         * @brief Destructor
         */
        ~Tile() = default;

    private:
        bool isSolid_;             //!< Stores whether tile is a solid or an empty tile
        char id_;                  //!< Tile id
        Index index_;              //!< Position of the tile in the tilemap
        Sprite sprite_;            //!< Tile texture representation
        sf::RectangleShape tile_;  //!< Tile
        sf::Color prevFillColour_; //!< Tiles fill colour before it was hidden
    };
}

#endif // IME_TILE_H
