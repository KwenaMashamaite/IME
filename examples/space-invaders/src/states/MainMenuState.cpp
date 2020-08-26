#include "MainMenuState.h"
#include "IME/core/Scoreboard.h"
#include "IME/gui/drawer/Drawer.h"
#include "IME/utility/DiskFileReader.h"
#include "IME/core/engine/Engine.h"
#include "IME/gui/control/TextBlock.h"
#include "IME/gui/control/Button.h"
#include "IME/gui/layout/Canvas.h"
#include "IME/gui/layout/StackPanel.h"
#include "PlayingState.h"
#include <algorithm>
#include <cassert>

namespace SI {
    MainMenuState::MainMenuState(IME::Engine &engine)
        : State(engine),
          isInitialized_(false),
          musicPlayer_{"resources/music/"},
          currentView_(View::None)
    {}

    void MainMenuState::initialize() {
        createInfoPanel();
        createTitle();
        createReturnButton();
        createNavigationButtons();
        initNavigationButtonActions();
        changeView(View::Main);
        //musicPlayer_.play("mainMenubackgroundMusic.ogg");
        isInitialized_ = true;
    }

    void MainMenuState::render(IME::Gui::Window &renderTarget) {
        renderTarget.clear({32, 28, 28});
        static auto drawer = IME::Gui::Drawer(renderTarget);
        drawer.drawBackground("mainMenuBackground.jpg");
        switch (currentView_){
            case View::Main:
                renderTarget.draw(*(panels_["titlePanel"]));
                renderTarget.draw(*(panels_["navButtonsPanel"]));
                break;
            case View::Info:
                renderTarget.draw(*(panels_["onClickInfoPanel"]));
                break;
            case View::None:
                break;
        }
    }

    void MainMenuState::update() {
        //Nothing to update yet
    }

    void MainMenuState::fixedUpdate(float deltaTime) {
        //Nothing to update yet
    }

    void MainMenuState::pause() {
        //Buttons need to be hidden because they can still be interacted with if only cleared
        musicPlayer_.pause();
    }

    void MainMenuState::resume() {
        musicPlayer_.play();
    }

    void MainMenuState::exit() {

    }

    bool MainMenuState::isInitialized() const {
        return isInitialized_;
    }

    void MainMenuState::reset() {
        musicPlayer_.stop();
    }

    void MainMenuState::createInfoPanel(){
        auto onClickInfoPanel = engine().getGuiFactory()->getPanel<IME::Gui::Canvas>(0, 0);
        onClickInfoPanel->setDimensions(IME::Gui::Window::getDimensions());
        onClickInfoPanel->setFillColour(IME::Gui::Colour::Transparent);
        auto infoPanelTextBlock = engine().getGuiFactory()->getUIElement<IME::Gui::TextBlock>("");
        infoPanelTextBlock->setTextCharSize(engine().getWindowSize().height * 4.0f / 100.0f);
        infoPanelTextBlock->setBackgroundColour({128, 128, 128, 10});
        infoPanelTextBlock->setOutlineColour({0, 0, 0, 15});
        infoPanelTextBlock->setOutlineThickness(2.0f);
        infoPanelTextBlock->setTextFont("europe-underground-dark.ttf");
        infoPanelTextBlock->setPosition({engine().getWindowSize().width / 2,engine().getWindowSize().height / 2});
        onClickInfoPanel->addElement("infoTextBlock", std::move(infoPanelTextBlock));
        panels_.insert(std::pair("onClickInfoPanel", std::move(onClickInfoPanel)));
    }


    void MainMenuState::createTitle() {
        auto title = engine().getGuiFactory()->getUIElement<IME::Gui::Label>(engine().getGameName());
        //title->setTextFont("basson.ttf");
        title->setMargin({0, 0, 20, 0});
        title->setBackgroundColour(IME::Gui::Colour::Transparent);
        title->setTextCharSize(engine().getWindowSize().height * 13.0f / 100.0f);

        auto titlePanel = engine().getGuiFactory()->getPanel<IME::Gui::StackPanel>(IME::Gui::StackPanel::Orientation::Horizontal);
        titlePanel->addElement("title", std::move(title));
        titlePanel->setPosition({
            engine().getWindowSize().width / 2 - titlePanel->getDimensions().width / 2, 0
        });
        panels_.insert({"titlePanel", std::move(titlePanel)});
    }

    void MainMenuState::createNavigationButtons() {
        struct ButtonDetails{std::string name; std::string text;};
        auto navigationButtons = std::vector<ButtonDetails>{
            {"play-btn", "PLAY"},
            {"instructions-btn", "INSTRUCTIONS"},
            {"highscores-btn", "HIGHSCORES"},
            {"controls-btn", "CONTROLS"},
            {"exit-btn", "EXIT"}
        };
        auto buttonsPanel = std::make_unique<IME::Gui::StackPanel>( IME::Gui::StackPanel::Orientation::Vertical);
        std::for_each(navigationButtons.begin(), navigationButtons.end(), [&](auto& buttonInfo){
            auto button = std::make_unique<IME::Gui::Button>(buttonInfo.text);
            button->setTextCharSize(engine().getWindowSize().height * 4.0f / 100.0f);
            button->setTextFont("europe-underground-dark.ttf");
            button->setMargin({0, 0, 0,engine().getWindowSize().height * 5.0f / 100.0f});
            button->setBackgroundColour(IME::Gui::Colour::Transparent);
            button->setTextColour({28, 28, 28, 185});
            button->setHoverBackgroundColour(IME::Gui::Colour::Transparent);
            button->setHoverTextColour({0 , 100, 0, 180});
            buttonsPanel->addElement(buttonInfo.name, std::move(button));
        });
        buttonsPanel->setPosition({
        engine().getWindowSize().width / 2 - buttonsPanel->getDimensions().width / 2,
        engine().getWindowSize().height / 2 - buttonsPanel->getDimensions().height / 2
        });
        panels_.insert(std::pair("navButtonsPanel", std::move(buttonsPanel)));
    }

    void MainMenuState::initNavigationButtonActions() {
        auto& navButtonsPanel = panels_["navButtonsPanel"];
        auto updateInfoPanelOnButtonClick = [this, &navButtonsPanel](const std::string& childName, const std::string& text){
            navButtonsPanel->subscribeChildToEvent(childName, "click", IME::Callback<>([this, text]{
                changeView(View::Info);
                updateInfoPanel(text);
            }));
        };

        ////////PLAY BUTTON ///////////
        navButtonsPanel->subscribeChildToEvent("play-btn", "click", IME::Callback<>([this] {
            engine().popState();
            engine().pushState(std::move(std::make_shared<PlayingState>(engine())));
        }));

        auto fileReader = IME::Utility::DiskFileReader();
        auto textBuffer =  std::stringstream();

        //// INSTRUCTIONS BUTTON ///////
        fileReader.readFileInto("files/instructions.txt", textBuffer);
        updateInfoPanelOnButtonClick("instructions-btn", textBuffer.str());

        //// CONTROLS BUTTON //////////
        textBuffer.str("");
        fileReader.readFileInto("files/controls.txt", textBuffer);
        updateInfoPanelOnButtonClick("controls-btn", textBuffer.str());

        //// HIGHSCORES BUTTON ///////
        auto scoreBoard =   IME::Scoreboard("files/highscores.txt");
        auto numOfScores = std::distance(scoreBoard.cBegin(), scoreBoard.cEnd());
        auto highscoresText =  std::string("TOP " + std::to_string(numOfScores) + " HIGHSCORES");
        std::for_each(scoreBoard.cBegin(), scoreBoard.cEnd(),
            [this, &highscoresText, counter = 1u](unsigned int score) mutable{
                highscoresText.append("\n" + std::to_string(counter++) + ". " + std::to_string(score));
        });
        updateInfoPanelOnButtonClick("highscores-btn", highscoresText);

        //// EXIT BUTTON ///////////
        navButtonsPanel->subscribeChildToEvent("exit-btn", "click", IME::Callback<>([this]{
            engine().popState();
        }));
    }

    void MainMenuState::updateInfoPanel(const std::string& newInfo) {
        auto found = panels_.find("onClickInfoPanel");
        if (found != panels_.end()){
            assert(panels_["onClickInfoPanel"]->getElement("infoTextBlock") && "info panel must always have info element");
            auto& infoElement = panels_["onClickInfoPanel"]->getElement("infoTextBlock");
            infoElement->setText(newInfo);
            infoElement->setPosition(
                engine().getWindowSize().width / 2 - infoElement->getSize().width / 2,
                engine().getWindowSize().height / 2 - infoElement->getSize().height / 2
            );
        }
    }

    void MainMenuState::createReturnButton() {
        auto returnButton = engine().getGuiFactory()->getUIElement<IME::Gui::Button>("back");
        returnButton->setTextCharSize(engine().getWindowSize().height * 3.0f / 100.0f);
        returnButton->setOutlineThickness(2.0f);
        returnButton->setTextFont("europe-underground-dark.ttf");
        returnButton->setPosition(1, 1);
        returnButton->on("click", IME::Callback<>([this](){ changeView(View::Main);}));
        panels_["onClickInfoPanel"]->addElement("return-btn", std::move(returnButton));
    }

    void MainMenuState::changeView(MainMenuState::View view) {
        currentView_ = view;
        switch (view) {
            case View::Main:
                panels_.at("navButtonsPanel")->show();
                break;
            case View::Info:
                panels_.at("navButtonsPanel")->hide();
                break;
            case View::None:
                break;
        }
    }

    void MainMenuState::handleEvent(sf::Event event) {
        if (currentView_ == View::Main)
            panels_.at("navButtonsPanel")->handleEvent(event);
        else if (currentView_ == View::Info)
            panels_.at("onClickInfoPanel")->handleEvent(event);
    }
}
