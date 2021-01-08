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

#include "IME/graphics/ui/widgets/HorizontalLayout.h"
#include "IME/utility/Helpers.h"
#include <cassert>

//How long the edit box takes before its completely hidden or shown
const int fadeAnimDuration_ = 100;

namespace IME::UI {
    HorizontalLayout::HorizontalLayout(float width, float height)
        : layout_{tgui::HorizontalLayout::create({width, height})},
          renderer_{std::make_shared<BoxLayoutRenderer>()}
        {
            renderer_->setInternalPtr(layout_->getRenderer());
            initEvents();
        }

        void HorizontalLayout::setRenderer(std::shared_ptr<BoxLayoutRenderer> renderer) {
            assert(renderer && "A nullptr cannot be set as a renderer");
            renderer_ = renderer;
            layout_->setRenderer(renderer->getInternalPtr()->getData());
        }

        std::shared_ptr<BoxLayoutRenderer> HorizontalLayout::getRenderer() {
            return renderer_;
        }

    void HorizontalLayout::setTextSize(unsigned int charSize) {
        layout_->setTextSize(charSize);
    }

    void HorizontalLayout::setText(const std::string &) {

    }

    void HorizontalLayout::setSize(float width, float height) {
        layout_->setSize({width, height});
    }

    Vector2f HorizontalLayout::getSize() const {
        return {layout_->getSize().x, layout_->getSize().y};
    }

    Vector2f HorizontalLayout::getAbsoluteSize() {
        return {layout_->getFullSize().x, layout_->getFullSize().y};
    }

    std::string HorizontalLayout::getText() const {
        return "";
    }

    unsigned int HorizontalLayout::getTextSize() const {
        return layout_->getTextSize();
    }

    std::string HorizontalLayout::getType() const {
        return "HorizontalLayout";
    }

    void HorizontalLayout::toggleVisibility() {
        if (isHidden())
            show();
        else
            hide();
    }

    bool HorizontalLayout::contains(float x, float y) const {
        return layout_->isMouseOnWidget({x, y});
    }

    void HorizontalLayout::hide() {
        layout_->hideWithEffect(tgui::ShowAnimationType::Fade, fadeAnimDuration_);
    }

    void HorizontalLayout::show() {
        layout_->showWithEffect(tgui::ShowAnimationType::Fade, fadeAnimDuration_);
    }

    bool HorizontalLayout::isHidden() const {
        return !layout_->isVisible();
    }

    void HorizontalLayout::setPosition(float x, float y) {
        layout_->setPosition({x, y});
    }

    void HorizontalLayout::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    void HorizontalLayout::setRotation(float angle) {
        layout_->setRotation(angle);
    }

    void HorizontalLayout::setScale(float factorX, float factorY) {
        layout_->setScale({factorX, factorY});
    }

    void HorizontalLayout::setOrigin(float x, float y) {
        layout_->setOrigin({x, y});
    }

    Vector2f HorizontalLayout::getPosition() const {
        return {layout_->getPosition().x, layout_->getPosition().y};
    }

    Vector2f HorizontalLayout::getOrigin() const {
        return {layout_->getOrigin().x, layout_->getOrigin().y};
    }

    float HorizontalLayout::getRotation() const {
        return layout_->getRotation();
    }

    void HorizontalLayout::move(float offsetX, float offsetY) {
        layout_->setPosition(getPosition().x + offsetX,
             getPosition().y + offsetY);
    }

    void HorizontalLayout::rotate(float angle) {
        setRotation(getRotation() + angle);
    }

    void HorizontalLayout::scale(float factorX, float factorY) {
        setScale(layout_->getScale().x + factorX, layout_->getScale().y + factorY);
    }

    void HorizontalLayout::insertWidget(std::size_t index,
        std::shared_ptr<IWidget> widget, const std::string &name)
    {
        layout_->insert(index, widget->getInternalPtr(), name);
    }

    bool HorizontalLayout::removeWidgetAt(std::size_t index) {
        return layout_->remove(index);
    }

    std::shared_ptr<IWidget>
    HorizontalLayout::getWidgetAt(std::size_t) const {
        return std::shared_ptr<IWidget>(); //@TODO implement
    }

    void HorizontalLayout::addSpace(float ratio) {
       layout_->addSpace(ratio);
    }

    void HorizontalLayout::insertSpace(std::size_t index, float ratio) {
        layout_->insertSpace(index, ratio);
    }

    bool HorizontalLayout::setRatio(std::shared_ptr<IWidget> widget, float ratio) {
        return layout_->setRatio(widget->getInternalPtr(), ratio);
    }

    bool HorizontalLayout::setRatio(std::size_t index, float ratio) {
        return layout_->setRatio(index, ratio);
    }

    float HorizontalLayout::getRatio(std::shared_ptr<IWidget> widget) const {
        return layout_->getRatio(widget->getInternalPtr());
    }

    float HorizontalLayout::getRatio(std::size_t index) const {
        return layout_->getRatio(index);
    }

    bool HorizontalLayout::addWidget(std::shared_ptr<IWidget> widget,
        const std::string &name)
    {
        assert(widget && "Cannot add null widget to Horizontal layout container");
        if (widgets_.insert({name, widget}).second) {
            layout_->add(widget->getInternalPtr(), name);
            return true;
        }
        return false;
    }

    std::shared_ptr<IWidget> HorizontalLayout::getWidget(const std::string &name) const {
        if (Utility::findIn(widgets_, name))
            return widgets_.at(name);
        return nullptr;
    }

    bool HorizontalLayout::removeWidget(const std::string &widget) {
        if (Utility::findIn(widgets_, widget)) {
            layout_->remove(widgets_[widget]->getInternalPtr());
            widgets_.erase(widget);
            return true;
        }
        return false;
    }

    void HorizontalLayout::removeAllWidgets() {
        layout_->removeAllWidgets();
        widgets_.clear();
    }

    void HorizontalLayout::moveWidgetToFront(std::shared_ptr<IWidget> widget) {
        layout_->moveWidgetToFront(widget->getInternalPtr());
    }

    void HorizontalLayout::moveWidgetToBack(std::shared_ptr<IWidget> widget) {
        layout_->moveWidgetToBack(widget->getInternalPtr());
    }

    size_t HorizontalLayout::moveWidgetForward(std::shared_ptr<UI::IWidget> widget) {
        return layout_->moveWidgetForward(widget->getInternalPtr());
    }

    size_t
    HorizontalLayout::moveWidgetBackward(std::shared_ptr<UI::IWidget> widget) {
        return layout_->moveWidgetBackward(widget->getInternalPtr());
    }

    std::shared_ptr<UI::IWidget> HorizontalLayout::getFocusedWidget() const {
        auto widget = layout_->getFocusedChild();
        if (widget)
            return widgets_.at(widget->getWidgetName().toAnsiString());
        return nullptr;
    }

    std::shared_ptr<UI::IWidget> HorizontalLayout::getFocusedLeaf() const {
        auto widget = layout_->getFocusedLeaf();
        if (widget)
            return widgets_.at(widget->getWidgetName().toAnsiString());
        return nullptr;
    }

    std::shared_ptr<UI::IWidget> HorizontalLayout::getWidgetAtPosition(Vector2f pos) const {
        auto widget = layout_->getWidgetAtPosition({pos.x, pos.y});
        if (widget)
            return widgets_.at(widget->getWidgetName().toAnsiString());
        return nullptr;
    }

    bool HorizontalLayout::focusNextWidget(bool recursive) {
        return layout_->focusNextWidget(recursive);
    }

    bool HorizontalLayout::focusPreviousWidget(bool recursive) {
        return layout_->focusPreviousWidget(recursive);
    }

    std::shared_ptr<tgui::Widget> HorizontalLayout::getInternalPtr() {
        return layout_;
    }

    void HorizontalLayout::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void HorizontalLayout::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    void HorizontalLayout::move(Vector2f offset) {
        move(offset.x, offset.y);
    }

    void HorizontalLayout::scale(Vector2f offset) {
        scale(offset.x, offset.y);
    }

    void HorizontalLayout::initEvents() {
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

    Vector2f HorizontalLayout::getScale() const {
        return {layout_->getScale().x, layout_->getScale().y};
    }
}