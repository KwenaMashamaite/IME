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

#include "IME/ui/widgets/TabsContainer.h"
#include "IME/ui/widgets/WidgetImpl.h"
#include <TGUI/Widgets/TabContainer.hpp>
#include <unordered_map>

namespace ime::ui {
    static unsigned int count = 1; // Keeps track of how many widgets of this type have been instantiated

    class TabsContainer::TabsContainerImpl {
    public:
        explicit TabsContainerImpl(tgui::Widget* widget) :
            tabContainer_{static_cast<tgui::TabContainer*>(widget)}
        {}

        TabsContainerImpl(const TabsContainerImpl& other) :
            tabContainer_{static_cast<tgui::TabContainer*>(other.tabContainer_)}
        {
            for (const auto& [index, panel] : other.panels_) {
                panels_.insert({index, panel->copy()});
            }
        }

        TabsContainerImpl& operator=(const TabsContainerImpl& rhs) {
            if (this != &rhs) {
                auto temp{rhs};
                std::swap(tabContainer_, temp.tabContainer_);
                std::swap(panels_, temp.panels_);
            }

            return *this;
        }

        TabsContainerImpl(TabsContainerImpl&&) noexcept = default;
        TabsContainerImpl& operator=(TabsContainerImpl&&) noexcept = default;

        tgui::TabContainer* tabContainer_;
        std::unordered_map<std::size_t, Panel::Ptr> panels_; //!< Stores a panel with its index
    }; // class WidgetContainerImpl

    ////////////////////////////////////////////////////////////////////////////
    
    TabsContainer::TabsContainer(const std::string& width, const std::string& height) :
        Widget(std::make_unique<priv::WidgetImpl<tgui::TabContainer>>(tgui::TabContainer::create({width.c_str(), height.c_str()}))),
        pimpl_{std::make_unique<TabsContainerImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("TabsContainer" + std::to_string(count++));
        setRenderer(std::make_unique<TabsRenderer>());
        initEvents();
    }

    TabsContainer::TabsContainer(const TabsContainer& other) :
        Widget(other),
        pimpl_{std::make_unique<TabsContainerImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("TabsContainer" + std::to_string(count++));
        initEvents();
    }

    TabsContainer &TabsContainer::operator=(const TabsContainer& rhs) {
        if (this != &rhs) {
            Widget::operator=(rhs);
            pimpl_ = std::make_unique<TabsContainerImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get());
            initEvents();
        }

        return *this;
    }

    TabsContainer::TabsContainer(TabsContainer&& other) noexcept = default;
    TabsContainer &TabsContainer::operator=(TabsContainer&& rhs) noexcept = default;

    TabsContainer::Ptr TabsContainer::create(const std::string& width,
        const std::string& height)
    {
        return Ptr(new TabsContainer(width, height));
    }

    TabsContainer::Ptr TabsContainer::copy() const {
        return TabsContainer::Ptr(static_cast<TabsContainer*>(clone().release()));
    }

    TabsRenderer* TabsContainer::getRenderer() {
        return static_cast<TabsRenderer*>(Widget::getRenderer());
    }
    
    const TabsRenderer* TabsContainer::getRenderer() const {
        return static_cast<const TabsRenderer*>(Widget::getRenderer());
    }

    void TabsContainer::setTabsHeight(float height) {
        pimpl_->tabContainer_->setTabsHeight(height);
    }

    Panel* TabsContainer::addPanel(Panel::Ptr panel, const std::string &text, bool select) {
        IME_ASSERT(panel, "Cannot add nullptr to a TabsContainer");
        auto [iter, inserted] = pimpl_->panels_.insert({pimpl_->tabContainer_->getPanelCount() + 1, std::move(panel)});
        IME_UNUSED(inserted);

        pimpl_->tabContainer_->addPanel(
            std::static_pointer_cast<tgui::Panel>(std::static_pointer_cast<tgui::Widget>(iter->second->getInternalPtr())),
            text, select);

        return iter->second.get();
    }

    bool TabsContainer::insertPanel(Panel::Ptr panel, const std::string &text,
        std::size_t index, bool select)
    {
        //@TODO Open up space for the new widget because in our container because
        // If the index is not at end, then a widget already exists with
        // the given index and an our unordered_map will deny the insertion
        // event though insertion in the third party container succeeds
        IME_UNUSED(panel);
        IME_UNUSED(text);
        IME_UNUSED(index);
        IME_UNUSED(select);

        return false;
    }

    void TabsContainer::removePanel(Panel* panel) {
        auto panelCount = pimpl_->tabContainer_->getPanelCount();
        auto panelIndex = getIndex(panel);
        pimpl_->tabContainer_->removePanel(std::static_pointer_cast<tgui::Panel>(
            std::static_pointer_cast<tgui::Widget>(panel->getInternalPtr())));

        if (pimpl_->tabContainer_->getPanelCount() == panelCount - 1)
            pimpl_->panels_.erase(panelIndex);
    }

    void TabsContainer::select(std::size_t index) {
        pimpl_->tabContainer_->select(index);
    }

    Panel* TabsContainer::getSelected() {
        if (pimpl_->tabContainer_->getSelected())
            return pimpl_->panels_[pimpl_->tabContainer_->getSelectedIndex()].get();
        return nullptr;
    }

    std::size_t TabsContainer::getPanelCount() const {
        return pimpl_->tabContainer_->getPanelCount();
    }

    int TabsContainer::getIndex(const Panel* panel) {
        return pimpl_->tabContainer_->getIndex(std::static_pointer_cast<tgui::Panel>(
            std::static_pointer_cast<tgui::Widget>(panel->getInternalPtr())));
    }

    int TabsContainer::getSelectedIndex() const {
        return pimpl_->tabContainer_->getSelectedIndex();
    }

    Panel* TabsContainer::getPanel(int index) const {
        if (pimpl_->panels_.find(index) != pimpl_->panels_.end())
            return pimpl_->panels_.at(index).get();
        return nullptr;
    }

    std::string TabsContainer::getTabText(std::size_t index) const {
        return pimpl_->tabContainer_->getTabText(index).toStdString();
    }

    bool TabsContainer::changeTabText(std::size_t index, const std::string &text) {
        return pimpl_->tabContainer_->changeTabText(index, text);
    }

    Widget::Ptr TabsContainer::clone() const {
        return std::make_unique<TabsContainer>(*this);
    }

    std::string TabsContainer::getWidgetType() const {
        return "TabsContainer";
    }

    void TabsContainer::initEvents() {
        pimpl_->tabContainer_->onSelectionChanged([this](int index){
            emit("selectionChange", index);
        });
    }

    TabsContainer::~TabsContainer() = default;
}

