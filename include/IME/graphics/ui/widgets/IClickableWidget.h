#ifndef ICLICKABLEWIDGET_H
#define ICLICKABLEWIDGET_H

#include "IWidget.h"
#include <string>

namespace IME {
    namespace Graphics::UI {
        class IClickableWidget : public IWidget {
        public:
            /**
             * @brief Set the text colour of the button when the mouse cursor
             *        enters it
             * @param textColour Button text colour to set
             *
             * The buttons text colour changes to dark grey by default
             * on "mouseEnter". The colour changes back to the way it
             * was prior to "mouseEnter" on "mouseLeave"
             */
            virtual void setHoverTextColour(Colour textColour) = 0;

            /**
             * @brief Set the back ground colour of the button when the mouse
             *        cursor enters it
             * @param backgroundColour Background colour to set
             *
             * The button colour changes to dim grey by default on mouse
             * enter. The colour changes back to the way it was
             * prior to "mouseEnter" on "mouseLeave"
             */
            virtual void setHoverBackgroundColour(Colour backgroundColour) = 0;

            /**
             * @brief Set the outline colour of the button when the
             *        mouse cursor enters the button
             * @param outlineColour Outline colour to set
             *
             * The buttons outline colour changes to light sky blue
             * by default on "mouseEnter". The colour changes back
             * to the way it was prior to "mouseEnter" on "mouseLeave"
             */
            virtual void setHoverOutlineColour(Colour outlineColour) = 0;

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

            /**
             * @brief Set the image that is shown on the widget
             * @param filename Name of the image file
             * @throws FileNotFound if the image cannot be found on the disk
             *
             * @note When this image is set, the background color property will
             *       be ignored
             */
            virtual void setTexture(const std::string& filename) = 0;

            /**
             * @brief Set the image that is displayed when the widget is focused
             *        but not hovered
             * @param filename Filename of the image to be displayed
             * @throws FileNotFound if the image cannot be found on the disk
             */
            virtual void setOnFocusedImage(const std::string& filename) = 0;

            /**
             * @brief Set the image that is displayed when the widget is disabled
             * @param filename Filename of the image to be displayed
             * @throws FileNotFound if the image cannot be found on the disk
             */
            virtual void setOnDisabledImage(const std::string& filename) = 0;

            /**
             * @brief Set the image that is displayed when the mouse is held
             *        down on the widget
             * @param filename Filename of the image to be displayed
             * @throws FileNotFound if the image cannot be found on the disk
             *
             * No image is displayed by default
             */
            virtual void setOnMouseDownImage(const std::string& filename) = 0;

            /**
             * @brief Set the image that is displayed when the mouse enters the
             *        widget
             * @param filename Filename of the image to be displayed
             * @throws FileNotFound if the image cannot be found on the disk
             *
             * No image is displayed by default
             */
            virtual void setOnHoverImage(const std::string& filename) = 0;
        };
    }
}

#endif
