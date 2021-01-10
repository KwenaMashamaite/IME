////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include "IME/ui/widgets/Label.h"
#include "IME/core/managers/ResourceManager.h"
#include "IME/utility/Helpers.h"
#include <TGUI/GuiBase.hpp>
#include <cassert>

//How long the label takes before its completely hidden or shown
const int fadeAnimDuration_ = 100;

namespace ime::ui {
    Label::Label(const std::string &text) :
        label_{tgui::Label::create(text)},
        renderer_{std::make_shared<LabelRenderer>()}
    {
        renderer_->setInternalPtr(label_->getRenderer());
    }

    Label::sharedPtr Label::create(const std::string &text) {
        return std::make_shared<Label>(text);
    }

    std::shared_ptr<LabelRenderer> Label::getRenderer() {
        return renderer_;
    }

    void Label::setRenderer(std::shared_ptr<LabelRenderer> renderer) {
        assert(renderer && "A nullptr cannot be set as a renderer");
        renderer_ = renderer;
        label_->setRenderer(renderer->getInternalPtr()->getData());
    }

    void Label::setHorizontalAlignment(HorizontalAlignment alignment) {
        label_->setHorizontalAlignment(static_cast<tgui::Label::HorizontalAlignment>(alignment));
    }

    Label::HorizontalAlignment Label::getHorizontalAlignment() const {
        return static_cast<HorizontalAlignment>(label_->getHorizontalAlignment());
    }

    void Label::setVerticalAlignment(VerticalAlignment alignment) {
        label_->setVerticalAlignment(static_cast<tgui::Label::VerticalAlignment>(alignment));
    }

    Label::VerticalAlignment Label::getVerticalAlignment() const {
        return static_cast<VerticalAlignment>(label_->getVerticalAlignment());
    }

    void Label::setAutoSize(bool autoSize) {
        label_->setAutoSize(autoSize);
    }

    bool Label::getAutoSize() const {
        return label_->getAutoSize();
    }

    void Label::setMaximumTextWidth(float maximumWidth) {
        label_->setMaximumTextWidth(maximumWidth);
    }

    float Label::getMaximumTextWidth() const {
        return label_->getMaximumTextWidth();
    }

    std::string Label::getType() const {
        return "Label";
    }

    void Label::setPosition(float x, float y) {
        label_->setPosition({x, y});
    }

    void Label::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    void Label::setPosition(const std::string &x, const std::string &y) {
        label_->setPosition({x.c_str(), y.c_str()});
    }

    void Label::setRotation(float angle) {
        label_->setRotation(angle);
    }

    void Label::setScale(float factorX, float factorY) {
        label_->setScale({factorX, factorY});
    }

    void Label::setOrigin(float x, float y) {
        label_->setOrigin({x, y});
    }

    Vector2f Label::getPosition() const {
        return {label_->getPosition().x, label_->getPosition().y};
    }

    Vector2f Label::getOrigin() const {
        return {label_->getOrigin().x, label_->getOrigin().y};
    }

    float Label::getRotation() const {
        return label_->getRotation();
    }

    void Label::move(float xOffset, float yOffset) {
        label_->setPosition(getPosition().x + xOffset,
            getPosition().y + yOffset);
    }

    void Label::rotate(float offset) {
        label_->setRotation(label_->getRotation() + offset);
    }

    void Label::scale(float factorX, float factorY) {
        label_->setScale({label_->getScale().x + factorX,
            label_->getScale().y + factorY});
    }

    void Label::hide() {
        label_->hideWithEffect(tgui::ShowAnimationType::Fade,
            fadeAnimDuration_);
    }

    void Label::show() {
        label_->showWithEffect(tgui::ShowAnimationType::Fade,
            fadeAnimDuration_);
    }

    bool Label::isHidden() const {
        return !label_->isVisible();
    }

    void Label::setTextSize(unsigned int charSize) {
        label_->setTextSize(charSize);
    }

    void Label::setText(const std::string &content) {
        label_->setText(content);
    }

    void Label::setSize(float width, float height) {
        label_->setSize({width, height});
    }

    void Label::setSize(const std::string &width, const std::string &height) {
        label_->setSize({width.c_str(), height.c_str()});
    }

    Vector2f Label::getSize() const {
        return {label_->getSize().x, label_->getSize().y};
    }

    Vector2f Label::getAbsoluteSize() {
        return {label_->getFullSize().x, label_->getFullSize().y};;
    }

    void Label::setWidth(float width) {
        label_->setWidth(width);
    }

    void Label::setWidth(const std::string &width) {
        label_->setWidth(width.c_str());
    }

    void Label::setHeight(float height) {
        label_->setHeight(height);
    }

    void Label::setHeight(const std::string &height) {
        label_->setHeight(height.c_str());
    }

    std::string Label::getText() const {
        return label_->getText().toAnsiString();
    }

    unsigned int Label::getTextSize() const {
        return label_->getTextSize();
    }

    void Label::toggleVisibility() {
        label_->setVisible(!label_->isVisible());
    }

    bool Label::contains(float x, float y) const {
        return label_->isMouseOnWidget({x, y});;
    }

    void Label::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void Label::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    void Label::move(Vector2f offset) {
        move(offset.x, offset.y);
    }

    void Label::scale(Vector2f offset) {
        scale(offset.x, offset.y);
    }

    std::shared_ptr<tgui::Widget> Label::getInternalPtr() {
        return label_;
    }

    Vector2f Label::getScale() const {
        return {label_->getScale().x, label_->getScale().y};
    }
}