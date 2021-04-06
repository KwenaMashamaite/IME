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

#ifndef IME_BOXCOLLIDER_H
#define IME_BOXCOLLIDER_H

#include "IME/Config.h"
#include "Collider.h"
#include "IME/common/Vector2.h"
#include <memory>

class b2PolygonShape;

namespace ime {
    /**
     * @brief A box collider
     *
     * The box is axis-aligned (Its edges are parallel to the X or Y
     * axis of the local space
     */
    class IME_API BoxCollider final : public Collider {
    public:
        using Ptr = std::shared_ptr<BoxCollider>; //!< shred collider pointer
        using ConstPtr = std::shared_ptr<const BoxCollider>; //!< Const shared collider pointer

        /**
         * @brief Default constructor
         * @param size The size of the box
         *
         * By default the size is 0.1f (width) x 0.1f (height)
         *
         * @warning The minimum size of the rectangle is 0.1f x 0.1f. Any
         * size below this is undefined behaviour
         *
         * @warning The collider must be attached to a rigid body before
         * any of its functions are are called. Calling a member function
         * without a rigid body is undefined behavior
         */
        explicit BoxCollider(Vector2f size = {0.1f, 0.1f});

        /**
         * @brief Move constructor
         */
        BoxCollider(BoxCollider&&) noexcept;

        /**
         * @brief Move assignment operator
         */
        BoxCollider& operator=(BoxCollider&&) noexcept;

        /**
         * @brief Create a box collider object
         * @param size The size of the box
         * @return The new box collider instance
         *
         * This function is just a helper function for creating a shared
         * pointer to a box collider. The class does not keep the pointer
         *
         * By default the size is 0.1f (width) x 0.1f (height)
         *
         * @warning The minimum size of the rectangle is 0.1f x 0.1f. Any
         * size below this is undefined behaviour
         *
         * @warning The collider must be attached to a rigid body before
         * any of its functions are are called. Calling a member function
         * without a rigid body is undefined behavior
         */
        static BoxCollider::Ptr create(Vector2f size = {0.1f, 0.1f});

        /**
         * @brief Create a copy of the collider
         * @return The new box collider
         *
         * @warning You must attach a rigid Body to the returned collider
         * before using it. Failure to do so is undefined behavior
         *
         * @see clone
         */
        BoxCollider::Ptr copy() const;

        /**
         * @brief Create a copy of the collider
         * @return A copy of the collider
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
         * @brief Get the name of this class
         * @return The name of this class
         */
        std::string getClassName() const override;

        /**
         * @brief Set the size of the box
         * @param width The width of the box
         * @param height The height of the box
         *
         * The box is centred at the local origin
         */
        void setSize(float width, float height);

        /**
         * @brief Set the size of the box
         * @param size The size of the box
         */
        void setSize(Vector2f size);

        /**
         * @brief Get the size of the box
         * @return The size of the box
         */
        Vector2f getSize() const;

        /**
         * @brief Destructor
         */
        ~BoxCollider() override;

    private:
        /**
         * @brief Copy constructor
         */
        BoxCollider(const BoxCollider&);

        /**
         * @brief Copy assignment operator
         */
        BoxCollider& operator=(const BoxCollider&);

        /**
         * @brief Get the internal shape
         * @return The internal shape
         */
        b2Shape &getInternalShape() override;
        const b2Shape &getInternalShape() const override;

    private:
        Vector2f size_;                       //!< The size of the box
        std::unique_ptr<b2PolygonShape> box_; //!< Internal box
    };
}

#endif //IME_BOXCOLLIDER_H
