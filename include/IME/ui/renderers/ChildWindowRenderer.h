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

#ifndef IME_CHILDWINDOWRENDERER_H
#define IME_CHILDWINDOWRENDERER_H

#include "IME/Config.h"
#include "IWidgetRenderer.h"
#include "IME/graphics/Colour.h"

namespace tgui {
    class ChildWindowRenderer;
}

namespace ime {
    namespace ui {
        /**
         * @brief A ChildWindow widget renderer
         *
         * This class allows you to manipulate the render properties of a
         * ChildWindow
         */
        class IME_API ChildWindowRenderer : public IWidgetRenderer {
        public:
            using Ptr = std::shared_ptr<ChildWindowRenderer>; //!< Shared renderer pointer

            /**
             * @brief Change the ize of the widget borders
             * @param borders The size of the borders
             */
            void setBorders(const Borders& borders);

            /**
             * @brief Get the ize of the widgets borders
             * @return The size of the widgets borders
             */
            Borders getBorders() const;

            /**
             * @brief Set the height of teh title bar
             * @param height New height of the title bar
             */
            void setTitleBarHeight(float height);
            
            /**
             * @brief Get the height of the title bar
             * @return
             */
            float getTitleBarHeight() const;

            /**
             * @brief Set the colour of the title bar
             * @param colour Colour to set
             */
            void setTitleBarColour(Colour colour);

            /**
             * @brief Get the colour of the title bar
             * @return The colour of the title bar
             */
            Colour getTitleBarColour() const;

            /**
             * @brief Set the colour of the title that is displayed in the title
             *        bar of the child window
             * @param colour Colour to set
             */
            void setTitleColour(Colour colour);

            /**
             * @brief Get the colour of the title that is displayed in the title
             *        bar of the child window
             * @return Title bar text colour
             */
            Colour getTitleColour() const;

            /**
             * @brief Set the background colour of the window
             * @param colour The background colour to set
             *
             * @note that this colour is ignored when you set a background image
             */
            void setBackgroundColour(Colour colour);

            /**
             * @brief Get the background colour of window
             * @return The background colour of the window
             */
            Colour getBackgroundColour() const;

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
             * @brief Set the border colour when the window is focused but not
             *        hovered
             * @param colour Border colour to set
             */
            void setFocusedBorderColour(Colour colour);

            /**
             * @brief Get the border colour when the window is focused but not
             *        hovered
             * @return The border colour when the window is focused but not
             *        hovered
             */
            Colour getBorderColourFocused() const;

            /**
             * @brief Set the distance between the title bar and the actual
             *        contents of the child window
             * @param border Space between title bar and child window contents
             */
            void setBorderBelowTitleBar(float border);

            /**
             * @brief Get the distance between the title bar and the actual
             *        contents of the child window
             * @return Space between title bar and child window contents
             */
            float getBorderBelowTitleBar() const;

            /**
             * @brief Set the distance of the title or close button from the
             *        side of the title bar
             * @param distanceToSide Distance between the title and the side of
             *        the title bar
             */
            void setDistanceToSide(float distanceToSide);

            /**
             * @brief Get the distance of the title or close button from the
             *        side of the title bar
             * @return Distance between the title and the side of the title bar
             */
            float getDistanceToSide() const;

            /**
             * @brief Set the distance between the title buttons if multiple
             *        exist
             * @param padding Distance between the title buttons
             */
            void setPaddingBetweenButtons(float padding);

            /**
             * #@brief Get the distance between the title buttons if multiple
             *         exist
             * @return Distance between the title buttons
             */
            float getPaddingBetweenButtons() const;

            /**
             * @brief Set the minimum width of the area where you can drag to
             *        resize the child window
             * @param minimumBorderWidth Minimum amount of pixels where the
             *        child window can be dragged to resize it
             *
             * If the border is larger than @a minimumBorderWidth then this
             * function has no effect. If the borders are smaller, several
             * invisible pixels next to the border can also be used to resize
             * the child window
             */
            void setMinimumResizableBorderWidth(float minimumBorderWidth);

            /**
             * @brief Get the minimum width of the area where you can drag to
             *        resize the child window
             * @return Minimum amount of pixels where the child window can be
             *          dragged to resize it
             */
            float getMinimumResizableBorderWidth() const;
            
            /**
             * @brief Set  whether characters are rendered on top of the title
             *        buttons
             * @param showText True if text is to be shown on the title bar
             *        buttons, otherwise false
             */
            void setShowTextOnTitleButtons(bool showText);
            
            /**
             * @brief Check if characters are rendered on top of the title 
             *        buttons
             * @return True if characters are rendered on top of the title 
             *        buttons, otherwise false
             */
            bool isTextShownOnTitleButtons() const;

            /**
             * @brief Set the image of the title bar
             * @param filename Filename of the image to be set
             * @throws FileNotFound If the image cannot be found on the disk
             *
             * When this image is set, the title bar colour property will be
             * ignored
             */
            void setTextureTitleBar(const std::string& filename);

            /**
             * @brief Set the background image
             * @param filename Filename of the image to be set
             * @throws FileNotFound If the image cannot be found on the disk
             *
             * When this image is set, the background colour property will be
             * ignored
             */
            void setTextureBackground(const std::string& filename);

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
            ~ChildWindowRenderer() override;

        private:
            tgui::ChildWindowRenderer *windowRenderer_; //!< Pointer to third party child window renderer
        };
    }
}

#endif // IME_CHILDWINDOWRENDERER_H
