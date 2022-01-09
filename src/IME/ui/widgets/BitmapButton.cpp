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

#include "IME/ui/widgets/BitmapButton.h"
#include "IME/core/resources/ResourceManager.h"
#include "IME/ui/widgets/WidgetImpl.h"
#include <TGUI/Widgets/BitmapButton.hpp>

namespace ime::ui {
    static unsigned int count = 1; // Keeps track of how many widgets of this type have been instantiated

    //////////////////////////////////////////////////////////////////////////
    // Button implementation
    //////////////////////////////////////////////////////////////////////////
    class BitmapButton::ButtonImpl {
    public:
        explicit ButtonImpl(tgui::Widget* widget) :
            button_{static_cast<tgui::BitmapButton*>(widget)}
        {}

        void setText(const std::string &text) {
            button_->setText(text);
        }

        std::string getText() const {
            return button_->getText().toStdString();
        }

        void setImage(const std::string &filename) {
            button_->setImage(ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture());
        }

        void setImageScaling(float relativeHeight) {
            button_->setImageScaling(relativeHeight);
        }

        float getImageScaling() const {
            return button_->getImageScaling();
        }

    private:
        tgui::BitmapButton* button_;
    }; // class bitmap button

    //////////////////////////////////////////////////////////////////////////
    // Button delegation
    //////////////////////////////////////////////////////////////////////////
    BitmapButton::BitmapButton(const std::string &buttonText) :
        ClickableWidget(std::make_unique<priv::WidgetImpl<tgui::BitmapButton>>(tgui::BitmapButton::create(buttonText))),
        pimpl_{std::make_unique<ButtonImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("BitmapButton" + std::to_string(count++));
        setRenderer(std::make_unique<ButtonRenderer>());
    }

    BitmapButton::BitmapButton(const BitmapButton& other) :
        ClickableWidget(other),
        pimpl_{std::make_unique<ButtonImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("BitmapButton" + std::to_string(count++));
    }

    BitmapButton &BitmapButton::operator=(const BitmapButton& rhs) {
        if (this != &rhs) {
            ClickableWidget::operator=(rhs);
            pimpl_ = std::make_unique<ButtonImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get());
        }

        return *this;
    }

    BitmapButton::BitmapButton(BitmapButton &&) noexcept = default;
    BitmapButton &BitmapButton::operator=(BitmapButton &&) noexcept = default;

    BitmapButton::Ptr BitmapButton::create(const std::string &text) {
        return BitmapButton::Ptr(new BitmapButton(text));
    }

    BitmapButton::Ptr BitmapButton::copy() const {
        return BitmapButton::Ptr(static_cast<BitmapButton*>(clone().release()));
    }

    ButtonRenderer* BitmapButton::getRenderer() {
        return static_cast<ButtonRenderer*>(Widget::getRenderer());
    }

    const ButtonRenderer* BitmapButton::getRenderer() const {
        return static_cast<const ButtonRenderer*>(Widget::getRenderer());
    }

    void BitmapButton::setText(const std::string &text) {
        pimpl_->setText(text);
    }

    std::string BitmapButton::getText() const {
        return pimpl_->getText();
    }

    void BitmapButton::setImage(const std::string &filename) {
        pimpl_->setImage(filename);
    }

    void BitmapButton::setImageScaling(float relativeHeight) {
        pimpl_->setImageScaling(relativeHeight);
    }

    float BitmapButton::getImageScaling() const {
        return pimpl_->getImageScaling();
    }

    Widget::Ptr BitmapButton::clone() const {
        return std::make_unique<BitmapButton>(*this);
    }

    std::string BitmapButton::getWidgetType() const {
        return "BitmapButton";
    }

    BitmapButton::~BitmapButton() = default;
}
