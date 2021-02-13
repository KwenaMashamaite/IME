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

#ifndef IME_COLLIDER_H
#define IME_COLLIDER_H

#include "IME/Config.h"
#include <memory>

class b2Shape;

namespace ime {
    /**
     * @brief Abstract Base class for all colliders
     *
     * A collider enables collisions between entities. A collider may
     * be attached directly to an Entity without a rigid Body but usually
     * the collider is attached to a rigid Body which is then attached to
     * an Entity. This allows the entity to collide with other entities and
     * also be affected by physics (impulses, gravity, friction etc). Without
     * the rigid body, the Entity cannot react/respond to a collision because
     * colliders only allow Entities to collide with each other
     */
    class IME_API Collider {
    public:
        using sharedPtr = std::shared_ptr<Collider>; //!< Shared collider pointer

        /**
         * @brief The type of the collider
         */
        enum class Type {
            Circle,  //!< Circle collider
            Box,     //!< Box collider
            Polygon, //!< Polygon collider
            Edge     //!< Edge collider
        };

        /**
         * @brief Construct a collider
         * @param type Type of the collider
         */
        explicit Collider(Type type);

        /**
         * @brief Copy constructor
         */
        Collider(const Collider&) = delete;

        /**
         * @brief Move assignment operator
         */
        Collider& operator=(const Collider&) = delete;

        /**
         * @brief Move constructor
         */
        Collider(Collider&&) = default;

        /**
         * @brief Move assignment operator
         */
        Collider& operator=(Collider&&) = default;

        /**
         * @brief Create a copy of the collider
         * @return The new collider copied from this collider
         */
        virtual sharedPtr copy() = 0;
        virtual const sharedPtr copy() const = 0;

        /**
         * @brief Get the type of the collider
         * @return The type of the collider
         */
        Type getType() const;

        /**
         * @internal
         * @brief Get the internal collider
         * @return The internal collider
         *
         * @warning This function is intended for internal use and should
         * never be called outside of IME
         */
        virtual b2Shape& getInternalShape() = 0;
        virtual const b2Shape& getInternalShape() const = 0;

        /**
         * @brief Destructor
         */
        virtual ~Collider() = default;

    private:
        Type type_; //!< The type of the collider
    };
}

#endif //IME_COLLIDER_H
