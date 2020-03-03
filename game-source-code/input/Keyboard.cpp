#include "Keyboard.h"
#include <SFML/Graphics.hpp>

bool Keyboard::isKeyPressed(Key keyId){
    auto isKeyCurrentlyPressed = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(keyId));
    auto wasKeyPressed = prevKeyStateMap_[keyId];
    prevKeyStateMap_[keyId] = isKeyCurrentlyPressed;
    return isKeyCurrentlyPressed && !wasKeyPressed;
}