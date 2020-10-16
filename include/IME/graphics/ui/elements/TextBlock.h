/**
 * @brief UI element that can display single and multiple lines of text
 */

#ifndef TEXTBLOCK_H
#define TEXTBLOCK_H

#include "UIElement.h"
#include <string>

namespace IME {
    namespace Graphics::UI {
        class TextBlock final : public UIElement {
        public:
            /**
             * @brief Construct a new Text Block object
             * @param textContent text to be displayed inside the text block
             *
             * @note The elements text font must be set before it is drawn,
             * @see setTextFont() in @class UIElement
             */
            explicit TextBlock(const std::string &textContent);

            /**
             * @brief Get the type of the UI element
             * @return Type of the UI element
             */
            std::string getType() const override;
        };
    }
}

#endif
