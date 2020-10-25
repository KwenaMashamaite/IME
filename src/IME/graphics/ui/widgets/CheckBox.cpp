#include "IME/graphics/ui/widgets/CheckBox.h"
#include "IME/core/managers/ResourceManager.h"
#include "IME/utility/Helpers.h"
#include <TGUI/GuiBase.hpp>
#include <cassert>

namespace IME::Graphics::UI {
    CheckBox::CheckBox(const std::string &text)
        : checkBox_{tgui::CheckBox::create(text)},
          renderer_{std::make_shared<CheckBoxRenderer>()}
    {
        renderer_->setInternalPtr(checkBox_->getRenderer());
    }

    void CheckBox::setRenderer(std::shared_ptr<CheckBoxRenderer> renderer) {
        assert(renderer && "A nullptr cannot be set as a renderer");
        renderer_ = renderer;
        checkBox_->setRenderer(renderer->getInternalPtr()->getData());
    }

    std::shared_ptr<CheckBoxRenderer> CheckBox::getRenderer() {
        return renderer_;
    }

    void CheckBox::setTextClickable(bool acceptTextClick) {
        checkBox_->setTextClickable(acceptTextClick);
    }

    bool CheckBox::isTextClickable() const {
        return checkBox_->isTextClickable();
    }

    void CheckBox::setChecked(bool isChecked) {
        checkBox_->setChecked(isChecked);
    }

    bool CheckBox::isChecked() const {
        return checkBox_->isChecked();
    }

    void CheckBox::setPosition(float x, float y) {
        checkBox_->setPosition({x, y});
    }

    void CheckBox::setRotation(float angle) {
        checkBox_->setRotation(angle);
    }

    void CheckBox::setScale(float factorX, float factorY) {
        checkBox_->setScale({factorX, factorY});
    }

    void CheckBox::setOrigin(float x, float y) {
        checkBox_->setOrigin({x, y});
    }

    Position CheckBox::getPosition() const {
        return {checkBox_->getPosition().x, checkBox_->getPosition().y};
    }

    Position CheckBox::getOrigin() const {
        return {checkBox_->getOrigin().x, checkBox_->getOrigin().y};
    }

    float CheckBox::getRotation() const {
        return checkBox_->getRotation();
    }

    void CheckBox::move(float xOffset, float yOffset) {
        checkBox_->setPosition(getPosition().x + xOffset,
                             getPosition().y + yOffset);
    }

    void CheckBox::rotate(float offset) {
        checkBox_->setRotation(checkBox_->getRotation() + offset);
    }

    void CheckBox::scale(float factorX, float factorY) {
        checkBox_->setScale({checkBox_->getScale().x + factorX,
                           checkBox_->getScale().y + factorY});
    }

    void CheckBox::hide() {
        checkBox_->hideWithEffect(tgui::ShowAnimationType::Fade,
            fadeAnimDuration_);
    }

    void CheckBox::show() {
        checkBox_->showWithEffect(tgui::ShowAnimationType::Fade,
            fadeAnimDuration_);
    }

    bool CheckBox::isHidden() const {
        return !checkBox_->isVisible();
    }

    void CheckBox::setEnabled(bool isEnable) {
        checkBox_->setEnabled(isEnable);
    }

    bool CheckBox::isEnabled() const {
        return checkBox_->isEnabled();
    }

    void CheckBox::toggleEnabled() {
        setEnabled(!isEnabled());
    }

    bool CheckBox::isMouseOverElement() const {
        //@todo
        return false;
    }

    void CheckBox::setPosition(Position position) {
        setPosition(position.x, position.y);
    }

    void CheckBox::setTextSize(unsigned int charSize) {
        checkBox_->setTextSize(charSize);
    }

    void CheckBox::setText(const std::string &content) {
        checkBox_->setText(content);
    }

    void CheckBox::setSize(float width, float height) {
        checkBox_->setSize({width, height});
    }

    Dimensions CheckBox::getSize() const {
        return {checkBox_->getSize().x, checkBox_->getSize().y};
    }

    std::string CheckBox::getText() const {
        return checkBox_->getText().toAnsiString();
    }

    unsigned int CheckBox::getTextSize() const {
        return checkBox_->getTextSize();
    }

    std::string CheckBox::getType() const {
        return "CheckBox";
    }

    void CheckBox::toggleVisibility() {
        checkBox_->setVisible(!checkBox_->isVisible());
    }

    bool CheckBox::contains(float x, float y) const {
        return checkBox_->isMouseOnWidget({x, y});
    }

    void CheckBox::setFocused(bool isFocused) {
        checkBox_->setFocused(isFocused);
    }

    bool CheckBox::isFocused() const {
        return checkBox_->isFocused();
    }

    std::shared_ptr<tgui::Widget> CheckBox::getInternalPtr() {
        return checkBox_;
    }

    Dimensions CheckBox::getAbsoluteSize() {
        return {checkBox_->getFullSize().x, checkBox_->getFullSize().y};
    }
}