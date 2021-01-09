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

#ifndef IME_IDRAWABLE_H
#define IME_IDRAWABLE_H

#include "IME/Config.h"

namespace ime {
    class Window; //!< Window class forward declaration

    /**
     * @brief Interface for drawable objects
     */
    class IME_API IDrawable {
    public:
        /**
         * @brief Draw object on a render target
         * @param renderTarget Target to draw object on
         */
        virtual void draw(Window &renderTarget) const = 0;

        /**
         * @brief Hide object from a render target
         *
         * A hidden object will not be drawn on a render target when
         * calling draw function
         */
        virtual void hide() = 0;

        /**
         * @brief Show a hidden object
         *
         * This function will reveal an object that was hidden prior
         * to function call. Calling this function on an object that
         * is not hidden has no effect
         */
        virtual void show() = 0;

        /**
         * @brief Check is object is hidden or not
         * @return True if object is hidden, false if object is not hidden
         */
        virtual bool isHidden() const = 0;

        /**
         * @brief Destructor
         */
        virtual ~IDrawable() = default;
    };
}

#endif // IME_IDRAWABLE_H
