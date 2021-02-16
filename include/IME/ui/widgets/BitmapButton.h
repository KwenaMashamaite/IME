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

#ifndef IME_BITMAPBUTTON_H
#define IME_BITMAPBUTTON_H

#include "IME/Config.h"
#include "IME/ui/widgets/ClickableWidget.h"
#include "IME/ui/renderers/ButtonRenderer.h"
#include <memory>

namespace ime {
    namespace ui {
        /**
         * @brief Button widget with an image displayed next to the text (or
         *        centered in the button without text)
         */
        class IME_API BitmapButton : public ClickableWidget {
        public:
            using sharedPtr = std::shared_ptr<BitmapButton>; //!< Shared widget pointer
            using constSharedPtr = std::shared_ptr<const BitmapButton>; //!< const shared widget pointer

            /**
             * @brief Move constructor
             */
            BitmapButton(BitmapButton&&);

            /**
             * @brief Move assignment operator
             */
            BitmapButton& operator=(BitmapButton&&);

            /**
             * @brief Create a new bitmap button widget
             * @param text Text to display on the button
             * @return The new bitmap button
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
             * @param text New text to display
             *
             * This function will overwrite any text that was previously
             * set
             */
            void setText(const std::string &text);

            /**
             * @brief Get text displayed on the button
             * @return The Text displayed on the button
             */
            std::string getText() const;

            /**
             * @brief Set the image that should be displayed next to the text
             * @param filename Filename of the image to display
             * @throws FileNotFound if the specified image cannot be found on
             *         the disk
             */
            void setImage(const std::string& filename);

            /**
             * @brief Set the relative size of the image to display next to the
             *        text
             * @param relativeHeight height of the image compared to the button
             *        height
             *
             * The relative height must be in the range [0, 1] If set to 0
             * (default), the image will always have its original size, no
             * matter what the button size is
             */
            void setImageScaling(float relativeHeight);

            /**
             * @brief Get the relative size of the image displayed next to the
             *        text
             * @return The relative size of the image displayed next to the text
             */
            float getImageScaling() const;

            /**
             * @brief Get the type of the button
             * @return The type of the button
             */
            std::string getWidgetType() const override;

            /**
             * @brief Destructor
             */
            ~BitmapButton();

        private:
            /**
             * @brief Create a bitmap button
             * @param buttonText Text to be displayed on the button
             */
            BitmapButton(const std::string &buttonText = "");

        private:
            class ButtonImpl;
            std::unique_ptr<ButtonImpl> pimpl_;
        };
    }
}

#endif // IME_BITMAPBUTTON_H
