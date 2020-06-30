/**
 * @brief UI element that can display single and multiple lines of text
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
         * @param textContent text to be displayed inside the text block
         */
        explicit TextBlock(const std::string &textContent);
    };
}

#endif
