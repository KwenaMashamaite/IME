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

#include "IME/ui/widgets/HorizontalLayout.h"
#include "IME/utility/Helpers.h"
#include "IME/ui/widgets/WidgetImpl.h"
#include <TGUI/Widgets/HorizontalLayout.hpp>

namespace ime::ui {
    class HorizontalLayout::HorizontalLayoutImpl {
    public:
        explicit HorizontalLayoutImpl(tgui::Widget* widget) :
            layout_{static_cast<tgui::HorizontalLayout*>(widget)}
        {}

        tgui::HorizontalLayout* layout_;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    
    HorizontalLayout::HorizontalLayout(const std::string& width, const std::string& height) :
        IBoxLayout(std::make_unique<priv::WidgetImpl<tgui::HorizontalLayout>>(tgui::HorizontalLayout::create({width.c_str(), height.c_str()}))),
        pimpl_{std::make_unique<HorizontalLayoutImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setRenderer(std::make_unique<BoxLayoutRenderer>());
        setAsContainer(true);
    }

    HorizontalLayout::HorizontalLayout(const HorizontalLayout& other) :
        IBoxLayout(other),
        pimpl_{std::make_unique<HorizontalLayoutImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {}

    HorizontalLayout &HorizontalLayout::operator=(const HorizontalLayout& rhs) {
        if (this != &rhs) {
            IBoxLayout::operator=(rhs);
            pimpl_ = std::make_unique<HorizontalLayoutImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get());
        }

        return *this;
    }

    HorizontalLayout::HorizontalLayout(HorizontalLayout &&) noexcept = default;
    HorizontalLayout &HorizontalLayout::operator=(HorizontalLayout &&) noexcept = default;

    HorizontalLayout::Ptr HorizontalLayout::create(const std::string& width,
        const std::string& height)
    {
        return Ptr(new HorizontalLayout(width, height));
    }

    HorizontalLayout::Ptr HorizontalLayout::copy() const {
        return HorizontalLayout::Ptr(static_cast<HorizontalLayout*>(clone().release()));
    }

    Widget::Ptr HorizontalLayout::clone() const {
        return std::make_unique<HorizontalLayout>(*this);
    }

    std::string HorizontalLayout::getWidgetType() const {
        return "HorizontalLayout";
    }

    BoxLayoutRenderer* HorizontalLayout::getRenderer() {
        return static_cast<BoxLayoutRenderer*>(Widget::getRenderer());
    }

    const BoxLayoutRenderer* HorizontalLayout::getRenderer() const {
        return static_cast<const BoxLayoutRenderer*>(Widget::getRenderer());
    }

    void HorizontalLayout::insertWidget(std::size_t index, Widget* widget, const std::string &name) {
        pimpl_->layout_->insert(index, std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr()), name);
    }

    bool HorizontalLayout::removeWidgetAt(std::size_t index) {
        return pimpl_->layout_->remove(index);
    }

    void HorizontalLayout::addSpace(float ratio) {
       pimpl_->layout_->addSpace(ratio);
    }

    void HorizontalLayout::insertSpace(std::size_t index, float ratio) {
        pimpl_->layout_->insertSpace(index, ratio);
    }

    bool HorizontalLayout::setRatio(Widget* widget, float ratio) {
        return pimpl_->layout_->setRatio(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr()), ratio);
    }

    bool HorizontalLayout::setRatio(std::size_t index, float ratio) {
        return pimpl_->layout_->setRatio(index, ratio);
    }

    float HorizontalLayout::getRatio(const Widget* widget) const {
        return pimpl_->layout_->getRatio(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr()));
    }

    float HorizontalLayout::getRatio(std::size_t index) const {
        return pimpl_->layout_->getRatio(index);
    }

    HorizontalLayout::~HorizontalLayout() = default;
}