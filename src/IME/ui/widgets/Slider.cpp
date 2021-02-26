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

#include "IME/ui/widgets/Slider.h"
#include "WidgetImpl.h"
#include <TGUI/Widgets/Slider.hpp>

namespace ime::ui {
    class Slider::SliderImpl {
    public:
        SliderImpl(std::shared_ptr<tgui::Widget> widget) :
            slider_{std::static_pointer_cast<tgui::Slider>(widget)}
        {}

        std::shared_ptr<tgui::Slider> slider_;
    };

    ////////////////////////////////////////////////////////////////////////////

    Slider::Slider(float minValue, float maxValue) :
        Widget(std::make_unique<priv::WidgetImpl<tgui::Slider>>(tgui::Slider::create(minValue, maxValue))),
        pimpl_{std::make_unique<SliderImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()))}
    {
        setRenderer(std::make_shared<SliderRenderer>());

        pimpl_->slider_->onValueChange([this](float newValue) {
            emit("valueChange", newValue);
        });
    }

    Slider::Slider(Slider &&) = default;

    Slider &Slider::operator=(Slider &&) = default;

    Slider::Ptr Slider::create(float minimum, float maximum) {
        return Ptr(new Slider(minimum, maximum));
    }

    Slider::Ptr Slider::copy(Slider::ConstPtr other,
        bool shareRenderer)
    {
        auto widget = create();
        return widget;
    }

    std::shared_ptr<SliderRenderer> Slider::getRenderer() {
        return std::static_pointer_cast<SliderRenderer>(Widget::getRenderer());
    }

    const std::shared_ptr<SliderRenderer> Slider::getRenderer() const {
        return std::static_pointer_cast<SliderRenderer>(Widget::getRenderer());
    }

    void Slider::setMinimumValue(float minValue) {
        pimpl_->slider_->setMinimum(minValue);
    }

    float Slider::getMinimumValue() const {
        return pimpl_->slider_->getMinimum();
    }

    void Slider::setMaximumValue(float maxValue) {
        pimpl_->slider_->setMaximum(maxValue);
    }

    float Slider::getMaximumValue() const {
        return pimpl_->slider_->getMaximum();
    }

    void Slider::setValue(float value) {
        pimpl_->slider_->setValue(value);
    }

    float Slider::getValue() const {
        return pimpl_->slider_->getValue();
    }

    void Slider::setStep(float step) {
        pimpl_->slider_->setStep(step);
    }

    float Slider::getStep() const {
        return pimpl_->slider_->getStep();
    }

    void Slider::setVerticalScroll(bool isVertical) {
        pimpl_->slider_->setVerticalScroll(isVertical);
    }

    bool Slider::isVerticalScroll() const {
        return pimpl_->slider_->getVerticalScroll();
    }

    void Slider::invert(bool isInverted) {
        pimpl_->slider_->setInvertedDirection(isInverted);
    }

    bool Slider::isInverted() const {
        return pimpl_->slider_->getInvertedDirection();
    }

    void Slider::setChangeValueOnScroll(bool changeValueOnScroll) {
        pimpl_->slider_->setChangeValueOnScroll(changeValueOnScroll);
    }

    bool Slider::isValueChangedOnScroll() const {
        return pimpl_->slider_->getChangeValueOnScroll();
    }

    std::string Slider::getWidgetType() const {
        return "Slider";
    }

    Slider::~Slider() = default;
}
