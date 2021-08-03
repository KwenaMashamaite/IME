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

#ifndef IME_CIRCLECOLLIDER_H
#define IME_CIRCLECOLLIDER_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "Collider.h"
#include <memory>

class b2CircleShape;

namespace ime {
    /**
     * @brief A circle circle
     *
     * Circle colliders have a position and radius. Circles are solid.
     * You cannot make a hollow circle using the circle collider. The
     * origin of a circle collider is always at the local centre of
     * the circle
     */
    class IME_API CircleCollider final : public Collider {
    public:
        using Ptr = std::unique_ptr<CircleCollider>; //!< Unique collider pointer

        /**
         * @brief Default constructor
         * @param radius The radius of the circle
         *
         * By default, the circle radius is 0.0f
         */
        explicit CircleCollider(float radius = 0.0f);

        /**
         * @brief Move constructor
         */
        CircleCollider(CircleCollider&&) noexcept;

        /**
         * @brief Move assignment operator
         */
        CircleCollider& operator=(CircleCollider&&) noexcept;

        /**
         * @brief Create a copy of the collider
         * @return A new circle collider
         *
         * @warning You must attach a rigid Body to the returned collider
         * before using it. Failure to do so is undefined behavior
         *
         * @see clone
         */
        CircleCollider::Ptr copy() const;

        /**
         * @brief Create a copy of the collider
         * @return A new circle collider
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
         * @brief Create a new circle collider
         * @param radius The radius of the circle
         * @return The created circle collider
         *
         * This function is just a helper function for creating a shared
         * pointer to a circle collider. The class does not keep the pointer
         *
         * By default, the circle radius is 0.0f
         */
        static CircleCollider::Ptr create(float radius = 0.0f);

        /**
         * @brief Get the name of this class
         * @return The name of this class
         */
        std::string getClassName() const override;

        /**
         * @brief Set the position of the circle
         * @param position The position of the circle
         */
        void setPosition(const Vector2f& position);

        /**
         * @brief Get the position of the circle
         * @return The position of the circle
         */
        Vector2f getPosition() const;

        /**
         * @brief Set the radius of the circle
         * @param radius The radius of the circle
         */
        void setRadius(float radius);

        /**
         * @brief Get the radius of the circle
         * @return The radius of the circle
         */
        float getRadius() const;

        /**
         * @brief Destructor
         */
        ~CircleCollider() override;

    private:
        /**
         * @brief Copy constructor
         */
        CircleCollider(const CircleCollider&);

        /**
         * @brief Copy assignment operator
         */
        CircleCollider& operator=(const CircleCollider&);

        /**
         * @brief Get the internal collider
         * @return The internal collider
         */
        b2Shape& getInternalShape() override;
        const b2Shape& getInternalShape() const override;

    private:
        std::unique_ptr<b2CircleShape> circle_;  //!< Internal collision circle
    };
}

#endif //IME_CIRCLECOLLIDER_H
