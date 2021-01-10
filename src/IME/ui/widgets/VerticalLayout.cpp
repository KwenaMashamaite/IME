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

#include "IME/ui/widgets/VerticalLayout.h"
#include "IME/utility/Helpers.h"
#include <cassert>

namespace ime::ui {
    VerticalLayout::VerticalLayout(const std::string& width, const std::string& height) :
        layout_{tgui::VerticalLayout::create({width.c_str(), height.c_str()})},
        renderer_{std::make_shared<BoxLayoutRenderer>()}
    {
        renderer_->setInternalPtr(layout_->getRenderer());
        initEvents();
    }

    VerticalLayout::sharedPtr VerticalLayout::create(const std::string& width,
        const std::string& height)
    {
        return std::make_shared<VerticalLayout>(width, height);
    }

    void VerticalLayout::setRenderer(std::shared_ptr<BoxLayoutRenderer> renderer) {
        assert(renderer && "A nullptr cannot be set as a renderer");
        renderer_ = renderer;
        layout_->setRenderer(renderer->getInternalPtr()->getData());
    }

    std::shared_ptr<BoxLayoutRenderer> VerticalLayout::getRenderer() {
        return renderer_;
    }

    void VerticalLayout::setTextSize(unsigned int charSize) {
        layout_->setTextSize(charSize);
    }

    void VerticalLayout::setSize(float width, float height) {
        layout_->setSize({width, height});
    }

    void VerticalLayout::setSize(const std::string &width, const std::string &height) {
        layout_->setSize({width.c_str(), height.c_str()});
    }

    Vector2f VerticalLayout::getSize() const {
        return {layout_->getSize().x, layout_->getSize().y};
    }

    Vector2f VerticalLayout::getAbsoluteSize() {
        return {layout_->getFullSize().x, layout_->getFullSize().y};
    }

    void VerticalLayout::setWidth(float width) {
        layout_->setWidth(width);
    }

    void VerticalLayout::setWidth(const std::string &width) {
        layout_->setWidth(width.c_str());
    }

    void VerticalLayout::setHeight(float height) {
        layout_->setHeight(height);
    }

    void VerticalLayout::setHeight(const std::string &height) {
        layout_->setHeight(height.c_str());
    }

    unsigned int VerticalLayout::getTextSize() const {
        return layout_->getTextSize();
    }

    std::string VerticalLayout::getWidgetType() const {
        return "VerticalLayout";
    }

    void VerticalLayout::showWithEffect(ShowAnimationType type, int duration) {
        layout_->showWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    void VerticalLayout::hideWithEffect(ShowAnimationType type, int duration) {
        layout_->hideWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    bool VerticalLayout::isAnimationPlaying() const {
        return layout_->isAnimationPlaying();
    }

    void VerticalLayout::setVisible(bool visible) {
        layout_->setVisible(visible);
    }

    bool VerticalLayout::isVisible() const {
        return layout_->isVisible();
    }

    void VerticalLayout::toggleVisibility() {
        layout_->setVisible(!layout_->isVisible());
    }

    bool VerticalLayout::contains(float x, float y) const {
        return layout_->isMouseOnWidget({x, y});
    }

    void VerticalLayout::setPosition(float x, float y) {
        layout_->setPosition({x, y});
    }

    void VerticalLayout::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    void VerticalLayout::setPosition(const std::string &x, const std::string &y) {
        layout_->setPosition({x.c_str(), y.c_str()});
    }

    void VerticalLayout::setRotation(float angle) {
        layout_->setRotation(angle);
    }

    void VerticalLayout::setScale(float factorX, float factorY) {
        layout_->setScale({factorX, factorY});
    }

    void VerticalLayout::setOrigin(float x, float y) {
        layout_->setOrigin({x, y});
    }

    Vector2f VerticalLayout::getPosition() const {
        return {layout_->getPosition().x, layout_->getPosition().y};
    }

    Vector2f VerticalLayout::getAbsolutePosition() const {
        return {layout_->getAbsolutePosition().x, layout_->getAbsolutePosition().y};
    }

    Vector2f VerticalLayout::getOrigin() const {
        return {layout_->getOrigin().x, layout_->getOrigin().y};
    }

    float VerticalLayout::getRotation() const {
        return layout_->getRotation();
    }

    void VerticalLayout::move(float offsetX, float offsetY) {
        layout_->setPosition(getPosition().x + offsetX,
            getPosition().y + offsetY);
    }

    void VerticalLayout::rotate(float angle) {
        setRotation(getRotation() + angle);
    }

    void VerticalLayout::scale(float factorX, float factorY) {
        setScale(layout_->getScale().x + factorX, layout_->getScale().y + factorY);
    }

    void VerticalLayout::insertWidget(std::size_t index,
        std::shared_ptr<IWidget> widget, const std::string &name)
    {
        layout_->insert(index, widget->getInternalPtr(), name);
    }

    bool VerticalLayout::removeWidgetAt(std::size_t index) {
        return layout_->remove(index);
    }

    std::shared_ptr<IWidget>
    VerticalLayout::getWidgetAt(std::size_t ) const {
        return std::shared_ptr<IWidget>{}; //@TODO implement
    }

    void VerticalLayout::addSpace(float ratio) {
        layout_->addSpace(ratio);
    }

    void VerticalLayout::insertSpace(std::size_t index, float ratio) {
        layout_->insertSpace(index, ratio);
    }

    bool VerticalLayout::setRatio(std::shared_ptr<IWidget> widget, float ratio) {
        return layout_->setRatio(widget->getInternalPtr(), ratio);
    }

    bool VerticalLayout::setRatio(std::size_t index, float ratio) {
        return layout_->setRatio(index, ratio);
    }

    float VerticalLayout::getRatio(std::shared_ptr<IWidget> widget) const {
        return layout_->getRatio(widget->getInternalPtr());
    }

    float VerticalLayout::getRatio(std::size_t index) const {
        return layout_->getRatio(index);
    }

    bool VerticalLayout::addWidget(std::shared_ptr<IWidget> widget,
        const std::string &name)
    {
        assert(widget && "Cannot add null widget to Vertical layout container");
        if (widgets_.insert({name, widget}).second) {
            layout_->add(widget->getInternalPtr(), name);
            return true;
        }
        return false;
    }

    std::shared_ptr<IWidget> VerticalLayout::getWidget(const std::string &name) const {
        if (utility::findIn(widgets_, name))
            return widgets_.at(name);
        return nullptr;
    }

    bool VerticalLayout::removeWidget(const std::string &widget) {
        if (utility::findIn(widgets_, widget)) {
            layout_->remove(widgets_[widget]->getInternalPtr());
            widgets_.erase(widget);
            return true;
        }
        return false;
    }

    void VerticalLayout::removeAllWidgets() {
        layout_->removeAllWidgets();
        widgets_.clear();
    }

    void VerticalLayout::moveWidgetToFront(std::shared_ptr<IWidget> widget) {
        layout_->moveWidgetToFront(widget->getInternalPtr());
    }

    void VerticalLayout::moveWidgetToBack(std::shared_ptr<IWidget> widget) {
        layout_->moveWidgetToBack(widget->getInternalPtr());
    }

    size_t VerticalLayout::moveWidgetForward(std::shared_ptr<IWidget> widget) {
        return layout_->moveWidgetForward(widget->getInternalPtr());
    }

    size_t VerticalLayout::moveWidgetBackward(std::shared_ptr<IWidget> widget) {
        return layout_->moveWidgetBackward(widget->getInternalPtr());
    }

    std::shared_ptr<IWidget> VerticalLayout::getFocusedWidget() const {
        auto widget = layout_->getFocusedChild();
        if (widget)
            return widgets_.at(widget->getWidgetName().toAnsiString());
        return nullptr;
    }

    std::shared_ptr<IWidget> VerticalLayout::getFocusedLeaf() const {
        auto widget = layout_->getFocusedLeaf();
        if (widget)
            return widgets_.at(widget->getWidgetName().toAnsiString());
        return nullptr;
    }

    std::shared_ptr<IWidget> VerticalLayout::getWidgetAtPosition(Vector2f pos) const {
        auto widget = layout_->getWidgetAtPosition({pos.x, pos.y});
        if (widget)
            return widgets_.at(widget->getWidgetName().toAnsiString());
        return nullptr;
    }

    bool VerticalLayout::focusNextWidget(bool recursive) {
        return layout_->focusNextWidget(recursive);
    }

    bool VerticalLayout::focusPreviousWidget(bool recursive) {
        return layout_->focusPreviousWidget(recursive);
    }

    std::shared_ptr<tgui::Widget> VerticalLayout::getInternalPtr() {
        return layout_;
    }

    void VerticalLayout::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void VerticalLayout::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    void VerticalLayout::move(Vector2f offset) {
        move(offset.x, offset.y);
    }

    void VerticalLayout::scale(Vector2f offset) {
        scale(offset.x, offset.y);
    }

    void VerticalLayout::initEvents() {
        layout_->onMouseEnter([this]{emit("mouseEnter");});
        layout_->onMouseLeave([this]{emit("mouseLeave");});
        layout_->onFocus([this]{emit("focus");});
        layout_->onUnfocus([this]{emit("unfocus");});
        layout_->onAnimationFinish([this]{emit("animationFinish");});
        layout_->onSizeChange([this](tgui::Vector2f newSize) {
            emit("sizeChange", newSize.x, newSize.y);
        });

        layout_->onPositionChange([this](tgui::Vector2f newPos) {
            emit("positionChange", newPos.x, newPos.y);
        });
    }

    Vector2f VerticalLayout::getScale() const {
        return {layout_->getScale().x, layout_->getScale().y};
    }
}