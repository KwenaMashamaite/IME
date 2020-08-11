#include "IME/gui/control/TextBlock.h"

namespace IME::Gui {
    TextBlock::TextBlock(const std::string &textContent)
            : UIElement(textContent) {
        setBackgroundColour(Colour::White);
        setTextColour(Colour::Black);
    }

    std::string TextBlock::getType() const {
        return "TextBlock";
    }
}
