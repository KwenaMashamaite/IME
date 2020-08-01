#include "IME/gui/control/Label.h"
#include <algorithm>

const auto maxNumOfCharacters = 250u;

Gui::Label::Label() : Label("")
{}

Gui::Label::Label(std::string text) : UIElement("") {
    /*if (text.size() >= maxNumOfCharacters)
        text = std::move(text.substr(0, maxNumOfCharacters));

    auto found = std::find(text.begin(), text.end(), "\n");
    if (found != text.end())
        setText(text.substr(0, std::distance(text.begin(), found) - 1));
    else
        setText(text);*/
}
