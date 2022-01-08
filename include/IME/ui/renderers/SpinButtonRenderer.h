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

#ifndef IME_SPINBUTTONRENDERER_H
#define IME_SPINBUTTONRENDERER_H

#include "IME/Config.h"
#include "IME/ui/renderers/IWidgetRenderer.h"
#include "IME/graphics/Colour.h"

namespace tgui {
    class SpinButtonRenderer; //Forward declaration
}

namespace ime {
    namespace ui {
        /**
         * @brief A SpinControl widget renderer
         *
         * This class allows you to manipulate the render properties of a
         * SpinControl widget
         */
        class IME_API SpinButtonRenderer : public IWidgetRenderer {
        public:
            using Ptr = std::unique_ptr<SpinButtonRenderer>; //!< Unique renderer pointer

            /**
             * @brief Change the size of the widget borders
             * @param borders The size of the borders
             */
            void setBorders(const Borders& borders);

            /**
             * @brief Get the size of the widgets borders
             * @return The size of the widgets borders
             */
            Borders getBorders() const;

            /**
             * @brief Set the space between arrows
             * @param space The space to set
             */
            void setSpaceBetweenArrows(float space);

            /**
             * @brief Get the space between arrows
             * @return The space between arrows
             */
            float getSpaceBetweenArrows() const;

            /**
             * @brief Set the background colour of the tab
             * @param colour The background colour to set
             *
             * @note that this colour is ignored when you set a background image
             */
            void setBackgroundColour(Colour colour);

            /**
            * @brief Get the background colour of tab
            * @return The background colour of the tab
            */
            Colour getBackgroundColour() const;

            /**
             * @brief Set the background colour of the tab when the mouse
             *         enters it
             * @param colour The background colour to set
             *
             * @note that this colour is ignored when you set a background image
             */
            void setBackgroundHoverColour(Colour colour);

            /**
             * @brief Get the background colour of the tab when the mouse
             *         enters it
             * @return The background colour of the tab when the mouse
             *         enters it
             */
            Colour getBackgroundHoverColour() const;

            /**
             * @brief Set the colour of the arrows
             * @param colour The colour to set
             *
             * This colour is ignored if the up and down arrow textures are set
             */
            void setArrowColor(Colour colour);

            /**
             * @brief Get the colour of teh arrows
             * @return The colour of the arrows
             */
            Colour getArrowColour() const;

            /**
             * @brief Set the colour of the arrows when when the mouse enters
             *         enters the spin button
             * @param colour The colour to set
             */
            void setArrowHoverColor(Colour colour);

            /**
             * @brief Get the colour of the arrows when the mouse enters the
             *        spin button
             * @return
             */
            Colour getArrowHoverColour() const;

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
             * @brief Set the image that is used as the up arrow
             * @param filename Filename of the image to set
             *
             * When this image and the down image are set, the arrow color
             * property will be ignored
             */
            void setUpArrowTexture(const std::string& filename);

            /**
             * @brief Set the image that is used as the up arrow when the
             *        mouse enters the spin button
             * @param filename Filename of the image to set
             *
             * When this image is set, the hover arrow color property will be
             * ignored
             */
            void setUpArrowHoverTexture(const std::string& filename);

            /**
             * @brief Set the image that is used as the down arrow
             * @param filename Filename of the image to set
             *
             * When this image and the down image are set, the arrow color
             * property will be ignored
             */
            void setDownArrowTexture(const std::string& filename);

            /**
             * @brief Set the image that is used as the down arrow when the
             *        mouse enters the spin button
             * @param filename Filename of the image to set
             *
             * When this image is set, the hover arrow color property will be
             * ignored
             */
            void setDownArrowHoverTexture(const std::string& filename);

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
             * @brief Create a copy of the render
             * @return A copy of the render
             */
            IWidgetRenderer::Ptr clone() const override;

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
            ~SpinButtonRenderer() override;

        private:
            tgui::SpinButtonRenderer* renderer_;
        };
    }
}

#endif //IME_SPINBUTTONRENDERER_H
