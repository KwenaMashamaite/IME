#include "PlayingState.h"
#include "IME/core/engine/Engine.h"
#include "IME/gui/layout/StackPanel.h"
#include "IME/gui/control/TextBlock.h"

namespace SI {
    PlayingState::PlayingState(IME::Engine &engine)
            : State(engine),
              isInitialized_(false),
              scoreboard_{"resources/textFiles/highscores.txt"} {}

    void PlayingState::initialize() {
        container_ = getApp().getGuiFactory()->getPanel<IME::Gui::DockPanel>(0, 0);
        auto headerPanel = getApp().getGuiFactory()->getPanel<IME::Gui::StackPanel>(
                IME::Gui::StackPanel::Orientation::Horizontal);
        auto lives = getApp().getGuiFactory()->getUIElement<IME::Gui::TextBlock>(
                "LIVES: 5");
        auto currentScore = getApp().getGuiFactory()->getUIElement<IME::Gui::TextBlock>(
                std::to_string(scoreboard_.getCurrentScore()));
        auto topHighScore = getApp().getGuiFactory()->getUIElement<IME::Gui::TextBlock>(
                std::to_string(scoreboard_.getTopScore()));
        headerPanel->addElement("lives", std::move(lives));
        headerPanel->addElement("current-score", std::move(currentScore));
        headerPanel->addElement("high-score", std::move(topHighScore));
        //container_->dock(Gui::DockPanel::DockPosition::TopEdge,
        //     std::move(headerPanel));
        isInitialized_ = true;
    }

    void PlayingState::update() {

    }

    void PlayingState::fixedUpdate(float deltaTime) {

    }

    void PlayingState::render(IME::Gui::Window &renderTarget) {
        renderTarget.clear();
        renderTarget.draw(*container_);
    }

    void PlayingState::pause() {

    }

    void PlayingState::resume() {

    }

    bool PlayingState::isInitialized() const {
        return isInitialized_;
    }

    void PlayingState::reset() {

    }
}