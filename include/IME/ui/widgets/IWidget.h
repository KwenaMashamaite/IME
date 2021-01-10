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

namespace ime {
    enum class ShowAnimationType {
        Fade,          //!< Fade widget in or out
        Scale,         //!< Shrink to the center of the widget to hide or grow from its center to show
        SlideToRight,  //!< Slide to the right to hide or from left to show
        SlideToLeft,   //!< Slide to the left to hide or from right to show
        SlideToBottom, //!< Slide to the bottom to hide or from top to show
        SlideToTop,    //!< Slide to the top to hide or from bottom to show

        SlideFromLeft = SlideToRight, //!< Slide from left to show or to the right to hide
        SlideFromRight = SlideToLeft, //!< Slide from right to show or to the left to hide
        SlideFromTop = SlideToBottom, //!< Slide from top to show or to the bottom to hide
        SlideFromBottom = SlideToTop  //!< Slide from bottom to show or to the top to hide
    };

    namespace ui {
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
             * @brief Get the absolute position of the widget
             * @return The absolute position of the widget
             *
             * Unlike getPosition, this function returns the absolute
             * position of the top-left point of the widget instead
             * of the relative position to its parent
             *
             * @see setPosition
             */
            virtual Vector2f getAbsolutePosition() const = 0;

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
             * @brief Set the width of the widget
             * @param width New width of the widget
             *
             * This function sets the width while keeping the height
             * the same
             *
             * @see setSize
             */
            virtual void setWidth(float width) = 0;

            /**
             * @brief Set the width of the widget relative to its parent
             * @param width New width
             *
             * The relative width is given in percentages as shown:
             *
             * @code
             * widget->setWidth("10%");
             * @endcode
             *
             * This function sets the width of the widget while keeping the
             * height the same
             *
             * @see setSize
             */
            virtual void setWidth(const std::string& width) = 0;

            /**
             * @brief Set the height of the widget
             * @param height New height of the widget
             *
             * This function sets the height while keeping the width
             * the same
             *
             * @see setSize
             */
            virtual void setHeight(float height) = 0;

            /**
             * @brief Set the height of the widget relative to its parent
             * @param height New height
             *
             * The relative height is given in percentages as shown:
             *
             * @code
             * widget->setHeight("10%");
             * @endcode
             *
             * This function sets the height of the widget while keeping the
             * width the same
             *
             * @see setSize
             */
            virtual void setHeight(const std::string& height) = 0;

            /**
             * @brief Get the type of the widget
             * @return The type of the widget
             */
            virtual std::string getWidgetType() const = 0;

            /**
             * @brief Show the widget with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will be played if the widget currently
             * visible
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the widget
             * will be back in the state in which it was when this function
             * was called
             *
             * @see hideWithEffect
             * @see isAnimationPlaying
             */
            virtual void showWithEffect(ShowAnimationType type, int duration) = 0;

            /**
             * @brief Hide the widget with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will also be played if the widget currently
             * hidden but it will not be seen
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the widget
             * will be back in the state in which it was when this function
             * was called
             *
             * @see showWithEffect
             * @see isAnimationPlaying
             */
            virtual void hideWithEffect(ShowAnimationType type, int duration) = 0;

            /**
             * @brief Check whether or not an animation is currently playing
             * @return True if an animation is playing, otherwise false
             *
             * @see showWithEffect
             * @see hideWithEffect
             */
            virtual bool isAnimationPlaying() const = 0;

            /**
             * @brief Show or hide a widget
             * @param visible True to show or false to hide
             *
             * If the widget is hidden, it won't receive events
             * (and thus won't send callbacks) nor will it be drawn
             *
             * The widget is visible by default.
             */
            virtual void setVisible(bool visible) = 0;

            /**
             * @brief Check if the widget is visible or not
             * @return True if the widget is visible or false if hidden
             */
            virtual bool isVisible() const = 0;

            /**
             * @brief Toggle the visibility of the widget
             *
             * This function will hide the widget if its currently
             * visible and vice versa
             *
             * @see setVisible
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
