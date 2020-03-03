#include "Mouse.h"
#include <SFML/Graphics.hpp>

bool Mouse::isButtonPressed(Button button){
    return sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(button));
}