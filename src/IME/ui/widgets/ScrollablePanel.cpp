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
#include "IME/ui/widgets/WidgetImpl.h"
#include <TGUI/Widgets/ScrollablePanel.hpp>

namespace ime::ui {
    static unsigned int count = 1; // Keeps track of how many widgets of this type have been instantiated

    class ScrollablePanel::PanelImpl {
    public:
        explicit PanelImpl(tgui::Widget* widget) :
           panel_{static_cast<tgui::ScrollablePanel*>(widget)}
        {}

        tgui::ScrollablePanel* panel_;
    };

    ////////////////////////////////////////////////////////////////////////////

    ScrollablePanel::ScrollablePanel(const std::string &width, const std::string &height, Vector2f contentSize) :
        WidgetContainer(std::make_unique<priv::WidgetImpl<tgui::ScrollablePanel>>(tgui::ScrollablePanel::create({width.c_str(), height.c_str()}, {contentSize.x, contentSize.y}))),
        pimpl_{std::make_unique<PanelImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("ScrollablePanel" + std::to_string(count++));
        setRenderer(std::make_unique<ScrollablePanelRenderer>());
        setAsContainer(true);
        initEvents();
    }

    ScrollablePanel::ScrollablePanel(const ScrollablePanel& other) :
        WidgetContainer(other),
        pimpl_{std::make_unique<PanelImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("ScrollablePanel" + std::to_string(count++));
        initEvents();
    }

    ScrollablePanel &ScrollablePanel::operator=(const ScrollablePanel& rhs) {
        if (this != &rhs) {
            WidgetContainer::operator=(rhs);
            pimpl_ = std::make_unique<PanelImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get());
            initEvents();
        }

        return *this;
    }

    ScrollablePanel::ScrollablePanel(ScrollablePanel&& other) noexcept :
        WidgetContainer(std::move(other))
    {
        *this = std::move(other);
    }

    ScrollablePanel &ScrollablePanel::operator=(ScrollablePanel&& rhs) noexcept {
        if (this != &rhs) {
            pimpl_ = std::move(rhs.pimpl_);
            initEvents();
        }

        return *this;
    }

    ScrollablePanel::Ptr ScrollablePanel::create(const std::string &width,
        const std::string &height, Vector2f contentSize)
    {
        return Ptr(new ScrollablePanel(width, height, contentSize));
    }

    ScrollablePanel::Ptr ScrollablePanel::copy() const {
        return ScrollablePanel::Ptr(static_cast<ScrollablePanel*>(clone().release()));
    }

    ScrollablePanelRenderer* ScrollablePanel::getRenderer() {
        return static_cast<ScrollablePanelRenderer*>(Widget::getRenderer());
    }

    const ScrollablePanelRenderer* ScrollablePanel::getRenderer() const {
        return static_cast<const ScrollablePanelRenderer*>(Widget::getRenderer());
    }

    void ScrollablePanel::setContentSize(Vector2f size) {
       pimpl_->panel_->setContentSize({size.x, size.y});
    }

    Vector2f ScrollablePanel::getContentSize() const {
        return {pimpl_->panel_->getSize().x, pimpl_->panel_->getSize().y};
    }

    Vector2f ScrollablePanel::getContentOffset() const {
        return {pimpl_->panel_->getContentOffset().x, pimpl_->panel_->getContentOffset().y};
    }

    float ScrollablePanel::getScrollbarWidth() const {
        return pimpl_->panel_->getScrollbarWidth();
    }

    void ScrollablePanel::setVerticalScrollStep(unsigned int step) {
       pimpl_->panel_->setVerticalScrollAmount(step);
    }

    unsigned int ScrollablePanel::getVerticalScrollStep() const {
        return pimpl_->panel_->getVerticalScrollAmount();
    }

    void ScrollablePanel::setHorizontalScrollStep(unsigned int step) {
       pimpl_->panel_->setHorizontalScrollAmount(step);
    }

    unsigned int ScrollablePanel::getHorizontalScrollStep() const {
        return pimpl_->panel_->getHorizontalScrollAmount();
    }

    void ScrollablePanel::setVerticalThumbValue(unsigned int value) {
       pimpl_->panel_->setVerticalScrollbarValue(value);
    }

    unsigned int ScrollablePanel::getVerticalThumbValue() const {
        return pimpl_->panel_->getVerticalScrollbarValue();
    }

    void ScrollablePanel::setHorizontalThumbValue(unsigned int value) {
       pimpl_->panel_->setHorizontalScrollbarValue(value);
    }

    unsigned int ScrollablePanel::getHorizontalThumbValue() const {
        return pimpl_->panel_->getHorizontalScrollbarValue();
    }

    Widget::Ptr ScrollablePanel::clone() const {
        return std::make_unique<ScrollablePanel>(*this);
    }

    std::string ScrollablePanel::getWidgetType() const {
        return "ScrollablePanel";
    }

    void ScrollablePanel::initEvents() {
        pimpl_->panel_->onDoubleClick([this](tgui::Vector2f mousePos) {
            emit("doubleClick");
            emit("doubleClick", mousePos.x, mousePos.y);
        });
    }

    ScrollablePanel::~ScrollablePanel() = default;
}
