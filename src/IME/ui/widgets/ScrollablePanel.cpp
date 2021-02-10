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

#include "IME/ui/widgets/ScrollablePanel.h"
#include "IME/utility/Helpers.h"
#include <TGUI/Widgets/ScrollablePanel.hpp>

namespace ime::ui {
    ScrollablePanel::ScrollablePanel(const std::string &width, const std::string &height,
        Vector2f contentSize) :
            panel_{tgui::ScrollablePanel::create({width.c_str(), height.c_str()}, {contentSize.x, contentSize.y})},
            renderer_{std::make_shared<ScrollablePanelRenderer>()}
    {
        renderer_->setInternalPtr(panel_->getRenderer());
        setAsContainer(true);
        initEvents();
    }

    ScrollablePanel::sharedPtr ScrollablePanel::create(const std::string &width,
        const std::string &height, Vector2f contentSize)
    {
        return std::make_shared<ScrollablePanel>(width, height, contentSize);
    }

    ScrollablePanel::sharedPtr ScrollablePanel::copy(ScrollablePanel::constSharedPtr other,
        bool shareRenderer)
    {
        auto widget = create();
        widget->panel_ = widget->panel_->copy(other->panel_);

        if (!shareRenderer)
            widget->panel_->setRenderer(other->panel_->getRenderer()->clone());
        widget->renderer_->setInternalPtr(other->panel_->getRenderer());

        return widget;
    }

    void ScrollablePanel::setRenderer(ScrollablePanelRenderer::sharedPtr renderer) {
        IME_ASSERT(renderer, "Cannot set nullptr as renderer");
        renderer_ = renderer;
        panel_->setRenderer(renderer->getInternalPtr()->getData());
    }

    ScrollablePanelRenderer::sharedPtr ScrollablePanel::getRenderer() {
        return renderer_;
    }

    void ScrollablePanel::setContentSize(Vector2f size) {
        panel_->setContentSize({size.x, size.y});
    }

    Vector2f ScrollablePanel::getContentSize() const {
        return {panel_->getSize().x, panel_->getSize().y};
    }

    Vector2f ScrollablePanel::getContentOffset() const {
        return {panel_->getContentOffset().x, panel_->getContentOffset().y};
    }

    float ScrollablePanel::getScrollbarWidth() const {
        return panel_->getScrollbarWidth();
    }

    void ScrollablePanel::setVerticalScrollStep(unsigned int step) {
        panel_->setVerticalScrollAmount(step);
    }

    unsigned int ScrollablePanel::getVerticalScrollStep() const {
        return panel_->getVerticalScrollAmount();
    }

    void ScrollablePanel::setHorizontalScrollStep(unsigned int step) {
        panel_->setHorizontalScrollAmount(step);
    }

    unsigned int ScrollablePanel::getHorizontalScrollStep() const {
        return panel_->getHorizontalScrollAmount();
    }

    void ScrollablePanel::setVerticalThumbValue(unsigned int value) {
        panel_->setVerticalScrollbarValue(value);
    }

    unsigned int ScrollablePanel::getVerticalThumbValue() const {
        return panel_->getVerticalScrollbarValue();
    }

    void ScrollablePanel::setHorizontalThumbValue(unsigned int value) {
        panel_->setHorizontalScrollbarValue(value);
    }

    unsigned int ScrollablePanel::getHorizontalThumbValue() const {
        return panel_->getHorizontalScrollbarValue();
    }

    void ScrollablePanel::setTextSize(unsigned int charSize) {
        panel_->setTextSize(charSize);
    }

    unsigned int ScrollablePanel::getTextSize() const {
        return panel_->getTextSize();
    }

    void ScrollablePanel::setSize(float width, float height) {
        panel_->setSize({width, height});
    }

    void ScrollablePanel::setSize(const std::string &width, const std::string &height) {
        panel_->setSize({width.c_str(), height.c_str()});
    }

    Vector2f ScrollablePanel::getSize() const {
        return {panel_->getSize().x, panel_->getSize().y};
    }

    Vector2f ScrollablePanel::getAbsoluteSize() {
        return {panel_->getFullSize().x, panel_->getFullSize().y};
    }

    void ScrollablePanel::setWidth(float width) {
        panel_->setWidth(width);
    }

    void ScrollablePanel::setWidth(const std::string &width) {
        panel_->setWidth(width.c_str());
    }

    void ScrollablePanel::setHeight(float height) {
        panel_->setHeight(height);
    }

    void ScrollablePanel::setHeight(const std::string &height) {
        panel_->setHeight(height.c_str());
    }

    void ScrollablePanel::setMouseCursor(CursorType cursor) {
        panel_->setMouseCursor(static_cast<tgui::Cursor::Type>(static_cast<int>(cursor)));
    }

    CursorType ScrollablePanel::getMouseCursor() const {
        return static_cast<CursorType>(static_cast<int>(panel_->getMouseCursor()));
    }

    std::string ScrollablePanel::getWidgetType() const {
        return "ScrollablePanel";
    }

    void ScrollablePanel::showWithEffect(ShowAnimationType type, int duration) {
        panel_->showWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    void ScrollablePanel::hideWithEffect(ShowAnimationType type, int duration) {
        panel_->hideWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    bool ScrollablePanel::isAnimationPlaying() const {
        return panel_->isAnimationPlaying();
    }

    void ScrollablePanel::setVisible(bool visible) {
        panel_->setVisible(visible);
    }

    bool ScrollablePanel::isVisible() const {
        return panel_->isVisible();
    }

    void ScrollablePanel::toggleVisibility() {
        panel_->setVisible(!panel_->isVisible());
    }

    bool ScrollablePanel::contains(float x, float y) const {
        return panel_->isMouseOnWidget({x, y});
    }

    void ScrollablePanel::setPosition(float x, float y) {
        panel_->setPosition({x, y});
    }

    void ScrollablePanel::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    void ScrollablePanel::setPosition(const std::string &x, const std::string &y) {
        panel_->setPosition({x.c_str(), y.c_str()});
    }

    Vector2f ScrollablePanel::getPosition() const {
        return {panel_->getPosition().x, panel_->getPosition().y};
    }

    Vector2f ScrollablePanel::getAbsolutePosition() const {
        return {panel_->getAbsolutePosition().x, panel_->getAbsolutePosition().y};
    }

    void ScrollablePanel::setRotation(float angle) {
        panel_->setRotation(angle);
    }

    void ScrollablePanel::rotate(float angle) {
        panel_->setRotation(panel_->getRotation() + angle);
    }

    float ScrollablePanel::getRotation() const {
        return panel_->getRotation();
    }

    void ScrollablePanel::setScale(float factorX, float factorY) {
        panel_->setScale({factorX, factorY});
    }

    void ScrollablePanel::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void ScrollablePanel::scale(float factorX, float factorY) {
        panel_->setScale({panel_->getScale().x + factorX,
                          panel_->getScale().y + factorY});
    }

    void ScrollablePanel::scale(Vector2f offset) {
        scale(offset.x, offset.y);
    }

    Vector2f ScrollablePanel::getScale() const {
        return {panel_->getScale().x, panel_->getScale().y};
    }

    void ScrollablePanel::setOrigin(float x, float y) {
        panel_->setOrigin({x, y});
    }

    void ScrollablePanel::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    Vector2f ScrollablePanel::getOrigin() const {
        return {panel_->getOrigin().x, panel_->getOrigin().y};
    }

    void ScrollablePanel::move(float offsetX, float offsetY) {
        panel_->setPosition(getPosition().x + offsetX, getPosition().y + offsetY);
    }

    void ScrollablePanel::move(Vector2f offset) {
        move(offset.x, offset.y);
    }

    bool ScrollablePanel::addWidget(std::shared_ptr<IWidget> widget,
                          const std::string &name)
    {
        IME_ASSERT(widget, "Cannot add nullptr to a widget container");
        if (widgets_.insert({name, widget}).second) {
            panel_->add(widget->getInternalPtr(), name);
            return true;
        }
        return false;
    }

    std::shared_ptr<IWidget> ScrollablePanel::getWidget(const std::string &name) const {
        if (utility::findIn(widgets_, name))
            return widgets_.at(name);
        return utility::findRecursively(widgets_, name);
    }

    bool ScrollablePanel::removeWidget(const std::string &widget) {
        if (utility::findIn(widgets_, widget)) {
            panel_->remove(widgets_[widget]->getInternalPtr());
            widgets_.erase(widget);
            return true;
        }
        return false;
    }

    void ScrollablePanel::removeAllWidgets() {
        panel_->removeAllWidgets();
        widgets_.clear();
    }

    void ScrollablePanel::moveWidgetToFront(std::shared_ptr<IWidget> widget) {
        panel_->moveWidgetToFront(widget->getInternalPtr());
    }

    void ScrollablePanel::moveWidgetToBack(std::shared_ptr<IWidget> widget) {
        panel_->moveWidgetToBack(widget->getInternalPtr());
    }

    size_t ScrollablePanel::moveWidgetForward(std::shared_ptr<IWidget> widget) {
        return panel_->moveWidgetForward(widget->getInternalPtr());
    }

    size_t ScrollablePanel::moveWidgetBackward(std::shared_ptr<IWidget> widget) {
        return panel_->moveWidgetBackward(widget->getInternalPtr());
    }

    std::shared_ptr<IWidget> ScrollablePanel::getFocusedWidget() const {
        auto widget =panel_->getFocusedChild();
        if (widget)
            return widgets_.at(widget->getWidgetName().toStdString());
        return nullptr;
    }

    std::shared_ptr<IWidget> ScrollablePanel::getFocusedLeaf() const {
        auto widget = panel_->getFocusedLeaf();
        if (widget)
            return widgets_.at(widget->getWidgetName().toStdString());
        return nullptr;
    }

    std::shared_ptr<IWidget> ScrollablePanel::getWidgetAtPosition(Vector2f pos) const {
        auto widget = panel_->getWidgetAtPosition({pos.x, pos.y});
        if (widget)
            return widgets_.at(widget->getWidgetName().toStdString());
        return nullptr;
    }

    bool ScrollablePanel::focusNextWidget(bool recursive) {
        return panel_->focusNextWidget(recursive);
    }

    bool ScrollablePanel::focusPreviousWidget(bool recursive) {
        return panel_->focusPreviousWidget(recursive);
    }

    std::shared_ptr<tgui::Widget> ScrollablePanel::getInternalPtr() {
        return panel_;
    }

    void ScrollablePanel::initEvents() {
        panel_->onMouseEnter([this]{emit("mouseEnter");});
        panel_->onMouseLeave([this]{emit("mouseLeave");});
        panel_->onFocus([this]{emit("focus");});
        panel_->onUnfocus([this]{emit("unfocus");});
        panel_->onAnimationFinish([this]{emit("animationFinish");});
        panel_->onSizeChange([this](tgui::Vector2f newSize) {
            emit("sizeChange", newSize.x, newSize.y);
        });

        panel_->onPositionChange([this](tgui::Vector2f newPos) {
            emit("positionChange", newPos.x, newPos.y);
        });

        //Events triggered by left mouse button
        panel_->onClick([this](tgui::Vector2f mousePos){
            emit("click");
            emit("click", mousePos.x, mousePos.y);
        });

        panel_->onDoubleClick([this](tgui::Vector2f mousePos) {
            emit("doubleClick");
            emit("doubleClick", mousePos.x, mousePos.y);
        });

        panel_->onMousePress([this](tgui::Vector2f mousePos) {
            emit("leftMouseDown");
            emit("leftMouseDown", mousePos.x, mousePos.y);
        });

        panel_->onMouseRelease([this](tgui::Vector2f mousePos) {
            emit("leftMouseUp");
            emit("leftMouseUp", mousePos.x, mousePos.y);
        });

        //Events triggered by right mouse button
        panel_->onRightMousePress([this](tgui::Vector2f mousePos){
            emit("rightMouseDown");
            emit("rightMouseDown", mousePos.x, mousePos.y);
        });

        panel_->onRightMouseRelease([this](tgui::Vector2f mousePos){
            emit("rightMouseUp");
            emit("rightMouseUp", mousePos.x, mousePos.y);
        });

        panel_->onRightClick([this](tgui::Vector2f mousePos){
            emit("rightClick");
            emit("rightClick", mousePos.x, mousePos.y);
        });
    }
}
