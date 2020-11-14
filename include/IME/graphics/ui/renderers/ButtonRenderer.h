////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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

/**
 * @brief Class for rendering a button
 *
 * This class allows you to manipulate the render properties of a Button
 */

#ifndef IME_BUTTONRENDERER_H
#define IME_BUTTONRENDERER_H

#include "IWidgetRenderer.h"
#include "IME/graphics/ui/Enums.h"
#include "IME/graphics/ui/Structs.h"
#include "IME/graphics/Colour.h"
#include <TGUI/Renderers/ButtonRenderer.hpp>

namespace IME {
    namespace Graphics::UI {
        class ButtonRenderer : public IWidgetRenderer {
        public:
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
             * @brief Set the colour of the text displayed on the button
             *
             * @param colour The new test colour
             */
            void setTextColour(Colour colour);

            /**
             * @brief Get the colour of the button text
             * @return The colour of the button text
             */
            Colour getTextColour() const;

            /**
             * @brief Set the text colour when the mouse enters the button
             * @param colour The colour to be set
             */
            void setTextHoverColour(Colour colour);

            /**
             * @brief Get the text colour when the mouse enters the button
             * @return The text colour when the mouse enters the button
             */
            Colour getTextHoverColour() const;

            /**
             * @brief Set the text colour when the left mouse button is down on
             *        the button
             * @param colour Colour to set
             * 
             * This colour is the same as the text colour by default
             */
            void setTextColourOnMouseDown(Colour colour);
            
            /**
             * @brief Get the text colour when the left mouse button is down on 
             *        the button
             * @return The text colour when the left mouse button is down on the 
             *         button
             */
            Colour getTextColourOnMouseDown() const;
            
            /**
             * @brief Set the colour of the text when the button is disabled
             * @param colour The colour to be set
             */
            void setDisabledTextColour(Colour colour);
            
            /**
             * @brief Get the colour of the text when the button is disabled
             * @return The colour of the text when the button is disabled
             */
            Colour getDisabledTextColour() const;
            
            /**
             * @brief Set the text colour when the button is focused but not 
             *        hovered
             * @param colour Colour to be set 
             */
            void setFocusedTextColour(Colour colour);
            
            /**
             * @brief Get the text colour when the button is focused but not
             *         hovered
             * @return The text colour when the button is focused but not
             *         hovered
             */
            Colour getTextColourFocused() const;
            
            /**
             * @brief Set the background colour of the button
             * @param colour The background colour to set
             *
             * @note that this colour is ignored when you set a background image
             */
            void setBackgroundColour(Colour colour);
            
            /**
             * @brief Get the background colour of button
             * @return The background colour of the button
             */
            Colour getBackgroundColour() const;

            /**
             * @brief Set the background colour of the button when the mouse 
             *         enters it
             * @param colour The background colour to set
             *
             * @note that this colour is ignored when you set a background image
             */
            void setBackgroundHoverColour(Colour colour);
            
            /**
             * @brief Get the background colour of the button when the mouse 
             *         enters it
             * @return The background colour of the button when the mouse 
             *         enters it
             */
            Colour getBackgroundColorHover() const;
            
            /**
             * @brief Set the background colour when the left mouse button is 
             *          down on the button
             * @param colour The backgound colour to set
             * 
             * @note This colour is ignored when you set a background image
             */
            void setBackgroundColorDown(Colour colour);

            /**
             * @brief Get the background colour when the left mouse button is 
             *          down on the button
             * @return The background colour when the left mouse button is 
             *          down on the button
             */
            Colour getBackgroundColorDown() const;

            /**
             * @brief Set the background colour of the button when it is 
             *        disabled
             * @param colour Background colour to set
             * 
             * @note This colour is ignored when you set a background image
             */
            void setDisabledBackgroundColour(Colour colour);
            
            /**
             * @brief Get the background colour of the button when it is 
             *        disabled
             * @return The background colour of the button when it is 
             *        disabled
             */
            Colour getDisabledBackgroundColour() const;

            /**
             * @brief Set the background colour when the button is focused but 
             *        not hovered
             * @param colour Background colour to be set 
             * 
             * @note This colour is ignored when you set a background image
             */
            void setFocusedBackgroundColour(Colour colour);
            
            /**
             * @brief Get the background colour when the button is focused but 
             *        not hovered
             * @return The background colour when the button is focused but not
             *         hovered
             */
            Colour getFocusedBackgroundColour() const;

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
             *      button
            * @param colour The background colour to set
            */
            void setBorderHoverColour(Colour colour);
            
            /**
             * @brief Get the background colour of when the mouse enters the 
             *      button
             * @return The background colour of when the mouse enters the 
             *      button
             */
            Colour getBorderHoverColour() const;
            
            /**
             * @brief Set the background colour when the left mouse button is 
             *        down on the button
             * @param colour Background colour to set 
             */
            void setBorderColourOnMouseDown(Colour colour);

            /**
             * @brief Get the background colour when the left mouse button is 
             *        down on the button
             * @return The background colour when the left mouse button is 
             *        down on the button
             */
            Colour getBorderColourOnMouseDown() const;
            
            /**
             * #@brief Set the background colour when the button is disabled
             * @param colour The background colour when the button is disabled
             */
            void setDisabledBorderColour(Colour colour);

            /**
             * #@brief Get the background colour when the button is disabled
             * @return The background colour when the button is disabled
             */
            Colour getDisabledBorderColour() const;

            /**
             * @brief Set the border colour when the button is focused but not 
             *        hovered
             * @param colour Border colour to set
             */
            void setFocusedBorderColour(Colour colour);
            
            /**
             * @brief Get the border colour when the button is focused but not 
             *        hovered
             * @return The border colour when the button is focused but not 
             *        hovered
             */
            Colour getBorderColorFocused() const;
            
            /**
             * @brief Set the background image of the button
             * @param texture Filename of the image to be set
             * @throws FileNotFound If the image cannot be found on the disk
             * 
             * When this image is set then the background colour property will
             * be ignored
             */
            void setTexture(const std::string& texture);
            
            /**
             * @brief Set the image when the mouse enters the button
              * @param texture Filename of the image to be set
             * @throws FileNotFound If the image cannot be found on the disk
             * 
             * When this image is set then the background colour property will
             * be ignored
             */
            void setTextureHover(const std::string& texture);

            /**
             * @brief Set the image when the left mouse button is down on the 
             *         button
              * @param texture Filename of the image to be set
             * @throws FileNotFound If the image cannot be found on the disk
             * 
             * When this image is set then the background colour property will
             * be ignored
             */
            void setMouseDownTexture(const std::string& texture);
            
            /**
             * @brief Set the image when the button is disabled
              * @param texture Filename of the image to be set
             * @throws FileNotFound If the image cannot be found on the disk
             * 
             * When this image is set then the background colour property will
             * be ignored
             */
            void setDisabledTexture(const std::string& texture);

            /**
             * @brief Set the image when the button is focused but not hovered
              * @param texture Filename of the image to be set
             * @throws FileNotFound If the image cannot be found on the disk
             * 
             * When this image is set then the background colour property will
             * be ignored
             */
            void setFocusedTextureFocused(const std::string& texture);
            
            /**
             * @brief Set the text style
             * @param style The style to be set
             */
            void setTextStyle(TextStyle style);

            /**
             * @brief Get the text style
             * @return The text style
             */
            TextStyle getTextStyle() const;

            /**
             * @brief Set the text style when the mouse enters the button
             * @param style The style to be set
             */
            void setHoverTextStyle(TextStyle style);

            /**
             * @brief Get the text style when the mouse enters the button
             * @return The text style when the mouse enters the button
             */
            TextStyle getHoverTextStyle() const;
            
            /**
             * @brief Set the style when the left mouse button is down on the 
             *        button
             * @param style The style to be set
             */
            void setTextStyleOnMouseDown(TextStyle style);
            
            /**
             * @brief Get the style when the left mouse button is down on the 
             *        button
             * @return Get the style when the left mouse button is down on the 
             *        button
             */
            TextStyle getTextStyleOnMouseDown() const;
            
            /**
             * @param Set the text style used when the button is disabled
             * @param style The text style to be ste
             */
            void setTextStyleDisabled(TextStyle style);
            
            /**
             * @brief Get the text style used when the button is disabled
             * @return The text style used when the button is disabled
             */
            TextStyle getTextStyleDisabled() const;
            
            /**
             * @brief Set the text style used when the button is focused
             * @param style The style to set
             */
            void setTextStyleFocused(TextStyle style);

            /**
             * @brief Get the text style used when the button is focused
             * @return The text style used when the button is focused
             */
            TextStyle getTextStyleFocused() const;
            
            /**
             * @brief Set the outline colour of the text 
             * @param outlineColor The outline colour to set
             */
            void setTextOutlineColor(Colour outlineColor);

            /**
             * @brief Get the outline colour of the text
             * @return The outline colour of the text
             */
            Colour getTextOutlineColour() const;
            
            /**
             * @brief Set the thickness of the text outline
             * @param outlineThickness The new txt outline thickness
             */
            void setTextOutlineThickness(float outlineThickness);

            /**
             * @brief Get the thickness of the text outline
             * @return The thickness of the text outline
             */
            float getTextOutlineThickness() const;
            
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
             * @see ignoreTransparentTexture()
             */
            bool isTransparentTextureIgnored() const override;

            /**
             * @brief Add an event listener to a property change event
             * @param property Name of the property to listen for
             * @param callback Function to execute when the property changes
             * @return The event listeners identification number
             *
             * The callback function will be passed the new value of the
             * property on invocation
             */
            int onPropertyChange(const std::string& property,
                Callback<const std::string&> callback);

            /**
             * @brief Remove an event listener from a property change event
             * @param id The unique identification number of the event listener
             *
             * The id was given when the event listener was subscribed to the
             * event @see onPropertyChange
             */
            void unsubscribe(int id) override;

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
            virtual ~ButtonRenderer();

        private:
            //Pointer to third party button
            tgui::ButtonRenderer* buttonRenderer_;
        };
    }
}

#endif