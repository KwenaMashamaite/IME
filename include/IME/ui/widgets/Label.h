////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#ifndef IME_LABEL_H
#define IME_LABEL_H

#include "IME/Config.h"
#include "IME/ui/widgets/Widget.h"
#include "IME/ui/renderers/LabelRenderer.h"
#include <string>
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief Widget that displays a single or multiple lines of text
         *
         * Note that this widget does not generate any interaction events
         * such as click events
         */
        class IME_API Label : public Widget {
        public:
            using Ptr = std::unique_ptr<Label>; //!< Unique widget pointer
            using ConstPtr = std::unique_ptr<const Label>; //!< const unique widget pointer

            /**
             * @brief The horizontal text alignment
             */
            enum class HorizontalAlignment {
                Left,   //!< Put the text on the left side (default)
                Center, //!< Center the text horizontally
                Right   //!< Put the text on the right side (e.g. for numbers)
            };

            /**
             * @brief The vertical text alignment
             */
            enum class VerticalAlignment {
                Top ,   //!< Put the text at the top (default)
                Center, //!< Center the text vertically
                Bottom  //!< Put the text at the bottom
            };

            /**
             * @brief Copy constructor
             */
            Label(const Label&);

            /**
             * @brief Copy assignment operator
             */
            Label& operator=(const Label&);

            /**
             * @brief Move constructor
             */
            Label(Label&&) noexcept;

            /**
             * @brief Move assignment operator
             */
            Label& operator=(Label&&) noexcept;

            /**
             * @brief Create a new label widget
             * @param text Text to be displayed on the label
             * @return The new label
             */
            static Label::Ptr create(const std::string& text = "");

            /**
             * @brief Create a copy of this widget
             * @return A copy of this widget
             *
             * @see clone
             */
            Label::Ptr copy() const;

            /**
             * @brief Get the labels renderer
             * @return The labels renderer
             *
             * The renderer gives access to functions that determine how the
             * label is displayed. It allows you to manipulate things such
             * as the background colour, text colour, border colour etc...
             *
             * @see setRenderer
             */
            LabelRenderer* getRenderer();
            const LabelRenderer* getRenderer() const;

            /**
             * @brief Set the text displayed on the label
             * @param text New text content
             *
             * When the text is auto-sized (default), then the size of the
             * label will be changed to fit the whole text
             *
             * @see setAutoSize
             */
            void setText(const std::string &text);

            /**
             * @brief Get the labels text content
             * @return The labels text content
             */
            std::string getText() const;

            /**
             * @brief Set the horizontal text alignment
             * @param alignment The new horizontal alignment
             *
             * By default the alignment is to the left
             */
            void setHorizontalAlignment(HorizontalAlignment alignment);

            /**
             * @brief Get the current horizontal alignment
             * @return The current horizontal alignment
             */
            HorizontalAlignment getHorizontalAlignment() const;

            /**
             * @brief Set the vertical text alignment
             * @param alignment The new vertical text alignment
             *
             * By default the text is aligned to the top
             */
            void setVerticalAlignment(VerticalAlignment alignment);

            /**
             * @brief Get the current vertical text alignment
             * @return Vertical text alignment
             */
            VerticalAlignment getVerticalAlignment() const;

            /**
             * @brief Set whether ot not the label is auto-sized
             * @param autoSize True to enable auto-size of false to disable
             *
             * When the label is in auto-size mode, the width and height of
             * the label will be changed to fit the text. Otherwise, only
             * the part defined by the size will be visible
             *
             * The label is auto-sized by default
             */
            void setAutoSize(bool autoSize);

            /**
             * @brief Check if the label is auto-sized or not
             * @return True if the size of the label is changed when the text
             *         change, otherwise false
             */
            bool getAutoSize() const;

            /**
             * @brief Set the maximum width that the text will have when
             *        auto-sizing
             * @param maximumWidth The new maximum text width
             *
             * When the label is auto-sizing the text will be split over
             * several lines when its width would exceed the value passed
             * to this function.
             *
             * @note This property is ignored when an exact size has been
             * given. Pass 0 to this function to disable the maximum
             *
             * @see setAutoSize
             */
            void setMaximumTextWidth(float maximumWidth);

            /**
             * @brief Get the maximum width that the text will have when
             *        auto-sizing
             * @return The maximum width of the text
             *
             * This function will return:
             * - The width of the label minus the padding when a specific
             *   size was set.
             * - The maximum text width when auto-sizing and a maximum was set.
             * - 0 when auto-sizing but there is no maximum width.
             */
            float getMaximumTextWidth() const;

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
             * @brief Get the type of the widget
             * @return The type of the widget
             */
            std::string getWidgetType() const override;

            /**
             * @brief Destructor
             */
            ~Label() override;

        private:
            /**
             * @brief Create a label
             * @param text Text to be displayed on the label
             */
            explicit Label(const std::string &text);

        private:
            class LabelImpl;
            std::unique_ptr<LabelImpl> pimpl_;
        };
    }
} 

#endif // IME_LABEL_H
