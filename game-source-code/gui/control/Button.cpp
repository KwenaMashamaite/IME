#include "Button.h"

Gui::Button::Button() : Button("")
{}

Gui::Button::Button(const std::string& buttonText)
    : UIElement(buttonText)
{
    //Colours of the button when the mouse cursor enters it (may be changed at run-time)
    onHoverColours_.fillColour = {105, 105, 105}; //Dim gray
    onHoverColours_.TextColour = {169, 169, 169}; //Dark grey
    onHoverColours_.OutlineColour = {135,206,250}; //light sky blue

    //Colours of the button when the mouse cursor leaves it (May be changed at run-time)
    defaultColours_.fillColour = getFillColour();
    defaultColours_.TextColour = getTextFillColour();
    defaultColours_.OutlineColour = getOutlineColour();

    initializeDefaultBehavior();
}

void Gui::Button::initializeDefaultBehavior() {
    addListener("mouseDown", Callback<>([this] {
        setTextFillColour({0, 0, 0}); //Black
    }));

    addListener("click", Callback<>([this] {
        setFillColour(onHoverColours_.fillColour); //Back to hover colour, button not exited
        setTextFillColour(onHoverColours_.TextColour);
    }));

    addListener("mouseEnter", Callback<>([this] {
        defaultColours_.fillColour = getFillColour();
        defaultColours_.TextColour = getTextFillColour();
        defaultColours_.OutlineColour = getOutlineColour();
        setFillColour(onHoverColours_.fillColour);
        setTextFillColour(onHoverColours_.TextColour);
        setOutlineColour(onHoverColours_.OutlineColour);
    }));

    addListener("mouseLeave",Callback<>([this] {
        setFillColour(defaultColours_.fillColour);
        setTextFillColour(defaultColours_.TextColour);
        setOutlineColour(defaultColours_.OutlineColour);
    }));
}

void Gui::Button::setHoverFillColour(Gui::Colour fillColour) {
    onHoverColours_.fillColour = fillColour;
}

void Gui::Button::setHoverTextFillColour(Gui::Colour textFillColour) {
    onHoverColours_.TextColour = textFillColour;
}

void Gui::Button::setHoverOutlineColour(Gui::Colour outlineColour) {
    onHoverColours_.OutlineColour = outlineColour;
}
