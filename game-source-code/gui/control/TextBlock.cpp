#include "TextBlock.h"

Gui::TextBlock::TextBlock(const std::string &textContent)
    : UIElement(textContent), type_("TextBlock")
{
    setFillColour({255, 255, 255}); //White
    setTextFillColour({0, 0, 0}); //Black
}

const std::string &Gui::TextBlock::getType() const {
    return type_;
}
