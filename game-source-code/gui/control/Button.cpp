#include "Button.h"
#include "input/Mouse.h"
#include <utility>

Gui::Button::Button() : Button("")
{}

Gui::Button::Button(const std::string& buttonText)
    : UIElement(buttonText),
      isSelected_(false),
      onHoverColour_({105, 105, 105}), //Dim gray
      onHoverTextColour_({169, 169, 169}), //Dark grey
      onHoverOutlineColour_({135,206,250}) //light sky blue
{
    initializeEvents();
}

void Gui::Button::initializeEvents() {
    Window::addListener("mouseMoved", Callback<int, int>([this](int x, int y) {
        if (!isHidden()) {
            if (contains(x, y) && !isSelected_) {
                isSelected_ = true;
                emit("mouseEnter");
            } else if (!contains(x, y) && isSelected_) {
                isSelected_ = false;
                emit("mouseLeave");
            }
        }
    }));

    Window::addListener("mouseButtonPressed",  Callback<Mouse::Button>(
        [this](Mouse::Button button) {
            if (isSelected_ && button == Mouse::Button::LMouseButton && !isHidden())
                emit("mouseDown");
        })
    );

    Window::addListener("mouseButtonReleased", Callback<Mouse::Button>(
        [this](Mouse::Button button) {
            if (isSelected_ && button == Mouse::Button::LMouseButton && !isHidden())
                emit("mouseUp");
            })
    );

    addListener("mouseUp", Callback<>([this] {
        emit("click");
    }));

    auto mouseDownId = addListener("mouseDown", Callback<>([this] {
        setFillColour({0, 0, 0, 0}); //Transparent
        setTextFillColour({0, 0, 0}); //Black
    }));

    auto clickId = addListener("click", Callback<>([this] {
        setFillColour(onHoverColour_); //Back to hover colour, button not exited
        setTextFillColour(onHoverTextColour_);
    }));

    auto mouseEnterId = addListener("mouseEnter", Callback<>([this] {
        setFillColour(onHoverColour_);
        setTextFillColour(onHoverTextColour_);
        setOutlineColour(onHoverOutlineColour_);
    }));

    auto defaultFillColour = getFillColour();
    auto defaultTextColour = getTextFillColour();
    auto defaultOutlineColour = getOutlineColour();
    auto mouseLeaveId = addListener("mouseLeave",Callback<>([=] {
        setFillColour(defaultFillColour);
        setTextFillColour(defaultTextColour);
        setOutlineColour(defaultOutlineColour);
    }));

    //Save handler identification numbers
    handlerIdList_.emplace_back(std::pair("mouseLeave", mouseLeaveId));
    handlerIdList_.emplace_back(std::pair("mouseEnter", mouseEnterId));
    handlerIdList_.emplace_back(std::pair("mouseDown", mouseDownId));
    handlerIdList_.emplace_back(std::pair("click", clickId));
}

void Gui::Button::setHoverFillColour(Gui::Colour fillColour) {
    onHoverColour_ = fillColour;
}

void Gui::Button::setHoverTextFillColour(Gui::Colour textFillColour) {
    onHoverTextColour_ = textFillColour;
}

void Gui::Button::setHoverOutlineColour(Gui::Colour outlineColour) {
    onHoverOutlineColour_ = outlineColour;
}

void Gui::Button::resetDefault() {
    std::for_each(handlerIdList_.begin(), handlerIdList_.end(),
        [this](const auto& handlerNameIdPair){
            removeListener(handlerNameIdPair.first, handlerNameIdPair.second);
    });
}
