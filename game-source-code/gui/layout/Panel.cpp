#include "Panel.h"
#include <cassert>

Gui::Panel::Panel(float x, float y){
    panel_.setFillColor(sf::Color::Transparent);
    panel_.setSize(sf::Vector2f(0, 0));
    panel_.setPosition(x, y);
    panel_.setOutlineThickness(1.0f);
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
    eventEmitter_.emit("positionChanged");
}

void Gui::Panel::draw(Window &renderTarget) {
    renderTarget.draw(panel_);
    for (auto &element : uiElements_)
        element->draw(renderTarget);
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

unsigned int Gui::Panel::size() const {
    return uiElements_.size();
}

void Gui::Panel::on(std::string &&event, Callback<> callback) {
    eventEmitter_.addListener(
        static_cast<std::string &&>(event),std::move(callback)
    );
}

void Gui::Panel::setOutlineColour(Gui::Colour outlineColour) {
    panel_.setOutlineColor(sf::Color(
        outlineColour.red,
        outlineColour.green, 
        outlineColour.blue,
        outlineColour.opacity
    ));
}
