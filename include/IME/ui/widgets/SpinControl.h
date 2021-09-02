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
#include "IME/ui/widgets/Widget.h"
#include "IME/ui/renderers/SpinButtonRenderer.h"

namespace ime {
    namespace ui {
        /**
         * @brief A widget that can be used to select/adjust a value using
         *        the mouse by clicking up or down on it
         */
        class IME_API SpinControl : public Widget {
        public:
            using Ptr = std::unique_ptr<SpinControl>; //!< Unique widget pointer
            using ConstPtr = std::unique_ptr<const SpinControl>; //!< Const unique widget pointer

            /**
             * @brief Copy constructor
             */
            SpinControl(const SpinControl&);

            /**
             * @brief Copy assignment operator
             */
            SpinControl& operator=(const SpinControl&);

            /**
             * @brief Move constructor
             */
            SpinControl(SpinControl&&) noexcept;

            /**
             * @brief Move assignment operator
             */
            SpinControl& operator=(SpinControl&&) noexcept;

            /**
             * @brief Create a new spin control widget
             * @param minValue The minimum value of teh spin control
             * @param maxValue The maximum value of the spin control
             * @param initialValue The initial value of the spin control
             * @param decimal The number of decimal places to display
             * @param step The increment value
             * @return The new spin control
             */
            static SpinControl::Ptr create(float minValue = 0.0f, float maxValue = 10.0f,
                float initialValue = 0.0f, unsigned int decimal = 0, float step = 1.0f);

            /**
             * @brief Create a copy of this widget
             * @return A copy of this widget
             *
             * @see clone
             */
            SpinControl::Ptr copy() const;

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
            SpinButtonRenderer* getSpinButtonRenderer();
            const SpinButtonRenderer* getSpinButtonRenderer() const;

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
             * @brief Get the type of the spin control
             * @return The type of the spin control
             */
            std::string getWidgetType() const override;

            /**
             * @brief Destructor
             */
            ~SpinControl() override;

        private:
            /**
             * @brief Create a new spin control widget
             * @param minValue The minimum value of teh spin control
             * @param maxValue The maximum value of the spin control
             * @param initialValue The initial value of the spin control
             * @param decimal The number of decimal places to display
             * @param step The increment value
             */
            explicit SpinControl(float minValue = 0.0f, float maxValue = 10.0f,
                float initialValue = 0.0f, unsigned int decimal = 0, float step = 1.0f);

            /**
             * @brief Initialize events emitted by the widget
             */
            void initEvents();

        private:
            class SpinControlImpl;
            std::unique_ptr<SpinControlImpl> pimpl_;
        };
    }
}

#endif //IME_SPINCONTROL_H
