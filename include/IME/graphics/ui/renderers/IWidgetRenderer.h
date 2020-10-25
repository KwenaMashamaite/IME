/**
 * @brief Interface for widget renderers
 */

#ifndef IWIDGETRENDERER_H
#define IWIDGETRENDERER_H

#include <TGUI/Renderers/WidgetRenderer.hpp>
#include "IME/core/event/EventEmitter.h"
#include <string>

namespace IME {
    namespace Graphics::UI {
        class IWidgetRenderer {
        public:
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
             * @param font The new font
             */
            virtual void setFont(const std::string& font) = 0;

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
             * @see ignoreTransparentTexture()
             */
            virtual bool isTransparentTextureIgnored() const = 0;

            /**
             * @brief Add an event listener to a property change event
             * @param callback Function to execute when the property changes
             * @param property Name of the property to listen for
             * @return The event listeners identification number
             */
            virtual int onPropertyChange(const std::string &property,
                Callback<const std::string &> callback) = 0;

            /**
             * @brief Remove an event listener from a property change event
             * @param id The unique identification number of the event listener
             *
             * The id was given when the event listener was subscribed to the
             * event @see onPropertyChange
             */
            virtual void unsubscribe(int id) = 0;

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
        };
    }
}

#endif
