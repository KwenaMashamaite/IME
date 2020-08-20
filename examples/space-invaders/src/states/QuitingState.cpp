#include <iostream>
#include "QuitingState.h"
#include "IME/core/engine/Engine.h"
#include "IME/gui/control/TextBlock.h"
#include "IME/gui/control/Button.h"
#include "IME/gui/layout/StackPanel.h"

namespace SI {
    QuitingState::QuitingState(IME::Engine &engine) :
            State(engine), isInitialized_{false},
            panel_{app().getGuiFactory()->getPanel<IME::Gui::StackPanel>(IME::Gui::StackPanel::Orientation::Vertical)}
    {}

    void QuitingState::render(IME::Gui::Window &renderTarget) {
        renderTarget.draw(*panel_);
    }

    void QuitingState::update() {}

    void QuitingState::fixedUpdate(float deltaTime) {}

    void QuitingState::initialize() {
        panel_->setOutlineThickness(2.0f);
        auto question = app().getGuiFactory()->getUIElement<IME::Gui::TextBlock>("Are you sure you want to quit the application?");
        question->setTextCharSize(
                app().getRenderTarget().getDimensions().height * 2.5f / 100.0f);
        question->setOutlineThickness(1.0f);
        question->setPadding(1.0f);
        question->setOutlineColour({0, 0, 0});
        question->setBackgroundColour({151, 74, 78});
        question->setTextFont("europe-underground-dark.ttf");
        panel_->addElement("question", std::move(question));

        auto buttonsTextSize =
                app().getRenderTarget().getDimensions().height * 3.5f / 100.0f;
        auto buttonsTextFont = "philosopher.ttf";
        auto buttonsOutlineThickness = 1.0f;
        auto yesButton = app().getGuiFactory()->getUIElement<IME::Gui::Button>("yes");
        yesButton->setTextCharSize(buttonsTextSize);
        yesButton->setMargin({0, 0, 0, 0.01f});
        yesButton->setOutlineThickness(buttonsOutlineThickness);
        yesButton->setTextFont(buttonsTextFont);
        yesButton->on("click", IME::Callback<>([this] {
            app().stop();
        }));
        panel_->addElement("yes-btn", std::move(yesButton));

        auto noButton = app().getGuiFactory()->getUIElement<IME::Gui::Button>("no");
        noButton->setTextCharSize(buttonsTextSize);
        noButton->setOutlineThickness(buttonsOutlineThickness);
        noButton->setTextFont(buttonsTextFont);
        noButton->on("click", IME::Callback<>([this] {
            auto prevState = app().getStateManager().getPreviousStateName();
            app().getStateManager().changeState(prevState);
        }));
        panel_->addElement("no-btn", std::move(noButton));

        panel_->setPosition({
                                    app().getRenderTarget().getDimensions().width / 2.0f - panel_->getDimensions().width / 2.0f,
                                    app().getRenderTarget().getDimensions().height / 2.0f - panel_->getDimensions().height / 2.0f
        });

        //Needs to be set after because the stack panel modifies the size of UI elements
        panel_->getElement("yes-btn")->setTextAlignment(IME::Gui::TextAlignment::Center);
        panel_->getElement("no-btn")->setTextAlignment(IME::Gui::TextAlignment::Center);

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

    void QuitingState::handleEvent(sf::Event event) {
        panel_->handleEvent(event);
    }
}