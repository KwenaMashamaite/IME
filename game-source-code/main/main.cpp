#include "gui/window/Window.h"
#include "resources/ResourceManager.h"
#include "input/InputManager.h"
#include "event/EventPublisher.h"
#include "globals/Globals.h"
#include "gui/control/TextBlock.h"
#include "gui/layout/StackPanel.h"
#include <iostream>

int main(){
    auto window = Gui::Window();
    window.create("duel invaders", 600u, 600u);
    auto resourceManager = ResourceManager();
    auto background = sf::Sprite(resourceManager.getTexture("backgroundTwo.png"));
    auto play = std::make_shared<Gui::TextBlock>("PLAY");
    auto exit = std::make_shared<Gui::TextBlock>("EXIT");
    auto buttonPanel = Gui::StackPanel(window.getDimensions().width / 2.0f, window.getDimensions().height /2.0f, Gui::Orientation::Vertical);
    buttonPanel.addElement(play);
    buttonPanel.addElement(exit);
    auto inputManager = InputManager();

    Globals::Events::windowClose.addListener([&window](){
        window.close();
    });

    while (window.isOpen()){
        EventPublisher::update(window);

        if(inputManager.isKeyPressed(InputManager::Key::A)){
            std::cout << "you pressed A" << std::endl;
        }
        if(inputManager.isMouseButtonPressed(InputManager::MouseButton::RMouseButton)){
            std::cout << "You right clicked mouse" << std::endl;
        }
        inputManager.update();
        window.clear();
        window.draw(background);
        buttonPanel.draw(window);
        window.display();
    }

    return 0;
}