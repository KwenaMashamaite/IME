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

#include "IME/graphics/ui/GuiContainer.h"
#include "IME/graphics/Window.h"
#include "IME/graphics/ui/widgets/IWidget.h"
#include "IME/core/managers/ResourceManager.h"
#include "IME/utility/Helpers.h"
#include <cassert>

namespace ime::ui {
    GuiContainer::GuiContainer(Window &target) :
        sfmlGui_{target.window_}
    {}

    void GuiContainer::handleEvent(sf::Event event) {
        sfmlGui_.handleEvent(event);
    }

    void GuiContainer::setTabKeyUsageEnabled(bool enabled) {
        sfmlGui_.setTabKeyUsageEnabled(enabled);
    }

    bool GuiContainer::isTabKeyUsageEnabled() const {
        return sfmlGui_.isTabKeyUsageEnabled();
    }

    void GuiContainer::draw() {
        sfmlGui_.draw();
    }

    void GuiContainer::setFont(const std::string& filename) {
        sfmlGui_.setFont(utility::get_TGUI_Font(filename));
    }

    void GuiContainer::removeAllWidgets() {
        sfmlGui_.removeAllWidgets();
        widgets_.clear();
    }

    void GuiContainer::setTarget(Window &target) {
        sfmlGui_.setTarget(target.window_);
    }

    std::shared_ptr<IWidget>
    GuiContainer::getWidgetBelowMouseCursor(Vector2f mousePos) const {
        auto widget = sfmlGui_.getWidgetBelowMouseCursor({static_cast<int>(mousePos.x), static_cast<int>(mousePos.y)});
        if (widget)
            return widgets_.at(widget->getWidgetName().toAnsiString());
        return nullptr;
    }

    void GuiContainer::unfocusAllWidgets() {
        sfmlGui_.unfocusAllWidgets();
    }

    void GuiContainer::setOpacity(float opacity) {
        sfmlGui_.setOpacity(opacity);
    }

    float GuiContainer::getOpacity() const {
        return sfmlGui_.getOpacity();
    }

    void GuiContainer::setMouseCursor(CursorType cursorType) {
        sfmlGui_.setOverrideMouseCursor(static_cast<tgui::Cursor::Type>(cursorType));
    }

    void GuiContainer::restoreMouseCursor() {
        sfmlGui_.restoreOverrideMouseCursor();
    }

    void GuiContainer::requestMouseCursor(CursorType cursorType) {
        sfmlGui_.requestMouseCursor(static_cast<tgui::Cursor::Type>(cursorType));
    }

    bool GuiContainer::addWidget(std::shared_ptr<IWidget> widget,
         const std::string &widgetName)
    {
        assert(widget && "Cannot add null widget to gui container");
        if (widgets_.insert({widgetName, widget}).second) {
            sfmlGui_.add(widget->getInternalPtr(), widgetName);
            return true;
        }
        return false;
    }

    std::shared_ptr<IWidget>
    GuiContainer::getWidget(const std::string &widgetName) const {
        if (utility::findIn(widgets_, widgetName))
            return widgets_.at(widgetName);
        return nullptr;
    }

    bool GuiContainer::removeWidget(const std::string &widget) {
        if (utility::findIn(widgets_, widget)) {
            sfmlGui_.remove(widgets_[widget]->getInternalPtr());
            widgets_.erase(widget);
            return true;
        }
        return false;
    }

    std::shared_ptr<IWidget> GuiContainer::getFocusedWidget() const {
        auto widget = sfmlGui_.getFocusedChild();
        if (widget)
            return widgets_.at(widget->getWidgetName().toAnsiString());
        return nullptr;
    }

    std::shared_ptr<IWidget> GuiContainer::getFocusedLeaf() const {
        auto widget = sfmlGui_.getFocusedLeaf();
        if (widget)
            return widgets_.at(widget->getWidgetName().toAnsiString());
        return nullptr;
    }

    std::shared_ptr<IWidget> GuiContainer::getWidgetAtPosition(Vector2f pos) const {
        auto widget = sfmlGui_.getWidgetAtPosition({pos.x, pos.y});
        if (widget)
            return widgets_.at(widget->getWidgetName().toAnsiString());
        return nullptr;
    }

    bool GuiContainer::focusNextWidget(bool recursive) {
        return sfmlGui_.focusNextWidget(recursive);
    }

    bool GuiContainer::focusPreviousWidget(bool recursive) {
        return sfmlGui_.focusPreviousWidget(recursive);
    }

    void GuiContainer::moveWidgetToFront(const std::shared_ptr<IWidget> &widget) {
        sfmlGui_.moveWidgetToFront(widget->getInternalPtr());
    }

    void GuiContainer::moveWidgetToBack(const std::shared_ptr<IWidget> &widget) {
        sfmlGui_.moveWidgetToBack(widget->getInternalPtr());
    }

    size_t GuiContainer::moveWidgetForward(std::shared_ptr<IWidget> widget) {
        return sfmlGui_.moveWidgetForward(widget->getInternalPtr());
    }

    size_t GuiContainer::moveWidgetBackward(std::shared_ptr<IWidget> widget) {
        return sfmlGui_.moveWidgetBackward(widget->getInternalPtr());
    }

    void GuiContainer::setTextSize(unsigned int size) {
        sfmlGui_.setTextSize(size);
    }

    unsigned int GuiContainer::getTextSize() const {
        return sfmlGui_.getTextSize();
    }

    bool GuiContainer::isTargetSet() const {
        return sfmlGui_.getTarget() != nullptr;
    }
}
