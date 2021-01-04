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

#include "IWidget.h"
#include "IME/graphics/ui/renderers/SliderRenderer.h"
#include <TGUI/Widgets/Slider.hpp>

namespace IME {
    namespace UI {
        /**
         * @brief Slider widget
         */
        class IME_API Slider : public IWidget {
        public:
            /**
             * @brief Construct a slider
             * @param minValue The minimum slider value
             * @param maxValue The maximum slider value
             */
            Slider(float minValue = 0, float maxValue = 10);

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
             * @brief Set the tooltip text
             * @param text New text content
             *
             * The tooltip text is displayed when when hovering over the slider
             */
            void setText(const std::string &text) override;

            /**
             * @brief Get the tooltip text
             * @return The tooltip text
             *
             * @see setText
             */
            std::string getText() const override;

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
             * @brief Get the type of the slider
             * @return The type of the slider
             */
            std::string getType() const override;

            /**
             * @brief Show a hidden slider
             *
             * This function will reveal the slider that was hidden prior to
             * function call. Calling this function on a slider that is not
             * hidden has no effect
             */
            void show() override;

            /**
             * @brief Hide slider
             */
            void hide() override;

            /**
             * @brief Check if the slider is hidden or not
             * @return True if the slider is hidden, otherwise false
             */
            bool isHidden() const override;

            /**
             * @brief Toggle the visibility of the slider
             *
             * This function will hide the slider if its currently
             * visible and vice versa
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
             * @brief Get the position of the slider
             * @return Current position of the slider
             */
            Vector2f getPosition() const override;

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
            std::string text_;                         //!< Tooltip text
        };
    }
}

#endif // IME_SLIDER_H
