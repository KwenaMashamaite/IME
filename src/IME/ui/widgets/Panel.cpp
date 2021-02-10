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

#include "IME/ui/widgets/Panel.h"
#include "IME/utility/Helpers.h"

namespace ime::ui {
    Panel::Panel(const std::string& width, const std::string& height) :
        panel_{tgui::Panel::create({width.c_str(), height.c_str()})},
        renderer_{std::make_shared<PanelRenderer>()}
    {
        renderer_->setInternalPtr(panel_->getRenderer());
        setAsContainer(true);
        initEvents();
    }

    Panel::sharedPtr Panel::create(const std::string& width, const std::string& height) {
        return std::make_shared<Panel>(width, height);
    }

    Panel::sharedPtr Panel::copy(Panel::constSharedPtr other, bool shareRenderer) {
        auto widget = create();
        widget->panel_ = widget->panel_->copy(other->panel_);

        if (!shareRenderer)
            widget->panel_->setRenderer(other->panel_->getRenderer()->clone());
        widget->renderer_->setInternalPtr(other->panel_->getRenderer());

        return widget;
    }

    void Panel::setRenderer(std::shared_ptr<PanelRenderer> renderer) {
        IME_ASSERT(renderer, "Cannot set nullptr as renderer");
        renderer_ = renderer;
        panel_->setRenderer(renderer->getInternalPtr()->getData());
    }

    std::shared_ptr<PanelRenderer> Panel::getRenderer() {
        return renderer_;
    }

    void Panel::setTextSize(unsigned int charSize) {
        panel_->setTextSize(charSize);
    }

    unsigned int Panel::getTextSize() const {
        return panel_->getTextSize();
    }

    void Panel::setSize(float width, float height) {
        panel_->setSize({width, height});
    }

    void Panel::setSize(const std::string &width, const std::string &height) {
        panel_->setSize({width.c_str(), height.c_str()});
    }

    Vector2f Panel::getSize() const {
        return {panel_->getSize().x, panel_->getSize().y};
    }

    Vector2f Panel::getAbsoluteSize() {
        return {panel_->getFullSize().x, panel_->getFullSize().y};
    }

    void Panel::setWidth(float width) {
        panel_->setWidth(width);
    }

    void Panel::setWidth(const std::string &width) {
        panel_->setWidth(width.c_str());
    }

    void Panel::setHeight(float height) {
        panel_->setHeight(height);
    }

    void Panel::setHeight(const std::string &height) {
        panel_->setHeight(height.c_str());
    }

    void Panel::setMouseCursor(CursorType cursor) {
        panel_->setMouseCursor(static_cast<tgui::Cursor::Type>(static_cast<int>(cursor)));
    }

    CursorType Panel::getMouseCursor() const {
        return static_cast<CursorType>(static_cast<int>(panel_->getMouseCursor()));
    }

    std::string Panel::getWidgetType() const {
        return "Panel";
    }

    void Panel::showWithEffect(ShowAnimationType type, int duration) {
        panel_->showWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    void Panel::hideWithEffect(ShowAnimationType type, int duration) {
        panel_->hideWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    bool Panel::isAnimationPlaying() const {
        return panel_->isAnimationPlaying();
    }

    void Panel::setVisible(bool visible) {
        panel_->setVisible(visible);
    }

    bool Panel::isVisible() const {
        return panel_->isVisible();
    }

    void Panel::toggleVisibility() {
        panel_->setVisible(!panel_->isVisible());
    }

    bool Panel::contains(float x, float y) const {
        return panel_->isMouseOnWidget({x, y});
    }

    void Panel::setPosition(float x, float y) {
        panel_->setPosition({x, y});
    }

    void Panel::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    void Panel::setPosition(const std::string &x, const std::string &y) {
        panel_->setPosition({x.c_str(), y.c_str()});
    }

    Vector2f Panel::getPosition() const {
        return {panel_->getPosition().x, panel_->getPosition().y};
    }

    Vector2f Panel::getAbsolutePosition() const {
        return {panel_->getAbsolutePosition().x, panel_->getAbsolutePosition().y};
    }

    void Panel::setRotation(float angle) {
        panel_->setRotation(angle);
    }

    void Panel::rotate(float angle) {
        panel_->setRotation(panel_->getRotation() + angle);
    }

    float Panel::getRotation() const {
        return panel_->getRotation();
    }

    void Panel::setScale(float factorX, float factorY) {
        panel_->setScale({factorX, factorY});
    }

    void Panel::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void Panel::scale(float factorX, float factorY) {
        panel_->setScale({panel_->getScale().x + factorX,
            panel_->getScale().y + factorY});
    }

    void Panel::scale(Vector2f offset) {
        scale(offset.x, offset.y);
    }

    Vector2f Panel::getScale() const {
        return {panel_->getScale().x, panel_->getScale().y};
    }

    void Panel::setOrigin(float x, float y) {
        panel_->setOrigin({x, y});
    }

    void Panel::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    Vector2f Panel::getOrigin() const {
        return {panel_->getOrigin().x, panel_->getOrigin().y};
    }

    void Panel::move(float offsetX, float offsetY) {
        panel_->setPosition(getPosition().x + offsetX, getPosition().y + offsetY);
    }

    void Panel::move(Vector2f offset) {
        move(offset.x, offset.y);
    }

    bool Panel::addWidget(std::shared_ptr<IWidget> widget,
        const std::string &name)
    {
        IME_ASSERT(widget, "Cannot add nullptr to a widget container");
        if (widgets_.insert({name, widget}).second) {
            panel_->add(widget->getInternalPtr(), name);
            return true;
        }
        return false;
    }

    std::shared_ptr<IWidget> Panel::getWidget(const std::string &name) const {
        if (utility::findIn(widgets_, name))
            return widgets_.at(name);
        return utility::findRecursively(widgets_, name);
    }

    bool Panel::removeWidget(const std::string &widget) {
        if (utility::findIn(widgets_, widget)) {
            panel_->remove(widgets_[widget]->getInternalPtr());
            widgets_.erase(widget);
            return true;
        }
        return false;
    }

    void Panel::removeAllWidgets() {
       panel_->removeAllWidgets();
       widgets_.clear();
    }

    void Panel::moveWidgetToFront(std::shared_ptr<IWidget> widget) {
       panel_->moveWidgetToFront(widget->getInternalPtr());
    }

    void Panel::moveWidgetToBack(std::shared_ptr<IWidget> widget) {
       panel_->moveWidgetToBack(widget->getInternalPtr());
    }

    size_t Panel::moveWidgetForward(std::shared_ptr<IWidget> widget) {
        return panel_->moveWidgetForward(widget->getInternalPtr());
    }

    size_t Panel::moveWidgetBackward(std::shared_ptr<IWidget> widget) {
        return panel_->moveWidgetBackward(widget->getInternalPtr());
    }

    std::shared_ptr<IWidget> Panel::getFocusedWidget() const {
        auto widget =panel_->getFocusedChild();
        if (widget)
            return widgets_.at(widget->getWidgetName().toStdString());
        return nullptr;
    }

    std::shared_ptr<IWidget> Panel::getFocusedLeaf() const {
        auto widget = panel_->getFocusedLeaf();
        if (widget)
            return widgets_.at(widget->getWidgetName().toStdString());
        return nullptr;
    }

    std::shared_ptr<IWidget> Panel::getWidgetAtPosition(Vector2f pos) const {
        auto widget = panel_->getWidgetAtPosition({pos.x, pos.y});
        if (widget)
            return widgets_.at(widget->getWidgetName().toStdString());
        return nullptr;
    }

    bool Panel::focusNextWidget(bool recursive) {
        return panel_->focusNextWidget(recursive);
    }

    bool Panel::focusPreviousWidget(bool recursive) {
        return panel_->focusPreviousWidget(recursive);
    }

    std::shared_ptr<tgui::Widget> Panel::getInternalPtr() {
        return panel_;
    }

    void Panel::initEvents() {
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
