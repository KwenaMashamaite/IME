#include "EventPublisher.h"
#include "input/Keyboard.h"
#include "globals/Globals.h"
#include <SFML/Graphics.hpp>

using Globals::Events;

void EventPublisher::update(Gui::Window &renderTarget) {
    sf::Event event;
    while (renderTarget.pollEvent(event)) {
        switch (event.type){
            case sf::Event::Closed:
                Events::windowClose.notifyListeners();
                break;
            case sf::Event::KeyPressed:
                Events::keyPressed.notifyListeners(
                    static_cast<Keyboard::Key>(
                        static_cast<unsigned int>(event.key.code)
                    )
                ); 
                break;
            case sf::Event::KeyReleased:
                Events::keyReleased.notifyListeners(
                    static_cast<Keyboard::Key>(
                        static_cast<unsigned int>(event.key.code)
                    )
                ); 
                break;
            case sf::Event::MouseMoved:
                Events::mouseMoved.notifyListeners(
					event.mouseMove.x,
                    event.mouseMove.y
				);
                break;
            case sf::Event::MouseButtonPressed:
                Events::mouseButtonPressed.notifyListeners(
                    static_cast<Mouse::MouseButton>(static_cast<unsigned int>(
                    event.mouseButton.button))
                ); 
                break;
            case sf::Event::MouseButtonReleased:
                Events::mouseButtonReleased.notifyListeners(
                    static_cast<Mouse::MouseButton>(static_cast<unsigned int>(
                    event.mouseButton.button))
                ); 
                break;
            default:
                break;
        }
    }
}
