#include "MainMenu.h"
#include "gui/layout/Canvas.h"
#include "gui/layout/StackPanel.h"
#include <algorithm>

Gui::MainMenu::MainMenu(Window &renderTarget)
    : renderTarget_(renderTarget),
      state_(State::Main),
      mainLayoutPanel_(std::make_unique<DockPanel>(0.0f, 0.0f)),
      onClickInfoPanel_(std::make_unique<StackPanel>(0.0f,0.0f, Orientation::Vertical))
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
    navInfo->setTextCharSize(15.0f);
    navInfo->setPadding({100, 100, 0, 0});
    auto navInfoPanel = std::make_unique<Gui::StackPanel>(0.0f, 0.0f, Gui::Orientation::Horizontal);
    navInfoPanel->setFillColour({45, 78, 251});
    navInfoPanel->addElement("navInfo", std::move(navInfo));
    this->mainLayoutPanel_->dock(Gui::DockPanel::DockPosition::BottomEdge, std::move(navInfoPanel));
}

void Gui::MainMenu::createTitle() {
    auto title = std::make_unique<TextBlock>("SFML 2.5.0 GAME DEV TEMPLATE");
    title->setPadding({0.0f, 0.0f, 10.0f, 80.0f });
    title->setFillColour({14, 45, 178});
    auto titlePanel = std::make_unique<StackPanel>(0.0f, 0.0f,Orientation::Vertical);
    titlePanel->addElement("title", std::move(title));
    mainLayoutPanel_->dock(DockPanel::DockPosition::TopEdge, std::move(titlePanel));
}

void Gui::MainMenu::createNavigationButtons() {
    auto buttonTexts = std::vector{
        std::pair(ButtonType::Play, "PLAY"),
        std::pair(ButtonType::Instructions, "INSTRUCTIONS"),
        std::pair(ButtonType::Highscores, "HIGHSCORES"),
        std::pair(ButtonType::Controls, "CONTROLS"),
        std::pair(ButtonType::Exit, "EXIT")
    };

    auto navButtonsFont = "basson.ttf";
    auto navButtonsTextCharSize = 40u;
    std::for_each(buttonTexts.begin(), buttonTexts.end(),[&](auto& buttonText){
        auto button = std::make_unique<Button>(buttonText.second, navButtonsFont, navButtonsTextCharSize);
        navButtons_.push_back(std::pair(buttonText.first, std::move(button)));
    });
}

void Gui::MainMenu::initNavigationButtonActions() {
    auto navigationPanel = std::make_unique<StackPanel>(0.0f, 0.0f, Orientation::Vertical);
    navigationPanel->setFillColour({157, 15, 241});
    navigationPanel->setOutlineThickness(5.0f);

    for (auto i = 0u; i < navButtons_.size(); ++i){
        auto &buttonPointee = (*(navButtons_[i].second.get()));
        switch (navButtons_[i].first) {
            case ButtonType::Play:
                buttonPointee.on("mouseEnter", Callback<>([this]() {
                    updateInfoPanel("Click button to start the game");
                }));
                buttonPointee.on("click", Callback<>([this]() {
                    //emit("playButtonClicked");
                }));
                break;
            case ButtonType::Instructions:
                buttonPointee.on("mouseEnter", Callback<>([this]() {
                    updateInfoPanel("Click button to see the main objective of the game");
                }));
                buttonPointee.on("click", Callback<>([this]() {
                    state_ = State::Info;
                    onClickInfoPanel_->getElement("infoTextBlock")->setText(
                            onClickButtonInfo_[ButtonType::Instructions]);
                }));
                break;
            case ButtonType::Controls:
                buttonPointee.on("mouseEnter", Callback<>([this]() {
                    updateInfoPanel("Click button to see the instructions on how to play the game");
                }));
                buttonPointee.on("click", Callback<>([this]() {
                    state_ = State::Info;
                    onClickInfoPanel_->getElement("infoTextBlock")->setText(
                            onClickButtonInfo_[ButtonType::Controls]);
                }));
                break;
            case ButtonType::Highscores:
                buttonPointee.on("mouseEnter", Callback<>([this]() {
                    updateInfoPanel("Click button to see the top 5 highscores from the previous game");
                }));
                buttonPointee.on("click", Callback<>([this]() {
                    state_ = State::Info;
                    onClickInfoPanel_->getElement("infoTextBlock")->setText(
                            onClickButtonInfo_[ButtonType::Highscores]);
                }));
                break;
            case ButtonType::Exit:
                buttonPointee.on("mouseEnter", Callback<>([this]() {
                    updateInfoPanel("Click button to exit the game");
                }));
                buttonPointee.on("click", Callback<>([this]() {
                    renderTarget_.close();
                }));
                break;
        }
        navigationPanel->addElement(std::to_string(static_cast<int>(navButtons_[i].first)), std::move(navButtons_[i].second));
    }
    navButtons_.clear();
    mainLayoutPanel_->dock(DockPanel::DockPosition::LeftEdge, std::move(navigationPanel));
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
    auto buttonTextFont = "philosopher.ttf";
    auto buttonSize = 20u;
    auto returnButton = std::make_unique<Button>("back to main", buttonTextFont, buttonSize);
    (*(returnButton.get())).on("click", Callback<>([this](){state_ = State::Main;}));
    onClickInfoPanel_->addElement("returnButton", std::move(returnButton));
}

void Gui::MainMenu::createOnHoverInfoPanel() {
    auto onHoverInfoPanel = std::make_unique<StackPanel>(0.0f,0.0f, Orientation::Vertical);
    auto infoElement = std::make_unique<TextBlock>(""); //Assuming initially no button is hovered over
    onHoverInfoPanel->addElement("onHoverInfo", std::move(infoElement));
    mainLayoutPanel_->dock(DockPanel::DockPosition::RightEdge, std::move(onHoverInfoPanel));
}
