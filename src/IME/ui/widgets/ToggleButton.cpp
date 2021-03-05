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

#include "IME/ui/widgets/ToggleButton.h"
#include "WidgetImpl.h"
#include <TGUI/Widgets/ToggleButton.hpp>

namespace ime::ui {
    //////////////////////////////////////////////////////////////////////////
    // Button implementation
    //////////////////////////////////////////////////////////////////////////
    class ToggleButton::ButtonImpl {
    public:
        ButtonImpl(std::shared_ptr<tgui::Widget> widget) :
            button_{std::static_pointer_cast<tgui::ToggleButton>(widget)}
        {}

        void setText(const std::string &text) {
            button_->setText(text);
        }

        std::string getText() const {
            return button_->getText().toStdString();
        }

        void setChecked(bool checked) {
            button_->setDown(checked);
        }

        bool isChecked() const {
            return button_->isDown();
        }

        std::shared_ptr<tgui::ToggleButton> getPtr() {
            return button_;
        }

    private:
        std::shared_ptr<tgui::ToggleButton> button_;
    };

    //////////////////////////////////////////////////////////////////////////
    // Button delegation
    //////////////////////////////////////////////////////////////////////////
    ToggleButton::ToggleButton(const std::string &buttonText, bool checked) :
        ClickableWidget(std::make_unique<priv::WidgetImpl<tgui::ToggleButton>>(tgui::ToggleButton::create(buttonText, checked))),
        pimpl_{std::make_unique<ButtonImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()))}
    {
        setRenderer(std::make_shared<ButtonRenderer>());

        pimpl_->getPtr()->onToggle([this](bool checkedStatus) {
            emit("toggle");
            emit("toggle", checkedStatus);
        });
    }

    ToggleButton::ToggleButton(const ToggleButton& other) :
        ClickableWidget(other),
        pimpl_{std::make_unique<ButtonImpl>(*other.pimpl_)}
    {}

    ToggleButton &ToggleButton::operator=(const ToggleButton& rhs) {
        if (this != &rhs) {
            pimpl_ = std::make_unique<ButtonImpl>(*rhs.pimpl_);
        }

        return *this;
    }

    ToggleButton::ToggleButton(ToggleButton &&) noexcept = default;
    ToggleButton &ToggleButton::operator=(ToggleButton &&) noexcept = default;

    ToggleButton::Ptr ToggleButton::create(const std::string &text, bool checked) {
        return ToggleButton::Ptr(new ToggleButton(text, checked));
    }

    ToggleButton::Ptr ToggleButton::copy() {
        return std::static_pointer_cast<ToggleButton>(clone());
    }

    std::shared_ptr<ButtonRenderer> ToggleButton::getRenderer() {
        return std::static_pointer_cast<ButtonRenderer>(Widget::getRenderer());
    }

    const ButtonRenderer::Ptr ToggleButton::getRenderer() const {
        return std::static_pointer_cast<ButtonRenderer>(Widget::getRenderer());
    }

    void ToggleButton::setText(const std::string &text) {
        pimpl_->setText(text);
    }

    std::string ToggleButton::getText() const {
        return pimpl_->getText();
    }

    void ToggleButton::setChecked(bool checked) {
        pimpl_->setChecked(checked);
    }

    bool ToggleButton::isChecked() const {
        return pimpl_->isChecked();
    }

    Widget::Ptr ToggleButton::clone() const {
        return std::make_shared<ToggleButton>(*this);
    }

    std::string ToggleButton::getWidgetType() const {
        return "ToggleButton";
    }

    ToggleButton::~ToggleButton() = default;
}
