/**
 * @brief UI element that can be interacted with (e.g clicked). A callback function can be registered
 *        in order to be notified when the button is hovered over, clicked or lost focus (mouse left button)
 */

#ifndef GUIBUTTON_H
#define GUIBUTTON_H

#include "ClickableUIElement.h"
#include <string>

namespace Gui {
    class Button : public ClickableUIElement {
    public:
        /**
         * @brief Construct a new Button object
         * @param buttonText Text to be displayed on the button
         *
         * The button is placed at (0, 0) and the button text
         * has a character size of 30 by default
         */
        explicit Button(const std::string &buttonText);

        /**
         * @brief Creates a gui button with the dimensions of the button text
         * @param content Text to be displayed on the button
         * @param font  Font used for the text
         * @param textCharSize Character size of the text
         */
        Button(const std::string &content, const std::string &font, unsigned int textCharSize);
    };
}

#endif