#include "gui/window/Window.h"

int main(){
    auto window = Gui::Window();
    window.create("duel invaders", 600u, 600u);
    while(window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear(sf::Color::Magenta);
        window.display();
    }

    return 0;
}