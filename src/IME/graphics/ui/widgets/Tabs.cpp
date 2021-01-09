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

#include "IME/graphics/ui/widgets/Tabs.h"
#include <cassert>

//How long the tabs take before its completely hidden or shown
const int fadeAnimDuration_ = 100;

namespace ime::ui {
    Tabs::Tabs() :
        tabs_{tgui::Tabs::create()},
        renderer_{std::make_shared<TabsRenderer>()}
    {
        renderer_->setInternalPtr(tabs_->getRenderer());
        initEvents();
    }

    Tabs::sharedPtr Tabs::create() {
        return std::make_shared<Tabs>();
    }

    void Tabs::setRenderer(std::shared_ptr<TabsRenderer> renderer) {
        assert(renderer && "A nullptr cannot be set as a renderer");
        renderer_ = renderer;
        tabs_->setRenderer(renderer->getInternalPtr()->getData());
    }

    std::shared_ptr<TabsRenderer> Tabs::getRenderer() {
        return renderer_;
    }

    void Tabs::setAutoSize(bool autoSize) {
        tabs_->setAutoSize(autoSize);
    }

    bool Tabs::getAutoSize() const {
        return tabs_->getAutoSize();
    }

    std::size_t Tabs::add(const std::string &text, bool select) {
        return tabs_->add(text, select);
    }

    void Tabs::insert(std::size_t index, const std::string &text, bool select) {
        tabs_->insert(index, text, select);
    }

    std::string Tabs::getText(std::size_t index) const {
        return tabs_->getText(index).toAnsiString();
    }

    bool Tabs::changeText(std::size_t index, const std::string &text) {
        return tabs_->changeText(index, text);
    }

    bool Tabs::select(const std::string &text) {
        return tabs_->select(text);
    }

    bool Tabs::select(std::size_t index) {
        return tabs_->select(index);
    }

    void Tabs::deselect() {
        tabs_->deselect();
    }

    bool Tabs::remove(const std::string &text) {
        return tabs_->remove(text);
    }

    bool Tabs::remove(std::size_t index) {
        return tabs_->remove(index);
    }

    void Tabs::removeAll() {
        tabs_->removeAll();
    }

    std::string Tabs::getSelected() const {
        return tabs_->getSelected().toAnsiString();
    }

    int Tabs::getSelectedIndex() const {
        return tabs_->getSelectedIndex();
    }

    void Tabs::setTabVisible(std::size_t index, bool visible) {
        tabs_->setTabVisible(index, visible);
    }

    bool Tabs::isTabVisible(std::size_t index) const {
        return tabs_->getTabVisible(index);
    }

    void Tabs::setTabEnabled(std::size_t index, bool enabled) {
        tabs_->setTabEnabled(index, enabled);
    }

    bool Tabs::isTabEnabled(std::size_t index) const {
        return tabs_->getTabEnabled(index);
    }

    void Tabs::setTabHeight(float height) {
        tabs_->setTabHeight(height);
    }

    void Tabs::setMaximumTabWidth(float maximumWidth) {
        tabs_->setMaximumTabWidth(maximumWidth);
    }

    float Tabs::getMaximumTabWidth() const {
        return tabs_->getMaximumTabWidth();
    }

    void Tabs::setMinimumTabWidth(float minimumWidth) {
        tabs_->setMinimumTabWidth(minimumWidth);
    }

    float Tabs::getMinimumTabWidth() const {
        return tabs_->getMinimumTabWidth();
    }

    std::size_t Tabs::getTabsCount() const {
        return tabs_->getTabsCount();
    }

    void Tabs::setTextSize(unsigned int charSize) {
        tabs_->setTextSize(charSize);
    }

    unsigned int Tabs::getTextSize() const {
        return tabs_->getTextSize();
    }

    void Tabs::setSize(float width, float height) {
        tabs_->setSize({width, height});
    }

    void Tabs::setSize(const std::string &width, const std::string &height) {
        tabs_->setSize({width.c_str(), height.c_str()});
    }

    Vector2f Tabs::getSize() const {
        return {tabs_->getSize().x, tabs_->getSize().y};
    }

    Vector2f Tabs::getAbsoluteSize() {
        return {tabs_->getFullSize().x, tabs_->getFullSize().y};
    }

    void Tabs::setWidth(float width) {
        tabs_->setWidth(width);
    }

    void Tabs::setWidth(const std::string &width) {
        tabs_->setWidth(width.c_str());
    }

    void Tabs::setHeight(float height) {
        tabs_->setHeight(height);
    }

    void Tabs::setHeight(const std::string &height) {
        tabs_->setHeight(height.c_str());
    }

    std::string Tabs::getType() const {
        return "Tab";
    }

    void Tabs::show() {
        tabs_->showWithEffect(tgui::ShowAnimationType::Fade,
            fadeAnimDuration_);
    }

    void Tabs::hide() {
        tabs_->hideWithEffect(tgui::ShowAnimationType::Fade,
            fadeAnimDuration_);
    }

    bool Tabs::isHidden() const {
        return !tabs_->isVisible();
    }

    void Tabs::toggleVisibility() {
        tabs_->setVisible(!tabs_->isVisible());
    }

    bool Tabs::contains(float x, float y) const {
        return tabs_->isMouseOnWidget({x, y});
    }

    void Tabs::setPosition(float x, float y) {
        tabs_->setPosition({x, y});
    }

    void Tabs::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    void Tabs::setPosition(const std::string &x, const std::string &y) {
        tabs_->setPosition({x.c_str(), y.c_str()});
    }

    Vector2f Tabs::getPosition() const {
        return {tabs_->getPosition().x, tabs_->getPosition().y};
    }

    void Tabs::setRotation(float angle) {
        tabs_->setRotation(angle);
    }

    void Tabs::rotate(float angle) {
        tabs_->setRotation(tabs_->getRotation() + angle);
    }

    float Tabs::getRotation() const {
        return tabs_->getRotation();
    }

    void Tabs::setScale(float factorX, float factorY) {
        tabs_->setScale({factorX, factorY});
    }

    void Tabs::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void Tabs::scale(float factorX, float factorY) {
        tabs_->setScale({tabs_->getScale().x + factorX,
                         tabs_->getScale().y + factorY});
    }

    void Tabs::scale(Vector2f offset) {
        scale(offset.x, offset.y);
    }

    Vector2f Tabs::getScale() const {
        return {tabs_->getScale().x, tabs_->getScale().y};
    }

    void Tabs::setOrigin(float x, float y) {
        tabs_->setOrigin({x, y});
    }

    void Tabs::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    Vector2f Tabs::getOrigin() const {
        return {tabs_->getOrigin().x, tabs_->getOrigin().y};
    }

    void Tabs::move(float offsetX, float offsetY) {
        tabs_->setPosition(getPosition().x + offsetX, getPosition().y + offsetY);
    }

    void Tabs::move(Vector2f offset) {
        move(offset.x, offset.y);
    }

    std::shared_ptr<tgui::Widget> Tabs::getInternalPtr() {
        return tabs_;
    }

    void Tabs::initEvents() {
        tabs_->onMouseEnter([this]{emit("mouseEnter");});
        tabs_->onMouseLeave([this]{emit("mouseLeave");});
        tabs_->onFocus([this]{emit("focus");});
        tabs_->onUnfocus([this]{emit("unfocus");});
        tabs_->onAnimationFinish([this]{emit("animationFinish");});
        tabs_->onSizeChange([this](tgui::Vector2f newSize) {
            emit("sizeChange", newSize.x, newSize.y);
        });

        tabs_->onPositionChange([this](tgui::Vector2f newPos) {
            emit("positionChange", newPos.x, newPos.y);
        });

        tabs_->onTabSelect([this](const tgui::String& item){
            emit("select", item.toAnsiString());
        });
    }
}