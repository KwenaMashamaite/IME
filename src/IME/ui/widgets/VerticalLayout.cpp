////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

#include "IME/ui/widgets/VerticalLayout.h"
#include "IME/utility/Helpers.h"
#include "IME/ui/widgets/WidgetImpl.h"
#include <TGUI/Widgets/VerticalLayout.hpp>

namespace ime::ui {
    static unsigned int count = 1; // Keeps track of how many widgets of this type have been instantiated

    class VerticalLayout::VerticalLayoutImpl {
    public:
        explicit VerticalLayoutImpl(tgui::Widget* widget) :
            layout_{static_cast<tgui::VerticalLayout*>(widget)}
        {}

        tgui::VerticalLayout* layout_;
    };

    ////////////////////////////////////////////////////////////////////////////

    VerticalLayout::VerticalLayout(const std::string& width, const std::string& height) :
        IBoxLayout(std::make_unique<priv::WidgetImpl<tgui::VerticalLayout>>(tgui::VerticalLayout::create({width.c_str(), height.c_str()}))),
        pimpl_{std::make_unique<VerticalLayoutImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("VerticalLayout" + std::to_string(count++));
        setRenderer(std::make_unique<BoxLayoutRenderer>());
        setAsContainer(true);
    }

    VerticalLayout::VerticalLayout(const VerticalLayout& other) :
        IBoxLayout(other),
        pimpl_{std::make_unique<VerticalLayoutImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("VerticalLayout" + std::to_string(count++));
    }

    VerticalLayout &VerticalLayout::operator=(const VerticalLayout& rhs) {
        if (this != &rhs) {
            IBoxLayout::operator=(rhs);
            pimpl_ = std::make_unique<VerticalLayoutImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get());
        }

        return *this;
    }

    VerticalLayout::VerticalLayout(VerticalLayout&&) noexcept = default;
    VerticalLayout &VerticalLayout::operator=(VerticalLayout&&) noexcept = default;

    VerticalLayout::Ptr VerticalLayout::create(const std::string& width, const std::string& height) {
        return VerticalLayout::Ptr(new VerticalLayout(width, height));
    }

    VerticalLayout::Ptr VerticalLayout::copy() const {
        return VerticalLayout::Ptr(static_cast<VerticalLayout*>(clone().release()));
    }

    BoxLayoutRenderer* VerticalLayout::getRenderer() {
        return static_cast<BoxLayoutRenderer*>(Widget::getRenderer());
    }

    const BoxLayoutRenderer* VerticalLayout::getRenderer() const {
        return static_cast<const BoxLayoutRenderer*>(Widget::getRenderer());
    }

    std::string VerticalLayout::getWidgetType() const {
        return "HorizontalLayout";
    }

    void VerticalLayout::insertWidget(std::size_t index, Widget* widget, const std::string &name) {
        pimpl_->layout_->insert(index, std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr()), name);
    }

    bool VerticalLayout::removeWidgetAt(std::size_t index) {
        return pimpl_->layout_->remove(index);
    }

    void VerticalLayout::addSpace(float ratio) {
        pimpl_->layout_->addSpace(ratio);
    }

    void VerticalLayout::insertSpace(std::size_t index, float ratio) {
        pimpl_->layout_->insertSpace(index, ratio);
    }

    bool VerticalLayout::setRatio(Widget* widget, float ratio) {
        return pimpl_->layout_->setRatio(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr()), ratio);
    }

    bool VerticalLayout::setRatio(std::size_t index, float ratio) {
        return pimpl_->layout_->setRatio(index, ratio);
    }

    float VerticalLayout::getRatio(const Widget* widget) const {
        return pimpl_->layout_->getRatio(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr()));
    }

    float VerticalLayout::getRatio(std::size_t index) const {
        return pimpl_->layout_->getRatio(index);
    }

    Widget::Ptr VerticalLayout::clone() const {
        return std::make_unique<VerticalLayout>(*this);
    }

    VerticalLayout::~VerticalLayout() = default;
}
