/**
 * @brief UI element that can perform actions
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "UIElement.h"
#include <string>

namespace Gui {
    class Button final : public UIElement {
    public:
        /**
         * @brief Create a button
         *
         * The button is placed at (0, 0) and the button text
         * has a character size of 30 by default
         */
        Button();

        /**
         * @brief Create a button
         * @param buttonText Text to be displayed on the button
         *
         * The button has the dimensions of the button text and
         * a position of (0, 0) by default
         */
        explicit Button(const std::string& buttonText);

        /**
         * @brief Set the colour of the button text when the
         *        mouse cursor enters the button
         * @param textFillColour Button text colour to set
         */
        void setHoverTextFillColour(Colour textFillColour);

        /**
         * @brief Set the colour of the button when the mouse
         *        cursor enters it
         * @param fillColour Button colour to set
         */
        void setHoverFillColour(Colour fillColour);

        /**
         * @brief Set the outline colour of the button when the
         *        mouse enters the button
         * @param outlineColour Outline colour to set
         */
        void setHoverOutlineColour(Colour outlineColour);

    private:
        /**
         * @brief Subscribe button to system events
         */
        void subscribeToEvents();

    private:
        //Selection state
        bool isSelected_;
        //Button Colour when mouse enters it
        Colour onHoverColour_;
        //Button text colour when mouse enters it
        Colour onHoverTextColour_;
        //Button outline colour when mouse enters it
        Colour onHoverOutlineColour_;
    };
}

#endif
