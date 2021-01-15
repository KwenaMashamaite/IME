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

#ifndef IME_SLIDER_H
#define IME_SLIDER_H

#include "IME/Config.h"
#include "IWidget.h"
#include "IME/ui/renderers/SliderRenderer.h"
#include <TGUI/Widgets/Slider.hpp>
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief Slider widget
         */
        class IME_API Slider : public IWidget {
        public:
            using sharedPtr = std::shared_ptr<Slider>; //!< Shared widget pointer
            using constSharedPtr = std::shared_ptr<const Slider>; //!< const shared widget pointer

            /**
             * @brief Construct a slider
             * @param minValue The minimum slider value
             * @param maxValue The maximum slider value
             */
            explicit Slider(float minValue = 0, float maxValue = 10);

            /**
             * @brief Create a new slider widget
             * @param minimum The minimum value of the slider
             * @param maximum The maximum value of the slider
             * @return The new slider
             */
            static sharedPtr create(float minimum = 0, float maximum = 10);

            /**
             * @brief Create a copy of another slider
             * @param other The slider to copy
             * @param shareRenderer True if the new slider should have the
             *          same renderer as the copied slider
             * @return The new slider widget
             *
             * When the sliders share a renderer, changes in a render
             * property of one of the sliders automatically reflect on
             * the other slider, otherwise each slider has its own renderer
             * and changes in render properties are isolated to the specific
             * slider.
             *
             * @note when the sliders don't share a render, the renderer of
             * the new slider widget will initially have the properties of
             * the copied slider such that the two look the same after this
             * function returns
             *
             * By default, the sliders share a renderer
             *
             * @warning Once a renderer is shared, it cannot be unshared at
             * a later time
             */
            static sharedPtr copy(constSharedPtr other, bool shareRenderer = true);

            /**
             * @brief Set the sliders renderer
             * @param renderer The new renderer
             *
             * The renderer determines how the label is displayed. The slider
             * has a default renderer which can be manipulated using the
             * getRenderer function
             *
             * @see getRenderer
             */
            void setRenderer(std::shared_ptr<SliderRenderer> renderer);

            /**
             * @brief Get the sliders renderer
             * @return The sliders renderer
             *
             * The renderer gives access to functions that determine how the
             * widget is displayed. It allows you to manipulate things such
             * as the background colour, border colour etc...
             *
             * @see setRenderer
             */
            std::shared_ptr<SliderRenderer> getRenderer();

            /**
             * @brief Set a minimum value for the slider
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
             * @brief Set the maximum value for the slider
             * @param maxValue The value to be set
             *
             * The default maximum value is 10
             *
             * @see setMinimumValue
             */
            void setMaximumValue(float maxValue);

            /**
             * @brief Get the maximum value for the slider
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
             * @brief Change the number of positions the thumb advances with
             *        each move
             * @param step The new step size
             *
             *
             * The default step size is 1, which means the slider will only use
             * integer values between minimum and maximum. When set to 0, the
             * slider will be able to use any floating point value between
             * minimum and maximum values
             */
            void setStep(float step);

            /**
             * @brief Get the number of positions the thumb advances with each
             *        move
             * @return The current step size
             */
            float getStep() const;

            /**
             * @brief Set the orientation of the slider
             * @param isVertical Set true to place the slider vertically or false
             *                 to set the orientation horizontal
             *
             * The default orientation is horizontal
             */
            void setVerticalScroll(bool isVertical);

            /**
             * @brief Check if the slider lies vertically or horizontally
             * @return True if the slider lies vertically or false if the slider
             *          lies horizontally
             */
            bool isVerticalScroll() const;

            /**
             * @brief Invert the minimum and maximum positions
             * @param isInverted True to invert the direction, otherwise
             *         false
             *
             * By default the minimum is on the left for horizontal sliders and
             * on the bottom for vertical sliders. The slider is not inverted
             * by default
             */
            void invert(bool isInverted);

            /**
             * @brief Check if the slider is inverted or not
             * @return True if the slider is inverted, otherwise false
             *
             * @see setInvertedDirection
             */
            bool isInverted() const;

            /**
             * @brief Set whether the mouse wheel can be used to change the
             *        value of the slider
             * @param changeValueOnScroll True to change the value with the
             *        mouse wheel, otherwise false
             *
             * The value is changeable by the mouse wheel by default
             */
            void setChangeValueOnScroll(bool changeValueOnScroll);

            /**
             * @brief Check if the value is changed with the mouse wheel or not
             * @return True if the value is changed with the mouse wheel,
             *         otherwise false
             */
            bool isValueChangedOnScroll() const;

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
             * @brief Set the size of the slider
             * @param width The width of the slider
             * @param height The height of the slider
             */
            void setSize(float width, float height) override;

            /**
             * @brief Set the size of the slider relative to the size of
             *        its parent
             * @param width The new width of the slider
             * @param height The new height of the slider
             *
             * The size is specified in percentages as shown below:
             *
             * @code
             * slider->setSize({"20%", "5%"});
             * @endcode
             */
            void setSize(const std::string& width, const std::string& height) override;

            /**
             * @brief Get the size of the slider
             * @return Current size of the slider
             *
             * This function only returns the size of the slider (It does
             * not accommodate margin, outline thickness etc ...)
             *
             * @see getAbsoluteSize
             */
            Vector2f getSize() const override;

            /**
             * @brief Get the absolute size of the slider
             * @return The absolute size of the slider
             *
             * The absolute size includes the size of the slider, the padding,
             * margin and outline thickness
             *
             * @see getSize
             */
            Vector2f getAbsoluteSize() override;

            /**
             * @brief Set the width of the slider
             * @param width New width of the slider
             * 
             * This function sets the width while keeping the height
             * the same
             * 
             * @see setSize
             */
            void setWidth(float width) override;

            /**
             * @brief Set the width of the slider relative to its parent
             * @param width New width
             * 
             * The relative width is given in percentages as shown:
             * 
             * @code
             * slider->setWidth("10%");
             * @endcode
             * 
             * This function sets the width of the slider while keeping the
             * height the same
             * 
             * @see setSize
             */
            void setWidth(const std::string& width) override;

            /**
             * @brief Set the height of the slider
             * @param height New height of the slider
             * 
             * This function sets the height while keeping the width 
             * the same
             * 
             * @see setSize
             */
            void setHeight(float height) override;

            /**
             * @brief Set the height of the slider relative to its parent
             * @param height New height
             * 
             * The relative height is given in percentages as shown:
             * 
             * @code
             * slider->setHeight("10%");
             * @endcode
             * 
             * This function sets the height of the slider while keeping the
             * width the same
             * 
             * @see setSize
             */
            void setHeight(const std::string& height) override;

            /**
             * @brief Set the mouse cursor that is displayed when the mouse
             *        is on top of the slider
             * @param cursor The cursor to be shown
             *
             * By default, the arrow cursor is shown
             */
            void setMouseCursor(CursorType cursor) override;

            /**
             * @brief Get the mouse cursor that is displayed when the mouse
             *        is on top of the slider
             * @return The cursor shown when hovering above the slider
             */
            CursorType getMouseCursor() const override;

            /**
             * @brief Get the type of the slider
             * @return The type of the slider
             */
            std::string getWidgetType() const override;

            /**
             * @brief Show the slider with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will be played if the slider currently
             * visible
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the slider
             * will be back in the state in which it was when this function
             * was called
             *
             * @see hideWithEffect
             * @see isAnimationPlaying
             */
            void showWithEffect(ShowAnimationType type, int duration) override;

            /**
             * @brief Hide the slider with an animation
             * @param type Type of the animation
             * @param duration Duration of the animation in milliseconds
             *
             * The animation will also be played if the slider currently
             * hidden but it will not be seen
             *
             * @note During the animation the position, size and/or opacity
             * opacity may change. Once the animation is done the slider
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
             * @brief Show or hide a slider
             * @param visible True to show or false to hide
             *
             * If the slider is hidden, it won't receive events
             * (and thus won't send callbacks) nor will it be drawn
             *
             * The slider is visible by default.
             */
            void setVisible(bool visible) override;

            /**
             * @brief Check if the slider is visible or not
             * @return True if the slider is visible or false if hidden
             */
            bool isVisible() const override;

            /**
             * @brief Toggle the visibility of the slider
             *
             * This function will hide the slider if its currently
             * visible and vice versa
             * 
             * @see setVisible
             */
            void toggleVisibility() override;

            /**
             * @brief Check if coordinates lie inside the slider
             * @param x X coordinate to be checked
             * @param y Y coordinate to be checked
             * @return true if coordinates lie inside the slider, false if
             *         coordinates do not lie inside the slider
             */
            bool contains(float x, float y) const override;

            /**
             * @brief Set the position of the slider
             * @param x X coordinate of the new position
             * @param y Y coordinate of the new position
             *
             * This function completely overwrites the previous position.
             * use move function to apply an offset based on the previous
             * position instead
             *
             * The default position of a the slider is (0, 0)
             *
             * @see move
             */
            void setPosition(float x, float y) override;

            /**
             * @brief Set the position of the slider
             * @param position New position
             *
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead. 
             * 
             * The default position of the slider is (0, 0)
             * 
             * @see move
             */
            void setPosition(Vector2f position) override;

            /**
             * @brief Set the position of the slider relative to the
             *        size of its parent
             * @param x New x coordinate of the slider
             * @param y New y coordinate of the slider
             * 
             * The position is specified in percentages as shown below:
             * 
             * @code
             * slider->setPosition({"5%", "10%"});
             * @endcode
             * 
             * This function completely overwrites the previous position.
             * Use the move function to apply an offset based on the previous
             * position instead.
             *
             * The default position of the slider is (0, 0)
             *
             * @see move
             */
            void setPosition(const std::string& x, const std::string& y) override;

            /**
             * @brief Get the position of the slider
             * @return Current position of the slider
             */
            Vector2f getPosition() const override;

            /**
             * @brief Get the absolute position of the slider
             * @return The absolute position of the slider
             * 
             * Unlike getPosition, this function returns the absolute 
             * position of the top-left point of the slider instead 
             * of the relative position to its parent
             * 
             * @see setPosition
             */
            Vector2f getAbsolutePosition() const override;

            /**
             * @brief Set the orientation of the slider
             * @param angle New rotation, in degrees
             *
             * This function completely overwrites the previous rotation.
             * See the rotate function to add an angle based on the previous
             * rotation instead. 
             * 
             * The default rotation of the slider is 0
             *
             * @see rotate
             */
            void setRotation(float angle) override;

            /**
             * @brief Rotate the slider
             * @param angle Angle of rotation, in degrees
             *
             * This function adds to the current rotation of the slider,
             * unlike setRotation which overwrites it
             * 
             * @see setRotation
             */
            void rotate(float angle) override;

            /**
             * @brief Get the orientation of the slider
             * @return Current rotation, in degrees
             *
             * The rotation is always in the range [0, 360]
             */
            float getRotation() const override;

            /**
             * @brief Set the scale factors of the slider
             * @param factorX New horizontal scale factor
             * @param factorY New vertical scale factor
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(float factorX, float factorY) override;

            /**
             * @brief Set the scale factor of the slider
             * @param scale New scale
             *
             * This function completely overwrites the previous scale
             *
             * @see scale
             */
            void setScale(Vector2f scale) override;

            /**
             * @brief Scale the slider by an offset
             * @param factorX Horizontal scale factor
             * @param factorY Vertical scale factor
             *
             * This function multiplies the current scale of the slider,
             * unlike setScale which overwrites it
             * 
             * @see setScale
             */
            void scale(float factorX, float factorY) override;

            /**
             * @brief Scale the slider by an offset
             * @param offset Offset to apply
             *
             * This function multiplies the current scale of the slider,
             * unlike setScale which overwrites it
             * 
             * @see setScale
             */
            void scale(Vector2f offset) override;

            /**
             * @brief Get the current scale of the slider
             * @return Current scale of the slider
             */
            Vector2f getScale() const override;

            /**
             * @brief Set the local origin of the slider
             * @param x X coordinate of the new origin
             * @param y Y coordinate of the new origin
             *
             * The origin of the slider defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the slider, and ignore all
             * transformations (position, scale, rotation).
             *
             * The default origin of the slider is (0, 0)
             */
            void setOrigin(float x, float y) override;

            /**
             * @brief Set the local origin of the slider
             * @param origin New origin
             *
             * The origin of the slider defines the center point for
             * all transformations (position, scale, rotation).
             * The coordinates of this point must be relative to the
             * top-left corner of the slider, and ignore all
             * transformations (position, scale, rotation).
             * 
             * The default origin of the slider is (0, 0)
             */
            void setOrigin(Vector2f origin) override;

            /**
             * @brief Get the local origin of the slider
             * @return Local origin of the slider
             */
            Vector2f getOrigin() const override;

            /**
             * @brief Move the slider by a given offset
             * @param offsetX Horizontal offset
             * @param offsetY Vertical offset
             *
             * This function adds to the current position of the slider,
             * unlike setPosition which overwrites it
             * 
             * @see setPosition
             */
            void move(float offsetX, float offsetY) override;

            /**
             * @brief Move the slider by a given offset
             * @param offset Offset to apply
             *
             * This function adds to the current position of the slider,
             * unlike setPosition which overwrites it
             * 
             * @see setPosition
             */
            void move(Vector2f offset) override;

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
             * change of the object when that state changes
             */
            void initEvents();

        private:
            std::shared_ptr<tgui::Slider> slider_;     //!< Pointer to third party library
            std::shared_ptr<SliderRenderer> renderer_; //!< Renderer for this slider
        };
    }
}

#endif // IME_SLIDER_H
