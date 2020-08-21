#include "IME/gui/control/Label.h"

namespace IME::Gui {
    Label::Label() : Label("")
    {}

    Label::Label(const std::string& text) : UIElement("") {
        auto newLineCharPos = text.find_first_of('\n');
        if (newLineCharPos != std::string::npos)
            setText(text.substr(0, newLineCharPos));
        else
            setText(text);
    }

    std::string Label::getType() const {
        return "Label";
    }
}