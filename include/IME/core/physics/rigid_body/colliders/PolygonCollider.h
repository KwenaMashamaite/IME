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

#ifndef IME_POLYGONCOLLIDER_H
#define IME_POLYGONCOLLIDER_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "Collider.h"
#include <vector>
#include <memory>

class b2PolygonShape;

namespace ime {
    /**
     * @brief Solid convex polygon collider
     *
     * A polygon is convex when all line segments connecting two points in t
     * he interior do not cross any edge of the polygon. Polygons are solid
     * and never hollow. A polygon must have 3 or more vertices
     */
    class IME_API PolygonCollider final : public Collider {
    public:
        using sharedPtr = std::shared_ptr<PolygonCollider>; //!< Shared polygon collider

        /**
         * @brief Move constructor
         */
        PolygonCollider(PolygonCollider&&) = default;

        /**
         * @brief Move assignment operator
         */
        PolygonCollider& operator=(PolygonCollider&&) = default;

        /**
         * @brief Create a new polygon collider
         * @return The created polygon collider
         */
        static sharedPtr create();

        /**
         * @brief Create a new collider from an existing polygon collider
         * @param other The polygon collider to contract the new one from
         * @return The new polygon collider instance
         */
        Collider::sharedPtr copy() override;
        const Collider::sharedPtr copy() const override;

        /**
         * @brief Create a convex hull from the an array of local points
         * @param vertices The vertices to create the convex hull from
         *
         * The origin of the polygon is at the local coordinate (0, 0)
         *
         * @warning The maximum number of vertices allowed is 8
         *
         * @warning The points may be reordered, even if they form a convex
         * polygon. Collinear points are handled but not removed. Collinear
         * points may lead to poor stacking behaviour
         */
        void set(const std::vector<Vector2f>& vertices);

        /**
         * @internal
         * @brief Get the internal collider
         * @return The internal collider
         *
         * @warning This function is intended for internal use and should never
         * be called outside of IME
         */
        b2Shape& getInternalShape() override;
        const b2Shape& getInternalShape() const override;

    private:
        /**
         * @brief Default constructor
         */
        PolygonCollider();

    private:
        std::unique_ptr<b2PolygonShape> polygon_; //!< Internal polygon collider
    };
}

#endif //IME_POLYGONCOLLIDER_H