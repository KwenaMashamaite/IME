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

#ifndef IME_WIDGET_H
#define IME_WIDGET_H

#include "IME/Config.h"
#include "IME/graphics/Colour.h"
#include "IME/core/event/EventEmitter.h"
#include "IME/common/ITransformable.h"
#include "IME/common/Vector2.h"
#include "IME/core/time/Time.h"
#include "IME/ui/renderers/IWidgetRenderer.h"
#include <string>
#include <memory>

namespace ime {
    /**
     * @internal
     */
    namespace priv {
        class IWidgetImpl;
    }

    /**
     * @brief Mouse cursor types
     */
    enum class CursorType {
        Arrow,                  //!< Arrow cursor (default)
        Text,                   //!< I-beam, cursor when hovering over a text field
        Hand,                   //!< Pointing hand cursor
        SizeLeft,               //!< Left arrow on Linux, horizontal double arrow cursor on Windows and macOS
        SizeRight,              //!< Right arrow on Linux, horizontal double arrow cursor on Windows and macOS
        SizeTop,                //!< Up arrow on Linux, vertical double arrow cursor on Windows and macOS
        SizeBottom,             //!< Down arrow on Linux, vertical double arrow cursor on Windows and macOS
        SizeTopLeft,            //!< Top-left arrow on Linux, double arrow cursor going from top-left to bottom-right on Windows and macOS
        SizeBottomRight,        //!< Bottom-right arrow on Linux, double arrow cursor going from top-left to bottom-right on Windows and
        SizeBottomLeft,         //!< Bottom-left arrow on Linux, double arrow cursor going from bottom-left to top-right on Windows and macOS
        SizeTopRight,           //!< Top-right arrow on Linux, double arrow cursor going from bottom-left to top-right on Windows and macOS
        Crosshair,              //!< Crosshair cursor
        Help,                   //!< Help cursor
        NotAllowed              //!< Action not allowed cursor
    };

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
        class IME_API Widget : public ITransformable {
        public:
            using Ptr = std::unique_ptr<Widget>; //!< Unique widget pointer

            /**
             * @internal
             * @brief Constructor
             * @param impl The widgets implementation
             */
            explicit Widget(std::unique_ptr<priv::IWidgetImpl> impl);

            /**
             * @brief Copy constructor
             */
            Widget(const Widget&);

            /**
             * @brief Copy assignment operator
             */
            Widget& operator=(const Widget&);

            /**
             * @brief Move constructor
             */
            Widget(Widget&&) noexcept;

            /**
             * @brief Move assignment operator
             */
            Widget& operator=(Widget&&) noexcept;

            /**
             * @brief Set the widgets renderer
             * @param renderer The new renderer
             *
             * The renderer determines how the widget is displayed.
             *
             * @see getRenderer
             */
            void setRenderer(IWidgetRenderer::Ptr renderer);

            /**
             * @brief Get the widgets renderer
             * @return The widgets renderer
             *
             * The renderer gives access to functions that determine how the
             * widget is displayed. It allows you to manipulate things such
             * as the background colour, border colour etc...
             *
             * @see setRenderer
             */
            IWidgetRenderer* getRenderer();
            const IWidgetRenderer* getRenderer() const;

            /**
             * @brief Set the position of the widget
             * @param x X coordinate of the new position
             * @param y Y coordinate of the new position
             *
             * This function completely overwrites the previous position.
             * use move function to apply an offset based on the previous
             * position instead
             *
             * The default position of a the widget is (0, 0)
             *
             * @see move
             */
            void setPosition(float x, float y) override;

            /**
             * @brief Set the position of the widget
             * @param position New position
             *
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the widget is (0, 0)
             *
             * @see move
             */
            void setPosition(Vector2f position) override;

            /**
             * @brief Set the position of the widget relative to the
             *        size of its parent
             * @param x New x coordinate of the widget
             * @param y New y coordinate of the widget
             *
             * The position is specified in percentages as shown below:
             *
             * @code
             * widget->setPosition("5%", "10%");
             * @endcode
             *
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the widget is (0, 0)
             *
             * @see move
             */
            void setPosition(const std::string& x, const std::string& y);

            /**
             * @brief Get the position of the widget
             * @return Current position of the widget
             */
            Vector2f getPosition() const override;

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
            Vector2f getAbsolutePosition() const;

            /**
             * @brief Set the orientation of the widget
             * @param angle New rotation, in degrees
             *
             * This function completely overwrites the previous rotation.
             * See the rotate function to add an angle based on the previous
             * rotation instead.
             *
             * The default rotation of the widget is 0
             *
             * @see rotate
             */
            void setRotation(float angle) override;

            /**
             * @brief Rotate the widget
             * @param angle Angle of rotation, in degrees
             *
             * This function adds to the current rotation of the widget,
             * unlike setRotation which overwrites it
             *
             * @see setRotation
             */
            void rotate(float angle) override;

            /**
             * @brief Get the orientation of the widget
             * @return Current rotation, in degrees
             *
             * The rotation is always in the range [0, 360]
             */
            float getRotation() const override;

            /**
             * @brief Set the scale factors of the widget
             * @param factorX New horizontal scale factor
             * @param factorY New vertical scale factor
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(float factorX, float factorY) override;

            /**
             * @brief Set the scale factor of the widget
             * @param scale New scale
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(Vector2f scale) override;

            /**
             * @brief Scale the widget by an offset
             * @param factorX Horizontal scale factor
             * @param factorY Vertical scale factor
             *
             * This function multiplies the current scale of the widget,
             * unlike setScale which overwrites it
             *
             * @see setScale
             */
            void scale(float factorX, float factorY) override;

            /**
             * @brief Scale the widget by an offset
             * @param factor Offset to apply
             *
             * This function multiplies the current scale of the widget,
             * unlike setScale which overwrites it
             *
             * @see setScale
             */
            void scale(Vector2f factor) override;

            /**
             * @brief Get the current scale of the widget
             * @return Current scale of the widget
             */
            Vector2f getScale() const override;

            /**
             * @brief Set the local origin of the widget
             * @param x X coordinate of the new origin
             * @param y Y coordinate of the new origin
             *
             * The origin of the widget defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the widget, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the widget is (0, 0)
             */
            void setOrigin(float x, float y) override;

            /**
             * @brief Set the local origin of the widget
             * @param origin New origin
             *
             * The origin of the widget defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the widget, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the widget is (0, 0)
             */
            void setOrigin(Vector2f origin) override;

            /**
             * @brief Get the local origin of the widget
             * @return Local origin of the widget
             */
            Vector2f getOrigin() const override;

            /**
             * @brief Move the widget by a given offset
             * @param offsetX Horizontal offset
             * @param offsetY Vertical offset
             *
             * This function adds to the current position of the widget,
             * unlike setPosition which overwrites it
             *
             * @see setPosition
             */
            void move(float offsetX, float offsetY) override;

            /**
             * @brief Move the widget by a given offset
             * @param offset Offset to apply
             *
             * This function adds to the current position of the widget,
             * unlike setPosition which overwrites it
             *
             * @see setPosition
             */
            void move(Vector2f offset) override;

            /**
             * @brief Set the character size of the text
             * @param size New character size
             */
            void setTextSize(unsigned int size);

            /**
             * @brief Get the character size of the text
             * @return The character size of the text
             */
            unsigned int getTextSize() const;

            /**
             * @brief Set the size of the widget
             * @param width The width of the widget
             * @param height The height of the widget
             */
            void setSize(float width, float height);

            /**
             * @brief Set the size of the widget relative to the size of
             *        its parent
             * @param width The new width of the widget
             * @param height The new height of the widget
             *
             * The size is specified in percentages as shown below:
             *
             * @code
             * widget->setSize("20%", "5%");
             * @endcode
             */
            void setSize(const std::string& width, const std::string& height);

            /**
             * @brief Get the size of the widget
             * @return Current size of the widget
             *
             * This function only returns the size of the widget (It does
             * not accommodate margin, outline thickness etc ...)
             *
             * @see getAbsoluteSize
             */
            Vector2f getSize() const;

            /**
             * @brief Get the absolute size of the widget
             * @return The absolute size of the widget
             *
             * The absolute size includes the size of the widget, the padding,
             * margin and outline thickness
             *
             * @see getSize
             */
            Vector2f getAbsoluteSize();

            /**
             * @brief Set the width of the widget
             * @param width New width of the widget
             *
             * This function sets the width while keeping the height
             * the same
             *
             * @see setSize
             */
            void setWidth(float width);

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
            void setWidth(const std::string& width);

            /**
             * @brief Set the height of the widget
             * @param height New height of the widget
             *
             * This function sets the height while keeping the width
             * the same
             *
             * @see setSize
             */
            void setHeight(float height);

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
            void setHeight(const std::string& height);

            /**
             * @brief Set the mouse cursor that is displayed when the mouse
             *        is on top of the widget
             * @param cursor The cursor to be shown
             *
             * By default, the arrow cursor is shown
             */
            void setMouseCursor(CursorType cursor);

            /**
             * @brief Get the mouse cursor that is displayed when the mouse
             *        is on top of the widget
             * @return The cursor shown when hovering above the widget
             */
            CursorType getMouseCursor() const;

            /**
             * @brief Get the type of the widget
             * @return The type of the widget
             */
            virtual std::string getWidgetType() const = 0;

            /**
             * @brief Show the widget with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation
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
            void showWithEffect(ShowAnimationType type, Time duration);

            /**
             * @brief Hide the widget with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation
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
            void hideWithEffect(ShowAnimationType type, Time duration);

            /**
             * @brief Check whether or not an animation is currently playing
             * @return True if an animation is playing, otherwise false
             *
             * @see showWithEffect
             * @see hideWithEffect
             */
            bool isAnimationPlaying() const;

            /**
             * @brief Show or hide a widget
             * @param visible True to show or false to hide
             *
             * If the widget is hidden, it won't receive events
             * (and thus won't send callbacks) nor will it be drawn
             *
             * The widget is visible by default.
             */
            void setVisible(bool visible);

            /**
             * @brief Check if the widget is visible or not
             * @return True if the widget is visible or false if hidden
             */
            bool isVisible() const;

            /**
             * @brief Toggle the visibility of the widget
             *
             * This function will hide the widget if its currently
             * visible and vice versa
             *
             * @see setVisible
             */
            void toggleVisibility();

            /**
             * @brief Check if the widget is a container or not
             * @return True if the widget is a container, otherwise false
             *
             * A container widget is a widget that can store other widgets
             * inside it. Such widgets inherit from IWidget class
             */
            bool isContainer() const;

            /**
             * @brief Check if coordinates lie inside the widget
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return true if coordinates lie inside the widget, false if
             *         coordinates do not lie inside the widget
             */
            bool contains(float x, float y) const;

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
            bool unsubscribe(const std::string& event, int id);

            /**
             * @brief Make a copy of the widget
             * @return A copy of the widget
             *
             * You should use this function if you don't care about the type
             * of the widget, otherwise use the widgets copy function for
             * copying purposes
             */
            virtual Widget::Ptr clone() const = 0;

            /**
             * @internal
             * @brief Get the internal widget pointer
             * @return The internal widget pointer
             *
             * @warning This function is intended for internal use only and
             * should never be called outside of IME
             */
            const std::shared_ptr<void> getInternalPtr() const;

            /**
             * @brief Destructor
             */
            ~Widget() override;

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

            /**
             * @brief Set whether or not the widget is a container
             * @param container True to flag as container, otherwise false
             *
             * A container widget is a widget that can store other widgets
             * inside it. Such widgets inherit from IWidget class
             *
             * All widgets are not containers by default
             */
            void setAsContainer(bool container);

        private:
            std::unique_ptr<priv::IWidgetImpl> pimpl_;
            EventEmitter eventEmitter_; //!< Widgets event publisher
            bool isContainer_{false};   //!< Stores whether or not a widget inherits from IContainer
        };
    } // namespace ui

    /**
     * @brief Bind to the x position of a widget
     * @param widget Widget to bind to
     * @return The bound position
     */
    extern IME_API std::string bindLeft(ui::Widget* widget);

    /**
     * @brief Bind to the y position of the widget
     * @param widget Widget to bind to
     * @return The bound position
     */
    extern IME_API std::string bindTop(ui::Widget* widget);

    /**
     * @brief Bind to the width of a widget
     * @param widget The widget to bind to
     * @return The bound size
     */
    extern IME_API std::string bindWidth(ui::Widget* widget);

    /**
     * @brief Bind to the height of a widget
     * @param widget The widget to bind to
     * @return The bound size
     */
    extern IME_API std::string bindHeight(ui::Widget* widget);

    /**
     * @brief Bind to the right position of a widget
     * @param widget Widget to bind to
     * @return The bound position
     */
    extern IME_API std::string bindRight(ui::Widget* widget);

    /**
     * @brief Bind to the bottom position of a widget
     * @param widget Widget to bind to
     * @return The bound position
     */
    extern IME_API std::string bindBottom(ui::Widget* widget);

    /**
     * @brief Bind to the position of the widget
     * @param widget Widget to bind to
     * @return The bound position
     */
    extern IME_API std::string bindPosition(ui::Widget* widget);

    /**
     * @brief Bind to the size of the widget
     * @param widget The widget to bind to
     * @return The bound size
     */
    extern IME_API std::string bindSize(ui::Widget* widget);

    /**
     * @brief Bind to the minimum value of two values
     * @param value1 The first value
     * @param value2 The second value
     * @return The bound minimum
     *
     * The values can be relative or absolute. For relative values insert
     * the percentage (%) at the end
     *
     * @code
     * widget->setHeight(ime::bindMin("50, "100"); //Height will be set to 50 pixels
     *
     * widget->setHeight(ime::bindMin("10%", "15%"); //Height will be set to 10% of the widgets parent height
     *
     * @endcode
     */
    extern IME_API std::string bindMin(const std::string& value1, const std::string& value2);

    /**
     * @brief Bind to the maximum of two values
     * @param value1 The first value
     * @param value2 The second value
     * @return The bound value
     *
     * The values can be relative or absolute. For relative values insert
     * the percentage (%) at the end
     *
     * @code
     * widget->setHeight(ime::bindMin("50, "100"); //Height will be set to 100 pixels
     *
     * widget->setHeight(ime::bindMin("10%", "15%"); //Height will be set to 15% of the widgets parent height
     *
     * @endcode
     */
    extern IME_API std::string bindMax(const std::string& value1, const std::string& value2);
}

#endif // IME_WIDGET_H
