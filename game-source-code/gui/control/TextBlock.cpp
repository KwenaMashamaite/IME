#include "TextBlock.h"

Gui::TextBlock::TextBlock(const std::string &labelText)
        : UIElement(labelText)
{}

Gui::TextBlock::TextBlock(const std::string &content, const std::string &font, unsigned int textCharSize)
        : UIElement(content, font, textCharSize)
{}
