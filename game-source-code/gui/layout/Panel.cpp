#include "Panel.h"

Gui::Panel::Panel(float x, float y){
    panel_.setFillColor(sf::Color::Transparent);
    panel_.setSize(sf::Vector2f(0, 0));
    panel_.setPosition(x, y);
}

Dimensions Gui::Panel::getDimensions() const {
    return {static_cast<unsigned int>(panel_.getGlobalBounds().width),
            static_cast<unsigned int>(panel_.getGlobalBounds().height)};
}

void Gui::Panel::setDimensions(const Dimensions &dimensions) {
    panel_.setSize(sf::Vector2f(dimensions.width, dimensions.height));
}

Position Gui::Panel::getPosition() const {
    return {panel_.getPosition().x, panel_.getPosition().y};
}

void Gui::Panel::setPosition(const Position &position) {
    panel_.setPosition(position.x, position.y);
}