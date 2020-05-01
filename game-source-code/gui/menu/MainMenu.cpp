#include "MainMenu.h"
#include "gui/layout/Canvas.h"
#include "gui/layout/StackPanel.h"
#include <algorithm>
#include <iostream>

Gui::MainMenu::MainMenu(Window &renderTarget)
    : renderTarget_(renderTarget),
      state_(State::Main),
      mainLayoutPanel_(std::make_unique<DockPanel>(0.0f, 0.0f)),
      onClickInfoPanel_(std::make_unique<StackPanel>(Orientation::Vertical))
{
    mainLayoutPanel_->setDimensions(Window::getDimensions());
    onClickInfoPanel_->addElement("infoTextBlock", std::make_unique<TextBlock>(""));

    initOnClickInfo();
    createTitle();
    createNavigationButtons();
    initNavigationButtonActions();
    createReturnButton();
    createFooter();
    createOnHoverInfoPanel();
}

void Gui::MainMenu::createFooter() {
    auto navInfo = std::make_unique<TextBlock>("USE THE MOUSE TO INTERACT WITH MENU");
    auto navInfoPanel = std::make_unique<Gui::StackPanel>(Gui::Orientation::Horizontal);
    navInfoPanel->addElement("navInfo", std::move(navInfo));
    mainLayoutPanel_->dock(Gui::DockPanel::DockPosition::BottomEdge, std::move(navInfoPanel));
}

void Gui::MainMenu::createTitle() {
    auto title = std::make_unique<TextBlock>("GAME TITLE");
    title->setTextFont("basson.ttf");
    title->setTextCharSize(40u);
    title->setMargin({100, 100, 10, 10});
    auto titlePanel = std::make_unique<StackPanel>(Orientation::Horizontal);
    titlePanel->addElement("title", std::move(title));
    mainLayoutPanel_->dock(DockPanel::DockPosition::TopEdge, std::move(titlePanel));
}

void Gui::MainMenu::createNavigationButtons() {
    struct ButtonDetails{std::string name; std::string value;};
    auto navigationButtons = std::vector<ButtonDetails>{
            {"play-btn", "PLAY"},
            {"instructions-btn", "INSTRUCTIONS"},
            {"highscores-btn", "HIGHSCORES"},
            {"controls-btn", "CONTROLS"},
            {"exit-btn", "EXIT"}
    };
    auto navigationPanel = std::make_unique<StackPanel>( Orientation::Vertical);
    std::for_each(navigationButtons.begin(), navigationButtons.end(), [&](auto& buttonInfo){
        auto button = std::make_unique<Button>(buttonInfo.value);
        button->setTextFont("europe-underground-light.ttf");
        navigationPanel->addElement(buttonInfo.name, std::move(button));
    });
    mainLayoutPanel_->dock(DockPanel::DockPosition::LeftEdge, std::move(navigationPanel));
}

void Gui::MainMenu::initNavigationButtonActions() {
    auto& navigationPanel = mainLayoutPanel_->getPanelAt(DockPanel::DockPosition::LeftEdge);

    ////////PLAY BUTTON ///////////
    navigationPanel->subscribeChildToEvent("play-btn", "click", Callback<>([this]{
        //Game::RequestStateChange(State::Playing);
    }));

    navigationPanel->subscribeChildToEvent("play-btn", "mouseEnter", Callback<>([this]{
        updateInfoPanel("Click to start game");
    }));

    //// INSTRUCTIONS BUTTON ///////
    navigationPanel->subscribeChildToEvent("instructions-btn", "click", Callback<>([this]{
        state_ = State::Info;
        onClickInfoPanel_->getElement("infoTextBlock")->setText(
                onClickButtonInfo_[ButtonType::Instructions]);
    }));

    navigationPanel->subscribeChildToEvent("instructions-btn", "mouseEnter", Callback<>([this]{
        updateInfoPanel("Click to see the main\nobjective of the game");
    }));

    //// CONTROLS BUTTON //////////
    navigationPanel->subscribeChildToEvent("controls-btn", "click", Callback<>([this]{
        state_ = State::Info;
        onClickInfoPanel_->getElement("infoTextBlock")->setText(
            onClickButtonInfo_[ButtonType::Controls]);
    }));

    navigationPanel->subscribeChildToEvent("controls-btn", "mouseEnter", Callback<>([this]{
        updateInfoPanel("Click to see instructions\non how to play the game");
    }));

    //// HIGHSCORES BUTTON ///////
    navigationPanel->subscribeChildToEvent("highscores-btn", "click", Callback<>([this]{
        state_ = State::Info;
        onClickInfoPanel_->getElement("infoTextBlock")->setText(
            onClickButtonInfo_[ButtonType::Highscores]);
    }));

    navigationPanel->subscribeChildToEvent("highscores-btn", "mouseEnter", Callback<>([this]{
        updateInfoPanel("Click to see the top five\nhighscoresfrom prev game");
    }));

    //// EXIT BUTTON ///////////
    navigationPanel->subscribeChildToEvent("exit-btn", "click", Callback<>([this]{
        renderTarget_.close();
    }));
    navigationPanel->subscribeChildToEvent("exit-btn", "mouseEnter", Callback<>([this]{
        updateInfoPanel("Click to exit game");
    }));
}

void Gui::MainMenu::draw() {
    switch (state_){
        case State::Main:
            mainLayoutPanel_->draw(renderTarget_);
            break;
        case State::Info:
            onClickInfoPanel_->draw(renderTarget_);
            break;
    }
}

void Gui::MainMenu::clear() {
   onClickInfoPanel_->hide();
   mainLayoutPanel_->hide();
}

void Gui::MainMenu::updateInfoPanel(const std::string& newInfo) {
    auto& infoPanel = mainLayoutPanel_->getPanelAt(DockPanel::DockPosition::RightEdge);
    if (infoPanel){
        auto& infoElement = infoPanel->getElement("onHoverInfo");
        if (infoElement)
            infoElement->setText(newInfo);
        else{
			infoPanel->addElement("onHoverInfo", std::move(std::make_unique<Button>(newInfo)));
        }
    }
}

void Gui::MainMenu::initOnClickInfo() {
    //@TODO The following is sample text, Replace it with your own text

    //INSTRUCTIONS
    auto instructionsText = R"(OBJECTIVE:
		Defeat all alien invaders before they invade planet earth (By reaching the player row).
		The game ends when all the invaders have been destroyed or if you lose all lives.

GAME MODES:
		The game can be played in two modes:

		1. SINGLE PLAYER MODE:
			In this mode the player ...

		2. MULTI-PLAYER MODE:
			In this mode ...
)";

    //CONTROLS
    auto controlsText = R"(MOVEMENT:
		Left/Right   = Move player left/right
		Up/Down   = Move player up/down

SHOOTING:
		Space bar   = Use primary weapon

GAME:
		P                   = Pause/Resume
		ESC              = Exit
	)";

    //@TODO Replace hard coded highscores with high scores from the ScoreBoard
    //HIGH SCORES
    auto highScoresText = R"(TOP FIVE HIGH SCORES
1. 1240 ASD

2. 45461 AAA

3. 7756 DGF

4. 4534T

5. 800 FFF
    )";

    onClickButtonInfo_.insert(std::pair(ButtonType::Instructions, instructionsText));
    onClickButtonInfo_.insert(std::pair(ButtonType::Controls, controlsText));
    onClickButtonInfo_.insert(std::pair(ButtonType::Highscores, highScoresText));
}

void Gui::MainMenu::createReturnButton() {
    auto returnButton = std::make_unique<Button>("back to main");
    returnButton->setTextCharSize(20u);
    (*(returnButton.get())).on("click", Callback<>([this](){state_ = State::Main;}));
    onClickInfoPanel_->addElement("returnButton", std::move(returnButton));
}

void Gui::MainMenu::createOnHoverInfoPanel() {
    auto onHoverInfoPanel = std::make_unique<StackPanel>( Orientation::Vertical);
    auto infoElement = std::make_unique<TextBlock>("Hover over button to display\naddtional info");
    infoElement->setFillColour({0, 0, 0, 0});
    onHoverInfoPanel->addElement("onHoverInfo", std::move(infoElement));
    mainLayoutPanel_->dock(DockPanel::DockPosition::RightEdge, std::move(onHoverInfoPanel));
}
