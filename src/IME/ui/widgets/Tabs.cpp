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

#include "IME/ui/widgets/Tabs.h"
#include "WidgetImpl.h"
#include <TGUI/Widgets/Tabs.hpp>

namespace ime::ui {
    class Tabs::TabsImpl {
    public:
        TabsImpl(std::shared_ptr<tgui::Widget> widget) :
            tabs_{std::static_pointer_cast<tgui::Tabs>(widget)}
        {}

        std::shared_ptr<tgui::Tabs> tabs_;
    }; // class TabsImpl

    ////////////////////////////////////////////////////////////////////////////

    Tabs::Tabs() :
        Widget(std::make_unique<priv::WidgetImpl<tgui::Tabs>>(tgui::Tabs::create())),
        pimpl_{std::make_unique<TabsImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()))}
    {
        setRenderer(std::make_shared<TabsRenderer>());

        pimpl_->tabs_->onTabSelect([this](const tgui::String& item){
            emit("select", item.toStdString());
        });
    }

    Tabs::Tabs(Tabs &&) = default;

    Tabs &Tabs::operator=(Tabs &&) = default;

    Tabs::sharedPtr Tabs::create() {
        return sharedPtr(new Tabs());
    }

    Tabs::sharedPtr Tabs::copy(Tabs::constSharedPtr other, bool shareRenderer) {
        auto widget = create();
        return widget;
    }

    std::shared_ptr<TabsRenderer> Tabs::getRenderer() {
        return std::static_pointer_cast<TabsRenderer>(Widget::getRenderer());
    }

    const std::shared_ptr<TabsRenderer> Tabs::getRenderer() const {
        return std::static_pointer_cast<TabsRenderer>(Widget::getRenderer());
    }

    void Tabs::setAutoSize(bool autoSize) {
        pimpl_->tabs_->setAutoSize(autoSize);
    }

    bool Tabs::getAutoSize() const {
        return pimpl_->tabs_->getAutoSize();
    }

    std::size_t Tabs::add(const std::string &text, bool select) {
        return pimpl_->tabs_->add(text, select);
    }

    void Tabs::insert(std::size_t index, const std::string &text, bool select) {
        pimpl_->tabs_->insert(index, text, select);
    }

    std::string Tabs::getText(std::size_t index) const {
        return pimpl_->tabs_->getText(index).toStdString();
    }

    bool Tabs::changeText(std::size_t index, const std::string &text) {
        return pimpl_->tabs_->changeText(index, text);
    }

    bool Tabs::select(const std::string &text) {
        return pimpl_->tabs_->select(text);
    }

    bool Tabs::select(std::size_t index) {
        return pimpl_->tabs_->select(index);
    }

    void Tabs::deselect() {
        pimpl_->tabs_->deselect();
    }

    bool Tabs::remove(const std::string &text) {
        return pimpl_->tabs_->remove(text);
    }

    bool Tabs::remove(std::size_t index) {
        return pimpl_->tabs_->remove(index);
    }

    void Tabs::removeAll() {
        pimpl_->tabs_->removeAll();
    }

    std::string Tabs::getSelected() const {
        return pimpl_->tabs_->getSelected().toStdString();
    }

    int Tabs::getSelectedIndex() const {
        return pimpl_->tabs_->getSelectedIndex();
    }

    void Tabs::setTabVisible(std::size_t index, bool visible) {
        pimpl_->tabs_->setTabVisible(index, visible);
    }

    bool Tabs::isTabVisible(std::size_t index) const {
        return pimpl_->tabs_->getTabVisible(index);
    }

    void Tabs::setTabEnabled(std::size_t index, bool enabled) {
        pimpl_->tabs_->setTabEnabled(index, enabled);
    }

    bool Tabs::isTabEnabled(std::size_t index) const {
        return pimpl_->tabs_->getTabEnabled(index);
    }

    void Tabs::setTabHeight(float height) {
        pimpl_->tabs_->setTabHeight(height);
    }

    void Tabs::setMaximumTabWidth(float maximumWidth) {
        pimpl_->tabs_->setMaximumTabWidth(maximumWidth);
    }

    float Tabs::getMaximumTabWidth() const {
        return pimpl_->tabs_->getMaximumTabWidth();
    }

    void Tabs::setMinimumTabWidth(float minimumWidth) {
        pimpl_->tabs_->setMinimumTabWidth(minimumWidth);
    }

    float Tabs::getMinimumTabWidth() const {
        return pimpl_->tabs_->getMinimumTabWidth();
    }

    std::size_t Tabs::getTabsCount() const {
        return pimpl_->tabs_->getTabsCount();
    }

    std::string Tabs::getWidgetType() const {
        return "Tabs";
    }

    Tabs::~Tabs() = default;
}