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

#ifndef IME_CONVEXSHAPE_H
#define IME_CONVEXSHAPE_H

#include "IME/Config.h"
#include "IME/graphics/shapes/Shape.h"
#include <memory>

namespace ime {
    /**
     * @brief A convex shape
     */
    class IME_API ConvexShape : public Shape {
    public:
        using Ptr = std::shared_ptr<ConvexShape>; //!< Shared shape pointer

        /**
         * @brief Default constructor
         * @param pointCount The number of points of the polygon
         */
        explicit ConvexShape(std::size_t pointCount = 0);

        /**
         * @brief Copy constructor
         */
        ConvexShape(const ConvexShape&);

        /**
         * @brief Copy assignment operator
         */
        ConvexShape& operator=(const ConvexShape&);

        /**
         * @brief Move constructor
         */
        ConvexShape(ConvexShape&&) noexcept;

        /**
         * @brief Move assignment operator
         */
        ConvexShape& operator=(ConvexShape&&) noexcept;

        /**
         * @brief Create a new convex shape
         * @param pointCount The number of points of the polygon
         * @return The created convex shape shape
         */
        static ConvexShape::Ptr create(std::size_t pointCount = 0);

        /**
         * @brief Set the number of points of the polygon
         * @param count The new number of points of the polygon
         * 
         * @note @a count must be greater than 2 to define a valid shape
         */
        void setPointCount(std::size_t count);
        
        /**
         * @brief Get the number of points of the polygon
         * @return The number of points of the polygon
         */
        std::size_t getPointCount() const;
        
        /**
         * @brief Set the position of a point
         * @param index Index of the point to change, in range [0 .. getPointCount() - 1]
         * @param point New position of the point
         * 
         * @warning The polygon must remain convex, and the points need to 
         * stay ordered!. setPointCount must be called first in order to set 
         * the total number of points. The result is undefined if @a index 
         * is out of the valid range
         * 
         * @see getPointCount
         */
        void setPoint(std::size_t index, const Vector2f& point);
        
        /**
         * @brief Get the position of a point
         * @param index Index of the point to get, in range [0 .. getPointCount() - 1]
         * @return Position of the index-th point of the polygon
         * 
         * The returned point is in local coordinates, that is,  the shape's 
         * transforms (position, rotation, scale) are not taken into account
         *
         * @warning The result is undefined if @a index is out of the valid
         * range
         *
         * @see setPointCount
         */
        Vector2f getPoint(std::size_t index) const;

        /**
         * @brief Set the fill colour of the polygon
         * @param colour The new colour of the polygon
         *
         * By default, the polygon's fill colour is opaque white.
         */
        void setFillColour(const Colour& colour) override;

        /**
         * @brief Get the fill colour of the polygon
         * @return The fill colour of the polygon
         */
        Colour getFillColour() const override;

        /**
         * @brief Set the outline colour of the polygon
         * @param colour The new outline colour
         *
         * By default, the polygon's outline colour is opaque white.
         */
        void setOutlineColour(const Colour& colour) override;

        /**
         * @brief Get the outline colour of the polygon
         * @return The outline colour of the polygon
         */
        Colour getOutlineColour() const override;

        /**
         * @brief Set the thickness of the polygon's outline
         * @param thickness The new outline thickness
         *
         * Note that negative values are allowed (so that the outline
         * expands towards the center of the polygon), and using zero
         * disables the outline.
         *
         * By default, the outline thickness is 0.
         */
        void setOutlineThickness(float thickness) override;

        /**
         * @brief Get the outline thickness of the polygon
         * @return The outline thickness of the polygon
         */
        float getOutlineThickness() const override;

        /**
         * @brief Get the local bounding polygon of the polygon
         * @return The local bounding polygon of the polygon
         *
         * The returned polygon is in local coordinates, which means
         * that it ignores the transformations (translation, rotation,
         * scale, ...) that are applied to the entity
         */
        FloatRect getLocalBounds() const override;

        /**
         * @brief Get the global bounding polygon of the polygon
         * @return The global bounding polygon of the polygon
         *
         * The returned polygon is in global coordinates, which means
         * that it takes into account the transformations (translation,
         * rotation, scale, ...) that are applied to the entity.
         * In other words, this function returns the bounds of the
         * polygon in the global 2D world's coordinate system.
         */
        FloatRect getGlobalBounds() const override;

        /**
         * @brief Set the position of the polygon
         * @param x X coordinate of the new position
         * @param y Y coordinate of the new position
         *
         * This function completely overwrites the previous position.
         * use move function to apply an offset based on the previous
         * position instead
         *
         * The default position of a the polygon is (0, 0)
         *
         * @see move
         */
        void setPosition(float x, float y) override;

        /**
         * @brief Set the position of the polygon
         * @param position New position
         *
         * This function completely overwrites the previous position.
         * Use the move function to apply an offset based on the previous
         * position instead.
         *
         * The default position of the polygon is (0, 0)
         *
         * @see move
         */
        void setPosition(Vector2f position) override;

        /**
         * @brief Get the position of the polygon
         * @return Current position of the polygon
         */
        Vector2f getPosition() const override;

        /**
         * @brief Set the orientation of the polygon
         * @param angle New rotation, in degrees
         *
         * This function completely overwrites the previous rotation.
         * See the rotate function to add an angle based on the previous
         * rotation instead.
         *
         * The default rotation of the polygon is 0
         *
         * @see rotate
         */
        void setRotation(float angle) override;

        /**
         * @brief Rotate the polygon
         * @param angle Angle of rotation, in degrees
         *
         * This function adds to the current rotation of the polygon,
         * unlike setRotation which overwrites it
         *
         * @see setRotation
         */
        void rotate(float angle) override;

        /**
         * @brief Get the orientation of the polygon
         * @return Current rotation, in degrees
         *
         * The rotation is always in the range [0, 360]
         */
        float getRotation() const override;

        /**
         * @brief Set the scale factors of the polygon
         * @param factorX New horizontal scale factor
         * @param factorY New vertical scale factor
         *
         * This function completely overwrites the previous scale
         *
         * @see scale
         */
        void setScale(float factorX, float factorY) override;

        /**
         * @brief Set the scale factor of the polygon
         * @param scale New scale
         *
         * This function completely overwrites the previous scale
         *
         * @see scale
         */
        void setScale(Vector2f scale) override;

        /**
         * @brief Scale the polygon by an offset
         * @param factorX Horizontal scale factor
         * @param factorY Vertical scale factor
         *
         * This function multiplies the current scale of the polygon,
         * unlike setScale which overwrites it
         *
         * @see setScale
         */
        void scale(float factorX, float factorY) override;

        /**
         * @brief Scale the polygon by an offset
         * @param offset Offset to apply
         *
         * This function multiplies the current scale of the polygon,
         * unlike setScale which overwrites it
         *
         * @see setScale
         */
        void scale(Vector2f offset) override;

        /**
         * @brief Get the current scale of the polygon
         * @return Current scale of the polygon
         */
        Vector2f getScale() const override;

        /**
         * @brief Set the local origin of the polygon
         * @param x X coordinate of the new origin
         * @param y Y coordinate of the new origin
         *
         * The origin of the polygon defines the center point for
         * all transformations (position, scale, rotation).
         * The coordinates of this point must be relative to the
         * top-left corner of the polygon, and ignore all
         * transformations (position, scale, rotation).
         *
         * The default origin of the polygon is (0, 0)
         */
        void setOrigin(float x, float y) override;

        /**
         * @brief Set the local origin of the polygon
         * @param origin New origin
         *
         * The origin of the polygon defines the center point for
         * all transformations (position, scale, rotation).
         * The coordinates of this point must be relative to the
         * top-left corner of the polygon, and ignore all
         * transformations (position, scale, rotation).
         *
         * The default origin of the polygon is (0, 0)
         */
        void setOrigin(Vector2f origin) override;

        /**
         * @brief Get the local origin of the polygon
         * @return Local origin of the polygon
         */
        Vector2f getOrigin() const override;

        /**
         * @brief Move the polygon by a given offset
         * @param offsetX Horizontal offset
         * @param offsetY Vertical offset
         *
         * This function adds to the current position of the polygon,
         * unlike setPosition which overwrites it
         *
         * @see setPosition
         */
        void move(float offsetX, float offsetY) override;

        /**
         * @brief Move the polygon by a given offset
         * @param offset Offset to apply
         *
         * This function adds to the current position of the polygon,
         * unlike setPosition which overwrites it
         *
         * @see setPosition
         */
        void move(Vector2f offset) override;

        /**
         * @brief Draw the polygon on a render target
         * @param renderTarget Target to draw object on
         */
        void draw(Window &renderTarget) const override;

        /**
         * @brief Destructor
         */
        ~ConvexShape();

    private:
        struct Impl;
        std::unique_ptr<Impl> impl_;
    };
}

#endif //IME_CONVEXSHAPE_H
