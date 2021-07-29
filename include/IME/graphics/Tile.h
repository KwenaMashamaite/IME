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
        Tile(Tile&&) noexcept = default;

        /**
         * @brief Move assignment operator
         */
        Tile& operator=(Tile&&) noexcept = default;

        /**
         * @brief Set the position of the tile
         * @param x X coordinate of the tile
         * @param y Y coordinate of the tile
         *
         * By default, the position is (0, 0)
         */
        void setPosition(float x, float y);

        /**
         * @brief Set the position of the tile
         * @param pos The new position of the tile
         *
         * By default, the position is (0, 0)
         */
        void setPosition(Vector2f pos);

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
         * @brief Show or hide the tile
         * @param visible True to show or false to hide
         *
         * When hidden the tile will not be shown on the render target,
         * However it can still be collided with if its collidable
         *
         * By default, the tile is visible
         *
         * @see setCollidable
         */
        void setVisible(bool visible);

        /**
         * @brief Check whether or not the tile is visible
         * @return True if visible, otherwise false
         */
        bool isVisible() const;

        /**
         * @brief Set the index of the tile in the tilemap
         * @param index The index of the tile in the tilemap
         *
         * The index corresponds to the position of the tile in the tilemap
         *
         * By default, the index is (-1, -1)
         */
        void setIndex(Index index);

        /**
         * @brief Get the index of the tile in the tilemap
         * @return The index of the tile in the tilemap
         *
         * Note that each tile in the tilemap has a unique index
         */
        Index getIndex() const;

        /**
         * @brief Assign the tile an identification token
         * @param id Identification token to assign
         *
         * By default, the tile id is '\0'
         *
         * Note that multiple tiles can have the same identification token
         */
        void setId(char id);

        /**
         * @brief Get the id of the tile
         * @return The id of the tile
         */
        char getId() const;

        /**
         * @brief Set whether tile is collidable or not
         * @param collidable True to set collidable, otherwise false
         *
         * Note that disabling a collision for a tile that was previously
         * had a Collider attached to it does not remove the collider. This
         * removes the need to create a new collider everytime the collidability
         * of the tile is re-enabled. The collider can be explicitly removed
         * from the tile by calling the removeCollider() function
         *
         * By default, the tile is not collidable
         *
         * @see attachCollider
         */
        void setCollidable(bool collidable);

        /**
         * @brief Check if the tile is collidable or not
         * @return True if the tile is collidable, otherwise false
         */
        bool isCollidable() const;

        /**
         * @brief Set the fill colour of the tile
         * @param colour New fill colour of the tile
         */
        void setFillColour(const Colour& colour);

        /**
         * @brief Get the fill colour of the tile
         * @return The fill colour of the tile
         */
        Colour getFillColour() const;

        /**
         * @brief Get the name of this class
         * @return The name of this class
         */
        std::string getClassName() const override;

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
         * @brief Check if the tile contains a world coordinate
         * @param point The point (in world coordinates) to be checked
         * @return True if the tile contains the coordinates, otherwise
         *         false
         */
        bool contains(Vector2f point) const;

        /**
         * @brief Add a collider to the tile
         * @param collider The collider to be added
         *
         * Without a Collider, only game objects that are controlled by a
         * GridMover can collide with the tile. Attaching a collider makes
         * a GameObject with a RigidBody that has a Collider attached to it
         * able to collide with the tile. The tile can can only have one
         * collider attached to it. The current collider must be removed first
         * before attaching a new one
         *
         * By default, the tile does not have a collider attached to it
         *
         * @warning A RigidBody is required before attaching a Collider,
         * doing so without a RigidBody is undefined behavior. Use the
         * setBody() function to add a RigidBody
         *
         * @see removeCollider and hasCollider
         */
        void attachCollider(std::unique_ptr<BoxCollider> collider);

        /**
         * @brief Remove the collider added to the tile
         *
         * Note that when the collider is removed, the tile will no longer
         * participate in RigidBody physics, however grid-based physics
         * (see ime::GridMover) will continue as normal.
         *
         * @see attachCollider and hasCollider
         */
        void removeCollider();

        /**
         * @brief Check if the tile has a collider or not
         * @return True if the tile has a collider, otherwise false
         */
        bool hasCollider() const;

        /**
         * @brief Toggle the visibility of the tile
         *
         * This function will hide the tile if its currently
         * visible or show it if it is currently hidden
         */
        void toggleVisibility();

        /**
         * @brief Swap the contents of this tile with that of another tile
         * @param other The tile to swap contents with
         */
        void swap(Tile& other);

        /**
         * @brief Set the tiles RigidBody
         * @param body The physics body to set
         *
         * The rigid body is only required if you intend to attach a Collider.
         * The rigid body must be of type ime::RigidBody::Type::Static
         *
         * @see attachCollider
         */
        void setBody(RigidBody::Ptr body);

        /**
         * @internal
         * @brief Draw the tile on a render target
         * @param renderTarget Render target to draw tile on
         *
         * @note This function is intended for internal use only
         */
        void draw(priv::RenderTarget &renderTarget) const override;

        /**
         * @brief Destructor
         */
        ~Tile() override;

    private:
        char id_;               //!< Tile id
        Index index_;           //!< Position of the tile in the tilemap
        RectangleShape tile_;   //!< Tile
        Colour prevFillColour_; //!< Tiles fill colour before it was hidden
        bool isCollidable_;     //!< A flag indicating whether or not the tile is collidable
    };
}

#endif // IME_TILE_H
