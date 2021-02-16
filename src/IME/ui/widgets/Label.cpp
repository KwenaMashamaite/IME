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

#include "IME/ui/widgets/Label.h"
#include "WidgetImpl.h"
#include <TGUI/Widgets/Label.hpp>

namespace ime::ui {
    //////////////////////////////////////////////////////////////////////////
    // Label implementation
    //////////////////////////////////////////////////////////////////////////
    class Label::LabelImpl {
    public:
        LabelImpl(std::shared_ptr<tgui::Widget> widget) :
            label_{std::static_pointer_cast<tgui::Label>(widget)}
        {}

        void setText(const std::string &text) {
            label_->setText(text);
        }

        std::string getText() const {
            return label_->getText().toStdString();
        }

        void setHorizontalAlignment(HorizontalAlignment alignment) {
            label_->setHorizontalAlignment(static_cast<tgui::Label::HorizontalAlignment>(alignment));
        }

        HorizontalAlignment getHorizontalAlignment() const {
            return static_cast<HorizontalAlignment>(label_->getHorizontalAlignment());
        }

        void setVerticalAlignment(VerticalAlignment alignment) {
            label_->setVerticalAlignment(static_cast<tgui::Label::VerticalAlignment>(alignment));
        }

        VerticalAlignment getVerticalAlignment() const {
            return static_cast<VerticalAlignment>(label_->getVerticalAlignment());
        }

        void setAutoSize(bool autoSize) {
            label_->setAutoSize(autoSize);
        }

        bool getAutoSize() const {
            return label_->getAutoSize();
        }

        void setMaximumTextWidth(float maximumWidth) {
            label_->setMaximumTextWidth(maximumWidth);
        }

        float getMaximumTextWidth() const {
            return label_->getMaximumTextWidth();
        }

    private:
        std::shared_ptr<tgui::Label> label_;
    }; // class LabelImpl

    //////////////////////////////////////////////////////////////////////////
    // Label delegation
    //////////////////////////////////////////////////////////////////////////
    Label::Label(const std::string &text) :
        Widget(std::make_unique<priv::WidgetImpl<tgui::Label>>(tgui::Label::create(text))),
        pimpl_{std::make_unique<LabelImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()))}
    {
        setRenderer(std::make_shared<LabelRenderer>());
    }

    Label::sharedPtr Label::create(const std::string &text) {
        return Label::sharedPtr(new Label(text));
    }

    Label::sharedPtr Label::copy(Label::constSharedPtr other, bool shareRenderer) {
        auto widget = create();
        /*widget->label_ = widget->label_->copy(other->label_);

        if (!shareRenderer)
            widget->label_->setRenderer(other->label_->getRenderer()->clone());
        widget->renderer_->setInternalPtr(other->label_->getRenderer());*/

        return widget;
    }

    std::shared_ptr<LabelRenderer> Label::getRenderer() {
        return std::static_pointer_cast<LabelRenderer>(Widget::getRenderer());
    }

    const std::shared_ptr<LabelRenderer> Label::getRenderer() const {
        return std::static_pointer_cast<LabelRenderer>(Widget::getRenderer());
    }

    void Label::setText(const std::string &text) {
        pimpl_->setText(text);
    }

    std::string Label::getText() const {
        return pimpl_->getText();
    }

    void Label::setHorizontalAlignment(HorizontalAlignment alignment) {
        pimpl_->setHorizontalAlignment(alignment);
    }

    Label::HorizontalAlignment Label::getHorizontalAlignment() const {
        return pimpl_->getHorizontalAlignment();
    }

    void Label::setVerticalAlignment(VerticalAlignment alignment) {
        pimpl_->setVerticalAlignment(alignment);
    }

    Label::VerticalAlignment Label::getVerticalAlignment() const {
        return pimpl_->getVerticalAlignment();
    }

    void Label::setAutoSize(bool autoSize) {
        pimpl_->setAutoSize(autoSize);
    }

    bool Label::getAutoSize() const {
        return pimpl_->getAutoSize();
    }

    void Label::setMaximumTextWidth(float maximumWidth) {
        pimpl_->setMaximumTextWidth(maximumWidth);
    }

    float Label::getMaximumTextWidth() const {
        return pimpl_->getMaximumTextWidth();
    }

    std::string Label::getWidgetType() const {
        return "Label";
    }
}