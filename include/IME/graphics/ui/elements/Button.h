/**
 * @brief UI element that can perform actions
 */

#ifndef BUTTON_H
#define BUTTON_H

#include "ClickableUIElement.h"
#include <string>

namespace IME {
    namespace Graphics::UI {
        class Button final : public ClickableUIElement {
        public:
            /**
             * @brief Create a button
             *
             * The button has no text, is located at (0, 0), has the
             * dimensions (0, 0) and a character size of 25 by default
             * @note The elements text font must be set before it is drawn,
             * @see setTextFont() in @class UIElement
             */
            Button();

            /**
             * @brief Create a button
             * @param buttonText Text to be displayed on the button
             *
             * The button has the dimensions of the button text, a
             * character size of 30 and it's position is (0, 0) by
             * default. @note The elements text font must be set before
             * it is drawn, @see setTextFont() in @class UIElement
             */
            explicit Button(const std::string &buttonText);

            /**
              * @brief Select/deselect button
              * @param isSelected Set true to select button, false to deselect button
              *
              * The button is not selected by default
              */
            void setSelected(bool isSelected);

            /**
             * @brief Set the text colour of the button when the mouse cursor
             *        enters it
             * @param textColour Button text colour to set
             *
             * The buttons text colour changes to dark grey by default
             * on "mouseEnter". The colour changes back to the way it
             * was prior to "mouseEnter" on "mouseLeave"
             */
            void setHoverTextColour(Colour textColour);

            /**
             * @brief Set the back ground colour of the button when the mouse
             *        cursor enters it
             * @param backgroundColour Background colour to set
             *
             * The button colour changes to dim grey by default on mouse
             * enter. The colour changes back to the way it was
             * prior to "mouseEnter" on "mouseLeave"
             */
            void setHoverBackgroundColour(Colour backgroundColour);

            /**
             * @brief Set the outline colour of the button when the
             *        mouse cursor enters the button
             * @param outlineColour Outline colour to set
             *
             * The buttons outline colour changes to light sky blue
             * by default on "mouseEnter". The colour changes back
             * to the way it was prior to "mouseEnter" on "mouseLeave"
             */
            void setHoverOutlineColour(Colour outlineColour);

            /**
             * @brief Get the type of the UI element
             * @return Type of the UI element
             */
            std::string getType() const override;

            /**
             * @brief Check if button is selected or not
             * @return True if button is selected or false if button is not selected
             */
            bool isSelected() const;

        private:
            /**
             * @brief Initialize the default behaviour of the button
             *
             * This function will make the button respond to the mouse
             * by default. That is, the button will graphically change
             * to indicate when the mouse enters the button, leaves the
             * button or when the button is clicked.
             */
            void initializeDefaultBehavior();

        private:
            //Selected state
            bool isSelected_;

            //Group of colours
            struct Colours {
                Colour backgroundColour;
                Colour textColour;
                Colour outlineColour;
            };

            //Button colours when the mouse cursor interacts with it
            Colours onHoverColours_;
            //Button colours when mouse cursor leaves it
            Colours defaultColours_;
        };
    }
} // namespace IME

#endif
