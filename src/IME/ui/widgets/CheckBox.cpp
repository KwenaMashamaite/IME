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

#include "IME/ui/widgets/CheckBox.h"
#include "IME/ui/widgets/WidgetImpl.h"
#include <TGUI/Widgets/CheckBox.hpp>

namespace ime::ui {
    static unsigned int count = 1; // Keeps track of how many widgets of this type have been instantiated

    class CheckBox::CheckBoxImpl {
    public:
        explicit CheckBoxImpl(tgui::Widget* widget) :
            checkbox_{static_cast<tgui::CheckBox*>(widget)}
        {}
        
        tgui::CheckBox* checkbox_;
    }; // class WidgetContainerImpl


    ////////////////////////////////////////////////////////////////////////////
    CheckBox::CheckBox(const std::string &text) :
        ClickableWidget(std::make_unique<priv::WidgetImpl<tgui::CheckBox>>(tgui::CheckBox::create(text))),
        pimpl_{std::make_unique<CheckBoxImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("Checkbox" + std::to_string(count++));
        setRenderer(std::make_unique<CheckBoxRenderer>());
        initEvents();
    }

    CheckBox::CheckBox(const CheckBox& other) :
        ClickableWidget(other),
        pimpl_{std::make_unique<CheckBoxImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("Checkbox" + std::to_string(count++));
        initEvents();
    }

    CheckBox &CheckBox::operator=(const CheckBox& rhs) {
        if (this != &rhs) {
            ClickableWidget::operator=(rhs);
            pimpl_ = std::make_unique<CheckBoxImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get());
            initEvents();
        }

        return *this;
    }

    CheckBox::CheckBox(CheckBox &&) noexcept = default;
    CheckBox &CheckBox::operator=(CheckBox &&) noexcept = default;

    CheckBox::Ptr CheckBox::create(const std::string &text) {
        return CheckBox::Ptr(new  CheckBox(text));
    }

    CheckBox::Ptr CheckBox::copy() const {
        return CheckBox::Ptr(static_cast<CheckBox*>(clone().release()));
    }

    CheckBoxRenderer* CheckBox::getRenderer() {
        return static_cast<CheckBoxRenderer*>(Widget::getRenderer());
    }

    const CheckBoxRenderer* CheckBox::getRenderer() const {
        return static_cast<const CheckBoxRenderer*>(Widget::getRenderer());
    }
    
    void CheckBox::setText(const std::string &content) {
        pimpl_->checkbox_->setText(content);
    }
    
    std::string CheckBox::getText() const {
        return pimpl_->checkbox_->getText().toStdString();
    }

    void CheckBox::setTextClickable(bool acceptTextClick) {
        pimpl_->checkbox_->setTextClickable(acceptTextClick);
    }

    bool CheckBox::isTextClickable() const {
        return pimpl_->checkbox_->isTextClickable();
    }

    void CheckBox::setChecked(bool isChecked) {
        pimpl_->checkbox_->setChecked(isChecked);
    }

    bool CheckBox::isChecked() const {
        return pimpl_->checkbox_->isChecked();
    }

    Widget::Ptr CheckBox::clone() const {
        return std::make_unique<CheckBox>(*this);
    }

    std::string CheckBox::getWidgetType() const {
        return "CheckBox";
    }

    void CheckBox::initEvents() {
        pimpl_->checkbox_->onCheck([this] {
            emit("check");
        });

        pimpl_->checkbox_->onUncheck([this] {
            emit("uncheck");
        });

        pimpl_->checkbox_->onChange([this](bool checked) {
            emit("valueChange", checked);
        });
    }

    CheckBox::~CheckBox() = default;
}