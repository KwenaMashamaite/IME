#include "IME/graphics/ui/elements/Button.h"

namespace IME::Graphics::UI {
    Button::Button() : Button("")
    {}

    Button::Button(const std::string& buttonText)
        : ClickableUIElement(buttonText), isSelected_(false)
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

    void Button::initializeDefaultBehavior() {
        addEventListener("leftMouseDown", Callback<>([this] {
            setTextColour({0, 0, 0, 110}); //Black
        }));

        addEventListener("click", Callback<>([this] {
            setBackgroundColour(onHoverColours_.backgroundColour); //Back to hover colour, button not exited
            setTextColour(onHoverColours_.textColour);
            setOutlineColour(onHoverColours_.outlineColour);
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
        addEventListener("disabled",Callback<>([this] {
            if (!isHidden()) {
                //Save currently set colours before overriding them
                defaultColours_.backgroundColour = getBackgroundColour();
                defaultColours_.textColour = getTextColour();
                defaultColours_.outlineColour = getOutlineColour();
                setTextColour({0, 0, 0, 90}); //Black
                setBackgroundColour({105, 105, 105, 70}); //Dim Grey
                setOutlineColour({128, 128, 128, 70}); //Grey
            }
        }));

        // Restore button colours to the way they were before it was disabled
        addEventListener("enabled", Callback<>([this] {
            if (!isHidden()) {
                setTextColour(defaultColours_.textColour);
                setBackgroundColour(defaultColours_.backgroundColour);
                setOutlineColour(defaultColours_.outlineColour);
            }
        }));
    }

    void Button::setSelected(bool isSelected) {
        if (isSelected != isSelected_ && isEnabled() && !isHidden()) {
            isSelected_ = isSelected;
            if (isSelected_)
                emit("selected");
            else
                emit("deselected");
        }
    }

    void Button::setHoverBackgroundColour(Colour backgroundColour) {
        onHoverColours_.backgroundColour = backgroundColour;
    }

    void Button::setHoverTextColour(Colour textColour) {
        onHoverColours_.textColour = textColour;
    }

    void Button::setHoverOutlineColour(Colour outlineColour) {
        onHoverColours_.outlineColour = outlineColour;
    }

    std::string Button::getType() const {
        return "Button";
    }

    bool Button::isSelected() const {
        return isSelected_;
    }
}
