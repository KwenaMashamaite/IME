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

#include "IME/ui/widgets/MenuBar.h"
#include "TGUI/Widgets/MenuBar.hpp"
#include "IME/ui/widgets/WidgetImpl.h"

namespace ime::ui {
    static unsigned int count = 1; // Keeps track of how many widgets of this type have been instantiated

    class MenuBar::MenuBarImpl {
    public:
        explicit MenuBarImpl(tgui::Widget* widget) :
            menuBar{static_cast<tgui::MenuBar*>(widget)}
        {}

        tgui::MenuBar* menuBar;
    };

    ////////////////////////////////////////////////////////////////////////////

    MenuBar::MenuBar() :
        Widget(std::make_unique<priv::WidgetImpl<tgui::MenuBar>>(tgui::MenuBar::create())),
        pimpl_{std::make_unique<MenuBarImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("MenuBar" + std::to_string(count++));
        setRenderer(std::make_unique<MenuBarRenderer>());
        initEvents();
    }

    MenuBar::MenuBar(const MenuBar& other) :
        Widget(other),
        pimpl_{std::make_unique<MenuBarImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("MenuBar" + std::to_string(count++));
        initEvents();
    }

    MenuBar &MenuBar::operator=(const MenuBar& rhs) {
        if (this != &rhs) {
            Widget::operator=(rhs);
            pimpl_ = std::make_unique<MenuBarImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get());
            initEvents();
        }

        return *this;
    }

    MenuBar::MenuBar(MenuBar&& other) noexcept :
        Widget(std::move(other))
    {
        *this = std::move(other);
    }

    MenuBar &MenuBar::operator=(MenuBar&& rhs) noexcept {
        if (this != &rhs) {
            pimpl_ = std::move(rhs.pimpl_);
            initEvents();
        }

        return *this;
    }

    MenuBar::Ptr MenuBar::create() {
        return MenuBar::Ptr(new MenuBar());;
    }

    MenuBar::Ptr MenuBar::copy() const {
        return MenuBar::Ptr(static_cast<MenuBar*>(clone().release()));
    }

    Widget::Ptr MenuBar::clone() const {
        return std::make_unique<MenuBar>(*this);
    }

    MenuBarRenderer* MenuBar::getRenderer() {
        return static_cast<MenuBarRenderer*>(Widget::getRenderer());
    }

    const MenuBarRenderer* MenuBar::getRenderer() const {
        return static_cast<const MenuBarRenderer*>(Widget::getRenderer());
    }

    void MenuBar::addMenu(const std::string &text) {
        pimpl_->menuBar->addMenu(text);
    }

    void MenuBar::addMenus(const std::initializer_list<std::string> &menus) {
        for (const auto& menu : menus)
            pimpl_->menuBar->addMenu(menu);
    }

    bool MenuBar::addMenuItem(const std::string &text) {
        return pimpl_->menuBar->addMenuItem(text);
    }

    bool MenuBar::addMenuItem(const std::string &menu, const std::string &text) {
        return pimpl_->menuBar->addMenuItem(menu, text);
    }

    void MenuBar::addMenuItem(const std::initializer_list<std::string> &hierarchy) {
        pimpl_->menuBar->addMenuItem(std::vector<tgui::String>{hierarchy.begin(), hierarchy.end()});
    }

    void MenuBar::removeAllMenus() {
        pimpl_->menuBar->removeAllMenus();
    }

    bool MenuBar::removeMenu(const std::string &menu) {
        return pimpl_->menuBar->removeMenu(menu);
    }

    bool MenuBar::removeMenuItem(const std::string &menu, const std::string &menuItem) {
        return pimpl_->menuBar->removeMenuItem(menu, menuItem);
    }

    bool MenuBar::removeMenuItem(const std::initializer_list<std::string> &hierarchy, bool removeParentsWhenEmpty) {
        return pimpl_->menuBar->removeMenuItem(std::vector<tgui::String>{hierarchy.begin(), hierarchy.end()}, removeParentsWhenEmpty);
    }

    bool MenuBar::removeMenuItems(const std::string &menu) {
        return pimpl_->menuBar->removeMenuItems(menu);
    }

    bool MenuBar::removeSubMenuItems(const std::initializer_list<std::string> &hierarchy) {
        return pimpl_->menuBar->removeSubMenuItems(std::vector<tgui::String>{hierarchy.begin(), hierarchy.end()});
    }

    void MenuBar::setMenuEnable(const std::string &menu, bool enabled) {
        pimpl_->menuBar->setMenuEnabled(menu, enabled);
    }

    bool MenuBar::isMenuEnabled(const std::string &menu) const {
        return pimpl_->menuBar->getMenuEnabled(menu);
    }

    void MenuBar::setMenuItemEnable(const std::string &menu, const std::string &menuItem, bool enabled) {
        pimpl_->menuBar->setMenuItemEnabled(menu, menuItem, enabled);
    }

    void MenuBar::setMenuItemEnable(const std::initializer_list<std::string> &hierarchy, bool enabled) {
        pimpl_->menuBar->setMenuItemEnabled(std::vector<tgui::String>{hierarchy.begin(), hierarchy.end()}, enabled);
    }

    bool MenuBar::isMenuItemEnabled(const std::string &menu, const std::string &menuItem) const {
        return pimpl_->menuBar->getMenuItemEnabled(menu, menuItem);
    }

    bool MenuBar::isMenuItemEnabled(const std::initializer_list<std::string> &hierarchy) const {
        return pimpl_->menuBar->getMenuItemEnabled(std::vector<tgui::String>{hierarchy.begin(), hierarchy.end()});
    }

    void MenuBar::setMinimumSubMenuWidth(float minimumWidth) {
        pimpl_->menuBar->setMinimumSubMenuWidth(minimumWidth);
    }

    float MenuBar::getMinimumSubMenuWidth() const {
        return pimpl_->menuBar->getMinimumSubMenuWidth();
    }

    void MenuBar::invertMenuDirection(bool invert) {
        pimpl_->menuBar->setInvertedMenuDirection(invert);
    }

    bool MenuBar::isMenuDirectionInverted() const {
        return pimpl_->menuBar->getInvertedMenuDirection();
    }

    void MenuBar::closeMenu() {
        pimpl_->menuBar->closeMenu();
    }

    std::string MenuBar::getWidgetType() const {
        return "MenuBar";
    }

    void MenuBar::initEvents() {
        pimpl_->menuBar->onMenuItemClick([this] (const tgui::String& menuItem) {
            emit("menuItemClick", menuItem.toStdString());
        });
    }

    MenuBar::~MenuBar() = default;
}
