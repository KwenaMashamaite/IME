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

#ifndef IME_DRAWABLE_H
#define IME_DRAWABLE_H

#include "IME/Config.h"
#include "IME/common/Object.h"

namespace ime {

    /// @internal
    namespace priv {
        class Window; //!< Window class forward declaration
    }

    /**
     * @brief Interface for drawable objects
     */
    class IME_API Drawable : public Object {
    public:
        /**
         * @brief Get the name of this class
         * @return The name of this class
         *
         * Note that this function is only overridden by child classes
         * of Object which also serve as a base class for other classes
         *
         * @see Object::getClassType and Object::getClassName
         */
        std::string getClassType() const override {
            return "Drawable";
        }

        /**
         * @brief Draw object on a render target
         * @param renderTarget Target to draw object on
         *
         * @note This function is intended for internal use only
         */
        virtual void draw(priv::Window &renderTarget) const = 0;
    };
}

#endif // IME_DRAWABLE_H
