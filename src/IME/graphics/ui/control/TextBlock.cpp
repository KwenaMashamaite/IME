#include "IME/graphics/ui/control/TextBlock.h"

namespace IME::Graphics::UI {
    TextBlock::TextBlock(const std::string &textContent)
            : UIElement(textContent) {
        setBackgroundColour(Colour::White);
        setTextColour(Colour::Black);
    }

    std::string TextBlock::getType() const {
        return "TextBlock";
    }
}