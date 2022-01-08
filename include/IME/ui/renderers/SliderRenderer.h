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

#ifndef IME_SLIDERRENDERER_H
#define IME_SLIDERRENDERER_H

#include "IME/Config.h"
#include "IWidgetRenderer.h"
#include "IME/graphics/Colour.h"

namespace tgui {
    class SliderRenderer;
}

namespace ime {
    namespace ui {
        /**
         * @brief A Slider widget renderer
         *
         * This class allows you to manipulate the render properties of a Slider
         */
        class IME_API SliderRenderer : public IWidgetRenderer {
        public:
            using Ptr = std::unique_ptr<SliderRenderer>; //!< Unique renderer pointer

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
             * @brief Set the colour of the track
             * @param colour The colour to set
             */
            void setTrackColour(Colour colour);

            /**
             * @brief Get the track colour
             * @return The track colour
             */
            Colour getTrackColour() const;
            
            /**
             * @brief Set the colour of the track when the mouse enters it
             * @param colour The track colour to set 
             */
            void setTrackHoverColour(Colour colour);
            
            /**
             * @brief Get the colour of the track when the mouse enters it
             * @return The colour of the track whn the mouse enters it
             */
            Colour getTrackHoverColour() const;
            
            /**
             * @brief Set the thumb colour
             * @param colour The thumb colour to set 
             */
            void setThumbColour(Colour colour);

            /**
             * @brief Get the thumb colour
             * @return The thumb colour
             */
            Colour getThumbColour() const;
            
            /**
             * @brief Set the colour of the thumb when the mouse enter it
             * @param colour The thumb colour to set
             */
            void setThumbHoverColour(Colour colour);

            /**
             * @brief Get the colour of the thumb when the mouse enters it
             * @return The colour of the thumb when the mouse enter it
             */
            Colour getThumbHoverColour() const;

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
             * @brief Set the colour of the borders when the mouse enters the
             *        slider
             * @param colour The slider colour to set
             */
            void setBorderHoverColour(Colour colour);

            /**
             *@brief Get the colour of the borders when the mouse enters the
             *         slider
             * @return the colour of the borders when the mouse enters the
             *         slider
             */
            Colour getBorderHoverColour() const;

            /**
             * @brief Set the image of the track
             * @param filename Filename of the image to set
             * @throws FileNotFound if the image cannot be found on the disk
             */
            void setTrackTexture(const std::string& filename);

            /**
             * @brief Set the image of the track when the mouse enters it
             * @param filename Filename of the image to set
             * @throws FileNotFound if the image cannot be found on the disk
             */
            void setTrackHoverTexture(const std::string& filename);

            /**
             * @brief Set the image of the thumb
             * @param filename Filename of the image to set
             * @throws FileNotFound if the image cannot be found on the disk
             */
            void setThumbTexture(const std::string& filename);

            /**
             * @brief Set the image of the thumb when the mouse enters it
             * @param filename Filename of the image to set
             * @throws FileNotFound if the image cannot be found on the disk
             */
            void setThumbHoverTexture(const std::string& filename);

            /**
             * @brief Set whether the center of the thumb or the sides of the
             *        thumb must remain on top of the track
             * @param keepThumbInside True to keep thumb inside, otherwise false
             */
            void setThumbWithinTrack(bool keepThumbInside);

            /**
             * @brief Check whether the centre of the thumb or the sides of the
             *        thumb must remain on top of the track
             * @return True if the thumb is kept inside, otherwise false
             */
            bool isThumbWithinTrack() const;
            
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
            void setFont(const std::string& filename) override;

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
            tgui::WidgetRenderer* getInternalPtr() override;

            /**
             * @brief Destructor
             */
            ~SliderRenderer() override;

        private:
            tgui::SliderRenderer* sliderRenderer_; //!< Pointer to third party renderer
        };
    }
}

#endif // IME_SLIDERRENDERER_H
