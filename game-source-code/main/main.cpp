#include "gui/window/Window.h"
#include "resources/ResourceManager.h"
#include "input/InputManager.h"
#include "event/EventPublisher.h"
#include "globals/Globals.h"
#include <iostream>

int main(){
    auto window = Gui::Window();
    window.create("duel invaders", 600u, 600u);
    auto resourceManager = ResourceManager();
    auto background = sf::Sprite(resourceManager.getTexture("backgroundTwo.png"));
    auto title = sf::Text("DUEL INVADERS", resourceManager.getFont("basson.ttf"), 50u);
    title.setPosition(window.getDimensions().width / 2.0f - title.getGlobalBounds().width / 2.0f, 0.0f);
    auto playerOne = sf::Sprite(resourceManager.getTexture("playerOne.png"));
    playerOne.setPosition(window.getDimensions().width / 2.0f, window.getDimensions().height / 2.0f);
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
        window.draw(title);
        window.draw(playerOne);
        window.display();
    }

    return 0;
}