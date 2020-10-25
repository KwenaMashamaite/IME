#ifndef ICLICKABLEWIDGET_H
#define ICLICKABLEWIDGET_H

#include "IWidget.h"
#include <string>

namespace IME {
    namespace Graphics::UI {
        class IClickableWidget : public IWidget {
        public:
            /**
             * @brief Enable or disable the widget
             * @param isEnable Set true to enable the widget, false to
             *        disable the widget
             *
             * The widget is enabled by default
             *
             * @note Disabling the widget cancels all the interaction events.
             *       That is, the "mouseEnter", "mouseLeave", "click", "mouseUp"
             *       and "mouseDown" events will not fire while the widget is
             *       disabled
             */
            virtual void setEnabled(bool isEnable) = 0;

            /**
             * @brief Focus or unfocus widget
             * @param isFocused Set to true to focus or false to unfocus widget
             */
            virtual void setFocused(bool isFocused) = 0;

            /**
             * @brief Check if widget is focused or not
             * @return True if widget is focused. Otherwise, false
             */
            virtual bool isFocused() const = 0;

            /**
              * @brief Check if widget is enabled or disabled
              * @return True if widget is enabled, false if widget is disabled
              *
              * @note A disabled widget cannot be interacted with using the mouse.
              * @see setEnabled(bool). Also, Hiding an widget disables it, @see hide()
              * in @class IWidget
              */
            virtual bool isEnabled() const = 0;

            /**
             * @brief Disable widget if its currently enabled and vice versa
             */
            virtual void toggleEnabled() = 0;

            /**
             * @brief Check if mouse cursor is currently over the widget or not
             * @return True if mouse cursor is over the widget, false otherwise
             */
            virtual bool isMouseOverElement() const = 0;
        };
    }
}

#endif
