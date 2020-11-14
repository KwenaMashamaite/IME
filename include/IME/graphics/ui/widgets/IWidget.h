////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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

/**
 * @brief Abstract base class Graphical User Interface (GUI) widgets
 */

#ifndef IWIDGET_H
#define IWIDGET_H

#include "IME/graphics/Window.h"
#include "IME/graphics/IDrawable.h"
#include "IME/graphics/Colour.h"
#include "IME/core/event/EventEmitter.h"
#include "IME/common/ITransformable.h"
#include "IME/common/Vector2.h"
#include "IME/graphics/ui/Enums.h"
#include "IME/graphics/ui/Structs.h"
#include <TGUI/Widget.hpp>
#include <string>

namespace IME {
    namespace Graphics::UI {
        class IWidget : public ITransformable, public EventEmitter {
        public:
            /**
             * @brief Set the character size of the widget's text
             * @param charSize New character size
             *
             * The default character size is 30
             */
            virtual void setTextSize(unsigned int charSize) = 0;

            /**
             * @brief Set the text content of the widget
             * @param content New text content
             *
             * This function will overwrite any text that was previously
             * set
             */
            virtual void setText(const std::string &content) = 0;

            /**
             * @brief Set the size of the widget
             * @param width The width of the widget
             * @param height The hieght of teh widget
             */
            virtual void setSize(float width, float height) = 0;

            /**
             * @brief Get the size of the widget
             * @return Current size of the widget
             *
             * This function only returns the size of the widget, to get the
             * absolute size (with the margin, outline thickness etc...)
             * @see getAbsoluteSize()
             */
            virtual Vector2f getSize() const = 0;

            /**
             * @brief Get the absolute size of the widget
             * @return The absolute size of the widget
             *
             * The absolute size includes the size of the widget, the padding,
             * margin and outline thickness. To get just the size of the widget
             * use @see getSize()
             */
            virtual Vector2f getAbsoluteSize() = 0;

            /**
             * @brief Get the widgets text content
             * @return Elements text content
             */
            virtual std::string getText() const = 0;

            /**
             * @brief Get the character size of the text
             * @return The character size of the text
             */
            virtual unsigned int getTextSize() const = 0;

            /**
             * @brief Get the type of the widget
             * @return Type of the widget
             */
            virtual std::string getType() const = 0;

            /**
             * @brief Toggle the visibility of the widget
             *
             * This function will make the widget invisible if its currently
             * visible and vice versa. The visibility is not automatically
             * reflected on the render target. A call to draw() must be made
             * after calling this function
             */
            virtual void toggleVisibility() = 0;

            /**
             * @brief Check if coordinates lie inside the widget
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return true if coordinates lie inside the widget, false if
             *         coordinates do not lie inside the widget
             */
            virtual bool contains(float x, float y) const = 0;

            /**
             * @brief Hide widget from a render target
             */
            virtual void hide() = 0;

            /**
             * @brief Show a hidden widget
             *
             * This function will reveal the widget that was hidden prior to
             * function call. Calling this function on an object that is not
             * hidden has no effect
             */
            virtual void show() = 0;

            /**
             * @brief Check is the widget is hidden or not
             * @return True if the widget is hidden, otherwise false
             */
            virtual bool isHidden() const = 0;

            /**
             * @internal
             * @brief Get the internal pointer to a third party widget object
             * @return The internal pointer to a third party widget object
             *
             * @warning This function is intended for internal use only and
             * should never be called
             */
            virtual std::shared_ptr<tgui::Widget> getInternalPtr() = 0;

            /**
             * @brief Default destructor
             */
            virtual ~IWidget() = default;

        protected:
            /**
             * @brief Restrict the publication of widget events to
             *        class level
             *
             * This ensures that the publishing of events is exclusively
             * controlled by the class. For instance, if the method is
             * public, a click event can be raised on a button through
             * an instance, even thought the said button is not clicked.
             * This may cause bugs in the program
             */
            using EventEmitter::emit;
        };
    }
}

#endif
