#include "IME/graphics/ui/widgets/BitmapButton.h"
#include "IME/utility/Helpers.h"
#include <TGUI/GuiBase.hpp>
#include "IME/core/managers/ResourceManager.h"
#include <cassert>

namespace IME::Graphics::UI {
    BitmapButton::BitmapButton() : BitmapButton("") 
    {}

    BitmapButton::BitmapButton(const std::string &buttonText)
        : button_{tgui::BitmapButton::create(buttonText)},
          renderer_{std::make_shared<ButtonRenderer>()}
    {
        renderer_->setInternalPtr(button_->getRenderer());
    }

    void BitmapButton::setRenderer(std::shared_ptr<ButtonRenderer> renderer) {
        assert(renderer && "A nullptr cannot be set as a renderer");
        renderer_ = renderer;
        button_->setRenderer(renderer->getInternalPtr()->getData());
    }

    std::shared_ptr<ButtonRenderer> BitmapButton::getRenderer() {
        return renderer_;
    }
    
    void BitmapButton::setImage(const std::string &filename) {
        button_->setImage(IME::ResourceManager::getInstance()->getTexture(filename));
    }

    void BitmapButton::setImageScaling(float relativeHeight) {
        button_->setImageScaling(relativeHeight);
    }

    float BitmapButton::getImageScaling() const {
        return button_->getImageScaling();
    }

    void BitmapButton::setPosition(float x, float y) {
        button_->setPosition({x, y});
    }

    void BitmapButton::setRotation(float angle) {
        button_->setRotation(angle);
    }

    void BitmapButton::setScale(float factorX, float factorY) {
        button_->setScale({factorX, factorY});
    }

    void BitmapButton::setOrigin(float x, float y) {
        button_->setOrigin({x, y});
    }

    Position BitmapButton::getPosition() const {
        return {button_->getPosition().x, button_->getPosition().y};
    }

    Position BitmapButton::getOrigin() const {
        return {button_->getOrigin().x, button_->getOrigin().y};
    }

    float BitmapButton::getRotation() const {
        return button_->getRotation();
    }

    void BitmapButton::move(float xOffset, float yOffset) {
        button_->setPosition(getPosition().x + xOffset,
                             getPosition().y + yOffset);
    }

    void BitmapButton::rotate(float offset) {
        button_->setRotation(button_->getRotation() + offset);
    }

    void BitmapButton::scale(float factorX, float factorY) {
        button_->setScale({button_->getScale().x + factorX,
                           button_->getScale().y + factorY});
    }

    void BitmapButton::hide() {
        button_->hideWithEffect(tgui::ShowAnimationType::Fade,
                                fadeAnimDuration_);
    }

    void BitmapButton::show() {
        button_->showWithEffect(tgui::ShowAnimationType::Fade,
                                fadeAnimDuration_);
    }

    bool BitmapButton::isHidden() const {
        return !button_->isVisible();
    }

    void BitmapButton::setEnabled(bool isEnable) {
        button_->setEnabled(isEnable);
    }

    bool BitmapButton::isEnabled() const {
        return button_->isEnabled();
    }

    void BitmapButton::toggleEnabled() {
        setEnabled(!isEnabled());
    }

    bool BitmapButton::isMouseOverElement() const {
        //@todo
        return false;
    }

    void BitmapButton::setPosition(Position position) {
        setPosition(position.x, position.y);
    }

    void BitmapButton::setTextSize(unsigned int charSize) {
        button_->setTextSize(charSize);
    }

    void BitmapButton::setText(const std::string &content) {
        button_->setText(content);
    }

    void BitmapButton::setSize(float width, float height) {
        button_->setSize({width, height});
    }

    Dimensions BitmapButton::getSize() const {
        return {button_->getSize().x, button_->getSize().y};
    }

    std::string BitmapButton::getText() const {
        return button_->getText().toAnsiString();
    }

    unsigned int BitmapButton::getTextSize() const {
        return button_->getTextSize();
    }

    std::string BitmapButton::getType() const {
        return "BitmapButton";
    }

    void BitmapButton::toggleVisibility() {
        button_->setVisible(!button_->isVisible());
    }

    bool BitmapButton::contains(float x, float y) const {
        return button_->isMouseOnWidget({x, y});
    }

    void BitmapButton::setFocused(bool isFocused) {
        button_->setFocused(isFocused);
    }

    bool BitmapButton::isFocused() const {
        return button_->isFocused();
    }

    std::shared_ptr<tgui::Widget> BitmapButton::getInternalPtr() {
        return button_;
    }

    Dimensions BitmapButton::getAbsoluteSize() {
        return {button_->getFullSize().x, button_->getFullSize().y};
    }
}
