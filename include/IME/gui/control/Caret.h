
#ifndef IME_CARET_H
#define IME_CARET_H

#include "UIElement.h"
#include "IME/utility/Clock.h"

namespace IME{
    namespace Gui {
        class Caret : public UIElement {
        public:
            std::string getType() const override;

        private:
            Utility::Clock blinkCounter_;
        };
    } // namespace Gui
} // namespace IME

#endif
