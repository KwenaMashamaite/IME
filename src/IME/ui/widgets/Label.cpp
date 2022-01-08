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

#include "IME/ui/widgets/Label.h"
#include "IME/ui/widgets/WidgetImpl.h"
#include <TGUI/Widgets/Label.hpp>

namespace ime::ui {
    static unsigned int count = 1; // Keeps track of how many widgets of this type have been instantiated

    //////////////////////////////////////////////////////////////////////////
    // Label implementation
    //////////////////////////////////////////////////////////////////////////
    class Label::LabelImpl {
    public:
        explicit LabelImpl(tgui::Widget* widget) :
            label_{static_cast<tgui::Label*>(widget)}
        {}

        /// The shallow copy is intentional because the implementation and the
        /// base class must operate on the same third party widget. @param other
        /// is a copied version of the argument passed to the copy constructor
        /// of ime::Label, therefore no additional copies are required
        LabelImpl(const LabelImpl& other) :
            label_{static_cast<tgui::Label*>(other.label_)}
        {}

        LabelImpl& operator=(const LabelImpl& rhs) {
            if (this == &rhs) {
                label_ = rhs.label_;
            }

            return *this;
        }

        LabelImpl(LabelImpl&&) noexcept = default;
        LabelImpl& operator=(LabelImpl&&) noexcept = default;

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
        tgui::Label* label_;
    }; // class LabelImpl

    //////////////////////////////////////////////////////////////////////////
    // Label class delegation
    //////////////////////////////////////////////////////////////////////////
    Label::Label(const std::string &text) :
        Widget(std::make_unique<priv::WidgetImpl<tgui::Label>>(tgui::Label::create(text))),
        pimpl_{std::make_unique<LabelImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("Label" + std::to_string(count++));
        setRenderer(std::make_unique<LabelRenderer>());
    }

    Label::Label(const Label& other) :
        Widget(other),
        pimpl_{std::make_unique<LabelImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("Label" + std::to_string(count++));
    }

    Label &Label::operator=(const Label& rhs) {
        if (this != &rhs) {
            Widget::operator=(rhs);
            pimpl_ = std::make_unique<LabelImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get());
        }

        return *this;
    }

    Label::Label(Label &&) noexcept = default;
    Label &Label::operator=(Label &&) noexcept = default;

    Label::Ptr Label::create(const std::string &text) {
        return Label::Ptr(new Label(text));
    }

    Label::Ptr Label::copy() const {
        return Label::Ptr(static_cast<Label*>(clone().release()));
    }

    LabelRenderer* Label::getRenderer() {
        return static_cast<LabelRenderer*>(Widget::getRenderer());
    }

    const LabelRenderer* Label::getRenderer() const {
        return static_cast<const LabelRenderer*>(Widget::getRenderer());
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

    Widget::Ptr Label::clone() const {
        return std::make_unique<Label>(*this);
    }

    std::string Label::getWidgetType() const {
        return "Label";
    }

    Label::~Label() = default;
}