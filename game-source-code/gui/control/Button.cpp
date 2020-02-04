#include "Button.h"

Gui::Button::Button(const std::string &buttonText) : ClickableUIElement(buttonText)
{}

Gui::Button::Button(const std::string &content, const std::string &font, unsigned int textCharSize)
        : ClickableUIElement(content, font, textCharSize)
{}
