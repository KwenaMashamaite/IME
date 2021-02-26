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

#ifndef IME_PROGRESSBAR_H
#define IME_PROGRESSBAR_H

#include "IME/Config.h"
#include "IME/ui/widgets/ClickableWidget.h"
#include "IME/ui/renderers/ProgressBarRenderer.h"
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief Widget for displaying progress
         */
        class IME_API ProgressBar : public ClickableWidget {
        public:
            using Ptr = std::shared_ptr<ProgressBar>; //!< Shared widget pointer
            using ConstPtr = std::shared_ptr<const ProgressBar>; //!< const shared widget pointer

            /**
             * @brief Determines in which direction the progress bar is filled
             *        when value goes from minimum to maximum
             */
            enum class FillDirection {
                LeftToRight,  //!< Start filling at the left side and go to the right
                RightToLeft,  //!< Start filling at the right side and go to the left
                TopToBottom,  //!< Start filling at the top an go downward
                BottomToTop   //!< Start filling at the bottom and go upward
            };

            /**
             * @brief Move constructor
             */
            ProgressBar(ProgressBar&&);

            /**
             * @brief Move assignment operator
             */
            ProgressBar& operator=(ProgressBar&&);

            /**
             * @brief Create a new progress bar widget
             * @param text Text displayed on the progress bar
             * @return The new progress bar
             */
            static ProgressBar::Ptr create(const std::string& text = "");

            /**
             * @brief Create a copy of another progress bar
             * @param other The progress bar to copy
             * @param shareRenderer True if the new progress bar should have the
             *          same renderer as the copied progress bar
             * @return The new progress bar widget
             *
             * When the progress bars share a renderer, changes in a render
             * property of one of the progress bars automatically reflect on
             * the other progress bar, otherwise each progress bar has its own renderer
             * and changes in render properties are isolated to the specific
             * progress bar.
             *
             * @note when the progress bars don't share a render, the renderer of
             * the new progress bar widget will initially have the properties of
             * the copied progress bar such that the two look the same after this
             * function returns
             *
             * By default, the progress bars share a renderer
             *
             * @warning Once a renderer is shared, it cannot be unshared at
             * a later time
             */
            static ProgressBar::Ptr copy(ProgressBar::ConstPtr other,
                bool shareRenderer = true);

            /**
             * @brief Get the progress bars renderer
             * @return The progress bars renderer
             *
             * The renderer gives access to functions that determine how the
             * widget is displayed. It allows you to manipulate things such
             * as the background colour, text colour, border colour etc...
             *
             * @see setRenderer
             */
            ProgressBarRenderer::Ptr getRenderer();
            const ProgressBarRenderer::Ptr getRenderer() const;

            /**
             * @brief Set a minimum value
             * @param minValue The value to set
             *
             * If the specified value is larger than the maximum value then
             * it will be changed to this value and the previous maximum will
             * be the new minimum. The default minimum value is 0
             *
             * @see setMaximum
             */
            void setMinimumValue(unsigned int minValue);

            /**
             * @brief Get the minimum value
             * @return The minimum value
             */
            unsigned int getMinimumValue() const;

            /**
             * @brief Set the maximum value
             * @param maxValue The value to be set
             *
             * The default maximum value is 10
             *
             * @see setMinimumValue
             */
            void setMaximumValue(unsigned int maxValue);

            /**
             * @brief Get the maximum value
             * @return The maximum value
             */
            unsigned int getMaximumValue() const;

            /**
             * @brief Set the current value
             * @param value The value to be set
             *
             * The value must not be smaller than the minimum value or
             * bigger than the maximum value
             */
            void setValue(unsigned int value);

            /**
             * @brief Get the current value
             * @return The current value
             */
            unsigned int getValue() const;

            /**
             * @brief Increment the value
             * @return The new value
             *
             * The value is increased by 1 and will never exceed the maximum
             * value
             */
            unsigned int incrementValue();

            /**
             * @brief Set the fill direction of the progress bar
             * @param direction The fill direction to be set
             *
             * The fill direction defines how the progress bar is filled when
             * the value goes from minimum to maximum. By default the progress
             * bar is filled from left to right
             */
            void setFillDirection(FillDirection direction);

            /**
             * @brief Get the fill direction of the progress bar
             * @return The current fill direction
             */
            FillDirection getFillDirection() const;

            /**
             * @brief Set the text displayed on the progress bar
             * @param text New text content
             *
             * This text is centered by default
             */
            void setText(const std::string &text);

            /**
             * @brief Get the progress bars text content
             * @return The progress bars text content
             */
            std::string getText() const;

            /**
             * @brief Get the type of the progress bar
             * @return The type of the progress bar
             */
            std::string getWidgetType() const override;

            /**
             * @brief Destructor
             */
            ~ProgressBar();

        private:
            /**
             * @brief Construct a progress bar
             * @param text Text displayed on the progress bar
             */
            explicit ProgressBar(const std::string& text = "");

        private:
            class Impl;
            std::unique_ptr<Impl> pimpl_;
        };
    }
}

#endif // IME_PROGRESSBAR_H
