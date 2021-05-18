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
#include "IME/ui/widgets/Widget.h"
#include "IME/ui/renderers/SliderRenderer.h"
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief Slider widget
         */
        class IME_API Slider : public Widget {
        public:
            using Ptr = std::unique_ptr<Slider>; //!< Unique widget pointer
            using ConstPtr = std::unique_ptr<const Slider>; //!< Const unique widget pointer

            /**
             * @brief Copy constructor
             */
            Slider(const Slider&);

            /**
             * @brief Copy assignment operator
             */
            Slider& operator=(const Slider&);

            /**
             * @brief Move constructor
             */
            Slider(Slider&&) noexcept;

            /**
             * @brief Move assignment operator
             */
            Slider& operator=(Slider&&) noexcept;

            /**
             * @brief Create a new slider widget
             * @param minimum The minimum value of the slider
             * @param maximum The maximum value of the slider
             * @return The new slider
             */
            static Slider::Ptr create(float minimum = 0, float maximum = 10);

            /**
             * @brief Create a copy of this widget
             * @return A copy of this widget
             *
             * @see clone
             */
            Slider::Ptr copy() const;

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
            SliderRenderer* getRenderer();
            const SliderRenderer* getRenderer() const;

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
             * @brief Make a copy of this widget
             * @return A copy of this widget
             *
             * You should use this function if you don't care about the type
             * of the widget, otherwise use the widgets copy function
             *
             * @see copy
             */
            Widget::Ptr clone() const override;

            /**
             * @brief Get the type of the slider
             * @return The type of the slider
             */
            std::string getWidgetType() const override;

            /**
             * @brief Destructor
             */
            ~Slider() override;

        private:
            /**
             * @brief Construct a slider
             * @param minValue The minimum slider value
             * @param maxValue The maximum slider value
             */
            explicit Slider(float minValue = 0, float maxValue = 10);

            /**
             * @brief Initialize events emitted by the widget
             */
            void initEvents();

        private:
            class SliderImpl;
            std::unique_ptr<SliderImpl> pimpl_;
        };
    }
}

#endif // IME_SLIDER_H
