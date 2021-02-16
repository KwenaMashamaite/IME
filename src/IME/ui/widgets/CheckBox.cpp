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

#include "IME/ui/widgets/CheckBox.h"
#include "WidgetImpl.h"
#include <TGUI/Widgets/CheckBox.hpp>

namespace ime::ui {
    class CheckBox::Impl {
    public:
        Impl(std::shared_ptr<tgui::Widget> widget) :
            checkbox_{std::static_pointer_cast<tgui::CheckBox>(widget)}
        {}
        
        std::shared_ptr<tgui::CheckBox> checkbox_;
    }; // class Impl


////////////////////////////////////////////////////////////////////////////////
    CheckBox::CheckBox(const std::string &text) :
        ClickableWidget(std::make_unique<priv::WidgetImpl<tgui::CheckBox>>(tgui::CheckBox::create(text))),
        pimpl_{std::make_unique<Impl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()))}
    {
        setRenderer(std::make_shared<CheckBoxRenderer>());
    }

    CheckBox::CheckBox(CheckBox &&) = default;

    CheckBox &CheckBox::operator=(CheckBox &&) = default;

    CheckBox::sharedPtr CheckBox::create(const std::string &text) {
        return CheckBox::sharedPtr(new  CheckBox(text));
    }

    CheckBox::sharedPtr CheckBox::copy(CheckBox::constSharedPtr other, bool shareRenderer) {
        auto widget = create();
        return widget;
    }

    std::shared_ptr<CheckBoxRenderer> CheckBox::getRenderer() {
        return std::static_pointer_cast<CheckBoxRenderer>(Widget::getRenderer());
    }

    const CheckBoxRenderer::sharedPtr CheckBox::getRenderer() const {
        return std::static_pointer_cast<CheckBoxRenderer>(Widget::getRenderer());
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

    std::string CheckBox::getWidgetType() const {
        return "CheckBox";
    }

    CheckBox::~CheckBox() = default;
}