#include "MainMenu.h"
#include "scoreboard/Scoreboard.h"
#include "resources/FileReader.h"
#include "core/Engine.h"
#include <algorithm>
#include <cassert>

Gui::MainMenu::MainMenu()
    : state_(State::Main)
{
    createInfoPanel();
    createTitle();
    createReturnButton();
    createNavigationButtons();
    initNavigationButtonActions();
}

void Gui::MainMenu::createInfoPanel(){
    auto onClickInfoPanel = getGuiFactory()->getPanel<Canvas>( 0, 0);
    onClickInfoPanel->setDimensions(Window::getDimensions());
    onClickInfoPanel->setFillColour({0, 0, 0, 0});
    auto infoPanelTextBlock = getGuiFactory()->getUIElement<TextBlock>("");
    infoPanelTextBlock->setBackgroundColour({128, 128, 128, 10});
    infoPanelTextBlock->setOutlineColour({0, 0, 0, 15});
    infoPanelTextBlock->setOutlineThickness(2.0f);
    infoPanelTextBlock->setTextFont("europe-underground-dark.ttf");
    infoPanelTextBlock->setPosition(Window::getDimensions().width / 2, Window::getDimensions().height / 2);
    onClickInfoPanel->addElement("infoTextBlock", std::move(infoPanelTextBlock));
    panels_.insert(std::pair("onClickInfoPanel", std::move(onClickInfoPanel)));
}

void Gui::MainMenu::createTitle() {
    auto title = std::move(getGuiFactory()->getUIElement<TextBlock>("GAME TITLE"));
    title->setTextFont("basson.ttf");
    title->setBackgroundColour({0, 0, 0, 0});
    title->setTextCharSize(80u);

    auto titlePanel = getGuiFactory()->getPanel<StackPanel>( StackPanel::Orientation::Horizontal);
    titlePanel->addElement("title", std::move(title));
    titlePanel->setPosition({
        Window::getDimensions().width / 2 - titlePanel->getDimensions().width / 2, 0
    });
    panels_.insert(std::pair("titlePanel", std::move(titlePanel)));
}

void Gui::MainMenu::createNavigationButtons() {
    struct ButtonDetails{std::string name; std::string text;};
    auto navigationButtons = std::vector<ButtonDetails>{
        {"play-btn", "PLAY"},
        {"instructions-btn", "INSTRUCTIONS"},
        {"highscores-btn", "HIGHSCORES"},
        {"controls-btn", "CONTROLS"},
        {"exit-btn", "EXIT"}
    };
    auto buttonsPanel = std::make_unique<StackPanel>( StackPanel::Orientation::Vertical);
    std::for_each(navigationButtons.begin(), navigationButtons.end(), [&](auto& buttonInfo){
        //Convert std::unique_ptr<UIElement> to std::unique_ptr<Button>
        std::unique_ptr<Button> button(dynamic_cast<Button*>((getGuiFactory()->getUIElement<Button>(buttonInfo.text)).release()));
        button->setTextCharSize(25);
        button->setTextFont("basson.ttf");
        button->setMargin({0, 0, 0, 40});
        button->setBackgroundColour({0, 0, 0, 0});
        button->setHoverBackgroundColour({0, 0, 0, 0});
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
        Engine::changeState("playing");
    }));

    auto fileReader = Utility::FileReader();
    auto textBuffer =  std::stringstream();

    //// INSTRUCTIONS BUTTON ///////
    fileReader.readFileInto(textBuffer, "resources/textFiles/instructions.txt");
    updateInfoPanelOnButtonClick("instructions-btn", textBuffer.str());

    //// CONTROLS BUTTON //////////
    textBuffer.str("");
    fileReader.readFileInto(textBuffer, "resources/textFiles/controls.txt");
    updateInfoPanelOnButtonClick("controls-btn", textBuffer.str());

    //// HIGHSCORES BUTTON ///////
    auto scoreBoard = Scoreboard("resources/textFiles/highscores.txt");
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
        Engine::changeState("quit");
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
    auto returnButton = getGuiFactory()->getUIElement<Button>("<-back");
    returnButton->setTextCharSize(18u);
    returnButton->setOutlineThickness(2.0f);
    returnButton->setTextFont("europe-underground-dark.ttf");
    returnButton->setPosition(1, 1);
    returnButton->on("click", Callback<>([this](){state_ = State::Main;}));
    panels_["onClickInfoPanel"]->addElement("return-btn", std::move(returnButton));
}

void Gui::MainMenu::hide() {

}

void Gui::MainMenu::show() {

}

bool Gui::MainMenu::isHidden() const {
    return false;
}
