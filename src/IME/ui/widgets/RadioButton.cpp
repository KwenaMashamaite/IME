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
    class RadioButton::ButtonImpl {
    public:
        explicit ButtonImpl(const std::shared_ptr<tgui::Widget>& widget) :
            button_{std::static_pointer_cast<tgui::RadioButton>(widget)}
        {}

        std::shared_ptr<tgui::RadioButton> button_;
    }; // class ButtonImpl

    ////////////////////////////////////////////////////////////////////////////

    RadioButton::RadioButton(const std::string &buttonText) :
        ClickableWidget(std::make_unique<priv::WidgetImpl<tgui::RadioButton>>(tgui::RadioButton::create())),
        pimpl_{std::make_unique<ButtonImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()))}
    {
        setRenderer(std::make_shared<RadioButtonRenderer>());
        pimpl_->button_->setText(buttonText);

        pimpl_->button_->onCheck([this]{
            emit("check");
        });

        pimpl_->button_->onUncheck([this]{
            emit("uncheck");
        });

        pimpl_->button_->onChange([this](bool checked) {
            emit("checkedChanged", checked);
        });
    }

    RadioButton::RadioButton(const RadioButton& other) :
        ClickableWidget(other),
        pimpl_{std::make_unique<ButtonImpl>(*other.pimpl_)}
    {}

    RadioButton &RadioButton::operator=(const RadioButton& rhs) {
        if (this != &rhs) {
            pimpl_ = std::make_unique<ButtonImpl>(*rhs.pimpl_);
        }

        return *this;
    }

    RadioButton::RadioButton(RadioButton &&) noexcept = default;
    RadioButton &RadioButton::operator=(RadioButton &&) noexcept = default;

    RadioButton::Ptr RadioButton::create(const std::string &text) {
        return Ptr(new RadioButton(text));
    }

    RadioButton::Ptr RadioButton::copy() const {
        return std::static_pointer_cast<RadioButton>(clone());
    }

    std::shared_ptr<RadioButtonRenderer> RadioButton::getRenderer() {
        return std::static_pointer_cast<RadioButtonRenderer>(Widget::getRenderer());
    }

    const std::shared_ptr<RadioButtonRenderer> RadioButton::getRenderer() const {
        return std::static_pointer_cast<RadioButtonRenderer>(Widget::getRenderer());
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
        return std::make_shared<RadioButton>(*this);

    }

    std::string RadioButton::getWidgetType() const {
        return "RadioButton";
    }

    RadioButton::~RadioButton() = default;
}
