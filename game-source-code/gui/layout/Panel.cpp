#include "Panel.h"
#include <cassert>
#include <algorithm>

Gui::Panel::Panel(float x, float y){
    panel_.setFillColor(sf::Color::Transparent);
    panel_.setSize(sf::Vector2f(0, 0));
    panel_.setPosition(x, y);
}

Dimensions Gui::Panel::getDimensions() const {
    return Dimensions{
        static_cast<unsigned int>(panel_.getGlobalBounds().width),
        static_cast<unsigned int>(panel_.getGlobalBounds().height)
    };
}

void Gui::Panel::setDimensions(const Dimensions &dimensions) {
    panel_.setSize(sf::Vector2f(dimensions.width, dimensions.height));
}

Position Gui::Panel::getPosition() const {
    return Position{panel_.getPosition().x, panel_.getPosition().y};
}

void Gui::Panel::setPosition(const Position &position) {
    panel_.setPosition(position.x, position.y);
    eventEmitter_.emit("positionChanged", position);
}

void Gui::Panel::draw(Window &renderTarget) {
    renderTarget.draw(panel_);
    std::for_each(uiElements_.begin(), uiElements_.end(), [&](auto& uiElem){
        uiElem->draw(renderTarget);
    });
}

void Gui::Panel::setFillColour(Gui::Colour fillColour) {
    panel_.setFillColor(sf::Color(
        fillColour.red, fillColour.green,
        fillColour.blue, fillColour.opacity)
    );
}

void Gui::Panel::add(std::shared_ptr<UIElement> guiElement) {
    assert(guiElement && "GUI elements added to panel cannot be null");
    uiElements_.push_back(std::move(guiElement));
}

void Gui::Panel::setOutlineColour(Gui::Colour outlineColour) {
    panel_.setOutlineColor(sf::Color(
        outlineColour.red,outlineColour.green,
        outlineColour.blue,outlineColour.opacity
    ));
}

void Gui::Panel::setOutlineThickness(float outlineThickness) {
    panel_.setOutlineThickness(outlineThickness);
}

Gui::Panel::constIterator Gui::Panel::cBegin() const {
    return uiElements_.cbegin();
}

Gui::Panel::constIterator Gui::Panel::cEnd() const {
    return uiElements_.cend();
}

float Gui::Panel::getOutlineThickness() const {
    return panel_.getOutlineThickness();
}
