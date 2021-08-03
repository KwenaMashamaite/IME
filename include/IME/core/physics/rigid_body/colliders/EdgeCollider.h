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

#ifndef IME_EDGECOLLIDER_H
#define IME_EDGECOLLIDER_H

#include "IME/Config.h"
#include "Collider.h"
#include "IME/common/Vector2.h"
#include <memory>

class b2EdgeShape;

namespace ime {
    /**
     * @brief An edge collider is a line segment
     *
     * Note that edge colliders can collide with circles and polygons but not
     * with themselves because edge shapes have no volume
     */
    class IME_API EdgeCollider : public Collider {
    public:
        using Ptr = std::unique_ptr<EdgeCollider>; //!< Unique collider pointer

        /**
         * @brief Default constructor
         */
        EdgeCollider();

        /**
         * @brief Move constructor
         */
        EdgeCollider(EdgeCollider&&) noexcept;

        /**
         * @brief Move assignment operator
         */
        EdgeCollider& operator=(EdgeCollider&&) noexcept;

        /**
         * @brief Create a copy of the collider
         * @return A new edge collider
         *
         * @warning You must attach a rigid Body to the returned collider
         * before using it. Failure to do so is undefined behavior
         *
         * @see clone
         */
        EdgeCollider::Ptr copy() const;

        /**
         * @brief Create a copy of the collider
         * @return A new edge collider
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
         * @brief Create a new edge collider
         * @return The created edge collider
         *
         * This function is just a helper function for creating a shared
         * pointer to an edge collider. The class does not keep the pointer
         */
        static EdgeCollider::Ptr create();

        /**
         * @brief Get the name of this class
         * @return The name of this class
         */
        std::string getClassName() const override;

        /**
         * @brief Create a one sided collision edge
         * @param v0 A ghost vertex adjacent to the first edge vertex
         * @param v1 The first edge vertex
         * @param v2 The second edge vertex
         * @param v3 A ghost vertex adjacent to the second edge vertex
         *
         * In many cases a game environment is constructed by connecting several
         * edge shapes end-to-end. This can give rise to an unexpected artifact
         * when a polygon slides along the chain of edges (ghost collisions).
         * Ghost collisions occur when the polygon collides with an internal
         * vertex generating an internal collision normal. This function provides
         * a mechanism for eliminating ghost collisions by storing the adjacent
         * ghost vertices (@a v0 and @a v3) and using them internally to prevent
         * internal collisions that lead to ghost collision.
         *
         * @a v1 and @a v2 are the edge vertices whilst @a v0 and @a v3 are the
         * adjacent ghost vertices. The extra ghost vertices are used to provide
         * smooth movement across junctions.
         *
         * The edge normal points to the right looking from @a v1 to @a v2
         *
         * @see setTwoSided
         */
        void setOneSided(const Vector2f& v0, const Vector2f& v1, const Vector2f& v2,
            const Vector2f& v3);

        /**
         * @brief Create a two sided collision edge
         * @param v1 The first edge vertex
         * @param v2 The second edge vertex
         *
         * This function is more suited for edge colliders that are not chained
         * to other edge colliders. If edge colliders are chained, ghost collision
         * may occur when a polygon collider such as the BoxCollider slides
         * across the chain. To counteract this effect, use the setOneSided
         * function to construct the collider. However, if you don't care about
         * ghost collisions, then this function is the preferred function to
         * create an edge collider
         *
         * The edge normal points to the right looking from @a v1 to @a v2.
         *
         * @see setOneSided
         */
        void setTwoSided(const Vector2f& v1, const Vector2f& v2);

        /**
         * @brief Get the vertices that make up the edge
         * @return A pair, of which the first element is the first vertex
         *         and the second is the second vertex of the edge
         */
        std::pair<Vector2f, Vector2f> getEdgeVertices() const;

        /**
         * @brief Get the first vertex of the edge collider
         * @return The first vertex of the edge collider
         */
        Vector2f getFirstVertex() const;

        /**
         * @brief Get the second vertex of the edge collider
         * @return The second vertex of the edge collider
         */
        Vector2f getSecondVertex() const;

        /**
         * @brief Get the ghost vertices
         * @return A pair, of which the first element is the first ghost vertex
         *         and the second is the second ghost vertex
         *
         * If the collider is two sided then the ghost vertices are all 0.0f
         *
         * @see setOneSided and setTwoSided
         */
        std::pair<Vector2f, Vector2f> getGhostVertices() const;

        /**
         * @brief Check if the edge is collidable on one side or two sides
         * @return True if collidable on one side or false if collidable on
         *         two sides
         */
        bool isOneSided() const;

        /**
         * @brief Destructor
         */
        ~EdgeCollider() override;

    private:
        /**
         * @brief Copy constructor
         */
        EdgeCollider(const EdgeCollider&);

        /**
         * @brief Copy assignment operator
         */
        EdgeCollider& operator=(const EdgeCollider&);

        /**
         * @brief Get the internal collider
         * @return The internal collider
         */
        b2Shape& getInternalShape() override;
        const b2Shape& getInternalShape() const override;

    private:
        std::unique_ptr<b2EdgeShape> edgeShape_; //!< Internal shape
    };
}

#endif //IME_EDGECOLLIDER_H
