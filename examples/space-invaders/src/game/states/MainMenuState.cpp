#include "MainMenuState.h"
#include "IME/core/Scoreboard.h"
#include "IME/gui/drawer/Drawer.h"
#include "IME/utility/DiskFileReader.h"
#include "IME/core/engine/Engine.h"
#include "IME/gui/control/TextBlock.h"
#include "IME/gui/control/Button.h"
#include "IME/gui/layout/Canvas.h"
#include "IME/gui/layout/StackPanel.h"
#include <algorithm>
#include <cassert>

namespace SI {
    MainMenuState::MainMenuState(IME::Engine &engine)
            : State(engine),
              isInitialized_(false),
              musicPlayer_{"resources/music/"},
              currentView_(View::None)
    {
        //musicPlayer_.loadFromFile({"mainMenubackgroundMusic.ogg"});
    }

    void MainMenuState::initialize() {
        createInfoPanel();
        createTitle();
        createReturnButton();
        createNavigationButtons();
        initNavigationButtonActions();
        changeView(View::Main);
        musicPlayer_.setLoop(true);
        //musicPlayer_.play("mainMenubackgroundMusic.ogg");
        isInitialized_ = true;
    }

    void MainMenuState::render(IME::Gui::Window &renderTarget) {
        renderTarget.clear({32, 28, 28});
        static auto drawer = IME::Gui::Drawer(renderTarget);
        //drawer.drawBackground("mainMenuBackground.png");
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
        auto onClickInfoPanel = getApp().getGuiFactory()->getPanel<IME::Gui::Canvas>( 0, 0);
        onClickInfoPanel->setDimensions(getApp().getRenderTarget().getDimensions());
        onClickInfoPanel->setFillColour(IME::Gui::Colour::Transparent);
        auto infoPanelTextBlock = getApp().getGuiFactory()->getUIElement<IME::Gui::TextBlock>("");
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
        auto title = getApp().getGuiFactory()->getUIElement<IME::Gui::TextBlock>(getApp().getAppName());
        title->setTextFont("basson.ttf");
        title->setBackgroundColour(IME::Gui::Colour::Transparent);
        title->setTextCharSize(getApp().getRenderTarget().getDimensions().height * 13.0f / 100.0f);

        auto titlePanel = getApp().getGuiFactory()->getPanel<IME::Gui::StackPanel>( IME::Gui::StackPanel::Orientation::Horizontal);
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
        auto buttonsPanel = std::make_unique<IME::Gui::StackPanel>( IME::Gui::StackPanel::Orientation::Vertical);
        std::for_each(navigationButtons.begin(), navigationButtons.end(), [&](auto& buttonInfo){

            std::unique_ptr<IME::Gui::Button> button(dynamic_cast<IME::Gui::Button*>((getApp().getGuiFactory()->getUIElement<IME::Gui::Button>(buttonInfo.text)).release()));
            button->setTextCharSize(getApp().getRenderTarget().getDimensions().height * 4.0f / 100.0f);
            button->setTextFont("basson.ttf");
            button->setMargin({0, 0, 0, getApp().getRenderTarget().getDimensions().height * 5.0f / 100.0f});
            button->setBackgroundColour(IME::Gui::Colour::Transparent);
            button->setHoverBackgroundColour(IME::Gui::Colour::Transparent);
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
            navButtonsPanel->subscribeChildToEvent(childName, "click", IME::Callback<>([this, text]{
                changeView(View::Info);
                updateInfoPanel(text);
            }));
        };

        ////////PLAY BUTTON ///////////
        navButtonsPanel->subscribeChildToEvent("play-btn", "click", IME::Callback<>([this]{
            getApp().changeState("playing");
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
                getApp().getRenderTarget().getDimensions().width / 2 - infoElement->getSize().width / 2,
                getApp().getRenderTarget().getDimensions().height / 2 - infoElement->getSize().height / 2
            );
        }
    }

    void MainMenuState::createReturnButton() {
        auto returnButton = getApp().getGuiFactory()->getUIElement<IME::Gui::Button>("main menu");
        returnButton->setTextCharSize(getApp().getRenderTarget().getDimensions().height * 3.0f / 100.0f);
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
