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

#ifndef IME_MENUBARRENDERER_H
#define IME_MENUBARRENDERER_H

#include "IME/Config.h"
#include "IME/ui/renderers/IWidgetRenderer.h"
#include "IME/graphics/Colour.h"

namespace tgui {
    class MenuBarRenderer;
}

namespace ime {
    namespace ui {
        /**
         * @brief A MenuBar renderer
         *
         * This class allows you to manipulate the render properties of a
         * MenuBar widget
         */
        class IME_API MenuBarRenderer : public IWidgetRenderer {
        public:
            using Ptr = std::unique_ptr<MenuBarRenderer>; //!< Shared renderer pointer

            /**
             * @brief Set the background colour of the menu bar
             * @param colour The background colour to set
             *
             * @note that this colour is ignored when you set a background image
             */
            void setBackgroundColour(Colour colour);

            /**
            * @brief Get the background colour of menu bar
            * @return The background colour of the menu bar
            */
            Colour getBackgroundColour() const;

            /**
             * @brief Set the background colour of a menu item when it is selected
             * @param backgroundColour The background colour to set
             */
            void setSelectedBackgroundColour(Colour backgroundColour);

            /**
             * @brief Get the background colour of a menu item when it is selected
             * @return The selected item background colour
             */
            Colour getSelectedBackgroundColour() const;

            /**
             * @brief Set the colour of the text
             * @param textColour The new text colour
             */
            void setTextColour(Colour textColour);
            
            /**
             * @brief Get the colour of the text
             * @return The text colour
             */
            Colour getTextColour() const;

            /**
             * @brief Set the text colour of a menu item when it is selected
             * @param textColour The selected text colour to set
             */
            void setSelectedTextColour(Colour textColour);
            
            /**
             * @brief Get the text colour of a menu item when it is selected
             * @return The text colour of a menu item when it is selected
             */
            Colour getSelectedTextColour() const;

            /**
             * @brief Set the text colour when the menu bar is disabled
             * @param textColour Disabled menu bar text colour
             */
            void setDisabledTextColour(Colour textColour);
            
            /**
             * @brief Get the text colour of the menu bar when it is disabled
             * @return The text colour when disabled
             */
            Colour getDisabledTextColour() const;
            
            /**
             * @brief Set the background image of the menu bar
             * @param filename The filename of the image to set
             * @throws FileNotFoundException if @a filename cannot be found on the disk
             * 
             * When this image is set, the background colour property will be
             * ignored
             */
            void setBackgroundTexture(const std::string& filename);

            /**
             * @brief Set the background image of a menu item when it is not selected
             * @param filename Filename of the image to set
             */
            void setItemBackgroundTexture(const std::string& filename);

            /**
             * @brief Set the background image of a menu item when it is selected
             * @param filename Filename of the image to set
             */
            void setSelectedItemBackgroundTexture(const std::string& filename);
            
            /**
             * @brief Set the distance between the text and the side of the menu item
             * @param distanceToSide distance between the text and the side of the menu item
             */
            void setDistanceToSide(float distanceToSide);
            
            /**
             * @brief Get the distance between the text and the side of the menu item
             * @return The distance between the text and the side of the menu item
             */
            float getDistanceToSide() const;

            /**
             * @brief Set the opacity of the menu bar
             * @param opacity The new opacity of the menu bar in between 0 and 1
             *
             * 0 means completely transparent, while 1 (default) means fully
             * opaque
             */
            void setOpacity(float opacity) override;

            /**
             * @brief Get the opacity of the menu bar
             * @return The opacity of the menu bar
             */
            float getOpacity() const override;

            /**
             * @brief Set the opacity of the menu bar when it is disabled
             * @param opacity Opacity to set between 0 and 1
             *
             * 0 means completely transparent, while 1 (default) means fully
             * opaque. Set to -1 (default) to use the normal opacity value even
             * when the menu bar is disabled.
             */
            void setOpacityDisabled(float opacity) override;

            /**
             * @brief Get the opacity of the menu bar when it is disabled
             * @return The opacity of the menu bar in disabled state
             *
             * This function will return -1 if the menu bar uses the same opacity
             * as the enabled state when it is disabled
             */
            float getOpacityDisabled() const override;

            /**
             * @brief Change the menu bars font
             * @param filename Filename of the new font
             * @throws FileNotFoundException If the font cannot be found on the disk
             */
            void setFont(const std::string &filename) override;

            /**
             * @brief Set whether mouse events should be ignored on transparent
             *        parts of the texture of the menu bar in normal state
             * @param ignoreTransparentParts True to ignore mouse events on
             *        transparent parts of the texture, otherwise false
             *
             * When mouse events are ignored, they are passed to a menu bar behind
             * the menu bar. By default, mouse events are NOT ignored and the
             * menu bar will receive mouse events even on transparent texture
             * parts. This property does nothing if the menu bar doesn't use
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
            ~MenuBarRenderer() override;
            
        private:
            tgui::MenuBarRenderer* menuBarRenderer_; //!< Pointer to third party renderer
        };
    }
}

#endif //IME_MENUBARRENDERER_H
