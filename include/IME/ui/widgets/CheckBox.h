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

#ifndef IME_CHECKBOX_H
#define IME_CHECKBOX_H

#include "IME/Config.h"
#include "IME/ui/widgets/ClickableWidget.h"
#include "IME/ui/renderers/CheckBoxRenderer.h"
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief Checkbox widget
         */
        class IME_API CheckBox : public ClickableWidget {
        public:
            using Ptr = std::unique_ptr<CheckBox>; //!< Unique widget pointer
            using ConstPtr = std::shared_ptr<const CheckBox>; //!< Const unique widget pointer

            /**
             * @brief Copy constructor
             */
            CheckBox(const CheckBox&);

            /**
             * @brief Copy assignment operator
             */
            CheckBox& operator=(const CheckBox&);

            /**
             * @brief Move Constructor
             */
            CheckBox(CheckBox&&) noexcept;

            /**
             * @brief Move assignment operator
             */
            CheckBox& operator=(CheckBox&&) noexcept;

            /**
             * @brief Create a new checkbox widget
             * @param text Text to display next to the checkbox
             * @return The new checkbox
             */
            static CheckBox::Ptr create(const std::string& text = "");

            /**
             * @brief Create a copy of this widget
             * @return A copy of this widget
             *
             * @see clone
             */
            CheckBox::Ptr copy() const;

            /**
             * @brief Get the checkboxes renderer
             * @return The checkboxes renderer
             *
             * The renderer gives access to functions that determine how the
             * checkbox is displayed. It allows you to manipulate things such
             * as the background colour, text colour, border colour etc...
             *
             * @see setRenderer
             */
            CheckBoxRenderer* getRenderer();
            const CheckBoxRenderer* getRenderer() const;

            /**
             * @brief Allow or disallow the checkbox to be checked by clicking
             *        on the text next to it
             * @param acceptTextClick True to allow, or false to disallow
             */
            void setTextClickable(bool acceptTextClick);

            /**
             * @brief Check if the the radio checkbox can be checked by clicking
             *         on the text next to it
             * @return True if the checkbox is clickable by clicking on the
             *         text next to it, otherwise false
             */
            bool isTextClickable() const;

            /**
             * @brief Check or uncheck the checkbox
             * @param isChecked True to check the checkbox, otherwise false
             */
            void setChecked(bool isChecked);

            /**
             * @brief Check whether the checkbox is checked or not
             * @return True if it is checked, otherwise false
             */
            bool isChecked() const;

            /**
             * @brief Set the text to display next to the checkbox
             * @param text Text to display
             *
             * This function will overwrite any text that was previously
             * set
             */
            void setText(const std::string &text);

            /**
             * @brief Get the text displayed next to the checkbox
             * @return The text displayed next to the checkbox
             */
            std::string getText() const;

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
             * @brief Get the type of the check box
             * @return The type of the check box
             */
            std::string getWidgetType() const override;

            /**
             * @brief Destructor
             */
            ~CheckBox() override;

        private:
            /**
             * @brief Create the checkbox
             * @param text Text to display next to the checkbox
             */
            explicit CheckBox(const std::string &text = "");

        private:
            class CheckBoxImpl;
            std::unique_ptr<CheckBoxImpl> pimpl_;
        };
    }
}

#endif // IME_CHECKBOX_H
