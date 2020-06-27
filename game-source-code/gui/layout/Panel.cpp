#include "Panel.h"
#include "utility/Utility.h"
#include <cassert>
#include <algorithm>

Gui::Panel::Panel(float x, float y) : isHidden_(false){
    addEventListener("outlineThicknessChanged", Callback<>([this]() {
        setPosition(getPosition());
    }));
    setFillColour({0, 0, 0, 0}); //Transparent
    setOutlineColour({255, 255, 255}); //White
    setDimensions({0.0f, 0.0f});
    setOutlineThickness(0.0f);
    setPosition({x, y});
}

void Gui::Panel::setPosition(const Position &position) {
    panel_.setPosition(position.x + panel_.getOutlineThickness(), position.y + panel_.getOutlineThickness());
    emit("positionChanged", getPosition());
}

void Gui::Panel::setDimensions(const Dimensions &dimensions) {
    panel_.setSize(sf::Vector2f(dimensions.width, dimensions.height));
    emit("dimensionsChanged", getDimensions());
}

void Gui::Panel::setFillColour(Gui::Colour fillColour) {
    panel_.setFillColor(Utility::convertOwnColourTo3rdPartyColour(fillColour));
    emit("fillColourChanged", fillColour);
}

void Gui::Panel::setOutlineColour(Gui::Colour outlineColour) {
    panel_.setOutlineColor(Utility::convertOwnColourTo3rdPartyColour(outlineColour));
    emit("outlineColourChanged", outlineColour);
}

void Gui::Panel::setOutlineThickness(float outlineThickness) {
    panel_.setOutlineThickness(outlineThickness);
    emit("outlineThicknessChanged", outlineThickness);
}

Position Gui::Panel::getPosition() const {
    return {panel_.getPosition().x, panel_.getPosition().y};
}

Dimensions Gui::Panel::getDimensions() const {
    return {panel_.getGlobalBounds().width,
            panel_.getGlobalBounds().height};
}

float Gui::Panel::getOutlineThickness() const {
    return panel_.getOutlineThickness();
}

unsigned int Gui::Panel::getNumberOfElements() const {
    return uiElements_.size();
}

void Gui::Panel::add(const std::string &alias, std::unique_ptr<UIElement> guiElement) {
    assert(guiElement && "GUI elements added to panel cannot be null");
    auto found = findUIElement(alias);
    if (found == uiElements_.end()) {
        uiElements_.push_back(std::pair(alias, std::move(guiElement)));
        emit("newElementAdded", std::prev(uiElements_.end()));
    }
}

void Gui::Panel::removeElement(const std::string &uiElement) {
    auto found = findUIElement(uiElement);
    if (found != uiElements_.end()) {
        auto elementName = found->first;
        uiElements_.erase(found);
        emit("elementRemoved", elementName);
    }
}

void Gui::Panel::hide() {
    if (!isHidden_) {
        isHidden_ = true;
        Utility::makeInvisible(panel_);
        std::for_each(uiElements_.begin(), uiElements_.end(), [](auto &uiElem) {
            uiElem.second->hide();
        });
        emit("visibilityChanged", isHidden_);
    }
}

void Gui::Panel::show() {
    if (isHidden_) {
        isHidden_ = false;
        Utility::makeVisible(panel_);
        std::for_each(uiElements_.begin(), uiElements_.end(), [](auto &uiElem) {
            uiElem.second->show();
        });
        emit("visibilityChanged", isHidden_);
    }
}

const std::unique_ptr<Gui::UIElement>& Gui::Panel::getElement(const std::string &uiElementAlias) {
    auto found = findUIElement(uiElementAlias);
    if (found != uiElements_.end())
        return found->second;
    return null_Ptr;
}

void Gui::Panel::draw(Window &renderTarget) {
    if (!isHidden_) {
        renderTarget.draw(panel_);
        std::for_each(uiElements_.begin(), uiElements_.end(), [&](auto &uiElem) {
            renderTarget.draw(*(uiElem.second));
        });
    }
}

Gui::Panel::UIElementContainer::iterator Gui::Panel::findUIElement(const std::string &uiElemAlias) {
    return std::find_if(uiElements_.begin(), uiElements_.end(),
        [this, &uiElemAlias](const auto& uiElement){
            return uiElement.first == uiElemAlias;
        }
    );
}

Gui::Panel::ConstIterator Gui::Panel::cBegin() const {
    return uiElements_.cbegin();
}

Gui::Panel::ConstIterator Gui::Panel::cEnd() const {
    return uiElements_.cend();
}

bool Gui::Panel::isHidden() const {
    return isHidden_;
}
