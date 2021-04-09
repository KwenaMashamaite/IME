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
    class TabsContainer::TabsContainerImpl {
    public:
        explicit TabsContainerImpl(const std::shared_ptr<tgui::Widget>& widget) :
            tabContainer_{std::static_pointer_cast<tgui::TabContainer>(widget)}
        {}

        std::shared_ptr<tgui::TabContainer> tabContainer_;
        std::unordered_map<std::size_t, Panel::Ptr> panel_;
    }; // class WidgetContainerImpl

    ////////////////////////////////////////////////////////////////////////////
    
    TabsContainer::TabsContainer(const std::string& width, const std::string& height) :
        Widget(std::make_unique<priv::WidgetImpl<tgui::TabContainer>>(tgui::TabContainer::create({width.c_str(), height.c_str()}))),
        pimpl_{std::make_unique<TabsContainerImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()))}
    {
        setRenderer(std::make_shared<TabsRenderer>());
        
        pimpl_->tabContainer_->onSelectionChanged([this](int index){
            emit("selectionChange", index);
        });
    }

    TabsContainer::TabsContainer(const TabsContainer& other) :
        Widget(other),
        pimpl_{std::make_unique<TabsContainerImpl>(*other.pimpl_)}
    {}

    TabsContainer &TabsContainer::operator=(const TabsContainer& rhs) {
        if (this != &rhs) {
            pimpl_ = std::make_unique<TabsContainerImpl>(*rhs.pimpl_);
        }

        return *this;
    }

    TabsContainer::TabsContainer(TabsContainer &&) noexcept = default;
    TabsContainer &TabsContainer::operator=(TabsContainer &&) noexcept = default;

    TabsContainer::Ptr TabsContainer::create(const std::string& width,
        const std::string& height)
    {
        return Ptr(new TabsContainer(width, height));
    }

    TabsContainer::Ptr TabsContainer::copy() const {
        return std::static_pointer_cast<TabsContainer>(clone());
    }

    std::shared_ptr<TabsRenderer> TabsContainer::getRenderer() {
        return std::static_pointer_cast<TabsRenderer>(Widget::getRenderer());
    }
    
    const std::shared_ptr<TabsRenderer> TabsContainer::getRenderer() const {
        return std::static_pointer_cast<TabsRenderer>(Widget::getRenderer());
    }

    void TabsContainer::setTabsHeight(float height) {
        pimpl_->tabContainer_->setTabsHeight(height);
    }

    void TabsContainer::addPanel(std::shared_ptr<Panel> panel,
        const std::string &text, bool select)
    {
        IME_ASSERT(panel, "Cannot add nullptr to a TabsContainer");
        pimpl_->panel_.insert({pimpl_->tabContainer_->getPanelCount() + 1, panel});
        pimpl_->tabContainer_->addPanel(
            std::static_pointer_cast<tgui::Panel>(std::static_pointer_cast<tgui::Widget>(panel->getInternalPtr())),
            text, select);
    }

    bool TabsContainer::insertPanel(std::shared_ptr<Panel> panel,
        const std::string &text, std::size_t index, bool select)
    {
        //@TODO Open up space for the new widget because in our container because
        // If the index is not at end, then a widget already exists with
        // the given index and an our unordered_map will deny the insertion
        // event though insertion in the third party container succeeds
        if (pimpl_->tabContainer_->insertPanel(std::static_pointer_cast<tgui::Panel>(
            std::static_pointer_cast<tgui::Widget>(panel->getInternalPtr())), text, index, select))
        {
            if (pimpl_->panel_.insert({getIndex(panel), panel}).second)
                return true;
            else {
                removePanel(panel);
                return false;
            }
        }
        return false;
    }

    void TabsContainer::removePanel(std::shared_ptr<Panel> panel) {
        auto panelCount = pimpl_->tabContainer_->getPanelCount();
        auto panelIndex = getIndex(panel);
        pimpl_->tabContainer_->removePanel(std::static_pointer_cast<tgui::Panel>(
            std::static_pointer_cast<tgui::Widget>(panel->getInternalPtr())));

        if (pimpl_->tabContainer_->getPanelCount() == panelCount - 1)
            pimpl_->panel_.erase(panelIndex);
    }

    void TabsContainer::select(std::size_t index) {
        pimpl_->tabContainer_->select(index);
    }

    std::shared_ptr<Panel> TabsContainer::getSelected() {
        if (pimpl_->tabContainer_->getSelected())
            return pimpl_->panel_[pimpl_->tabContainer_->getSelectedIndex()];
        return nullptr;
    }

    std::size_t TabsContainer::getPanelCount() const {
        return pimpl_->tabContainer_->getPanelCount();
    }

    int TabsContainer::getIndex(std::shared_ptr<Panel> panel) {
        return pimpl_->tabContainer_->getIndex(std::static_pointer_cast<tgui::Panel>(
            std::static_pointer_cast<tgui::Widget>(panel->getInternalPtr())));
    }

    int TabsContainer::getSelectedIndex() const {
        return pimpl_->tabContainer_->getSelectedIndex();
    }

    std::shared_ptr<Panel> TabsContainer::getPanel(int index) {
        if (pimpl_->panel_.find(index) != pimpl_->panel_.end())
            return pimpl_->panel_[index];
        return nullptr;
    }

    std::string TabsContainer::getTabText(std::size_t index) const {
        return pimpl_->tabContainer_->getTabText(index).toStdString();
    }

    bool TabsContainer::changeTabText(std::size_t index, const std::string &text) {
        return pimpl_->tabContainer_->changeTabText(index, text);
    }

    Widget::Ptr TabsContainer::clone() const {
        return std::make_shared<TabsContainer>(*this);
    }

    std::string TabsContainer::getWidgetType() const {
        return "TabsContainer";
    }

    TabsContainer::~TabsContainer() = default;
}

