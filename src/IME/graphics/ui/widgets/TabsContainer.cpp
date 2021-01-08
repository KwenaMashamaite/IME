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

#include "IME/graphics/ui/widgets/TabsContainer.h"
#include <cassert>

//How long the tabs container take before its completely hidden or shown
const int fadeAnimDuration_ = 100;

namespace IME::UI {
    TabsContainer::TabsContainer(float width, float height) :
        tabContainer_{tgui::TabContainer::create({width, height})},
        renderer_{std::make_shared<TabsRenderer>()}
    {
        renderer_->setInternalPtr(tabContainer_->getTabsRenderer());
        initEvents();
    }

    TabsContainer::sharedPtr TabsContainer::create(float width, float height) {
        return std::make_shared<TabsContainer>(width, height);
    }

    void TabsContainer::setRenderer(std::shared_ptr<TabsRenderer> renderer) {
        assert(renderer && "A nullptr cannot be set as a renderer");
        renderer_ = renderer;
        tabContainer_->setRenderer(renderer->getInternalPtr()->getData());
    }

    std::shared_ptr<TabsRenderer> TabsContainer::getRenderer() {
        return renderer_;
    }

    void TabsContainer::setTabsHeight(float height) {
        tabContainer_->setTabsHeight(height);
    }

    void TabsContainer::addPanel(std::shared_ptr<Panel> panel,
        const std::string &text, bool select)
    {
        assert(panel && "A nullptr cannot be added as a panel");
        panels_.insert({tabContainer_->getPanelCount() + 1, panel});
        tabContainer_->addPanel(
            std::dynamic_pointer_cast<tgui::Panel>(panel->getInternalPtr()), text, select);
    }

    bool TabsContainer::insertPanel(std::shared_ptr<Panel> panel,
        const std::string &text, std::size_t index, bool select)
    {
        //@TODO Open up space for the new widget because in our container because
        // If the index is not at end, then a widget already exists with
        // the given index and an our unordered_map will deny the insertion
        // event though insertion in the third party container succeeds
        if (tabContainer_->insertPanel(std::dynamic_pointer_cast<tgui::Panel>(
            panel->getInternalPtr()), text, index, select)) 
        {
            if (panels_.insert({getIndex(panel), panel}).second)
                return true;
            else {
                removePanel(panel);
                return false;
            }
        }
        return false;
    }

    void TabsContainer::removePanel(std::shared_ptr<Panel> panel) {
        auto panelCount = tabContainer_->getPanelCount();
        auto panelIndex = getIndex(panel);
        tabContainer_->removePanel(
            std::dynamic_pointer_cast<tgui::Panel>(panel->getInternalPtr()));
        if (tabContainer_->getPanelCount() == panelCount - 1)
            panels_.erase(panelIndex);
    }

    void TabsContainer::select(std::size_t index) {
        tabContainer_->select(index);
    }

    std::size_t TabsContainer::getPanelCount() const {
        return tabContainer_->getPanelCount();
    }

    int TabsContainer::getIndex(std::shared_ptr<Panel> panel) {
        return tabContainer_->getIndex(
            std::dynamic_pointer_cast<tgui::Panel>(panel->getInternalPtr()));
    }

    std::shared_ptr<Panel> TabsContainer::getSelected() {
        if (tabContainer_->getSelected())
            return panels_[tabContainer_->getSelectedIndex()];
        return nullptr;
    }

    int TabsContainer::getSelectedIndex() const {
        return tabContainer_->getSelectedIndex();
    }

    std::shared_ptr<Panel> TabsContainer::getPanel(int index) {
        if (panels_.find(index) != panels_.end())
            return panels_[index];
        return nullptr;
    }

    std::string TabsContainer::getTabText(std::size_t index) const {
        return tabContainer_->getTabText(index).toAnsiString();
    }

    bool TabsContainer::changeTabText(std::size_t index, const tgui::String &text) {
        return tabContainer_->changeTabText(index, text);
    }

    void TabsContainer::setText(const std::string &) {

    }

    std::string TabsContainer::getText() const {
        return "";
    }

    void TabsContainer::setTextSize(unsigned int charSize) {
        tabContainer_->setTextSize(charSize);
    }

    unsigned int TabsContainer::getTextSize() const {
        return tabContainer_->getTextSize();
    }

    void TabsContainer::setSize(float width, float height) {
        tabContainer_->setSize({width, height});
    }

    Vector2f TabsContainer::getSize() const {
        return {tabContainer_->getSize().x, tabContainer_->getSize().y};
    }

    Vector2f TabsContainer::getAbsoluteSize() {
        return {tabContainer_->getFullSize().x, tabContainer_->getFullSize().y};
    }

    std::string TabsContainer::getType() const {
        return "Tab";
    }

    void TabsContainer::show() {
        tabContainer_->showWithEffect(tgui::ShowAnimationType::Fade,
            fadeAnimDuration_);
    }

    void TabsContainer::hide() {
        tabContainer_->hideWithEffect(tgui::ShowAnimationType::Fade,
            fadeAnimDuration_);
    }

    bool TabsContainer::isHidden() const {
        return !tabContainer_->isVisible();
    }

    void TabsContainer::toggleVisibility() {
        tabContainer_->setVisible(!tabContainer_->isVisible());
    }

    bool TabsContainer::contains(float x, float y) const {
        return tabContainer_->isMouseOnWidget({x, y});
    }

    void TabsContainer::setPosition(float x, float y) {
        tabContainer_->setPosition({x, y});
    }

    void TabsContainer::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    Vector2f TabsContainer::getPosition() const {
        return {tabContainer_->getPosition().x, tabContainer_->getPosition().y};
    }

    void TabsContainer::setRotation(float angle) {
        tabContainer_->setRotation(angle);
    }

    void TabsContainer::rotate(float angle) {
        tabContainer_->setRotation(tabContainer_->getRotation() + angle);
    }

    float TabsContainer::getRotation() const {
        return tabContainer_->getRotation();
    }

    void TabsContainer::setScale(float factorX, float factorY) {
        tabContainer_->setScale({factorX, factorY});
    }

    void TabsContainer::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void TabsContainer::scale(float factorX, float factorY) {
        tabContainer_->setScale({tabContainer_->getScale().x + factorX,
            tabContainer_->getScale().y + factorY});
    }

    void TabsContainer::scale(Vector2f offset) {
        scale(offset.x, offset.y);
    }

    Vector2f TabsContainer::getScale() const {
        return {tabContainer_->getScale().x, tabContainer_->getScale().y};
    }

    void TabsContainer::setOrigin(float x, float y) {
        tabContainer_->setOrigin({x, y});
    }

    void TabsContainer::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    Vector2f TabsContainer::getOrigin() const {
        return {tabContainer_->getOrigin().x, tabContainer_->getOrigin().y};
    }

    void TabsContainer::move(float offsetX, float offsetY) {
        tabContainer_->setPosition(getPosition().x + offsetX, getPosition().y + offsetY);
    }

    void TabsContainer::move(Vector2f offset) {
        move(offset.x, offset.y);
    }

    std::shared_ptr<tgui::Widget> TabsContainer::getInternalPtr() {
        return tabContainer_;
    }

    void TabsContainer::initEvents() {
        tabContainer_->onMouseEnter([this]{emit("mouseEnter");});
        tabContainer_->onMouseLeave([this]{emit("mouseLeave");});
        tabContainer_->onFocus([this]{emit("focus");});
        tabContainer_->onUnfocus([this]{emit("unfocus");});
        tabContainer_->onAnimationFinish([this]{emit("animationFinish");});
        tabContainer_->onSizeChange([this](tgui::Vector2f newSize) {
            emit("sizeChange", newSize.x, newSize.y);
        });

        tabContainer_->onPositionChange([this](tgui::Vector2f newPos) {
            emit("positionChange", newPos.x, newPos.y);
        });

        tabContainer_->onSelectionChanged([this](int index){
            emit("selectionChange", index);
        });
    }
}

