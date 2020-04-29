/**
 * @brief Static UI element that can display single and multiple lines of text
 */

#ifndef TEXTBLOCK_H
#define TEXTBLOCK_H

#include "UIElement.h"
#include <string>

namespace Gui {
    class TextBlock final : public UIElement {
    public:
        /**
         * @brief Construct a new Text Block object
         * @param labelText - text to be displayed
         */
        explicit TextBlock(const std::string &labelText);

        /**
         * @brief Construct a new TextBlock object
         * @param content Text to be displayed
         * @param font Font of the text
         * @param textCharSize Character size of the text
         */
        TextBlock(const std::string &content, const std::string &font, unsigned int textCharSize);
    };
}

#endif