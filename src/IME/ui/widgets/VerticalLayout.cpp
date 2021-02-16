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

#include "IME/ui/widgets/VerticalLayout.h"
#include "../../utility/Helpers.h"
#include "WidgetImpl.h"
#include <TGUI/Widgets/VerticalLayout.hpp>

namespace ime::ui {
    class VerticalLayout::Impl {
    public:
        Impl(std::shared_ptr<tgui::Widget> widget) :
            layout_{std::static_pointer_cast<tgui::VerticalLayout>(widget)}
        {}

        std::shared_ptr<tgui::VerticalLayout> layout_;
    };

    ////////////////////////////////////////////////////////////////////////////

    VerticalLayout::VerticalLayout(const std::string& width, const std::string& height) :
        IBoxLayout(std::make_unique<priv::WidgetImpl<tgui::VerticalLayout>>(tgui::VerticalLayout::create({width.c_str(), height.c_str()}))),
        pimpl_{std::make_unique<Impl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()))}
    {
        setRenderer(std::make_shared<BoxLayoutRenderer>());
        setAsContainer(true);
    }

    VerticalLayout::VerticalLayout(VerticalLayout &&) = default;

    VerticalLayout &VerticalLayout::operator=(VerticalLayout &&) = default;

    VerticalLayout::sharedPtr VerticalLayout::create(const std::string& width, const std::string& height)
    {
        return sharedPtr(new VerticalLayout(width, height));
    }

    VerticalLayout::sharedPtr VerticalLayout::copy(
            VerticalLayout::constSharedPtr other, bool shareRenderer)
    {
        auto widget = create();
        return widget;
    }

    std::string VerticalLayout::getWidgetType() const {
        return "HorizontalLayout";
    }

    void VerticalLayout::insertWidget(std::size_t index, std::shared_ptr<Widget> widget,
        const std::string &name)
    {
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

    bool VerticalLayout::setRatio(std::shared_ptr<Widget> widget, float ratio) {
        return pimpl_->layout_->setRatio(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr()), ratio);
    }

    bool VerticalLayout::setRatio(std::size_t index, float ratio) {
        return pimpl_->layout_->setRatio(index, ratio);
    }

    float VerticalLayout::getRatio(std::shared_ptr<Widget> widget) const {
        return pimpl_->layout_->getRatio(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr()));
    }

    float VerticalLayout::getRatio(std::size_t index) const {
        return pimpl_->layout_->getRatio(index);
    }

    VerticalLayout::~VerticalLayout() = default;
}
