#include "TextBlock.h"

Gui::TextBlock::TextBlock(const std::string &textContent)
    : UIElement(textContent)
{
    setFillColour({255, 255, 255}); //White
    setTextFillColour({0, 0, 0}); //Black
}
