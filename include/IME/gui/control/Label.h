#ifndef LABEL_H
#define LABEL_H

#include "UIElement.h"
namespace IME {
    namespace Gui {
        class Label : public UIElement {
        private:
            Label();

            /**
             *
             * @param text
             */
            explicit Label(std::string text);

        public:

        };
    } // namespace Gui
} // namespace IME

#endif
