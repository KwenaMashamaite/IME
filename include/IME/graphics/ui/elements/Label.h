/**
 * @brief UI element that displays a single line of text
 */

#ifndef LABEL_H
#define LABEL_H

#include "UIElement.h"

namespace IME {
    namespace Graphics::UI {
        class Label : public UIElement {
        public:
            /**
             * @brief Create a label with an empty text
             */
            Label();

            /**
             * @brief Create a label
             * @param text Text to display inside label
             *
             * @note If the provided text contains multiple lines, only
             * the first line will be displayed.
             */
            explicit Label(const std::string& text);

            /**
              * @brief Get the type of the UI element
              * @return Type of the UI element
              */
            std::string getType() const override;
        };
    }
} // namespace IME

#endif
