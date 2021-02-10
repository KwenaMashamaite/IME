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

#ifndef IME_SPINCONTROL_H
#define IME_SPINCONTROL_H

#include "IME/Config.h"
#include "IME/ui/widgets/IClickableWidget.h"
#include "IME/ui/renderers/SpinButtonRenderer.h"
#include "IME/ui/renderers/EditBoxRenderer.h"

namespace tgui {
    class SpinControl;
}

namespace ime {
    namespace ui {
        /**
         * @brief A spin control widget
         */
        class IME_API SpinControl : public IClickableWidget {
        public:
            using sharedPtr = std::shared_ptr<SpinControl>; //!< Shared widget pointer
            using constSharedPtr = std::shared_ptr<const SpinControl>; //!< const shared widget pointer
            
            /**
             * @brief Create a new spin control widget
             * @param minValue The minimum value of teh spin control
             * @param maxValue The maximum value of the spin control
             * @param initialValue The initial value of the spin control
             * @param decimal The number of decimal places to display
             * @param step The increment value
             */
            SpinControl(float minValue = 0.0f, float maxValue = 10.0f,
                float initialValue = 0.0f, unsigned int decimal = 0,
                float step = 1.0f);

            /**
             * @brief Create a new spin control widget
             * @param minValue The minimum value of teh spin control
             * @param maxValue The maximum value of the spin control
             * @param initialValue The initial value of the spin control
             * @param decimal The number of decimal places to display
             * @param step The increment value
             * @return The new spin control
             */
            static sharedPtr create(float minValue = 0.0f, float maxValue = 10.0f,
                float initialValue = 0.0f, unsigned int decimal = 0,
                float step = 1.0f);

            /**
             * @brief Create a copy of another spin control
             * @param other The spin control to be copied
             * @param shareRenderer True if the new spin control should have the
             *          same renderer as the copied spin control
             * @return The new toggle spin control widget
             *
             * When the spin controls share a renderer, changes in a render
             * property of one of the spin controls automatically reflect on
             * the other spin control, otherwise each spin control has its own
             * renderer and changes in render properties are isolated to the
             * specific spin control.
             *
             * @note when the spin controls don't share a render, the renderer
             * of the new spin control widget will initially have the properties
             * of the copied spin control such that the two look the same after
             * this function returns
             *
             * By default, the spin controls share a renderer
             *
             * @warning Once a renderer is shared, it cannot be unshared at
             * a later time
             */
            static sharedPtr copy(constSharedPtr other, bool shareRenderer = true);

            /**
             * @brief Set the spin controls renderer
             * @param renderer The new renderer
             *
             * The renderer determines how the spin control is displayed.
             *
             * @note The spin control has a default renderer
             *
             * @see getRenderer
             */
            void setSpinButtonRenderer(SpinButtonRenderer::sharedPtr renderer);

            /**
             * @brief Get the spin controls renderer
             * @return The spin controls renderer
             *
             * The renderer gives access to functions that determine how the
             * spin control is displayed. It allows you to manipulate things such
             * as the background colour, text colour, border colour etc...
             *
             * @see setRenderer
             */
            SpinButtonRenderer::sharedPtr getSpinButtonRenderer();

            /**
             * @brief Set a minimum value for the spin control
             * @param minValue The value to set
             *
             * If the specified value is larger than the maximum value then it
             * will be changed to this value and the previous maximum will be
             * the new minimum. The default minimum value is 0
             *
             * @see setMaximum
             */
            void setMinimumValue(float minValue);

            /**
             * @brief Get the minimum value
             * @return The minimum value
             */
            float getMinimumValue() const;

            /**
             * @brief Set the maximum value for the spin control
             * @param maxValue The value to be set
             *
             * The default maximum value is 10
             *
             * @see setMinimumValue
             */
            void setMaximumValue(float maxValue);

            /**
             * @brief Get the maximum value for the spin control
             * @return The maximum value
             */
            float getMaximumValue() const;

            /**
             * @brief Set the current value
             * @param value The value to be set
             *
             * The value must not be smaller than the minimum value or bigger
             * than the maximum value
             *
             * @see setMaximumValue and setMinimumValue
             */
            void setValue(float value);

            /**
             * @brief Get the current value
             * @return The current value
             */
            float getValue() const;

            /**
             * @brief Set by how much the value changes for each each arrow press
             * @param step The new step size
             *
             * The default step size is 1, which means the spin control will
             * only use integer values between minimum and maximum. When set
             * to 0, the slider will be able to use any floating point value
             * between minimum and maximum values.
             *
             * @note The step must not be negative
             */
            void setStep(float step);

            /**
             * @brief Get the step value on each arrow press
             * @return The step value on each arrow press
             *
             * @see setStep
             */
            float getStep() const;

            /**
             * @brief Set the number of decimal places to display
             * @param decimalPlaces The new number of decimal places
             *
             * The default value is 0, which means that the value has to be
             * an integer
             */
            void setDecimalPlaces(unsigned int decimalPlaces);

            /**
             * @brief Get the number of decimal places that are  displayed
             * @return The current number of decimal places
             */
            unsigned int getDecimalPlaces() const;

            /**
             * @brief Set the character size of the text
             * @param charSize New character size
             */
            void setTextSize(unsigned int charSize) override;

            /**
             * @brief Get the character size of the text
             * @return The character size of the text
             */
            unsigned int getTextSize() const override;

            /**
             * @brief Set the size of the spin control
             * @param width The width of the spin control
             * @param height The height of the spin control
             */
            void setSize(float width, float height) override;

            /**
             * @brief Set the size of the spin control relative to the size of
             *        its parent
             * @param width The new width of the spin control
             * @param height The new height of the spin control
             *
             * The size is specified in percentages as shown below:
             *
             * @code
             * spin control->setSize({"20%", "5%"});
             * @endcode
             */
            void setSize(const std::string& width, const std::string& height) override;

            /**
             * @brief Get the size of the spin control
             * @return Current size of the spin control
             *
             * This function only returns the size of the spin control (It does
             * not accommodate margin, outline thickness etc ...)
             *
             * @see getAbsoluteSize
             */
            Vector2f getSize() const override;

            /**
             * @brief Get the absolute size of the spin control
             * @return The absolute size of the spin control
             *
             * The absolute size includes the size of the spin control, the padding,
             * margin and outline thickness
             *
             * @see getSize
             */
            Vector2f getAbsoluteSize() override;

            /**
             * @brief Set the width of the spin control
             * @param width New width of the spin control
             *
             * This function sets the width while keeping the height
             * the same
             *
             * @see setSize
             */
            void setWidth(float width) override;

            /**
             * @brief Set the width of the spin control relative to its parent
             * @param width New width
             *
             * The relative width is given in percentages as shown:
             *
             * @code
             * spin control->setWidth("10%");
             * @endcode
             *
             * This function sets the width of the spin control while keeping the
             * height the same
             *
             * @see setSize
             */
            void setWidth(const std::string& width) override;

            /**
             * @brief Set the height of the spin control
             * @param height New height of the spin control
             *
             * This function sets the height while keeping the width
             * the same
             *
             * @see setSize
             */
            void setHeight(float height) override;

            /**
             * @brief Set the height of the spin control relative to its parent
             * @param height New height
             *
             * The relative height is given in percentages as shown:
             *
             * @code
             * spin control->setHeight("10%");
             * @endcode
             *
             * This function sets the height of the spin control while keeping the
             * width the same
             *
             * @see setSize
             */
            void setHeight(const std::string& height) override;

            /**
             * @brief Set the mouse cursor that is displayed when the mouse
             *        is on top of the spin control
             * @param cursor The cursor to be shown
             *
             * By default, the arrow cursor is shown
             */
            void setMouseCursor(CursorType cursor) override;

            /**
             * @brief Get the mouse cursor that is displayed when the mouse
             *        is on top of the spin control
             * @return The cursor shown when hovering above the spin control
             */
            CursorType getMouseCursor() const override;

            /**
             * @brief Get the type of the spin control
             * @return The type of the spin control
             */
            std::string getWidgetType() const override;

            /**
             * @brief Show the spin control with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will be played if the spin control currently
             * visible
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the spin control
             * will be back in the state in which it was when this function
             * was called
             *
             * @see hideWithEffect
             * @see isAnimationPlaying
             */
            void showWithEffect(ShowAnimationType type, int duration) override;

            /**
             * @brief Hide the spin control with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will also be played if the spin control currently
             * hidden but it will not be seen
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the spin control
             * will be back in the state in which it was when this function
             * was called
             *
             * @see showWithEffect
             * @see isAnimationPlaying
             */
            void hideWithEffect(ShowAnimationType type, int duration) override;

            /**
             * @brief Check whether or not an animation is currently playing
             * @return True if an animation is playing, otherwise false
             *
             * @see showWithEffect
             * @see hideWithEffect
             */
            bool isAnimationPlaying() const override;

            /**
             * @brief Show or hide a spin control
             * @param visible True to show or false to hide
             *
             * If the spin control is hidden, it won't receive events
             * (and thus won't send callbacks) nor will it be drawn
             *
             * The spin control is visible by default.
             */
            void setVisible(bool visible) override;

            /**
             * @brief Check if the spin control is visible or not
             * @return True if the spin control is visible or false if hidden
             */
            bool isVisible() const override;

            /**
             * @brief Toggle the visibility of the spin control
             *
             * This function will hide the spin control if its currently
             * visible and vice versa
             *
             * @see setVisible
             */
            void toggleVisibility() override;

            /**
             * @brief Check if coordinates lie inside the spin control
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return true if coordinates lie inside the spin control, false if
             *         coordinates do not lie inside the spin control
             */
            bool contains(float x, float y) const override;

            /**
             * @brief Set the position of the spin control
             * @param x X coordinate of the new position
             * @param y Y coordinate of the new position
             *
             * This function completely overwrites the previous position.
             * use move function to apply an offset based on the previous
             * position instead
             *
             * The default position of a the spin control is (0, 0)
             *
             * @see move
             */
            void setPosition(float x, float y) override;

            /**
             * @brief Set the position of the spin control
             * @param position New position
             *
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the spin control is (0, 0)
             *
             * @see move
             */
            void setPosition(Vector2f position) override;

            /**
             * @brief Set the position of the spin control relative to the
             *        size of its parent
             * @param x New x coordinate of the spin control
             * @param y New y coordinate of the spin control
             *
             * The position is specified in percentages as shown below:
             *
             * @code
             * spin control->setPosition({"5%", "10%"});
             * @endcode
             *
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the spin control is (0, 0)
             *
             * @see move
             */
            void setPosition(const std::string& x, const std::string& y) override;

            /**
             * @brief Get the position of the spin control
             * @return Current position of the spin control
             */
            Vector2f getPosition() const override;

            /**
             * @brief Get the absolute position of the spin control
             * @return The absolute position of the spin control
             *
             * Unlike getPosition, this function returns the absolute
             * position of the top-left point of the spin control instead
             * of the relative position to its parent
             *
             * @see setPosition
             */
            Vector2f getAbsolutePosition() const override;

            /**
             * @brief Set the orientation of the spin control
             * @param angle New rotation, in degrees
             *
             * This function completely overwrites the previous rotation.
             * See the rotate function to add an angle based on the previous
             * rotation instead.
             *
             * The default rotation of the spin control is 0
             *
             * @see rotate
             */
            void setRotation(float angle) override;

            /**
             * @brief Rotate the spin control
             * @param angle Angle of rotation, in degrees
             *
             * This function adds to the current rotation of the spin control,
             * unlike setRotation which overwrites it
             *
             * @see setRotation
             */
            void rotate(float angle) override;

            /**
             * @brief Get the orientation of the spin control
             * @return Current rotation, in degrees
             *
             * The rotation is always in the range [0, 360]
             */
            float getRotation() const override;

            /**
             * @brief Set the scale factors of the spin control
             * @param factorX New horizontal scale factor
             * @param factorY New vertical scale factor
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(float factorX, float factorY) override;

            /**
             * @brief Set the scale factor of the spin control
             * @param scale New scale
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(Vector2f scale) override;

            /**
             * @brief Scale the spin control by an offset
             * @param factorX Horizontal scale factor
             * @param factorY Vertical scale factor
             *
             * This function multiplies the current scale of the spin control,
             * unlike setScale which overwrites it
             *
             * @see setScale
             */
            void scale(float factorX, float factorY) override;

            /**
             * @brief Scale the spin control by an offset
             * @param offset Offset to apply
             *
             * This function multiplies the current scale of the spin control,
             * unlike setScale which overwrites it
             *
             * @see setScale
             */
            void scale(Vector2f offset) override;

            /**
             * @brief Get the current scale of the spin control
             * @return Current scale of the spin control
             */
            Vector2f getScale() const override;

            /**
             * @brief Set the local origin of the spin control
             * @param x X coordinate of the new origin
             * @param y Y coordinate of the new origin
             *
             * The origin of the spin control defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the spin control, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the spin control is (0, 0)
             */
            void setOrigin(float x, float y) override;

            /**
             * @brief Set the local origin of the spin control
             * @param origin New origin
             *
             * The origin of the spin control defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the spin control, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the spin control is (0, 0)
             */
            void setOrigin(Vector2f origin) override;

            /**
             * @brief Get the local origin of the spin control
             * @return Local origin of the spin control
             */
            Vector2f getOrigin() const override;

            /**
             * @brief Move the spin control by a given offset
             * @param offsetX Horizontal offset
             * @param offsetY Vertical offset
             *
             * This function adds to the current position of the spin control,
             * unlike setPosition which overwrites it
             *
             * @see setPosition
             */
            void move(float offsetX, float offsetY) override;

            /**
             * @brief Move the spin control by a given offset
             * @param offset Offset to apply
             *
             * This function adds to the current position of the spin control,
             * unlike setPosition which overwrites it
             *
             * @see setPosition
             */
            void move(Vector2f offset) override;

            /**
             * @brief Enable or disable the spin control
             * @param isEnable Set true to enable the spin control, false to
             *        disable the spin control
             *
             * The spin control is enabled by default
             *
             * @note Disabling the spin control cancels all the interaction events
             */
            void setEnabled(bool isEnable) override;

            /**
             * @brief Check if spin control is enabled or disabled
             * @return True if spin control is enabled, false if spin control is disabled
             */
            bool isEnabled() const override;

            /**
             * @brief Disable spin control if its currently enabled and vice versa
             */
            void toggleEnabled() override;

            /**
             * @brief Focus or unfocus spin control
             * @param isFocused True to focus or false to unfocus spin control
             */
            void setFocused(bool isFocused) override;

            /**
             * @brief Check if spin control is focused or not
             * @return True if spin control is focused. Otherwise, false
             */
            bool isFocused() const override;

            /**
             * @internal
             * @brief Get the internal pointer to a third party widget
             * @return The internal pointer to a third party widget
             *
             * @warning This function is intended for internal use only and
             * should never be called under any circumstance
             */
            std::shared_ptr<tgui::Widget> getInternalPtr() override;

        private:
            /**
             * @brief Initialize events
             *
             * These events will notify event listeners about an internal state
             * change of the widget when that state changes
             */
            void initEvents();

        private:
            std::shared_ptr<tgui::SpinControl> spinControl_;   //!< Internal spin control
            SpinButtonRenderer::sharedPtr spinButtonRenderer_; //!< Renderer for the spin button part of the widget
        };
    }
}

#endif //IME_SPINCONTROL_H
