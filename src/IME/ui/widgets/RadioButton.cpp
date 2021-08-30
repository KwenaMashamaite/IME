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

#include "IME/ui/widgets/RadioButton.h"
#include "IME/ui/widgets/WidgetImpl.h"
#include <TGUI/Widgets/RadioButton.hpp>

namespace ime::ui {
    static unsigned int count = 1; // Keeps track of how many widgets of this type have been instantiated

    class RadioButton::ButtonImpl {
    public:
        explicit ButtonImpl(tgui::Widget* widget) :
            button_{static_cast<tgui::RadioButton*>(widget)}
        {}

        tgui::RadioButton* button_;
    }; // class ButtonImpl

    ////////////////////////////////////////////////////////////////////////////

    RadioButton::RadioButton(const std::string &buttonText) :
        ClickableWidget(std::make_unique<priv::WidgetImpl<tgui::RadioButton>>(tgui::RadioButton::create())),
        pimpl_{std::make_unique<ButtonImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("RadioButton" + std::to_string(count++));
        setRenderer(std::make_unique<RadioButtonRenderer>());
        pimpl_->button_->setText(buttonText);
        initEvents();
    }

    RadioButton::RadioButton(const RadioButton& other) :
        ClickableWidget(other),
        pimpl_{std::make_unique<ButtonImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("RadioButton" + std::to_string(count++));
        initEvents();
    }

    RadioButton &RadioButton::operator=(const RadioButton& rhs) {
        if (this != &rhs) {
            ClickableWidget::operator=(rhs);
            pimpl_ = std::make_unique<ButtonImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get());
            initEvents();
        }

        return *this;
    }

    RadioButton::RadioButton(RadioButton&& other) noexcept = default;
    RadioButton &RadioButton::operator=(RadioButton&& rhs) noexcept = default;

    RadioButton::Ptr RadioButton::create(const std::string &text) {
        return Ptr(new RadioButton(text));
    }

    RadioButton::Ptr RadioButton::copy() const {
        return RadioButton::Ptr(static_cast<RadioButton*>(clone().release()));
    }

    RadioButtonRenderer* RadioButton::getRenderer() {
        return static_cast<RadioButtonRenderer*>(Widget::getRenderer());
    }

    const RadioButtonRenderer* RadioButton::getRenderer() const {
        return static_cast<const RadioButtonRenderer*>(Widget::getRenderer());
    }

    void RadioButton::setTextClickable(bool acceptTextClick) {
        pimpl_->button_->setTextClickable(acceptTextClick);
    }

    bool RadioButton::isTextClickable() const {
        return pimpl_->button_->isTextClickable();
    }

    void RadioButton::setChecked(bool isChecked) {
        pimpl_->button_->setChecked(isChecked);
    }

    bool RadioButton::isChecked() const {
        return pimpl_->button_->isChecked();
    }

    void RadioButton::setText(const std::string &text) {
        pimpl_->button_->setText(text);
    }

    std::string RadioButton::getText() const {
        return pimpl_->button_->getText().toStdString();
    }

    Widget::Ptr RadioButton::clone() const {
        return std::make_unique<RadioButton>(*this);

    }

    std::string RadioButton::getWidgetType() const {
        return "RadioButton";
    }

    void RadioButton::initEvents() {
        pimpl_->button_->onCheck([this]{
            emit("check");
        });

        pimpl_->button_->onUncheck([this]{
            emit("uncheck");
        });

        pimpl_->button_->onChange([this](bool checked) {
            emit("valueChange", checked);
        });
    }

    RadioButton::~RadioButton() = default;
}
