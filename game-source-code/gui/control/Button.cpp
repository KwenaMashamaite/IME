#include "Button.h"

Gui::Button::Button() : Button("")
{}

Gui::Button::Button(const std::string& buttonText)
    : ClickableUIElement(buttonText), type_("Button"), isSelected_(false)
{
    //Colours of the button when the mouse cursor enters it (may be changed at run-time)
    onHoverColours_.backgroundColour = {105, 105, 105}; //Dim gray
    onHoverColours_.textColour = {169, 169, 169}; //Dark grey
    onHoverColours_.outlineColour = {135, 206, 250}; //light sky blue

    //Colours of the button when the mouse cursor leaves it (May be changed at run-time)
    defaultColours_.backgroundColour = getBackgroundColour();
    defaultColours_.textColour = getTextColour();
    defaultColours_.outlineColour = getOutlineColour();

    initializeDefaultBehavior();
}

void Gui::Button::initializeDefaultBehavior() {
    addEventListener("mouseDown", Callback<>([this] {
        setTextColour({0, 0, 0}); //Black
    }));

    addEventListener("click", Callback<>([this] {
        setBackgroundColour(onHoverColours_.backgroundColour); //Back to hover colour, button not exited
        setTextColour(onHoverColours_.textColour);
    }));

    addEventListener("mouseEnter", Callback<>([this] {
        setSelected(true);
        defaultColours_.backgroundColour = getBackgroundColour();
        defaultColours_.textColour = getTextColour();
        defaultColours_.outlineColour = getOutlineColour();
        setBackgroundColour(onHoverColours_.backgroundColour);
        setTextColour(onHoverColours_.textColour);
        setOutlineColour(onHoverColours_.outlineColour);
    }));

    addEventListener("mouseLeave", Callback<>([this] {
        setSelected(false);
        setBackgroundColour(defaultColours_.backgroundColour);
        setTextColour(defaultColours_.textColour);
        setOutlineColour(defaultColours_.outlineColour);
    }));

    // Grey out button when it is disabled
    addEventListener("interactivityChanged",Callback<bool>([this](bool isEnabled) {
        if (!isHidden()) {
            if (!isEnabled) {
                //Save currently set colours before overriding them
                defaultColours_.backgroundColour = getBackgroundColour();
                defaultColours_.textColour = getTextColour();
                defaultColours_.outlineColour = getOutlineColour();
                setTextColour({0, 0, 0, 127}); //Black
                setBackgroundColour({105, 105, 105}); //Dim Grey
                setOutlineColour({128, 128, 128}); //Grey
            }else { //Restore previous colours when button is re-enabled
                setTextColour(defaultColours_.textColour);
                setBackgroundColour(defaultColours_.backgroundColour);
                setOutlineColour(defaultColours_.outlineColour);
            }
        }
    }));
}

void Gui::Button::setSelected(bool isSelected) {
    if (isSelected != isSelected_) {
        isSelected_ = isSelected;
        emit("selectionChanged", isSelected_);
    }
}

void Gui::Button::setHoverBackgroundColour(Gui::Colour backgroundColour) {
    onHoverColours_.backgroundColour = backgroundColour;
}

void Gui::Button::setHoverTextColour(Gui::Colour textColour) {
    onHoverColours_.textColour = textColour;
}

void Gui::Button::setHoverOutlineColour(Gui::Colour outlineColour) {
    onHoverColours_.outlineColour = outlineColour;
}

const std::string &Gui::Button::getType() const {
    return type_;
}

bool Gui::Button::isSelected() const {
    return isSelected_;
}
