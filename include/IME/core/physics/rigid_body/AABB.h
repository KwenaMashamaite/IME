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

#ifndef IME_AABB_H
#define IME_AABB_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/core/object/Object.h"

struct b2AABB;

namespace ime {
    /**
     * @brief An Axis Aligned Bounding Box (AABB)
     */
    class IME_API AABB : public Object {
    public:
        /**
         * @brief Default constructor
         */
        AABB();

        /**
         * @brief Create AABB from its bounds
         * @param lowerBounds The lower bounds
         * @param upperBounds The upper bounds
         */
        void create(Vector2f lowerBounds, Vector2f upperBounds);

        /**
         * @brief Get the name of this class
         * @return The name of this class
         */
        std::string getClassName() const override;

        /**
         * @brief Get the bounds of the AABB
         * @return A pair, of which the first element is the lower bounds of
         *         the AABB and the second is the upper bounds of the AABB
         */
        std::pair<Vector2f, Vector2f> getBounds() const;

        /**
         * @brief Get the lower bounds of the AABB
         * @return The lower bounds of the AABB
         */
        Vector2f getLowerBounds() const;

        /**
         * @brief Get the upper bounds of the AABB
         * @return The upper bounds of the AABB
         */
        Vector2f getUpperBounds() const;

        /**
         * @brief Get the perimeter of the AABB
         * @return The perimeter of the AABB
         */
        float getPerimeter() const;

        /**
         * @brief Get the centre of the AABB
         * @return The centre of the AABB
         */
        Vector2f getCenter() const;

        /**
         * @brief Combine this AABB with another AABB
         * @param aabb The AABB to combine into this one
         */
        void combine(const AABB& aabb);

        /**
         * @brief Combine two AABBs into this AABB
         * @param aabb1 The first AABB
         * @param aabb2 The second AABB
         *
         * This AABB will now be the size of the Two AABBs
         */
        void combine(const AABB& aabb1, const AABB& aabb2);

        /**
         * @brief Check if this AABB contains another AABB
         * @param aabb The AABB to be checked
         * @return True if this object contains @a aabb
         */
        bool contains(const AABB& aabb) const;

        /**
         * @internal
         * @brief Get the internal AABB
         * @return The internal AABB
         *
         * @warning This function is intended for internal use and should
         * never be called outside of IME
         */
        const b2AABB* getInternalAABB() const;

        /**
         * @brief Destructor
         */
        ~AABB() override;

    private:
        b2AABB* aabb_; //!< Internal AABB
    };
}

#endif //IME_AABB_H
