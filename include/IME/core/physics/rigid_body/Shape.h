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

#ifndef IME_SHAPE_H
#define IME_SHAPE_H

#include "IME/Config.h"

class b2Shape;

namespace ime {
    /**
     * @brief Abstract Base class for all shapes
     *
     * The shape is a physical shape of a rigid Body. It is used for collision
     * detection and cannot be rendered directly.
     */
    class IME_API Shape {
    public:
        /**
         * @brief The type of the shape
         */
        enum class Type {
            Circle,    //!< Circle shape shape
            Rectangle, //!< Specialized polygon shape
            Edge,      //!<
            Polygon,   //!<
            Chain      //!<
        };

        /**
         * @brief Construct a shape
         * @param type Type of the shape
         */
        explicit Shape(Type type);

        /**
         * @brief Get the type of the shape
         * @return The type of the shape
         */
        Type getType() const;

        /**
         * @internal
         * @brief Get the internal shape
         * @return The internal shape
         *
         * @warning This function is intended for internal use and should never
         * be called outside of IME
         */
        virtual b2Shape* getInternalShape() = 0;
        virtual const b2Shape* getInternalShape() const = 0;

        /**
         * @brief Destructor
         */
        virtual ~Shape() = default;

    private:
        Type type_; //!< The type of the shape
    };
}

#endif //IME_SHAPE_H
