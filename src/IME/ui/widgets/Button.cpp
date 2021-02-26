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

#include "IME/ui/widgets/Button.h"
#include "WidgetImpl.h"
#include <TGUI/Widgets/Button.hpp>

namespace ime::ui {
    //////////////////////////////////////////////////////////////////////////
    // Button implementation
    //////////////////////////////////////////////////////////////////////////
    class Button::ButtonImpl {
    public:
        ButtonImpl(std::shared_ptr<tgui::Widget> widget) :
            button_{std::static_pointer_cast<tgui::Button>(widget)}
        {}

        static Button::Ptr copy(Button::ConstPtr other, bool shareRenderer) {
            auto widget = create("");
            /*pimpl_->button_ = tgui::Button::copy(other->pimpl_->button_);

            if (!shareRenderer)
                ->setRenderer(other->pimpl_->widget_->getRenderer()->clone());
            widget->pimpl_->renderer_->setInternalPtr(other->pimpl_->widget_->getRenderer());*/

            return widget;
        }

        void setText(const std::string &text) {
            button_->setText(text);
        }

        std::string getText() const {
            return button_->getText().toStdString();
        }

    private:
        std::shared_ptr<tgui::Button> button_;
    };

    //////////////////////////////////////////////////////////////////////////
    // Button delegation
    //////////////////////////////////////////////////////////////////////////
    Button::Button(const std::string &buttonText) :
        ClickableWidget(std::make_unique<priv::WidgetImpl<tgui::Button>>(tgui::Button::create(buttonText))),
        pimpl_{std::make_unique<ButtonImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()))}
    {
        setRenderer(std::make_shared<ButtonRenderer>());
    }

    Button::Button(Button &&) = default;

    Button &Button::operator=(Button &&) = default;

    Button::Ptr Button::create(const std::string &text) {
        return Button::Ptr(new Button(text));
    }

    Button::Ptr Button::copy(Button::ConstPtr other, bool shareRenderer) {
        return ButtonImpl::copy(other, shareRenderer);
    }

    std::shared_ptr<ButtonRenderer> Button::getRenderer() {
        return std::static_pointer_cast<ButtonRenderer>(Widget::getRenderer());
    }

    const ButtonRenderer::Ptr Button::getRenderer() const {
        return std::static_pointer_cast<ButtonRenderer>(Widget::getRenderer());
    }

    void Button::setText(const std::string &text) {
        pimpl_->setText(text);
    }

    std::string Button::getText() const {
        return pimpl_->getText();
    }

    std::string Button::getWidgetType() const {
        return "Button";
    }

    Button::~Button() = default;
}
