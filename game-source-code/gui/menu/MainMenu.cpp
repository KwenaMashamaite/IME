#include "MainMenu.h"
#include "scoreboard/Scoreboard.h"
#include "../control/Button.h"
#include "../control/TextBlock.h"
#include "../layout/DockPanel.h"
#include "../layout/StackPanel.h"
#include "../layout/Canvas.h"
#include <algorithm>
#include <cassert>

Gui::MainMenu::MainMenu(Window &renderTarget)
    : renderTarget_(renderTarget),
      state_(State::Main)
{
    createInfoPanel();
    createTitle();
    createReturnButton();
    createNavigationButtons();
    initNavigationButtonActions();
}

void Gui::MainMenu::createInfoPanel(){
    auto onClickInfoPanel = std::make_unique<Canvas>(0, 0);
    onClickInfoPanel->setDimensions(Window::getDimensions());
    onClickInfoPanel->setFillColour({0, 0, 0, 0});
    auto infoPanelTextBlock = std::make_unique<TextBlock>("");
    infoPanelTextBlock->setFillColour({0, 0, 0, 0});
    infoPanelTextBlock->setTextFont("europe-underground-dark.ttf");
    infoPanelTextBlock->setPosition(Window::getDimensions().width / 2, Window::getDimensions().height / 2);
    onClickInfoPanel->addElement("infoTextBlock", std::move(infoPanelTextBlock));
    panels_.insert(std::pair("onClickInfoPanel", std::move(onClickInfoPanel)));
}

void Gui::MainMenu::createTitle() {
    auto title = std::make_unique<TextBlock>("GAME TITLE");
    title->setTextFont("basson.ttf");
    title->setFillColour({0, 0, 0, 0});
    title->setTextCharSize(80u);

    auto titlePanel = std::make_unique<StackPanel>(StackPanel::Orientation::Horizontal);
    titlePanel->addElement("title", std::move(title));
    titlePanel->setPosition({
        Window::getDimensions().width / 2 - titlePanel->getDimensions().width / 2, 0
    });
    panels_.insert(std::pair("titlePanel", std::move(titlePanel)));
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
    auto buttonsPanel = std::make_unique<StackPanel>( StackPanel::Orientation::Vertical);
    std::for_each(navigationButtons.begin(), navigationButtons.end(), [&](auto& buttonInfo){
        auto button = std::make_unique<Button>(buttonInfo.value);
        button->setTextCharSize(25);
        button->setTextFont("basson.ttf");
        button->setMargin({0, 0, 0, 40});
        button->setFillColour({0, 0, 0, 0});
        button->setHoverFillColour({0, 0, 0, 0});
        buttonsPanel->addElement(buttonInfo.name, std::move(button));
    });
    buttonsPanel->setPosition({
        Window::getDimensions().width / 2 - buttonsPanel->getDimensions().width / 2,
        Window::getDimensions().height / 2 - buttonsPanel->getDimensions().height / 2
    });
    panels_.insert(std::pair("navButtonsPanel", std::move(buttonsPanel)));
}

void Gui::MainMenu::initNavigationButtonActions() {
    auto& navButtonsPanel = panels_["navButtonsPanel"];

    auto updateInfoPanelOnButtonClick = [this, &navButtonsPanel](const std::string& childName, const std::string& text){
        navButtonsPanel->subscribeChildToEvent(childName, "click", Callback<>([this, text]{
            state_ = State::Info;
            updateInfoPanel(text);
        }));
    };

    ////////PLAY BUTTON ///////////
    navButtonsPanel->subscribeChildToEvent("play-btn", "click", Callback<>([this]{
        //@TODO - START GAME
    }));

    auto fileReader = Utility::FileReader();
    auto textBuffer =  std::stringstream();

    //// INSTRUCTIONS BUTTON ///////
    fileReader.readFileInto(textBuffer, "static/instructions.txt");
    updateInfoPanelOnButtonClick("instructions-btn", textBuffer.str());

    //// CONTROLS BUTTON //////////
    textBuffer.str("");
    fileReader.readFileInto(textBuffer, "static/controls.txt");
    updateInfoPanelOnButtonClick("controls-btn", textBuffer.str());

    //// HIGHSCORES BUTTON ///////
    auto scoreBoard = Scoreboard("static/highscores.txt");
    auto numOfScores = std::distance(scoreBoard.cBegin(), scoreBoard.cEnd());
    auto highscoresText =  std::string("TOP " + std::to_string(numOfScores) + " HIGHSCORES");
    std::for_each(scoreBoard.cBegin(), scoreBoard.cEnd(),
        [this, &highscoresText, counter = 1u](unsigned int score) mutable{
            highscoresText.append("\n" + std::to_string(counter++) + ". " + std::to_string(score));
        }
    );
    updateInfoPanelOnButtonClick("highscores-btn", highscoresText);

    //// EXIT BUTTON ///////////
    navButtonsPanel->subscribeChildToEvent("exit-btn", "click", Callback<>([this]{
        renderTarget_.close();
    }));
}

void Gui::MainMenu::draw(Window &renderTarget) {
    switch (state_){
        //Buttons need to be hidden because they can still be interacted with if only cleared
        case State::Main:
            panels_["navButtonsPanel"]->show();
            renderTarget.draw(*(panels_["titlePanel"]));
            renderTarget.draw(*(panels_["navButtonsPanel"]));
            break;
        case State::Info:
            panels_["navButtonsPanel"]->hide();
            renderTarget.draw(*(panels_["onClickInfoPanel"]));
            break;
    }
}

void Gui::MainMenu::updateInfoPanel(const std::string& newInfo) {
    auto found = panels_.find("onClickInfoPanel");
    if (found != panels_.end()){
        assert(panels_["onClickInfoPanel"]->getElement("infoTextBlock") && "info panel must always have info element");
        auto& infoElement = panels_["onClickInfoPanel"]->getElement("infoTextBlock");
        infoElement->setText(newInfo);
        infoElement->setPosition(
            Window::getDimensions().width / 2 - infoElement->getDimensions().width / 2,
            Window::getDimensions().height / 2 - infoElement->getDimensions().height / 2
        );
    }
}

void Gui::MainMenu::createReturnButton() {
    auto returnButton = std::make_unique<Button>("<-back");
    returnButton->setTextCharSize(18u);
    returnButton->setTextFont("europe-underground-dark.ttf");
    returnButton->setPosition(1, 1);
    returnButton->on("click", Callback<>([this](){state_ = State::Main;}));
    panels_["onClickInfoPanel"]->addElement("return-btn", std::move(returnButton));
}
