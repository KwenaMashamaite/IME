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


#ifndef IME_TABSRENDERER_H
#define IME_TABSRENDERER_H

#include "IME/Config.h"
#include "IWidgetRenderer.h"
#include "IME/graphics/Colour.h"
#include <TGUI/Renderers/TabsRenderer.hpp>

namespace ime {
    namespace ui {
        /**
         * @brief A Tabs widget renderer
         *
         * This class allows you to manipulate the render properties of a
         * Tabs widget
         */
        class IME_API TabsRenderer : public IWidgetRenderer {
        public:
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
             * @brief Set the background colour of the tab when it is 
             *        disabled
             * @param colour Background colour to set
             * 
             * @note This colour is ignored when you set a background image
             */
            void setDisabledBackgroundColour(Colour colour);

            /**
             * @brief Get the background colour of the tab when it is 
             *        disabled
             * @return The background colour of the tab when it is 
             *        disabled
             */
            Colour getDisabledBackgroundColour() const;

            /**
             * @brief Set the background colour of the selected tab
             * @param backgroundColour New selected tab background colour
             */
            void setSelectedBackgroundColour(Colour backgroundColour);
            
            /**
             * @brief Get the background colour of the elected tab
             * @return The background colour of the selected tab
             */
            Colour getSelectedBackgroundColour() const;

            /**
             * @brief Set the background colour of the selected tab when the
             *        mouse is on top of it
             * @param backgroundColour The new selected tab hover background
             *        colour
             */
            void setSelectedBackgroundHoverColour(Colour backgroundColour);

            /**
             * @brief Get the background colour of the selected tab when the
             *        mouse is on top of it
             * @return Selected tab background hover colour
             */
            Colour getSelectedBackgroundHoverColour() const;

            /**
             * @brief Set the colour of the text displayed on the tab
             *
             * @param colour The new test colour
             */
            void setTextColour(Colour colour);

            /**
             * @brief Get the colour of the tab text
             * @return The colour of the tab text
             */
            Colour getTextColour() const;

            /**
             * @brief Set the text colour when the mouse enters the tab
             * @param colour The colour to be set
             */
            void setTextHoverColour(Colour colour);

            /**
             * @brief Get the text colour when the mouse enters the tab
             * @return The text colour when the mouse enters the tab
             */
            Colour getTextHoverColour() const;

            /**
             * @brief Set the colour of the text when the tab is disabled
             * @param colour The colour to be set
             */
            void setDisabledTextColour(Colour colour);

            /**
             * @brief Get the colour of the text when the tab is disabled
             * @return The colour of the text when the tab is disabled
             */
            Colour getDisabledTextColour() const;

            /**
             * @brief Set the colour of the text for a selected tab
             * @param textColour The new selected tab colour
             */
            void setSelectedTextColour(Colour textColour);

            /**
             * @brief Get the colour of the text when the tab is selected
             * @return The colour of the text when th tab is selected
             */
            Colour getSelectedTextColour() const;

            /**
             * @brief Set the colour of the text for a tab when the mouse is
             *        on top of it
             * @param textColour The new selected tab hover text colour
             */
            void setSelectedTextHoverColour(Colour textColour);

            /**
             * @brief Get the colour of the text when it is selected and the
             *        mouse is on top of it
             * @return Selected tab hover  text colour
             */
            Colour getSelectedTextColourHover() const;

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
             * @brief Set the background colour of when the mouse enters the
             *      tab
             * @param colour The background colour to set
             */
            void setBorderHoverColour(Colour colour);

            /**
              * @brief Get the background colour of when the mouse enters the
              *      tab
              * @return The background colour of when the mouse enters the
              *      tab
              */
            Colour getBorderHoverColour() const;

            /**
             * @brief Set the border colours for a selected tab
             * @param colour The new selected border colour
             */
            void setSelectedBorderColour(Colour colour);

            /**
             * @brief Get the colour of the borders when a tab is selected
             * @return The colour of the borders when a tab is selected
             */
            Colour getSelectedBorderColour() const;

            /**
             * @brief Set the colour of the borders for a selected tab when
             *        the mouse is on top of it
             * @param colour The new selected tab hover colour
             */
            void setSelectedBorderHoverColour(Colour colour);

            /**
             * @brief Get the colour of the borders when a tab is selected and
             *        the mouse is on top of it
             * @return The selected border hover colour
             */
            Colour getSelectedBorderHoverColour() const;

            /**
             * @brief Set the image of a tab
             * @param filename Filename of the image to be set
             *
             * When this image is set, then the background colour properties
             * will be ignored for non-selected tabs
             */
            void setTabTexture(const std::string& filename);

            /**
             * @brief Set the image of the tab when the mouse is on top of it
             * @param filename Filename of the image to be set
             */
            void setTabHoverTexture(const std::string& filename);

            /**
             * @brief Set the image of a selected tab
             * @param filename Filename of the image to be set
             *
             * When this image is set then the background colour properties
             * will be ignored for selected tabs
             */
            void setSelectedTabTexture(const std::string& filename);

            /**
             * @brief Set the image of a selected tab when the mouse is on top
             *        of it
             * @param filename Filename of the image to set
             */
            void setSelectedTabHoverTexture(const std::string& filename);

            /**
             * @brief Set the image of the tab when it is disabled
             * @param filename Filename of the image to be set
             *
             * The disabled texture is only used when a normal and selected
             * tab texture are also set
             */
            void setDisabledTabTexture(const std::string& filename);

            /**
             * @brief Set the distance between the text and the side of the tab
             * @param distanceToSide distance between the text and the side of
             *        the tab
             */
            void setDistanceToSide(float distanceToSide);

            /**
             * @brief Get the distance between the text and the side of the tab
             * @return Distance between the text and the side of the tab
             */
            float getDistanceToSide() const;
            
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
            virtual ~TabsRenderer();

        private:
            tgui::TabsRenderer* tabsRenderer_; //!< Pointer to third party tabs renderer
        };
    }
}

#endif //IME_TABSRENDERER_H
