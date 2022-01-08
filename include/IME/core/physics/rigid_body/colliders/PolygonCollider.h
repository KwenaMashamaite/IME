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
        using Ptr = std::unique_ptr<PolygonCollider>; //!< Unique polygon collider

        /**
         * @brief Default constructor
         */
        PolygonCollider();

        /**
         * @brief Move constructor
         */
        PolygonCollider(PolygonCollider&&) noexcept;

        /**
         * @brief Move assignment operator
         */
        PolygonCollider& operator=(PolygonCollider&&) noexcept;

        /**
         * @brief Create a copy of the collider
         * @return A new polygon collider
         *
         * @warning You must attach a rigid Body to the returned collider
         * before using it. Failure to do so is undefined behavior
         *
         * @see clone
         */
        PolygonCollider::Ptr copy() const;

        /**
         * @brief Create a copy of the collider
         * @return A new polygon collider
         *
         * You should use this function if you don't care about the type
         * of the collider, otherwise use the colliders copy function
         *
         * @warning You must attach a rigid Body to the returned collider
         * before using it. Failure to do so is undefined behavior
         *
         * @see copy
         */
        Collider::Ptr clone() const override;

        /**
         * @brief Create a new polygon collider
         * @return The created polygon collider
         *
         * This function is just a helper function for creating a shared
         * pointer to a polygon collider. The class does not keep the pointer
         */
        static PolygonCollider::Ptr create();

        /**
         * @brief Get the name of this class
         * @return The name of this class
         */
        std::string getClassName() const override;

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
         * @brief Destructor
         */
        ~PolygonCollider() override;

    private:
        /**
         * @brief Copy constructor
         */
        PolygonCollider(const PolygonCollider&);

        /**
         * @brief Copy assignment operator
         */
        PolygonCollider& operator=(const PolygonCollider&);

        /**
         * @brief Get the internal collider
         * @return The internal collider
         */
        b2Shape& getInternalShape() override;
        const b2Shape& getInternalShape() const override;

    private:
        std::unique_ptr<b2PolygonShape> polygon_; //!< Internal polygon collider
    };
}

#endif //IME_POLYGONCOLLIDER_H
