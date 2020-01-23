#include "gui/window/Window.h"
#include "resources/ResourceManager.h"

int main(){
    auto window = Gui::Window();
    window.create("duel invaders", 600u, 600u);
    auto resourceManager = ResourceManager();
    auto background = sf::Sprite(resourceManager.getTexture("backgroundTwo.png"));
    auto title = sf::Text("DUEL INVADERS", resourceManager.getFont("basson.ttf"), 50u);
    title.setPosition(window.getDimensions().width / 2.0f - title.getGlobalBounds().width / 2.0f, 0.0f);
    auto playerOne = sf::Sprite(resourceManager.getTexture("playerOne.png"));
    playerOne.setPosition(window.getDimensions().width / 2.0f, window.getDimensions().height / 2.0f);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(background);
        window.draw(title);
        window.draw(playerOne);
        window.display();
    }

    return 0;
}