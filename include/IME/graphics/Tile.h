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
#include "IME/graphics/Drawable.h"
#include <unordered_map>
#include <memory>

namespace ime {
    class BoxCollider;

    /**
     * @brief A Tilemap tile
     */
    class IME_API Tile : public Drawable {
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
        class TilePassKey final {
            TilePassKey(){};
            TilePassKey(const TilePassKey&) = delete;
            TilePassKey& operator=(const TilePassKey&) = delete;

            // Classes that have access to restricted public member functions
            friend class TileMap;
            friend class Tile;
        };

        /**
         * @brief Construct a tile
         * @param size Size of the tile
         * @param position Position of the tile
         */
        Tile(Vector2u size, Vector2f position);

        /**
         * @brief Copy constructor
         */
        Tile(const Tile&);

        /**
         * @brief Copy assignment operator
         */
        Tile& operator=(Tile);

        /**
         * @brief Move constructor
         */
        Tile(Tile&&) noexcept;

        /**
         * @brief Move assignment operator
         */
        Tile& operator=(Tile&&) noexcept;

        /**
         * @brief Get the name of this class
         * @return The name of this class
         */
        std::string getClassName() const override;

        /**
         * @brief Get the size of the tile
         * @return The size of the tile
         */
        Vector2u getSize() const;

        /**
         * @brief Get the fill colour of the tile
         * @return The fill colour of the tile
         */
        Colour getFillColour() const;

        /**
         * @brief Get the position of the tile
         * @return The position of the tile
         */
        Vector2f getPosition() const;

        /**
         * @brief Get the tile's centre point in local coordinates
         * @return The tiles centre point in local coordinates
         */
        Vector2f getLocalCentre() const;

        /**
         * @brief Get the tile's centre point in world coordinates
         * @return The tiles centre point in world coordinates
         */
        Vector2f getWorldCentre() const;

        /**
         * @brief Get the index of the tile in the Tilemap
         * @return The index of the tile in the tilemap
         */
        Index getIndex() const;

        /**
         * @brief Get the id of the tile
         * @return The id of the tile
         */
        char getId() const;

        /**
         * @brief Check if the tile is collidable or not
         * @return True if the tile is collidable, otherwise false
         */
        bool isCollidable() const;

        /**
         * @brief Check if the tile contains a world coordinate
         * @param point The point (in world coordinates) to be checked
         * @return True if the tile contains the coordinates, otherwise
         *         false
         */
        bool contains(Vector2f point) const;

        /**
         * @internal
         * @brief Set the fill colour of the tile
         * @param colour New fill colour of the tile
         *
         * @note This function is intended for internal use only
         */
        void setFillColour(const Colour& colour, TilePassKey);

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
         * @internal
         * @brief Set whether or not the tile is collidable
         * @param collidable True to set collidable. otherwise false
         *
         * Note that disabling a collision for a tile that was previously
         * collidable does not remove the tiles collider, This may be
         * useful if the collision will be re-enabled at a later time. You
         * can explicitly remove the collider by calling the removeCollider
         * function
         *
         * @note This function is intended for internal use only
         *
         * @see setCollidable and removeCollider
         */
        void setCollidable(bool collidable, TilePassKey);

        /**
         * @internal
         * @brief Add a collider to the tile
         * @param collider The collider to be added
         *
         * @warning It is required that all tilemap tiles that are collidable
         * have a collider attached to them. The collider must be attached to
         * a static rigid body. Providing a collider that is not attached to a
         * rigid body is undefined behavior. In addition calling the function
         * setCollidable with an argument of true on a tile without a collider
         * is undefined behavior.
         *
         * Note that a tile can only have one collider attached to it. You
         * have to remove the previous collider first if you want to attach
         * a new one
         *
         * @note This function is intended for internal use only
         *
         * @see removeCollider and hasCollider
         */
        void attachCollider(std::shared_ptr<BoxCollider> collider);

        /**
         * @internal
         * @brief Remove the collider added to the tile
         *
         * Note that if the tile is collidable and the collider is removed,
         * it will no longer be collidable. This function has no effect if
         * the tile does not have a collider attached to it
         *
         * @note This function is intended for internal use only
         *
         * @see setCollidable and hasCollider
         */
        void removeCollider(TilePassKey);

        /**
         * @internal
         * @brief Check if the tile has a collider or not
         * @return True if the tile has a collider, otherwise false
         *
         * @note This function is intended for internal use only
         */
        bool hasCollider() const;

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
         * @internal
         * @brief Check whether or not the tile is visible
         * @return True if visible, otherwise false
         *
         * @note This function is intended for internal use only
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
         * @brief Destructor
         */
        ~Tile();

    private:
        /**
         * @brief Swap the contents of this tile with that of another tile
         * @param other The tile to swap contents with
         */
        void swap(Tile& other);

    private:
        bool isCollidable_;     //!< A flag indicating whether or not the tile is collidable
        char id_;               //!< Tile id
        Index index_;           //!< Position of the tile in the tilemap
        RectangleShape tile_;   //!< Tile reset
        Colour prevFillColour_; //!< Tiles fill colour before it was hidden
        std::shared_ptr<BoxCollider> collider_; //!< The tiles collider
    };
}

#endif // IME_TILE_H
