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

#ifndef IME_RECTANGLESHAPE_H
#define IME_RECTANGLESHAPE_H

#include "IME/Config.h"
#include "IME/graphics/shapes/Shape.h"
#include <memory>

namespace ime {
    /**
     * @brief A 2D shape having four sides and four corners (90 degree angles)
     */
    class IME_API RectangleShape : public Shape {
    public:
        /**
         * @brief Default constructor
         * @param size The size of the rectangle
         */
        explicit RectangleShape(const Vector2f& size = Vector2f(0, 0));

        /**
         * @brief Copy constructor
         */
        RectangleShape(const RectangleShape&);

        /**
         * @brief Copy assignment operator
         */
        RectangleShape& operator=(const RectangleShape&);

        /**
         * @brief Move constructor
         */
        RectangleShape(RectangleShape&&) = default;

        /**
         * @brief Move assignment operator
         */
        RectangleShape& operator=(RectangleShape&&) = default;

        /**
         * @brief Set the size of the rectangle
         * @param size The new size of the rectangle
         */
        void setSize(const Vector2f& size);

        /**
         * @brief Get the size of th rectangle
         * @return The size of the rectangle
         */
        Vector2f getSize() const;

        /**
         * @brief Set the fill colour of the rectangle
         * @param colour The new colour of the rectangle
         *
         * By default, the rectangle's fill colour is opaque white.
         */
        void setFillColour(const Colour& colour) override;

        /**
         * @brief Get the fill colour of the rectangle
         * @return The fill colour of the rectangle
         */
        Colour getFillColour() const override;

        /**
         * @brief Set the outline colour of the rectangle
         * @param colour The new outline colour
         *
         * By default, the rectangle's outline colour is opaque white.
         */
        void setOutlineColour(const Colour& colour) override;

        /**
         * @brief Get the outline colour of the rectangle
         * @return The outline colour of the rectangle
         */
        Colour getOutlineColour() const override;

        /**
         * @brief Set the thickness of the rectangle's outline
         * @param thickness The new outline thickness
         *
         * Note that negative values are allowed (so that the outline
         * expands towards the center of the rectangle), and using zero
         * disables the outline.
         *
         * By default, the outline thickness is 0.
         */
        void setOutlineThickness(float thickness) override;

        /**
         * @brief Get the outline thickness of the rectangle
         * @return The outline thickness of the rectangle
         */
        float getOutlineThickness() const override;

        /**
         * @brief Get the local bounding rectangle of the rectangle
         * @return The local bounding rectangle of the rectangle
         *
         * The returned rectangle is in local coordinates, which means
         * that it ignores the transformations (translation, rotation,
         * scale, ...) that are applied to the entity
         */
        FloatRect getLocalBounds() const override;

        /**
         * @brief Get the global bounding rectangle of the rectangle
         * @return The global bounding rectangle of the rectangle
         *
         * The returned rectangle is in global coordinates, which means
         * that it takes into account the transformations (translation,
         * rotation, scale, ...) that are applied to the entity.
         * In other words, this function returns the bounds of the
         * rectangle in the global 2D world's coordinate system.
         */
        FloatRect getGlobalBounds() const override;
        
        /**
         * @brief Set the position of the rectangle
         * @param x X coordinate of the new position
         * @param y Y coordinate of the new position
         *
         * This function completely overwrites the previous position.
         * use move function to apply an offset based on the previous
         * position instead
         *
         * The default position of a the rectangle is (0, 0)
         *
         * @see move
         */
        void setPosition(float x, float y) override;

        /**
         * @brief Set the position of the rectangle
         * @param position New position
         *
         * This function completely overwrites the previous position.
         * Use the move function to apply an offset based on the previous
         * position instead.
         *
         * The default position of the rectangle is (0, 0)
         *
         * @see move
         */
        void setPosition(Vector2f position) override;

        /**
         * @brief Get the position of the rectangle
         * @return Current position of the rectangle
         */
        Vector2f getPosition() const override;

        /**
         * @brief Set the orientation of the rectangle
         * @param angle New rotation, in degrees
         *
         * This function completely overwrites the previous rotation.
         * See the rotate function to add an angle based on the previous
         * rotation instead.
         *
         * The default rotation of the rectangle is 0
         *
         * @see rotate
         */
        void setRotation(float angle) override;

        /**
         * @brief Rotate the rectangle
         * @param angle Angle of rotation, in degrees
         *
         * This function adds to the current rotation of the rectangle,
         * unlike setRotation which overwrites it
         *
         * @see setRotation
         */
        void rotate(float angle) override;

        /**
         * @brief Get the orientation of the rectangle
         * @return Current rotation, in degrees
         *
         * The rotation is always in the range [0, 360]
         */
        float getRotation() const override;

        /**
         * @brief Set the scale factors of the rectangle
         * @param factorX New horizontal scale factor
         * @param factorY New vertical scale factor
         *
         * This function completely overwrites the previous scale
         *
         * @see scale
         */
        void setScale(float factorX, float factorY) override;

        /**
         * @brief Set the scale factor of the rectangle
         * @param scale New scale
         *
         * This function completely overwrites the previous scale
         *
         * @see scale
         */
        void setScale(Vector2f scale) override;

        /**
         * @brief Scale the rectangle by an offset
         * @param factorX Horizontal scale factor
         * @param factorY Vertical scale factor
         *
         * This function multiplies the current scale of the rectangle,
         * unlike setScale which overwrites it
         *
         * @see setScale
         */
        void scale(float factorX, float factorY) override;

        /**
         * @brief Scale the rectangle by an offset
         * @param offset Offset to apply
         *
         * This function multiplies the current scale of the rectangle,
         * unlike setScale which overwrites it
         *
         * @see setScale
         */
        void scale(Vector2f offset) override;

        /**
         * @brief Get the current scale of the rectangle
         * @return Current scale of the rectangle
         */
        Vector2f getScale() const override;

        /**
         * @brief Set the local origin of the rectangle
         * @param x X coordinate of the new origin
         * @param y Y coordinate of the new origin
         *
         * The origin of the rectangle defines the center point for
         * all transformations (position, scale, rotation).
         * The coordinates of this point must be relative to the
         * top-left corner of the rectangle, and ignore all
         * transformations (position, scale, rotation).
         *
         * The default origin of the rectangle is (0, 0)
         */
        void setOrigin(float x, float y) override;

        /**
         * @brief Set the local origin of the rectangle
         * @param origin New origin
         *
         * The origin of the rectangle defines the center point for
         * all transformations (position, scale, rotation).
         * The coordinates of this point must be relative to the
         * top-left corner of the rectangle, and ignore all
         * transformations (position, scale, rotation).
         *
         * The default origin of the rectangle is (0, 0)
         */
        void setOrigin(Vector2f origin) override;

        /**
         * @brief Get the local origin of the rectangle
         * @return Local origin of the rectangle
         */
        Vector2f getOrigin() const override;

        /**
         * @brief Move the rectangle by a given offset
         * @param offsetX Horizontal offset
         * @param offsetY Vertical offset
         *
         * This function adds to the current position of the rectangle,
         * unlike setPosition which overwrites it
         *
         * @see setPosition
         */
        void move(float offsetX, float offsetY) override;

        /**
         * @brief Move the rectangle by a given offset
         * @param offset Offset to apply
         *
         * This function adds to the current position of the rectangle,
         * unlike setPosition which overwrites it
         *
         * @see setPosition
         */
        void move(Vector2f offset) override;

        /**
         * @brief Draw the rectangle on a render target
         * @param renderTarget Target to draw object on
         */
        void draw(Window &renderTarget) const override;

        /**
         * @brief Destructor
         */
        ~RectangleShape();
        
    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}

#endif //IME_RECTANGLESHAPE_H
