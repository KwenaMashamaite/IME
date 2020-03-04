#include "Panel.h"

Gui::Panel::Panel(float x, float y){
    panel_.setFillColor(sf::Color::Transparent);
    panel_.setSize(sf::Vector2f(0, 0));
    panel_.setPosition(x, y);
    panel_.setOutlineThickness(1.0f);
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
    eventEmitter_.emit("positionChanged");
}

void Gui::Panel::draw(Window &renderTarget) {
    renderTarget.draw(panel_);
    for (auto &element : guiElementList_) {
        if (element != nullptr)
            element->draw(renderTarget);
    }
}

void Gui::Panel::setFillColour(Gui::Colour fillColour) {
    panel_.setFillColor(sf::Color(fillColour.red, fillColour.green,
                        fillColour.blue, fillColour.opacity));
}

bool Gui::Panel::add(std::shared_ptr<UIElement> UIElement) {
    if (UIElement == nullptr)
        return false;
    return guiElementList_.insert(UIElement).second;
}

unsigned int Gui::Panel::size() const {
    return guiElementList_.size();
}

void Gui::Panel::on(std::string &&event, Callback<> callback) {
    eventEmitter_.addListener(static_cast<std::string &&>(event), std::move(callback));
}

void Gui::Panel::setOutlineColour(Gui::Colour outlineColour) {
    panel_.setOutlineColor(sf::Color(
        outlineColour.red,
        outlineColour.green, 
        outlineColour.blue,
        outlineColour.opacity
    ));
}
