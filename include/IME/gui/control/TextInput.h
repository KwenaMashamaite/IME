/**
 * @brief Class for capturing user input
 */

#ifndef TEXTINPUT_H
#define TEXTINPUT_H

#include "ClickableUIElement.h"

namespace IME {
    namespace Gui {
        class TextInput : public ClickableUIElement {
        public:
            /**
             * @brief Constructor
             * @param placeholder
             */
            explicit TextInput(const std::string& placeholder = "|");

            /**
             * @brief Set the text to be shown on the element when text is not
             *        entered yet
             * @param placeholder Placeholder text
             */
            void setPlaceHolder(const std::string &placeholder);

            /**
             * @brief Focus or unfocus element
             * @param isFocused Set to true to focus or false to unfocus element
             */
            void setFocus(bool isFocused);

            /**
             * @brief Set the size of the element
             * @param width Width of the element
             * @param height Height of the element
             */
            void setSize(float width, float height);

            /**
             * @brief Set the size of the text element
             * @param size New size of the element
             */
            void setSize(Dimensions size);

            /**
             * @brief Check if element is focused or not
             * @return True if element is focused. Otherwise, false
             */
            bool isFocused() const;

            /**
             * @brief Get the type of the UI element
             * @return The type of the UI element
             */
            std::string getType() const override;

        private:
            /**
             * @brief Initialize element
             */
            void init();

            /**
             * @brief Check if the placeholder is cleared or not
             * @return True if the placeholder is cleared. Otherwise, false
             */
            bool isPlaceholderCleared() const;

            /**
             * @brief The text is set internally
             */
            using ClickableUIElement::setText;

            /**
             * @brief Remove the last entered character from the input text
             */
            void popBack();

            /**
             * @brief Append a character to the input text
             * @param character Character to append
             */
            void append(char character);

        private:
            //Colour to indicate focused state
            Colour onFocusOutlineColour_;
            //Colour to indicate unfocused state
            Colour defaultOutlineColour_;
            //Placeholder text
            std::string placeholder_;
            //Placeholder flag
            bool isPlaceholderCleared_;
            //Focus flag
            bool isFocused_;
            //
            std::size_t caretPosition_;
        };
    } // namespace Gui
} // namespace IME

#endif
