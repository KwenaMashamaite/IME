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

#ifndef IME_PROGRESSBARRENDERER_H
#define IME_PROGRESSBARRENDERER_H

#include "IWidgetRenderer.h"
#include "IME/graphics/Colour.h"
#include <TGUI/Renderers/ProgressBarRenderer.hpp>

namespace IME {
    namespace UI {
        /**
         * @brief Class for rendering a ProgressBar
         *
         * This class allows you to manipulate the render properties of a
         * ProgressBar
         */
        class IME_API ProgressBarRenderer : public IWidgetRenderer {
        public:
            /**
             * @brief Change the size of the widget borders
             * @param borders The size of the borders
             */
            void setBorders(const Borders& borders);

            /**
             * @brief Get the ize of the widgets borders
             * @return The size of the widgets borders
             */
            Borders getBorders() const;

            /**
             * @brief Set the colour of the text that is optionally displayed
             *        on top of the progress bar
             * @param colour The new test colour
             */
            void setTextColour(Colour colour);

            /**
             * @brief Get the colour of the text that is optionally displayed on
             *        top of the progress bar
             * @return The colour of the progress bar text
             */
            Colour getTextColour() const;

            /**
             * @brief Set the text colour of the text that is on top of the
             *        filled part of the progress bar
             * @param colour he new text colour that is displayed on top of the
             *        filled part
             */
            void setTextColourFilled(Colour colour);

            /**
             * @brief Get the colour of the text that is on top of the filled
             *        part of the progress bar
             * @return Text colour that is displayed on top of the filled part
             */
            Colour getTextColourFilled() const;

            /**
             * @brief Set the background colour of the progress bar
             * @param colour The background colour to set
             *
             * This is the colour that is displayed on the part of the progress
             * bar that is not filled.
             *
             * @note that this colour is ignored when you set a background image
             *
             * @see setBackgroundTexture
             */
            void setBackgroundColour(Colour colour);

            /**
             * @brief Get the background colour of the progress bar
             * @return The background colour of the progress bar
             */
            Colour getBackgroundColour() const;

            /**
             * @brief Set the fill colour of the progress bar
             * @param colour fill colour to set
             *
             * This is the colour that is used to fill the progress bar and is
             * drawn on top of the background colour
             *
             * @note that this colour is ignored when you set an fill image
             */
            void setFillColour(Colour colour);

            /**
             * @brief Get the fill colour of the progress bar
             * @return Fill colour of the progress bar
             */
            Colour getFillColour() const;

            /**
             * @brief Set the border colour
             * @param colour The border colour to set
             */
            void setBorderColour(Colour colour);

            /**
             * @brief Get the border colour
             * @return The border colour
             */
            Colour getBorderColour() const;

            /**
             * @brief Set the background image of the progress bar
             * @param texture The new background image
             *
             * When this image is set then the background colour property will
             * be ignored
             */
            void setBackgroundTexture(const std::string& texture);

            /**
             * @brief Set the fill image of the progress bar
             * @param texture The new fill texture
             *
             * When this image is set then the fill colour property will be
             * ignored
             */
            void setFillTexture(const std::string& texture);

            /**
             * @brief Set the text style
             * @param style TNew text style
             *
             * The default style is TextStyle::Regular
             */
            void setTextStyle(TextStyle style);

            /**
             * @brief Get the text style
             * @return The text style
             */
            TextStyle getTextStyle() const;

            /**
             * @brief Set the opacity of the widget
             * @param opacity The new opacity of the widget in between 0 and 1
             *
             * 0 means completely transparent, while 1 (default) means fully
             * opaque
             */
            void setOpacity(float opacity) override;

            /**
             * @brief Get the opacity of the widget
             * @return The opacity of the widget
             */
            float getOpacity() const override;

            /**
             * @brief Set the opacity of the widget when it is disabled
             * @param opacity Opacity to set between 0 and 1
             *
             * 0 means completely transparent, while 1 (default) means fully
             * opaque. Set to -1 (default) to use the normal opacity value even
             * when the widget is disabled.
             */
            void setOpacityDisabled(float opacity) override;

            /**
             * @brief Get the opacity of the widget when it is disabled
             * @return The opacity of the widget in disabled state
             *
             * This function will return -1 if the widget uses the same opacity
             * as the enabled state when it is disabled
             */
            float getOpacityDisabled() const override;

            /**
             * @brief Change the widgets font
             * @param filename Filename of the new font
             * @throws FileNotFound If the font cannot be found on the disk
             */
            void setFont(const std::string &filename) override;

            /**
             * @brief Set whether mouse events should be ignored on transparent
             *        parts of the texture of the widget in normal state
             * @param ignoreTransparentParts True to ignore mouse events on
             *        transparent parts of the texture, otherwise false
             *
             * When mouse events are ignored, they are passed to a widget behind
             * the widget. By default, mouse events are NOT ignored and the
             * widget will receive mouse events even on transparent texture
             * parts. This property does nothing if the widget doesn't use
             * textures
             */
            void ignoreTransparentTexture(bool ignoreTransparentParts) override;

            /**
             * @brief Check if mouse events are ignored on transparent parts of
             *        the texture or not
             * @return True if mouse events are ignored, otherwise false
             *
             * @see ignoreTransparentTexture
             */
            bool isTransparentTextureIgnored() const override;

            /**
             * @internal
             * @brief Set the pointer to the third party renderer
             * @param renderer The third party
             *
             * @warning This function is meant for internal usage only and
             * should never be called under any circumstance
             */
            void setInternalPtr(tgui::WidgetRenderer *renderer) override;

            /**
             * @internal
             * @brief Get pointer to third party renderer
             * @return The pointer to the third party renderer
             *
             * @warning This function is meant for internal usage only and
             * should never be called under any circumstance
             */
            tgui::WidgetRenderer *getInternalPtr() override;

            /**
             * @brief Destructor
             */
            virtual ~ProgressBarRenderer();

        private:
            tgui::ProgressBarRenderer* progressBarRenderer_; //!< Pointer to third party renderer
        };
    }
}

#endif // IME_PROGRESSBARRENDERER_H
