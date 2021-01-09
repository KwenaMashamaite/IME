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

#ifndef IME_IWIDGET_H
#define IME_IWIDGET_H

#include "IME/Config.h"
#include "IME/graphics/Colour.h"
#include "IME/core/event/EventEmitter.h"
#include "IME/common/ITransformable.h"
#include "IME/common/Vector2.h"
#include <TGUI/Widget.hpp>
#include <string>

namespace IME {
    namespace UI {
        /**
         * @brief Abstract base class for Graphical User Interface (GUI) elements
         */
        class IME_API IWidget : public ITransformable {
        public:
            /**
             * @brief Set the position of the widget relative to the
             *        size of its parent
             * @param x New x coordinate of the widget
             * @param y New y coordinate of the widget
             *
             * The position is specified using percentages as shown below:
             *
             * @code
             * widget->setPosition({"5%", "10%"});
             * @endcode
             */
            virtual void setPosition(const std::string& x, const std::string& y) = 0;
            using ITransformable::setPosition;

            /**
             * @brief Set the text content of the widget
             * @param text New text content
             *
             * This function will overwrite any text that was previously
             * set
             */
            virtual void setText(const std::string &text) = 0;

            /**
             * @brief Get the widgets text content
             * @return The widgets text content
             */
            virtual std::string getText() const = 0;

            /**
             * @brief Set the character size of the text
             * @param charSize New character size
             */
            virtual void setTextSize(unsigned int charSize) = 0;

            /**
             * @brief Get the character size of the text
             * @return The character size of the text
             */
            virtual unsigned int getTextSize() const = 0;

            /**
             * @brief Set the size of the widget
             * @param width The width of the widget
             * @param height The height of the widget
             */
            virtual void setSize(float width, float height) = 0;

            /**
             * @brief Set the size of the widget relative to the size of
             *        its parent
             * @param width The new width of the widget
             * @param height The new height of the widget
             *
             * The size is specified in percentages as shown below
             *
             * @code
             * widget->setSize({"20%", "5%"});
             * @endcode
             */
            virtual void setSize(const std::string& width,
                 const std::string& height) = 0;

            /**
             * @brief Get the size of the widget
             * @return Current size of the widget
             *
             * This function only returns the size of the widget (It does
             * not accommodate margin, outline thickness etc ...)
             *
             * @see getAbsoluteSize
             */
            virtual Vector2f getSize() const = 0;

            /**
             * @brief Get the absolute size of the widget
             * @return The absolute size of the widget
             *
             * The absolute size includes the size of the widget, the padding,
             * margin and outline thickness
             *
             * @see getSize
             */
            virtual Vector2f getAbsoluteSize() = 0;

            /**
             * @brief Get the type of the widget
             * @return The type of the widget
             */
            virtual std::string getType() const = 0;

            /**
             * @brief Show a hidden widget
             *
             * This function will reveal the widget that was hidden prior to
             * function call. Calling this function on an widget that is not
             * hidden has no effect
             */
            virtual void show() = 0;

            /**
             * @brief Hide widget
             */
            virtual void hide() = 0;

            /**
             * @brief Check if the widget is hidden or not
             * @return True if the widget is hidden, otherwise false
             */
            virtual bool isHidden() const = 0;

            /**
             * @brief Toggle the visibility of the widget
             *
             * This function will hide the widget if its currently
             * visible and vice versa
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
             * @brief Add an event listener to a widget event
             * @param event Event to add an event listener to
             * @param callback Function to execute when the event is fired
             * @return The event listeners identification number
             *
             * The id must if the event listener is to be removed later
             *
             * @see unsubscribe
             */
            template<typename... Args>
            int on(const std::string& event, Callback<Args...> callback) {
                return eventEmitter_.on(event, std::move(callback));
            }

            /**
             * @brief Remove an event listener from a widget event
             * @param event Event to remove event listener from
             * @param id Id number of the event listener
             * @return True if the event listener was removed or false
             *         if the given event does not exist or the event
             *         does not have an event listener with the given id
             *
             * The id is the number given when the event listener was
             * registered
             *
             * @see on
             */
            bool unsubscribe(const std::string& event, std::size_t id) {
                return eventEmitter_.removeEventListener(event, id);
            }

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
             * @brief Destructor
             */
            virtual ~IWidget() = default;

        protected:
            /**
             * @brief Emit a widget event
             * @param event Name of the event to be emitted
             * @param args Arguments to pass to event listeners
             *
             * This function will invoke all event listeners of the
             * given event
             */
            template<typename... Args>
            void emit(const std::string& event, Args&& ...args) {
                eventEmitter_.emit(event, std::forward<Args>(args)...);
            }

        private:
            EventEmitter eventEmitter_; //!< Widgets event publisher
        };
    }
}

#endif // IME_IWIDGET_H
