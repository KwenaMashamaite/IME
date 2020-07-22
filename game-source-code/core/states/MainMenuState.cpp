#include "MainMenuState.h"
#include "gui/drawer/Drawer.h"
#include "scoreboard/Scoreboard.h"
#include "resources/FileReader.h"
#include "core/Engine.h"
#include <algorithm>
#include <cassert>

namespace IME {
    MainMenuState::MainMenuState(Engine &engine)
        : MenuState(engine),
          isInitialized_(false),
          musicPlayer_{"resources/music/"},
          currentView_(View::None)
    {
        musicPlayer_.loadFromFile({"mainMenubackgroundMusic.wav"});
    }

    void MainMenuState::initialize() {
        createInfoPanel();
        createTitle();
        createReturnButton();
        createNavigationButtons();
        initNavigationButtonActions();
        changeView(View::Main);
        musicPlayer_.setLoop(true);
        musicPlayer_.play("mainMenubackgroundMusic.wav");
        isInitialized_ = true;
    }

    void MainMenuState::render(Gui::Window &renderTarget) {
        renderTarget.clear({32, 28, 28});
        static auto drawer = Gui::Drawer(renderTarget);
        drawer.drawBackground("mainMenuBackground.png");
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
        panels_["navButtonsPanel"]->hide();
        musicPlayer_.pause();
    }

    void MainMenuState::resume() {
        panels_["navButtonsPanel"]->show();
        musicPlayer_.play();
    }

    bool MainMenuState::isInitialized() const {
        return isInitialized_;
    }

    void MainMenuState::reset() {
        musicPlayer_.stop();
    }

    void MainMenuState::createInfoPanel(){
        auto onClickInfoPanel = getGuiFactory()->getPanel<Gui::Canvas>( 0, 0);
        onClickInfoPanel->setDimensions(getApp().getRenderTarget().getDimensions());
        onClickInfoPanel->setFillColour({0, 0, 0, 0});
        auto infoPanelTextBlock = getGuiFactory()->getUIElement<Gui::TextBlock>("");
        infoPanelTextBlock->setTextCharSize(getApp().getRenderTarget().getDimensions().height * 4.0f / 100.0f);
        infoPanelTextBlock->setBackgroundColour({128, 128, 128, 10});
        infoPanelTextBlock->setOutlineColour({0, 0, 0, 15});
        infoPanelTextBlock->setOutlineThickness(2.0f);
        infoPanelTextBlock->setTextFont("europe-underground-dark.ttf");
        infoPanelTextBlock->setPosition({
            getApp().getRenderTarget().getDimensions().width / 2,
            getApp().getRenderTarget().getDimensions().height / 2
        });
        onClickInfoPanel->addElement("infoTextBlock", std::move(infoPanelTextBlock));
        panels_.insert(std::pair("onClickInfoPanel", std::move(onClickInfoPanel)));
    }

    void MainMenuState::createTitle() {
        auto title = std::move(getGuiFactory()->getUIElement<Gui::TextBlock>(getApp().getAppName()));
        title->setTextFont("basson.ttf");
        title->setBackgroundColour({0, 0, 0, 0});
        title->setTextCharSize(getApp().getRenderTarget().getDimensions().height * 13.0f / 100.0f);

        auto titlePanel = getGuiFactory()->getPanel<Gui::StackPanel>( Gui::StackPanel::Orientation::Horizontal);
        titlePanel->addElement("title", std::move(title));
        titlePanel->setPosition({
            getApp().getRenderTarget().getDimensions().width / 2 - titlePanel->getDimensions().width / 2, 0
        });
        panels_.insert(std::pair("titlePanel", std::move(titlePanel)));
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
        auto buttonsPanel = std::make_unique<Gui::StackPanel>( Gui::StackPanel::Orientation::Vertical);
        std::for_each(navigationButtons.begin(), navigationButtons.end(), [&](auto& buttonInfo){
            auto button = getGuiFactory()->getUIElement<Gui::Button>(buttonInfo.text);
            button->setTextCharSize(getApp().getRenderTarget().getDimensions().height * 4.0f / 100.0f);
            button->setTextFont("basson.ttf");
            button->setMargin({0, 0, 0, getApp().getRenderTarget().getDimensions().height * 5.0f / 100.0f});
            button->setBackgroundColour({0, 0, 0, 0});
            button->setHoverBackgroundColour({0, 0, 0, 0});
            buttonsPanel->addElement(buttonInfo.name, std::move(button));
        });
        buttonsPanel->setPosition({
            getApp().getRenderTarget().getDimensions().width / 2 - buttonsPanel->getDimensions().width / 2,
            getApp().getRenderTarget().getDimensions().height / 2 - buttonsPanel->getDimensions().height / 2
        });
        panels_.insert(std::pair("navButtonsPanel", std::move(buttonsPanel)));
    }

    void MainMenuState::initNavigationButtonActions() {
        auto& navButtonsPanel = panels_["navButtonsPanel"];
        auto updateInfoPanelOnButtonClick = [this, &navButtonsPanel](const std::string& childName, const std::string& text){
            navButtonsPanel->subscribeChildToEvent(childName, "click", Callback<>([this, text]{
                changeView(View::Info);
                updateInfoPanel(text);
            }));
        };

        ////////PLAY BUTTON ///////////
        navButtonsPanel->subscribeChildToEvent("play-btn", "click", Callback<>([this]{
            getApp().changeState("playing");
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
        });
        updateInfoPanelOnButtonClick("highscores-btn", highscoresText);

        //// EXIT BUTTON ///////////
        navButtonsPanel->subscribeChildToEvent("exit-btn", "click", Callback<>([this]{
            getApp().changeState("quit");
        }));
    }

    void MainMenuState::updateInfoPanel(const std::string& newInfo) {
        auto found = panels_.find("onClickInfoPanel");
        if (found != panels_.end()){
            assert(panels_["onClickInfoPanel"]->getElement("infoTextBlock") && "info panel must always have info element");
            auto& infoElement = panels_["onClickInfoPanel"]->getElement("infoTextBlock");
            infoElement->setText(newInfo);
            infoElement->setPosition(
                getApp().getRenderTarget().getDimensions().width / 2 - infoElement->getDimensions().width / 2,
                getApp().getRenderTarget().getDimensions().height / 2 - infoElement->getDimensions().height / 2
            );
        }
    }

    void MainMenuState::createReturnButton() {
        auto returnButton = getGuiFactory()->getUIElement<Gui::Button>("<-back");
        returnButton->setTextCharSize(getApp().getRenderTarget().getDimensions().height * 3.0f / 100.0f);
        returnButton->setOutlineThickness(2.0f);
        returnButton->setTextFont("europe-underground-dark.ttf");
        returnButton->setPosition(1, 1);
        returnButton->on("click", Callback<>([this](){ changeView(View::Main);}));
        panels_["onClickInfoPanel"]->addElement("return-btn", std::move(returnButton));
    }

    void MainMenuState::changeView(MainMenuState::View view) {
        currentView_ = view;
        switch (view) {
            case View::Main:
                panels_["navButtonsPanel"]->show();
                break;
            case View::Info:
                panels_["navButtonsPanel"]->hide();
                break;
            case View::None:
                break;
        }
    }
}
