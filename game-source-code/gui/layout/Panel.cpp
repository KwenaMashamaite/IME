#include "Panel.h"
#include "utility/Utility.h"
#include <cassert>
#include <algorithm>

Gui::Panel::Panel(float x, float y){
    eventEmitter_.addListener("outlineThicknessChanged", Callback<>([this](){
        setPosition(getPosition());
    }));
    setFillColour({0, 0, 0, 0}); //Transparent
    setDimensions({0.0f, 0.0f});
    setPosition({x, y});
}

Dimensions Gui::Panel::getDimensions() const {
    return {panel_.getGlobalBounds().width,
            panel_.getGlobalBounds().height};
}

void Gui::Panel::setDimensions(const Dimensions &dimensions) {
    panel_.setSize(sf::Vector2f(dimensions.width, dimensions.height));
}

Position Gui::Panel::getPosition() const {
    return {panel_.getPosition().x, panel_.getPosition().y};
}

void Gui::Panel::setPosition(const Position &position) {
    panel_.setPosition(position.x + panel_.getOutlineThickness(), position.y + panel_.getOutlineThickness());
    eventEmitter_.emit("positionChanged", Position{panel_.getPosition().x, panel_.getPosition().y});
}

void Gui::Panel::draw(Window &renderTarget) {
    renderTarget.draw(panel_);
    std::for_each(uiElements_.begin(), uiElements_.end(), [&](auto& uiElem){
        uiElem.second->draw(renderTarget);
    });
}

void Gui::Panel::setFillColour(Gui::Colour fillColour) {
    panel_.setFillColor(Utility::convertOwnColourToSFMLColour(fillColour));
}

void Gui::Panel::add(const std::string &alias, std::unique_ptr<UIElement> guiElement) {
    assert(guiElement && "GUI elements added to panel cannot be null");
    auto found = findUIElement(alias);
    if (found == uiElements_.end())
        uiElements_.push_back(std::pair(alias, std::move(guiElement)));
}

void Gui::Panel::setOutlineColour(Gui::Colour outlineColour) {
    panel_.setOutlineColor(Utility::convertOwnColourToSFMLColour(outlineColour));
}

void Gui::Panel::setOutlineThickness(float outlineThickness) {
    panel_.setOutlineThickness(outlineThickness);
    eventEmitter_.emit("outlineThicknessChanged");
}

Gui::Panel::ConstIterator Gui::Panel::cBegin() const {
    return uiElements_.cbegin();
}

Gui::Panel::ConstIterator Gui::Panel::cEnd() const {
    return uiElements_.cend();
}

float Gui::Panel::getOutlineThickness() const {
    return panel_.getOutlineThickness();
}

void Gui::Panel::remove(const std::string &uiElementName) {
    auto found = findUIElement(uiElementName);
    if (found != uiElements_.end())
        uiElements_.erase(found);
}

const std::unique_ptr<Gui::UIElement>& Gui::Panel::getElement(const std::string &uiElementAlias) {
    auto found = findUIElement(uiElementAlias);
    if (found != uiElements_.end())
        return found->second;
    return null_Ptr;
}

void Gui::Panel::hide() {
    Utility::makeInvisible(panel_);
    std::for_each(uiElements_.begin(), uiElements_.end(), [](auto& uiElem){
        uiElem.second->hide();
    });
}

void Gui::Panel::unhide() {
    Utility::makeVisible(panel_);
    std::for_each(uiElements_.begin(), uiElements_.end(), [](auto& uiElem){
        uiElem.second->unHide();
    });
}
