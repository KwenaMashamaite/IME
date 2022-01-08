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

#include "IME/ui/widgets/ProgressBar.h"
#include "IME/ui/widgets/WidgetImpl.h"
#include <TGUI/Widgets/ProgressBar.hpp>

namespace ime::ui {
    static unsigned int count = 1; // Keeps track of how many widgets of this type have been instantiated

    class ProgressBar::ProgressBarImpl {
    public:
        explicit ProgressBarImpl(tgui::Widget* widget) :
            progressBar_{static_cast<tgui::ProgressBar*>(widget)}
        {}

        tgui::ProgressBar* progressBar_;
    };

    ////////////////////////////////////////////////////////////////////////////
    
    ProgressBar::ProgressBar(const std::string& text) :
        ClickableWidget(std::make_unique<priv::WidgetImpl<tgui::ProgressBar>>(tgui::ProgressBar::create())),
        pimpl_{std::make_unique<ProgressBarImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("ProgressBar" + std::to_string(count++));
        setRenderer(std::make_unique<ProgressBarRenderer>());
        pimpl_->progressBar_->setText(text);
        initEvents();
    }

    ProgressBar::ProgressBar(const ProgressBar& other) :
        ClickableWidget(other),
        pimpl_{std::make_unique<ProgressBarImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("ProgressBar" + std::to_string(count++));
        initEvents();
    }

    ProgressBar &ProgressBar::operator=(const ProgressBar& rhs) {
        if (this != &rhs) {
            ClickableWidget::operator=(rhs);
            pimpl_ = std::make_unique<ProgressBarImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get());
            initEvents();
        }

        return *this;
    }

    ProgressBar::ProgressBar(ProgressBar&& other) noexcept = default;
    ProgressBar &ProgressBar::operator=(ProgressBar&& rhs) noexcept = default;

    ProgressBar::Ptr ProgressBar::create(const std::string& text) {
        return Ptr(new ProgressBar(text));
    }

    ProgressBar::Ptr ProgressBar::copy() const {
        return ProgressBar::Ptr(static_cast<ProgressBar*>(clone().release()));
    }

    ProgressBarRenderer* ProgressBar::getRenderer() {
        return static_cast<ProgressBarRenderer*>(Widget::getRenderer());
    }

    const ProgressBarRenderer* ProgressBar::getRenderer() const {
        return static_cast<const ProgressBarRenderer*>(Widget::getRenderer());
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

    Widget::Ptr ProgressBar::clone() const {
        return std::make_unique<ProgressBar>(*this);
    }

    std::string ProgressBar::getWidgetType() const {
        return "ProgressBar";
    }

    void ProgressBar::initEvents() {
        pimpl_->progressBar_->onValueChange([this](unsigned int value) {
            emit("valueChange", value);
        });

        pimpl_->progressBar_->onFull([this] {
            emit("full");
        });
    }

    ProgressBar::~ProgressBar() = default;
}