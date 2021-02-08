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

#ifndef IME_POLYGONSHAPE_H
#define IME_POLYGONSHAPE_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/core/physics/rigid_body/Shape.h"
#include <vector>

class b2PolygonShape;

namespace ime {
    /**
     * @brief Solid convex polygons
     *
     * A polygon is convex when all line segments connecting two points in t
     * he interior do not cross any edge of the polygon. Polygons are solid
     * and never hollow. A polygon must have 3 or more vertices
     */
    class IME_API PolygonShape final : public Shape {
    public:
        /**
         * @brief Default constructor
         */
        PolygonShape();

        /**
         * @brief Create a convex hull from the an array of local points
         * @param vertices The vertices to create the convex hull from
         *
         * @warning The maximum number of vertices allowed is 8
         *
         * @warning The points may be reordered, even if they form a convex
         * polygon. Collinear points are handled but not removed. Collinear
         * points may lead to poor stacking behaviour
         */
        void set(const std::vector<Vector2f>& vertices);

        /**
         * @brief Build vertices to represent an axis-aligned box centred on
         *        the local origin
         * @param halfWidth The width of the box
         * @param halfHeight The height of the box
         */
        void setAsBox(float width, float height);

        /**
         * @brief Build vertices to represent an oriented box
         * @param halfWidth The width of the box
         * @param halfHeight The height of the box
         * @param center The center of the box in local coordinates
         * @param angle The rotation of the box in local coordinates
         */
        void setAsBox(float width, float height, Vector2f center, float angle);

        /**
         * @internal
         * @brief Get the internal shape
         * @return The internal shape
         *
         * @warning This function is intended for internal use and should never
         * be called outside of IME
         */
        b2Shape* getInternalShape() override;
        const b2Shape* getInternalShape() const override;

        /**
         * @brief Destructor
         */
        ~PolygonShape();

    private:
        b2PolygonShape* polygon_; //!< Internal polygon shape
    };
}

#endif //IME_POLYGONSHAPE_H
