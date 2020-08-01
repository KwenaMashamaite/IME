#include "IME/gui/control/TextBlock.h"

namespace IME::Gui {
    TextBlock::TextBlock(const std::string &textContent)
            : UIElement(textContent) {
        setBackgroundColour({255, 255, 255}); //White
        setTextColour({0, 0, 0}); //Black
    }

    std::string TextBlock::getType() const {
        return "TextBlock";
    }
}
