#include "IME/graphics/ui/layout/Panel.h"
#include "IME/utility/Helpers.h"
#include <cassert>
#include <algorithm>

namespace IME::Graphics::UI {
    Panel::Panel(float x, float y) : isHidden_(false){
        setFillColour(Colour::Transparent);
        setOutlineColour(Colour::White);
        setDimensions({0.0f, 0.0f});
        setOutlineThickness(0.0f);
        setPosition({x, y});

        addEventListener("outlineThicknessChanged", Callback<>([this]() {
            setPosition(getPosition());
        }));
    }

    void Panel::setPosition(const Position &position) {
        panel_.setPosition(position.x + panel_.getOutlineThickness(), position.y + panel_.getOutlineThickness());
        emit("positionChanged", getPosition());
    }

    void Panel::setDimensions(const Dimensions &dimensions) {
        panel_.setSize(sf::Vector2f(dimensions.width, dimensions.height));
        emit("dimensionsChanged", getDimensions());
    }

    void Panel::setFillColour(Colour fillColour) {
        panel_.setFillColor(Utility::convertTo3rdPartyColour(fillColour));
        emit("fillColourChanged", fillColour);
    }

    void Panel::setOutlineColour(Colour outlineColour) {
        panel_.setOutlineColor(Utility::convertTo3rdPartyColour(outlineColour));
        emit("outlineColourChanged", outlineColour);
    }

    void Panel::setOutlineThickness(float outlineThickness) {
        panel_.setOutlineThickness(outlineThickness);
        emit("outlineThicknessChanged", outlineThickness);
    }

    Position Panel::getPosition() const {
        return {panel_.getPosition().x, panel_.getPosition().y};
    }

    Dimensions Panel::getDimensions() const {
        return {panel_.getGlobalBounds().width,
                panel_.getGlobalBounds().height};
    }

    float Panel::getOutlineThickness() const {
        return panel_.getOutlineThickness();
    }

    unsigned int Panel::getNumberOfElements() const {
        return uiElements_.size();
    }

    bool Panel::add(const std::string &name, std::unique_ptr<UIElement> uiElement) {
        assert(uiElement && "GUI elements added to panel cannot be null");
        if (findUIElement(name) == uiElements_.end()) {
            uiElements_.push_back(std::pair(name, std::move(uiElement)));
            emit("newElementAdded", std::prev(uiElements_.end()));
            return true;
        }
        return false;
    }

    bool Panel::removeElement(const std::string &name) {
        if (auto found = findUIElement(name); found != uiElements_.end()) {
            auto elementName = found->first;
            uiElements_.erase(found);
            emit("elementRemoved", elementName);
        }
    }

    void Panel::hide() {
        if (!isHidden_) {
            isHidden_ = true;
            std::for_each(uiElements_.begin(), uiElements_.end(), [](auto &uiElem) {
                uiElem.second->hide();
            });
            emit("hidden");
        }
    }

    void Panel::show() {
        if (isHidden_) {
            isHidden_ = false;
            std::for_each(uiElements_.begin(), uiElements_.end(), [](auto &uiElem) {
                uiElem.second->show();
            });
            emit("shown");
        }
    }

    const std::unique_ptr<UIElement>& Panel::getElement(const std::string &name) {
        if (auto found = findUIElement(name); found != uiElements_.end())
            return found->second;
        return null_Ptr;
    }

    void Panel::draw(Window &renderTarget) {
        if (!isHidden_) {
            renderTarget.draw(panel_);
            std::for_each(uiElements_.begin(), uiElements_.end(), [&](auto &uiElem) {
                renderTarget.draw(*(uiElem.second));
            });
        }
    }

    void Panel::handleEvent(sf::Event event) {
        std::for_each(uiElements_.begin(), uiElements_.end(), [=](auto& uiElement) {
            uiElement.second->handleEvent(event);
        });
    }

    void Panel::forEach(Callback<UIElement &> callback) {
        std::for_each(uiElements_.begin(), uiElements_.end(), [&callback](auto& uiElement) {
            callback(*uiElement.second);
        });
    }

    Panel::UIElementContainer::iterator Panel::findUIElement(const std::string &uiElemAlias) {
        return std::find_if(uiElements_.begin(), uiElements_.end(),
            [this, &uiElemAlias](const auto& uiElement){
                return uiElement.first == uiElemAlias;
            }
        );
    }

    Panel::ConstIterator Panel::cBegin() const {
        return uiElements_.cbegin();
    }

    Panel::ConstIterator Panel::cEnd() const {
        return uiElements_.cend();
    }

    bool Panel::isHidden() const {
        return isHidden_;
    }
}