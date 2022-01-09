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

#ifndef IME_RADIOBUTTON_H
#define IME_RADIOBUTTON_H

#include "IME/Config.h"
#include "IME/ui/widgets/ClickableWidget.h"
#include "IME/ui/renderers/RadioButtonRenderer.h"
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief A round widget than can be selected or deselected when clicked
         *        with a mouse
         */
        class IME_API RadioButton : public ClickableWidget {
        public:
            using Ptr = std::unique_ptr<RadioButton>; //!< Unique widget pointer
            using ConstPtr = std::unique_ptr<const RadioButton>; //!< Const unique widget pointer

            /**
             * @brief Copy constructor
             */
            RadioButton(const RadioButton&);

            /**
             * @brief Copy assignment operator
             */
            RadioButton& operator=(const RadioButton&);

            /**
             * @brief Move constructor
             */
            RadioButton(RadioButton&&) noexcept;

            /**
             * @brief Move constructor
             */
            RadioButton& operator=(RadioButton&&) noexcept;

            /**
             * @brief Create a new radio button widget
             * @param text Text to be displayed next to the button
             * @return The new radio button
             */
            static RadioButton::Ptr create(const std::string& text = "");

            /**
             * @brief Create a copy of this widget
             * @return A copy of this widget
             *
             * @see clone
             */
            RadioButton::Ptr copy() const;

            /**
             * @brief Get the buttons renderer
             * @return The buttons renderer
             *
             * The renderer gives access to functions that determine how the
             * button is displayed. It allows you to manipulate things such
             * as the background colour, text colour, border colour etc...
             */
            RadioButtonRenderer* getRenderer();
            const RadioButtonRenderer* getRenderer() const;

            /**
             * @brief Allow or disallow the button to be checked by clicking
             *        on the text next to it
             * @param acceptTextClick True to allow, or false to disallow
             */
            void setTextClickable(bool acceptTextClick);

            /**
             * @brief Check if the the button can be checked by clicking
             *         on the text next to it
             * @return True if the button is clickable by clicking on the
             *         text next to it, otherwise false
             */
            bool isTextClickable() const;

            /**
             * @brief Check or uncheck the button
             * @param isChecked True to check the button, otherwise false
             */
            void setChecked(bool isChecked);

            /**
             * @brief Check whether the button is checked or not
             * @return True if it is checked, otherwise false
             */
            bool isChecked() const;

            /**
             * @brief Set the text displayed next to the button
             * @param text The text to display
             *
             * This function will overwrite any text that was previously
             * set
             */
            void setText(const std::string &text);

            /**
             * @brief Get the text displayed next to the button
             * @return The buttons text content
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
             * @brief Get the type of the button
             * @return The type of the button
             */
            std::string getWidgetType() const override;

            /**
             * @brief Destructor
             */
            ~RadioButton() override;

        private:
            /**
             * @brief Create a button
             * @param buttonText Text to be displayed next to the button
             */
            explicit RadioButton(const std::string &buttonText = "");

            /**
             * @brief Initialize events emitted by the widget
             */
            void initEvents();

        private:
            class ButtonImpl;
            std::unique_ptr<ButtonImpl> pimpl_;
        };
    }
}

/**
 * @class ime::ui::RadioButton
 * @ingroup ui
 *
 * <table>
 * <caption>Events generated by ime::ui::RadioButton </caption>
 * <tr><th> Name            <th> Argument Type  <th> Description
 * <tr><td> check           <td> void           <td> The radio button was checked
 * <tr><td> uncheck         <td> void           <td> The radio button was unchecked
 * <tr><td> valueChange     <td> bool           <td> The radio button was checked or unchecked.
 *                                                   Parameter = new state of the radio button
 * </table>
 *
 * Usage Example:
 * @code
 * radioButton.on("check", ime::Callback<>([] {
 *      std::cout << "Checked" << "\n";
 * }));
 *
 * radioButton.on("valueChange", ime::Callback<bool>([](bool checked) {
 *      if (checked)
 *          std::cout << "Checked" << "\n";
 *      else
 *          std::cout << "Unchecked" << "\n";
 * })):
 * @endcode
 */

#endif //IME_RADIOBUTTON_H
