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
#include "IME/ui/widgets/WidgetImpl.h"
#include <TGUI/Widgets/Slider.hpp>

namespace ime::ui {
    static unsigned int count = 1; // Keeps track of how many widgets of this type have been instantiated

    class Slider::SliderImpl {
    public:
        explicit SliderImpl(tgui::Widget* widget) :
            slider_{static_cast<tgui::Slider*>(widget)}
        {}

        tgui::Slider* slider_;
    };

    ////////////////////////////////////////////////////////////////////////////

    Slider::Slider(float minValue, float maxValue) :
        Widget(std::make_unique<priv::WidgetImpl<tgui::Slider>>(tgui::Slider::create(minValue, maxValue))),
        pimpl_{std::make_unique<SliderImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("Slider" + std::to_string(count++));
        setRenderer(std::make_unique<SliderRenderer>());
        initEvents();
    }

    Slider::Slider(const Slider &other) :
        Widget(other),
        pimpl_{std::make_unique<SliderImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("Slider" + std::to_string(count++));
        initEvents();
    }

    Slider &Slider::operator=(const Slider& rhs) {
        if (this != &rhs) {
            Widget::operator=(rhs);
            pimpl_ = std::make_unique<SliderImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get());
            initEvents();
        }

        return *this;
    }

    Slider::Slider(Slider&& other) noexcept :
        Widget(std::move(other))
    {
        *this = std::move(other);
    }

    Slider &Slider::operator=(Slider&& rhs) noexcept {
        if (this != &rhs) {
            pimpl_ = std::move(rhs.pimpl_);
            initEvents();
        }

        return *this;
    }

    Slider::Ptr Slider::create(float minimum, float maximum) {
        return Ptr(new Slider(minimum, maximum));
    }

    Slider::Ptr Slider::copy() const {
        return Slider::Ptr(static_cast<Slider*>(clone().release()));
    }

    SliderRenderer* Slider::getRenderer() {
        return static_cast<SliderRenderer*>(Widget::getRenderer());
    }

    const SliderRenderer* Slider::getRenderer() const {
        return static_cast<const SliderRenderer*>(Widget::getRenderer());
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

    Widget::Ptr Slider::clone() const {
        return std::make_unique<Slider>(*this);
    }

    std::string Slider::getWidgetType() const {
        return "Slider";
    }

    void Slider::initEvents() {
        pimpl_->slider_->onValueChange([this](float newValue) {
            emit("valueChange", newValue);
        });
    }

    Slider::~Slider() = default;
}
