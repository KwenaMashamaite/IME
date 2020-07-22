#include <iostream>
#include "QuitingState.h"
#include "core/Engine.h"

namespace IME {
    QuitingState::QuitingState(Engine &engine) :
        MenuState(engine), isInitialized_{false},
        panel_(getGuiFactory()->getPanel<Gui::StackPanel>(Gui::StackPanel::Orientation::Vertical))
    {}

    void QuitingState::render(Gui::Window &renderTarget) {
        renderTarget.draw(*panel_);
    }

    void QuitingState::update() {}

    void QuitingState::fixedUpdate(float deltaTime) {}

    void QuitingState::initialize() {
        panel_->setOutlineThickness(2.0f);
        auto question = std::make_unique<Gui::TextBlock>("Are you sure you want to quit the application?");
        question->setTextCharSize(getApp().getRenderTarget().getDimensions().height * 2.5f / 100.0f);
        question->setOutlineThickness(1.0f);
        question->setPadding(1.0f);
        question->setOutlineColour({0, 0, 0});
        question->setBackgroundColour({51, 74, 78});
        question->setTextFont("europe-underground-dark.ttf");
        panel_->addElement("question", std::move(question));

        auto buttonsTextSize = getApp().getRenderTarget().getDimensions().height * 3.5f / 100.0f;
        auto buttonsTextFont = "philosopher.ttf";
        auto buttonsOutlineThickness = 1.0f;
        auto yesButton = std::make_unique<Gui::Button>("yes");
        yesButton->setTextCharSize(buttonsTextSize);
        yesButton->setMargin({0, 0, 0, 0.05f});
        yesButton->setOutlineThickness(buttonsOutlineThickness);
        yesButton->setTextFont(buttonsTextFont);
        yesButton->on("click", Callback<>([this] {
            getApp().stop();
        }));
        panel_->addElement("yes-btn", std::move(yesButton));

        auto noButton = std::make_unique<Gui::Button>("no");
        noButton->setTextCharSize(buttonsTextSize);
        noButton->setOutlineThickness(buttonsOutlineThickness);
        noButton->setTextFont(buttonsTextFont);
        noButton->on("click", Callback<>([this] {
            auto prevState = getApp().getPreviousStateName();
            getApp().changeState(prevState);
        }));
        panel_->addElement("no-btn", std::move(noButton));

        panel_->setPosition({
            getApp().getRenderTarget().getDimensions().width / 2.0f - panel_->getDimensions().width / 2.0f,
            getApp().getRenderTarget().getDimensions().height / 2.0f -panel_->getDimensions().height / 2.0f
        });

        //Needs to be set after because the stack panel modifies the size of UI elements
        panel_->getElement("yes-btn")->setTextAlignment(Gui::TextAlignment::Center);
        panel_->getElement("no-btn")->setTextAlignment(Gui::TextAlignment::Center);

        isInitialized_ = true;
    }

    void QuitingState::pause() {
        panel_->hide();
    }

    void QuitingState::resume() {
        panel_->show();
    }

    bool QuitingState::isInitialized() const {
        return isInitialized_;
    }

    void QuitingState::reset() {

    }
}
