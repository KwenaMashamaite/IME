#include <iostream>
#include "WindowClosePopUpMenu.h"
#include "../control/Button.h"
#include "../control/TextBlock.h"

Gui::WindowClosePopUpMenu::WindowClosePopUpMenu(Window& renderTarget)
    : renderTarget_(renderTarget),
      panel_(StackPanel::Orientation::Vertical),
      isHidden_(false)
{
    panel_.setOutlineThickness(2.0f);
    auto question = std::make_unique<TextBlock>("Are you sure you want to quit the application?");
    question->setTextCharSize(20u);
    question->setOutlineThickness(1.0f);
    question->setPadding(1.0f);
    question->setOutlineColour({0, 0, 0});
    question->setFillColour({51, 74, 78});
    question->setTextFont("europe-underground-dark.ttf");
    panel_.addElement("question", std::move(question));

    auto yesButton = std::make_unique<Button>("yes");
    yesButton->setMargin({0, 0, 0, 0.05f});
    yesButton->setOutlineThickness(1.0f);
    yesButton->setTextFont("philosopher.ttf");
    yesButton->on("click", Callback<>([this]{
        renderTarget_.close();
    }));
    panel_.addElement("yes-btn", std::move(yesButton));

    auto noButton = std::make_unique<Button>("no");
    noButton->setOutlineThickness(1.0f);
    noButton->setTextFont("philosopher.ttf");
    noButton->on("click", Callback<>([this]{
        hide();
    }));
    panel_.addElement("no-btn", std::move(noButton));

    panel_.setPosition({
        Window::getDimensions().width / 2.0f - panel_.getDimensions().width / 2.0f,
        Window::getDimensions().height / 2.0f -panel_.getDimensions().height / 2.0f
    });

    //Needs to be set after because the stack panel modifies the size of UI elements
    panel_.getElement("yes-btn")->setTextAlignment(TextAlignment::Center);
    panel_.getElement("no-btn")->setTextAlignment(TextAlignment::Center);
}

void Gui::WindowClosePopUpMenu::draw(Gui::Window &renderTarget) {
    show(); //Menu is hidden if user previously chose not to close application
    while (renderTarget.isOpen() && !isHidden()){
        renderTarget.processEvents();
        renderTarget.draw(panel_);
        renderTarget.display();
    }
}

void Gui::WindowClosePopUpMenu::hide() {
    if (!isHidden()){
        isHidden_ = true;
        panel_.hide();
    }
}

void Gui::WindowClosePopUpMenu::show() {
    if (isHidden()){
        isHidden_ = false;
        panel_.show();
    }
}

bool Gui::WindowClosePopUpMenu::isHidden() const {
    return isHidden_;
}
