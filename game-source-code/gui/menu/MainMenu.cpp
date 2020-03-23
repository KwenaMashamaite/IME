#include "MainMenu.h"
#include "gui/layout/StackPanel.h"
#include "gui/layout/Canvas.h"
#include <vector>
#include <algorithm>
#include <iostream>

Gui::MainMenu::MainMenu(Window &renderTarget, SystemEventEmitter &sysEventEmitter)
    : Menu(renderTarget), state_(State::MAIN), systemEventEmitter_(sysEventEmitter)
{
    createNavigationButtons();
    initNavigationButtonsContent();

    //Create title
    auto title = createTextBlock("SFML 2.5.0 GAME DEVELOPMENT TEMPLATE");
    title->setTextCharSize(30u);
    title->setPadding(40.0f);
    auto titlePanel = std::make_unique<StackPanel>(Window::getDimensions().width / 2.0f -
            title->getDimensions().width / 2.0f,
            0.0f,
            Orientation::Vertical);

    titlePanel->addElement(std::move(title));
    addPanel("title", std::move(titlePanel));
    //Create button to return back to main menu after clicking any other button
    auto backButton = createButton("back");
    backButton->setPosition(backButton->getDimensions().width / 2.0f, 5.0f);
    backButton->on("click", [this](){state_ = State::MAIN;});
    auto backButtonPanel = std::make_unique<Canvas>(0.0f, 0.0f);
    backButtonPanel->setDimensions({50, 50});
    backButtonPanel->addElement(std::move(backButton));
    addPanel("return", std::move(backButtonPanel));
}

void Gui::MainMenu::createNavigationButtons() {
    auto buttonTexts = std::vector{"PLAY", "INSTRUCTIONS", "HIGHSCORES", "CONTROLS", "EXIT"};
    auto buttons = std::vector<std::unique_ptr<Button>>();
    std::for_each(buttonTexts.begin(), buttonTexts.end(),[&](auto& buttonText){
        buttons.push_back(std::move(createButton(buttonText)));
    });

    auto navigationPanel = std::make_unique<StackPanel>(15.0f, 100.0f, Orientation::Vertical);
    auto onClickCallbacks = getOnClickCallbacks();
    for (auto i = 0u; i < buttons.size(); i++){
        auto& buttonPointee = (*(buttons[i].get()));
        buttonPointee.on("click", Callback<>([](){std::cout << "hey, i'm clicked" << std::endl;})); /*onClickCallbacks.at(i));*/
        navigationPanel->addElement(std::move(buttons.at(i)));
    }
    navigationPanel->setFillColour({157, 15, 241});
    addPanel("navigation", std::move(navigationPanel));
}

void Gui::MainMenu::initNavigationButtonsContent() {

}

void Gui::MainMenu::draw() {
    if (state_ == State::MAIN)
        renderPanels({"title", "navigation"});
    else if (state_ == State::CONTROLS)
        renderPanels({"control", "return"});
    else if (state_ == State::HIGHSCORES)
        renderPanels({"highscore", "return"});
    else if (state_ == State::INSTRUCTIONS)
        renderPanels({"instructions", "return"});
}

void Gui::MainMenu::clear() {

}

std::vector<Callback<>> Gui::MainMenu::getOnClickCallbacks() {
    return std::vector{
        Callback<>([this]() {
            //emit("playButtonClicked");
        }),
        Callback<>([this]() {
            state_ = State::HIGHSCORES;
        }),
        Callback<>([this]() {
            state_ = State::HIGHSCORES;
        }),
        Callback<>([this]() {
            state_ = State::CONTROLS;
        }),
        Callback<>([this]() {
            getRenderTarget().close();
        })
    };
}

std::unique_ptr<Gui::TextBlock> Gui::MainMenu::createTextBlock(const std::string &text) {
    auto textBlock = std::make_unique<TextBlock>(text);
    textBlock->setPadding(5.0f);
    textBlock->setMargin(1.0f);
    textBlock->setTextCharSize(40u);
    textBlock->setFillColour({157, 38, 241});
    return textBlock;
}

std::unique_ptr<Gui::Button> Gui::MainMenu::createButton(const std::string &buttonText){
    auto button = std::make_unique<Button>(buttonText);
    button->initialize(systemEventEmitter_);
    button->setTextCharSize(30.0f);
    button->setTextFillColour({147, 138, 197});
    button->setMargin(20.5f);
    button->setPadding(15.0f);
    return button;
}

void Gui::MainMenu::renderPanels(const std::initializer_list<std::string>& panelNames) {
    std::for_each(panelNames.begin(), panelNames.end(), [this](auto& panelName){
        auto panelPtr = getPanel(panelName);
        if (panelPtr)
            panelPtr->draw(getRenderTarget());
    });
}



