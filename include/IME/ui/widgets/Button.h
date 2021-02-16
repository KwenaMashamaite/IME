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

#ifndef IME_BUTTON_H
#define IME_BUTTON_H

#include "IME/Config.h"
#include "IME/ui/widgets/ClickableWidget.h"
#include "IME/ui/renderers/ButtonRenderer.h"
#include <string>
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief Widget that can display text perform actions
         */
        class IME_API Button : public ClickableWidget {
        public:
            using sharedPtr = std::shared_ptr<Button>; //!< Shared widget pointer
            using constSharedPtr = std::shared_ptr<const Button>; //!< const shared widget pointer

            /**
             * @brief Move constructor
             */
            Button(Button&&);

            /**
             * @brief Move assignment operator
             */
            Button& operator=(Button&&);

            /**
             * @brief Create a new button widget
             * @param text The text to display on the button
             * @return The new button
             */
            static sharedPtr create(const std::string& text = "");

            /**
             * @brief Create a copy of another button
             * @param other The button to copy
             * @param shareRenderer True if the new button should have the
             *          same renderer as the copied button
             * @return The new button widget
             *
             * When the buttons share a renderer, changes in a render
             * property of one of the buttons automatically reflect on
             * the other button, otherwise each button has its own renderer
             * and changes in render properties are isolated to the specific
             * button.
             *
             * @note when the buttons don't share a render, the renderer of
             * the new button widget will initially have the properties of
             * the copied button such that the two look the same after this
             * function returns
             *
             * By default, the buttons share a renderer
             *
             * @warning Once a renderer is shared, it cannot be unshared at
             * a later time
             */
            static sharedPtr copy(constSharedPtr other, bool shareRenderer = true);

            /**
             * @brief Get the buttons renderer
             * @return The buttons renderer
             *
             * The renderer gives access to functions that determine how the
             * button is displayed. It allows you to manipulate things such
             * as the background colour, text colour, border colour etc...
             *
             * @see setRenderer
             */
            ButtonRenderer::sharedPtr getRenderer();
            const ButtonRenderer::sharedPtr getRenderer() const;

            /**
             * @brief Set the text displayed on the button
             * @param text Text to display
             *
             * This function will overwrite any text that was previously
             * set
             */
            void setText(const std::string &text);

            /**
             * @brief Get the text displayed on the button
             * @return The text displayed oon the button
             */
            std::string getText() const;

            /**
             * @brief Get the type of the button
             * @return The type of the button
             */
            std::string getWidgetType() const override;

            /**
             * @brief Destructor
             */
            ~Button();

        private:
            /**
             * @brief Create a button
             * @param buttonText Text to be displayed on the button
             */
            explicit Button(const std::string &buttonText);

        private:
            class ButtonImpl;
            std::unique_ptr<ButtonImpl> pimpl_;
        };
    }
}

#endif // IME_BUTTON_H
