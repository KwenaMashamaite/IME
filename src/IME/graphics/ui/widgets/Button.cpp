#include "IME/graphics/ui/widgets/Button.h"
#include "IME/utility/Helpers.h"
#include <TGUI/GuiBase.hpp>
#include "IME/core/managers/ResourceManager.h"
#include <cassert>

namespace IME::Graphics::UI {
    Button::Button() : Button("") {}

    Button::Button(const std::string &buttonText)
        : button_{tgui::Button::create(buttonText)},
          renderer_{std::make_shared<ButtonRenderer>()}
    {
        renderer_->setInternalPtr(button_->getRenderer());
    }

    void Button::setRenderer(std::shared_ptr<ButtonRenderer> renderer) {
        assert(renderer && "A nullptr cannot be set as a renderer");
        renderer_ = renderer;
        button_->setRenderer(renderer->getInternalPtr()->getData());
    }

    std::shared_ptr<ButtonRenderer> Button::getRenderer() {
        return renderer_;
    }

    void Button::setPosition(float x, float y) {
        button_->setPosition({x, y});
    }

    void Button::setRotation(float angle) {
        button_->setRotation(angle);
    }

    void Button::setScale(float factorX, float factorY) {
        button_->setScale({factorX, factorY});
    }

    void Button::setOrigin(float x, float y) {
        button_->setOrigin({x, y});
    }

    Position Button::getPosition() const {
        return {button_->getPosition().x, button_->getPosition().y};
    }

    Position Button::getOrigin() const {
        return {button_->getOrigin().x, button_->getOrigin().y};
    }

    float Button::getRotation() const {
        return button_->getRotation();
    }

    void Button::move(float xOffset, float yOffset) {
        button_->setPosition(getPosition().x + xOffset,
                             getPosition().y + yOffset);
    }

    void Button::rotate(float offset) {
        button_->setRotation(button_->getRotation() + offset);
    }

    void Button::scale(float factorX, float factorY) {
        button_->setScale({button_->getScale().x + factorX,
            button_->getScale().y + factorY});
    }

    void Button::hide() {
        button_->hideWithEffect(tgui::ShowAnimationType::Fade,
            fadeAnimDuration_);
    }

    void Button::show() {
        button_->showWithEffect(tgui::ShowAnimationType::Fade,
            fadeAnimDuration_);
    }

    bool Button::isHidden() const {
        return !button_->isVisible();
    }

    void Button::setEnabled(bool isEnable) {
        button_->setEnabled(isEnable);
    }

    bool Button::isEnabled() const {
        return button_->isEnabled();
    }

    void Button::toggleEnabled() {
        setEnabled(!isEnabled());
    }

    bool Button::isMouseOverElement() const {
        //@todo
        return false;
    }

    void Button::setPosition(Position position) {
        setPosition(position.x, position.y);
    }

    void Button::setTextSize(unsigned int charSize) {
        button_->setTextSize(charSize);
    }

    void Button::setText(const std::string &content) {
        button_->setText(content);
    }

    void Button::setSize(float width, float height) {
        button_->setSize({width, height});
    }

    Dimensions Button::getSize() const {
        return {button_->getSize().x, button_->getSize().y};
    }

    std::string Button::getText() const {
        return button_->getText().toAnsiString();
    }

    Dimensions Button::getAbsoluteSize() {
        return {button_->getFullSize().x, button_->getFullSize().y};
    }

    unsigned int Button::getTextSize() const {
        return button_->getTextSize();
    }

    std::string Button::getType() const {
        return "Button";
    }

    void Button::toggleVisibility() {
        button_->setVisible(!button_->isVisible());
    }

    bool Button::contains(float x, float y) const {
        return button_->isMouseOnWidget({x, y});
    }

    void Button::setFocused(bool isFocused) {
        button_->setFocused(isFocused);
    }

    bool Button::isFocused() const {
        return button_->isFocused();
    }

    std::shared_ptr<tgui::Widget> Button::getInternalPtr() {
        return button_;
    }
}
