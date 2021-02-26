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

#include "IME/ui/widgets/ProgressBar.h"
#include "WidgetImpl.h"
#include <TGUI/Widgets/ProgressBar.hpp>

namespace ime::ui {
    class ProgressBar::Impl {
    public:
        Impl(std::shared_ptr<tgui::Widget> widget) :
            progressBar_{std::static_pointer_cast<tgui::ProgressBar>(widget)}
        {}

        std::shared_ptr<tgui::ProgressBar> progressBar_;
    };

    ////////////////////////////////////////////////////////////////////////////
    
    ProgressBar::ProgressBar(const std::string& text) :
        ClickableWidget(std::make_unique<priv::WidgetImpl<tgui::ProgressBar>>(tgui::ProgressBar::create())),
        pimpl_{std::make_unique<Impl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()))}
    {
        setRenderer(std::make_shared<ProgressBarRenderer>());
        pimpl_->progressBar_->setText(text);

        pimpl_->progressBar_->onPositionChange([this](tgui::Vector2f newPos) {
            emit("positionChange", newPos.x, newPos.y);
        });
    }

    ProgressBar::ProgressBar(ProgressBar &&) = default;

    ProgressBar &ProgressBar::operator=(ProgressBar &&) = default;

    ProgressBar::Ptr ProgressBar::create(const std::string& text) {
        return Ptr(new ProgressBar(text));
    }

    ProgressBar::Ptr ProgressBar::copy(ProgressBar::ConstPtr other,
        bool shareRenderer)
    {
        auto widget = create();
        widget->pimpl_->progressBar_ = widget->pimpl_->progressBar_->copy(other->pimpl_->progressBar_);

        return widget;
    }

    std::shared_ptr<ProgressBarRenderer> ProgressBar::getRenderer() {
        return std::static_pointer_cast<ProgressBarRenderer>(Widget::getRenderer());
    }

    const std::shared_ptr<ProgressBarRenderer> ProgressBar::getRenderer() const {
        return std::static_pointer_cast<ProgressBarRenderer>(Widget::getRenderer());
    }

    void ProgressBar::setMinimumValue(unsigned int minValue) {
        pimpl_->progressBar_->setMinimum(minValue);
    }

    unsigned int ProgressBar::getMinimumValue() const {
        return pimpl_->progressBar_->getMinimum();
    }

    void ProgressBar::setMaximumValue(unsigned int maxValue) {
        pimpl_->progressBar_->setMaximum(maxValue);
    }

    unsigned int ProgressBar::getMaximumValue() const {
        return pimpl_->progressBar_->getMaximum();
    }

    void ProgressBar::setValue(unsigned int value) {
        pimpl_->progressBar_->setValue(value);
    }

    unsigned int ProgressBar::getValue() const {
        return pimpl_->progressBar_->getValue();
    }

    unsigned int ProgressBar::incrementValue() {
        return pimpl_->progressBar_->incrementValue();
    }

    void ProgressBar::setFillDirection(ProgressBar::FillDirection direction) {
        pimpl_->progressBar_->setFillDirection(
            static_cast<tgui::ProgressBar::FillDirection>(direction));
    }

    ProgressBar::FillDirection ProgressBar::getFillDirection() const {
        return static_cast<FillDirection>(pimpl_->progressBar_->getFillDirection());
    }

    void ProgressBar::setText(const std::string &content) {
        pimpl_->progressBar_->setText(content);
    }

    std::string ProgressBar::getText() const {
        return pimpl_->progressBar_->getText().toStdString();
    }

    std::string ProgressBar::getWidgetType() const {
        return "ProgressBar";
    }

    ProgressBar::~ProgressBar() = default;
}