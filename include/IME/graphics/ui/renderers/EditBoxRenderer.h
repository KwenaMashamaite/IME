/**
 * @brief Class for rendering an edit box
 *
 * This class allows you to manipulate the render properties of an edit box
 */

#ifndef EDITBOXRENDERER_H
#define EDITBOXRENDERER_H

#include "IWidgetRenderer.h"
#include "IME/graphics/ui/Enums.h"
#include "IME/graphics/ui/Structs.h"
#include "IME/graphics/Colour.h"
#include <TGUI/Renderers/EditBoxRenderer.hpp>

namespace IME {
    namespace Graphics::UI {
        class EditBoxRenderer : public IWidgetRenderer {
        public:
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
             * @brief Set the style of the defaut text
             * @param style The style to set
             */
            void setDefaultTextStyle(TextStyle style);

            /**
             * @brief Get the style of the default text
             * @return The style of the default text
             */
            TextStyle getDefaultTextStyle() const;

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
             * @brief SDet the adding of the edit box
             * @param padding The new padding
             * 
             * When the text is auto-scaled then it will be drawn within the 
             * area defined by the size minus the border and padding. The 
             * padding is also used to define the clipping area for when the 
             * text it too long
             */
            void setPadding(const Padding& padding);
            
            /**
             * @brief Get the padding
             * @return The padding set on the edit box
             */
            Padding getPadding() const;


            /**
             * @brief Set the width of the caret
             * @param width New width of the caret
             */
            void setCaretWidth(float width);

            /**
             * @brief Get the caret width
             * @return The caret width
             */
            float getCaretWidth() const;

            /**
             * @brief Set the text colour that will be used inside the edit box
             * @param textColour The new text colour
             */
            void setTextColour(Colour textColour);

            /**
             * @brief Get the text colour that will be used inside the edit box
             * @return The text colour that will be used inside the edit box
             */
            Colour getTextColour() const;
            
            /**
             * @brief Set the text colour when the edit box is disabled        
             * @param textColour Colour to set
             */
            void setDisabledTextColour(Colour textColour);
            
            /**
             * @brief Get the text colour when the edit box is disabled     
             * @return The text colour when the edit box is disabled     
             */
            Colour getDisabledTextColour() const;
            
            /**
             * @brief Set the text colour when the edit box is focused
             * @param textColour Colour to set
             */
            void setFocusedTextColour(Colour textColour);
            
            /**
             * @brief Get the text colour when the edit box is focused
             * @return Get the text colour when the edit box is focused
             */
            Colour getFocusedTextColour() const;


            /**
             * @brief Set the text colour of the selected text
             * @param colour New colour
             */
            void setSelectedTextColour(Colour colour);

            /**
             * @brief Get the text color of the selected text
             * @return The text color of the selected text
             */
            Colour getSelectedTextColour() const;

            /**
             * @brief Set the background colour of the selected text 
             * @param backgroundColour New background colour
             */
            void setSelectedTextBackgroundColour(Colour backgroundColour);
            
            /**
             * @brief Get the background colour of the selected text 
             * @return The background colour of the selected text 
             */
            Colour getSelectedTextBackgroundColour() const;
            
            /**
             * @brief Set the colour f the default text
             * @param defaultTextColour The colour to set
             */
            void setDefaultTextColour(Colour defaultTextColour);

            /**
             * @brief Get the colour f the default text
             * @return The colour of the default text
             */
            Colour getDefaultTextColour() const;
            
            /**
             * @brief Set the background colour of the edit box
             * @param colour The background colour to set
             *
             * @note that this colour is ignored when you set a background image
             */
            void setBackgroundColour(Colour colour);

            /**
            * @brief Get the background colour of edit box
            * @return The background colour of the edit box
            */
            Colour getBackgroundColour() const;

            /**
             * @brief Set the background colour of the edit box when the mouse 
             *         enters it
             * @param colour The background colour to set
             *
             * @note that this colour is ignored when you set a background image
             */
            void setBackgroundHoverColour(Colour colour);

            /**
             * @brief Get the background colour of the edit box when the mouse 
             *         enters it
             * @return The background colour of the edit box when the mouse 
             *         enters it
             */
            Colour getBackgroundColorHover() const;

            /**
             * @brief Set the background colour of the edit box when it is 
             *        disabled
             * @param colour Background colour to set
             * 
             * @note This colour is ignored when you set a background image
             */
            void setDisabledBackgroundColour(Colour colour);

            /**
             * @brief Get the background colour of the edit box when it is 
             *        disabled
             * @return The background colour of the edit box when it is 
             *        disabled
             */
            Colour getDisabledBackgroundColour() const;

            /**
             * @brief Set the background colour when the edit box is focused but 
             *        not hovered
             * @param colour Background colour to be set 
             * 
             * @note This colour is ignored when you set a background image
             */
            void setFocusedBackgroundColour(Colour colour);

            /**
             * @brief Get the background colour when the edit box is focused but 
             *        not hovered
             * @return The background colour when the edit box is focused but not
             *         hovered
             */
            Colour getFocusedBackgroundColour() const;

            /**
             * @brief Set the colour of the caret
             * @param caretColor The colour of the caret 
             */
            void setCaretColour(Colour caretColour);

            /**
             * @brief Get the colour of the caret
             * @return The colour of the caret
             */
            Colour getCaretColour() const;
            
            /**
             * @brief Set the colour of the caret when the mouse enters the edit
             *         box
             * @param caretColour The coulour to set
             */
            void setCaretHoverColour(Colour caretColour);

            /**
             * @brief Get the colour of the caret when the mouse enters the edit
             *         box
             * @return The colour of the caret when the mouse enters the edit
             *         box
             */
            Colour getCaretHoverColour() const;

            /**
             * @brief Set the colour of the caret when the edit box is focused
             * @param caretColour The new caret colour
             */
            void setCaretColorFocused(Colour caretColour);
            
            /**
             * @brief Get the colour of the caret when the edit box is focused
             * @return The colour of the caret when the edit box is focused
             */
            Colour getFocusedCaretColour() const;

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
             *      edit box
             * @param colour The background colour to set
             */
            void setBorderHoverColour(Colour colour);

            /**
              * @brief Get the background colour of when the mouse enters the 
              *      edit box
              * @return The background colour of when the mouse enters the 
              *      edit box
              */
            Colour getBorderHoverColour() const;
            
            /**
             * @brief Set the background colour when the edit box is disabled
             * @param colour The background colour when the edit box is disabled
             */
            void setDisabledBorderColour(Colour colour);
            
            /**
             * @brief Get the background colour when the edit box is disabled
             * @return The background colour when the edit box is disabled
             */
            Colour getDisabledBorderColour() const;
            
            /**
             * @brief Set the border colour when the edit box is focused but not 
             *        hovered
             * @param colour Border colour to set
             */
            void setFocusedBorderColour(Colour colour);

            /**
             * @brief Get the border colour when the edit box is focused but not 
             *        hovered
             * @return The border colour when the edit box is focused but not 
             *        hovered
             */
            Colour getFocusedBorderColour() const;

            /**
             * @brief Set the background image of the edit box
             * @param filename Filename of the image to be set
             * @throws FileNotFound If the image cannot be found on the disk
             * 
             * When this image is set then the background colour property will
             * be ignored
             */
            void setTexture(const std::string& filename);

            /**
             * @brief Set the image when the mouse enters the edit box
             * @param filename Filename of the image to be set
             * @throws FileNotFound If the image cannot be found on the disk
             * 
             * When this image is set then the background colour property will
             * be ignored
             */
            void setHoverTexture(const std::string& filename);

            /**
             * @brief Set the image when the edit box is disabled
             * @param filename Filename of the image to be set
             * @throws FileNotFound If the image cannot be found on the disk
             * 
             * When this image is set then the background colour property will
             * be ignored
             */
            void setDisabledTexture(const std::string& filename);
            
            /**
             * @brief Set the image when the edit box is focused but not hovered
             * @param filename Filename of the image to be set
             * @throws FileNotFound If the image cannot be found on the disk
             * 
             * When this image is set then the background colour property will
             * be ignored
             */
            void setFocusedTexture(const std::string& filename);

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
            virtual ~EditBoxRenderer();

        private:
            //Pointer to third party edit box renderer
            tgui::EditBoxRenderer* editBoxRenderer_;
        };
    }
}

#endif
