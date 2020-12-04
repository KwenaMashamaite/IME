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
 * @brief Class for rendering a checkbox
 *
 * This class allows you to manipulate the render properties of a checkbox
 */

#ifndef IME_CHECKBOXRENDERER_H
#define IME_CHECKBOXRENDERER_H

#include "IWidgetRenderer.h"
#include "IME/graphics/ui/Enums.h"
#include "IME/graphics/ui/Structs.h"
#include "IME/graphics/Colour.h"
#include <TGUI/Renderers/CheckBoxRenderer.hpp>

namespace IME {
    namespace UI {
        class IME_API CheckBoxRenderer : public IWidgetRenderer {
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
             * @brief Set the relative distance between the checkbox and the
             *        text next to it
             * @param ratio The ratio of the distance based on the width of the
             *         checkbox
             *         
             * The default value is 0.2 which means that if the width of the 
             * checkbox would be 50 pixels then the gap between the radio 
             * button and the text will be 10 pixels.
             */
            void setTextDistanceRatio(float ratio);
            
            /**
             * @brief Get the relative distance between the checkbox and the 
             *        text next to it
             * @return The relative distance between the checkbox and the text
             *         next to it
             */
            float getTextDistanceRatio() const;


            /**
             * @brief Set the text colour that will be used inside the checkbox
             * @param textColour The new text colour
             */
            void setTextColour(Colour textColour);

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
             * @brief Set the text colour when the checkbox is disabled        
             * @param textColour Colour to set
             */
            void setDisabledTextColour(Colour textColour);

            /**
             * @brief Get the text colour when the checkbox is disabled     
             * @return The text colour when the checkbox is disabled     
             */
            Colour getDisabledTextColour() const;

            /**
             * @brief Set the colour of text when the checkbox is checked
             * @param colour Colour to set 
             */
            void setCheckedTextColour(Colour colour);
            
            /**
             * @brief Get the colour of text when the checkbox is checked
             * @return The colour of text when the checkbox is checked
             */
            Colour getTextColorChecked() const;
            
            /**
             * @brief Set the colour of the text when the mouse enters the
             *        checkbox and it is checked
             * @param colour The colour to set
             */
            void setCheckedTextHoverColour(Colour colour);
            
            /**
             * @brief Get the colour of the text when the mouse enters the
             *        checkbox and it is checked
             * @return The checked hover colour
             */
            Colour getCheckedTextHoverColour() const;
            
            /**
             * @brief Set the colour of the text when the checkbox is 
             *        checked and disabled
             * @param colour New colour 
             */
            void setCheckedDisabledTextColour(Colour colour);

            /**
             * @brief Get the colour of the text when the checkbox is 
             *          checked and disabled
             * @return The colour of the text when the checkbox is 
             *          checked and disabled
             */
            Colour getCheckedDisabledTextColour() const;
            
            /**
             * @brief Set the background colour of the checkbox
             * @param colour The background colour to set
             *
             * @note that this colour is ignored when you set a background image
             */
            void setBackgroundColour(Colour colour);

            /**
            * @brief Get the background colour of checkbox
            * @return The background colour of the checkbox
            */
            Colour getBackgroundColour() const;

            /**
             * @brief Set the background colour of the checkbox when the mouse 
             *         enters it
             * @param colour The background colour to set
             *
             * @note that this colour is ignored when you set a background image
             */
            void setBackgroundHoverColour(Colour colour);

            /**
             * @brief Get the background colour of the checkbox when the mouse 
             *         enters it
             * @return The background colour of the checkbox when the mouse 
             *         enters it
             */
            Colour getBackgroundHoverColour() const;
            
            /**
             * @brief Set the background colour of the checkbox when it is 
             *        disabled
             * @param colour Background colour to set
             * 
             * @note This colour is ignored when you set a background image
             */
            void setDisabledBackgroundColour(Colour colour);

            /**
             * @brief Get the background colour of the checkbox when it is 
             *        disabled
             * @return The background colour of the checkbox when it is 
             *        disabled
             */
            Colour getDisabledBackgroundColour() const;

            /**
             * @brief Set the background colour used when the checkbox is
             *          checked
             * @param colour the new colour
             */
            void setCheckedBackgroundColour(Colour colour);

            /**
             * @brief Get the background colour used when the checkbox is
             *          checked
             * @return The background colour used when the checkbox is
             *          checked
             */
            Colour getCheckedBackgroundColour() const;

            /**
             * @brief Set the background colour when the mouse cursor enters  
             *         the checkbox and it's checked
             * @param colour colour to set
             */
            void setCheckedHoverBackgroundColour(Colour colour);
            
            /**
             * @brief Get the background colour when the mouse cursor enters  
             *         the checkbox and it's checked
             * @return Checked hover background colour
             */
            Colour getCheckedHoverBackgroundColour() const;
            
            /**
             * @brief Set the background colour when the checkbox is checked and 
             *        disabled
             * @param colour Colour to set
             */
            void setCheckedDisabledBackgroundColour(Colour colour);

            /**
             * @brief Get the background colour when the checkbox is checked and 
             *        disabled
             * @return The background colour when the checkbox is checked and 
             *        disabled
             */
            Colour getCheckedDisabledBackgroundColour() const;
            
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
             *      checkbox
             * @param colour The background colour to set
             */
            void setBorderHoverColour(Colour colour);

            /**
              * @brief Get the background colour of when the mouse enters the 
              *      checkbox
              * @return The background colour of when the mouse enters the 
              *      checkbox
              */
            Colour getBorderHoverColour() const;

            /**
             * @brief Set the background colour when the checkbox is disabled
             * @param colour The background colour when the checkbox is disabled
             */
            void setDisabledBorderColour(Colour colour);

            /**
             * @brief Get the background colour when the checkbox is disabled
             * @return The background colour when the checkbox is disabled
             */
            Colour getDisabledBorderColour() const;

            /**
             * @brief Set the border colour when the checkbox is focused but not 
             *        hovered
             * @param colour Border colour to set
             */
            void setFocusedBorderColour(Colour colour);

            /**
             * @brief Get the border colour when the checkbox is focused but not 
             *        hovered
             * @return The border colour when the checkbox is focused but not 
             *        hovered
             */
            Colour getFocusedBorderColour() const;

            /**
             * @brief Set the border colour when the checkbox is checked
             * @param colour The colour to set
             */
            void setCheckedBorderColour(Colour colour);

            /**
             * @brief Get the border colour when the checkbox is checked
             * @return The border colour when the checkbox is checked
             */
            Colour getCheckedBorderColour() const;

            /**
             * @brief Set the colour of the checkbox when the mouse cursor
             *         enters it and it's checked
             * @param colour Colour to set
             */
            void setCheckedHoverBorderColour(Colour colour);

            /**
             * @brief Get the colour of the checkbox when the mouse cursor
             *         enters it and it's checked
             * @return The colour of the checkbox when the mouse cursor
             *         enters it and it's checked
             */
            Colour getCheckedHoverBorderColour() const;

            /**
             * @brief Set the border colour when the checkbox is checked and
             *         disabled
             * @param colour The colour to set
             */
            void setCheckedDisabledBorderColour(Colour colour);

            /**
             * @brief Get the border colour when the checkbox is checked and
             *         disabled
             * @return  The border colour when the checkbox is checked and
             *         disabled
             */
            Colour getCheckedDisabledBorderColour() const;

            /**
             * @brief Set the border colour when the checkbox is checked and
             *         focused
             * @param colour The colour to set
             */
            void setCheckedFocusedBorderColour(Colour colour);

            /**
             * @brief Get the border colour when the checkbox is checked and
             *         focused
             * @return  The border colour when the checkbox is checked and
             *         focused
             */
            Colour getCheckedFocusedBorderColour() const;

            /**
             * @brief Set the colour that is used to fill the checkbox when
             *          it is checked
             * @param colour Colour to set
             */
            void setCheckColour(Colour colour);

            /**
             * @brief Get the colour that is used to fill the checkbox when
             *          it is checked
             * @return The colour that is used to fill the checkbox when
             *          it is checked
             */
            Colour getCheckColour() const;

            /**
             * @brief Set the colour that is used to fill the checkbox when
             *         the mouse is on top of it
             * @param colour The colour to set
             */
            void setCheckHoverColour(Colour colour);

            /**
             * @brief Get the colour that is used to fill the checkbox when
             *         the mouse is on top of it
             * @return The colour that is used to fill the checkbox when
             *         the mouse is on top of it
             */
            Colour getCheckHoverColour() const;

            /**
             * @brief Set the colour that is used to fill the checkbox when
             *         the checkbox is disabled
             * @param colour The new colour to set
             */
            void setDisabledCheckedColour(Colour colour);

            /**
             * @brief Get the colour that is used to fill the checkbox when
             *         the checkbox is disabled
             * @return The colour that is used to fill the checkbox when
             *         the checkbox is disabled
             */
            Colour getDisabledCheckColour() const;
            
            /**
             * @brief Set the image that is displayed when the checkbox is not 
             *      checked
             * @param filename Filename of the image to be set
             * @throws FileNotFound If the image cannot be found on the disk
             * 
             * When checked and unchecked images are set, the background and 
             * check colour properties will be ignored
             */
            void setUncheckedTexture(const std::string& filename);
            
            /**
             * @brief Set the image that is displayed when the checkbox is checked
             * @param filename Filename of the image to be set
             * @throws FileNotFound If the image cannot be found on the disk
             * 
             * When checked and unchecked images are set, the background and 
             * check colour properties will be ignored.
             */
            void setCheckedTexture(const std::string& filename);

            /**
             * @brief Set the image that is displayed when the checkbox is not 
             *         checked and the mouse is on top of the checkbox
             * @param filename Filename of the image to be set
             * @throws FileNotFound If the image cannot be found on the disk
             * 
             * This only has effect when the normal checked and unchecked images 
             * are also set
             */
            void setUncheckedHoverTexture(const std::string& filename);

            /**
             * @brief Set the image that is displayed when the checkbox is
             *         checked and the mouse is on top of the checkbox
             * @param filename Filename of the image to be set
             * @throws FileNotFound If the image cannot be found on the disk
             * 
             * This only has effect when the normal checked and unchecked images 
             * are also set
             */
            void setCheckedHoverTexture(const std::string& filename);

            /**
             * @brief Set the image that is displayed when the checkbox is not
             *         checked and it's disabled
             * @param filename Filename of the image to be set
             * @throws FileNotFound If the image cannot be found on the disk
             * 
             * This only has effect when the normal checked and unchecked images 
             * are also set
             */
            void setUncheckedDisabledTexture(const std::string& filename);

            /**
             * @brief Set the image that is displayed when the checkbox is
             *         checked and it's disabled
             * @param filename Filename of the image to be set
             * @throws FileNotFound If the image cannot be found on the disk
             * 
             * This only has effect when the normal checked and unchecked images 
             * are also set
             */
            void setCheckedDisabledTexture(const std::string& filename);
            
            /**
             * @brief Set the image that is displayed on top of the checkbox 
             *          when it is unchecked and focused
             * @param filename Filename of the image to be set
             * @throws FileNotFound If the image cannot be found on the disk
             * 
             * This only has effect when the normal checked and unchecked images 
             * are also set. Pass an empty texture to unset the image
             */
            void setUncheckedFocusedTexture(const std::string& filename);

            /**
             * @brief Set the image that is displayed on top of the checkbox 
             *          when it is checked and focused
             * @param filename Filename of the image to be set
             * @throws FileNotFound If the image cannot be found on the disk
             * 
             * This only has effect when the normal checked and unchecked images 
             * are also set. Pass an empty texture to unset the image
             */
            void setCheckedFocusedTexture(const std::string& filename);

            /**
             * @brief Set the text style
             * @param style Style to set
             */
            void setTextStyle(TextStyle style);

            /**
             * @brief Get the text style
             * @return The text style
             */
            TextStyle getTextStyle() const;

            /**
             * @brief Set the text style when the checkbox is checked
             * @param style The new style
             */
            void setCheckedTextStyle(TextStyle style);

            /**
             * @brief Get the text style when the checkbox is checked
             * @return The text style when the checkbox is checked
             */
            TextStyle getCheckedTextStyle() const;

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
            virtual ~CheckBoxRenderer();

        private:
            //Pointer to third party checkbox renderer
            tgui::CheckBoxRenderer* checkBoxRenderer_;
        };
    }
}

#endif
