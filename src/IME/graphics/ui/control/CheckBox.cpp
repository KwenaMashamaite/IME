#include "IME/graphics/ui/control/CheckBox.h"

namespace IME::Graphics::UI {
    CheckBox::CheckBox() : ClickableUIElement("Checkbox"), isChecked_(false) {
        //setBackgroundColour(Colour::Transparent);
        setPadding(sprite_.getSize().width);
        //sprite_.setTexture("checkbox-unchecked.png");
        //sprite_.setPosition(getPosition());
        addEventListener("click", Callback<>([this]{
            toggleChecked();
        }));

        addEventListener("checked", Callback<>([this]{
           // sprite_.setColour(Colour::White);
        }));

        addEventListener("unchecked", Callback<>([this]{
            //sprite_.setColour(Colour::Black);
        }));

        addEventListener("positionChanged", Callback<float, float>([this](float x, float y){
            sprite_.setPosition(x, y);
        }));
    }

    std::string CheckBox::getType() const {
        return "CheckBox";
    }

    void CheckBox::setChecked(bool isChecked) {
        if (isChecked_ != isChecked) {
            isChecked_ = isChecked;
            if (isChecked_) {
                sprite_.setTexture("checkbox-checked.png");
                emit("checked");
            } else {
                sprite_.setTexture("checkbox-unchecked.png");
                emit("unchecked");
            }
        }
    }

    void CheckBox::toggleChecked() {
        setChecked(!isChecked_);
    }

    bool CheckBox::isChecked() const {
        return isChecked_;
    }

    void CheckBox::draw(Window &renderTarget) {
        UIElement::draw(renderTarget);
        renderTarget.draw(sprite_);
    }
}