#include "SystemEventEmitter.h"
#include "input/Keyboard.h"
#include "input/Mouse.h"
#include <SFML/Graphics.hpp>

SystemEventEmitter::SystemEventEmitter(Gui::Window &window) : renderTarget_(window)
{}

void SystemEventEmitter::process() {
    sf::Event event;
    while (renderTarget_.pollEvent(event)) {
        switch (event.type){
            case sf::Event::Closed:
                emit("Closed");
                break;
            case sf::Event::KeyPressed:
                emit("keyPressed",
                    static_cast<Keyboard::Key>(static_cast<unsigned int>(event.key.code))
                );
                break;
            case sf::Event::KeyReleased:
                emit("keyReleased",
                    static_cast<Keyboard::Key>(static_cast<unsigned int>(event.key.code))
                );
                break;
            case sf::Event::MouseMoved:
                emit("mouseMoved", event.mouseMove.x, event.mouseMove.y);
                break;
            case sf::Event::MouseButtonPressed:
                emit("mouseButtonPressed",
                    static_cast<Mouse::Button>(static_cast<unsigned int>(event.mouseButton.button))
                );
                break;
            case sf::Event::MouseButtonReleased:
                emit("mouseButtonReleased",
                    static_cast<Mouse::Button>(static_cast<unsigned int>(event.mouseButton.button))
                );
                break;
            default:
                break;
        }
    }
}