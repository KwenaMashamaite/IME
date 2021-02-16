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

#ifndef IME_IWIDGETRENDERER_H
#define IME_IWIDGETRENDERER_H

#include "IME/Config.h"
#include <memory>
#include <string>

namespace tgui {
    class WidgetRenderer;
}

namespace ime {
    /**
     * @brief Represents the spacing between the text and the
     *        border of a widget
     */
    struct Padding {
        float left = 0.0f;   //!< Left padding
        float top = 0.0f;    //!< Top padding
        float right = 0.0f;  //!< Right padding
        float bottom = 0.0f; //!< Bottom padding
    };

    /**
     * @brief Widget borders
     */
    struct Borders {
        float left = 0.0f;   //!< Left border
        float top = 0.0f;    //!< Top border
        float right = 0.0f;  //!< Right border
        float bottom = 0.0f; //!< Bottom border
    };

    /**
     * @brief Text styles
     */
    enum class TextStyle {
        Regular       = 0,      //!< Regular characters, no style
        Bold          = 1 << 0, //!< Bold characters
        Italic        = 1 << 1, //!< Italic characters
        Underlined    = 1 << 2, //!< Underlined characters
        StrikeThrough = 1 << 3  //!< Strike through characters
    };

    namespace ui {
        /**
         * @brief Interface for widget renderers
         */
        class IME_API IWidgetRenderer {
        public:
            using sharedPtr = std::shared_ptr<IWidgetRenderer>; //!< Shared renderer pointer

            /**
             * @brief Set the opacity of the widget
             * @param opacity The new opacity of the widget in between 0 and 1
             *
             * 0 means completely transparent, while 1 (default) means fully
             * opaque
             */
            virtual void setOpacity(float opacity) = 0;

            /**
             * @brief Get the opacity of the widget
             * @return The opacity of the widget
             */
            virtual float getOpacity() const = 0;

            /**
             * @brief Set the opacity of the widget when it is disabled
             * @param opacity Opacity to set between 0 and 1
             *
             * 0 means completely transparent, while 1 (default) means fully
             * opaque. Set to -1 (default) to use the normal opacity value even
             * when the widget is disabled.
             */
            virtual void setOpacityDisabled(float opacity) = 0;

            /**
             * @brief Get the opacity of the widget when it is disabled
             * @return The opacity of the widget in disabled state
             *
             * This function will return -1 if the widget uses the same opacity
             * as the enabled state when it is disabled
             */
            virtual float getOpacityDisabled() const = 0;

            /**
             * @brief Change the widgets font
             * @param filename Filename of the new font
             * @throws FileNotFound If the font cannot be found on the disk
             */
            virtual void setFont(const std::string& filename) = 0;

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
            virtual void ignoreTransparentTexture(bool ignoreTransparentParts) = 0;

            /**
             * @brief Check if mouse events are ignored on transparent parts of
             *        the texture or not
             * @return True if mouse events are ignored, otherwise false
             *
             * @see ignoreTransparentTexture
             */
            virtual bool isTransparentTextureIgnored() const = 0;

            /**
             * @internal
             * @brief Set the pointer to the third party renderer
             * @param renderer The third party
             *
             * @warning This function is meant for internal usage only and
             * should never be called under any circumstance
             */
            virtual void setInternalPtr(tgui::WidgetRenderer *renderer) = 0;

            /**
             * @internal
             * @brief Get pointer to third party renderer
             * @return The pointer to the third party renderer
             *
             * @warning This function is meant for internal usage only and
             * should never be called under any circumstance
             */
            virtual tgui::WidgetRenderer* getInternalPtr() = 0;

            /**
             * @brief Destructor
             */
            virtual ~IWidgetRenderer() = default;
        };
    }
}

#endif // IME_IWIDGETRENDERER_H
