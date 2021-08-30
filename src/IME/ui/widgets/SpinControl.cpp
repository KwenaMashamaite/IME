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

#include "IME/ui/widgets/SpinControl.h"
#include "IME/ui/widgets/WidgetImpl.h"
#include <TGUI/Widgets/SpinControl.hpp>

namespace ime::ui {
    static unsigned int count = 1; // Keeps track of how many widgets of this type have been instantiated

    class SpinControl::SpinControlImpl {
    public:
        explicit SpinControlImpl(tgui::Widget* widget) :
            spinControl_{static_cast<tgui::SpinControl*>(widget)}
        {}

        tgui::SpinControl* spinControl_;
    };

    ////////////////////////////////////////////////////////////////////////////

    SpinControl::SpinControl(float minValue, float maxValue, float initialValue,
        unsigned int decimal, float step) :
            Widget(std::make_unique<priv::WidgetImpl<tgui::SpinControl>>(
                tgui::SpinControl::create(minValue, maxValue, initialValue, decimal, step))),
            pimpl_{std::make_unique<SpinControlImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("SpinControl" + std::to_string(count++));
        setRenderer(std::make_unique<SpinButtonRenderer>());
        initEvents();
    }

    SpinControl::SpinControl(const SpinControl& other) :
        Widget(other),
        pimpl_{std::make_unique<SpinControlImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("SpinControl" + std::to_string(count++));
        initEvents();
    }

    SpinControl &SpinControl::operator=(const SpinControl& rhs) {
        if (this != &rhs) {
            Widget::operator=(rhs);
            pimpl_ = std::make_unique<SpinControlImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get());
            initEvents();
        }

        return *this;
    }

    SpinControl::SpinControl(SpinControl&& other) noexcept :
        Widget(std::move(other))
    {
        *this = std::move(other);
    }

    SpinControl &SpinControl::operator=(SpinControl&& rhs) noexcept {
        if (this != &rhs) {
            pimpl_ = std::move(rhs.pimpl_);
            initEvents();
        }

        return *this;
    }

    SpinControl::Ptr SpinControl::create(float minValue, float maxValue,
        float initialValue, unsigned int decimal, float step) 
    {
        return Ptr(new SpinControl(minValue, maxValue, initialValue, decimal, step));
    }

    SpinControl::Ptr SpinControl::copy() const {
        return SpinControl::Ptr(static_cast<SpinControl*>(clone().release()));
    }

    SpinButtonRenderer* SpinControl::getSpinButtonRenderer() {
        return static_cast<SpinButtonRenderer*>(Widget::getRenderer());
    }

    const SpinButtonRenderer* SpinControl::getSpinButtonRenderer() const {
        return static_cast<const SpinButtonRenderer*>(Widget::getRenderer());
    }

    void SpinControl::setMinimumValue(float minValue) {
        pimpl_->spinControl_->setMinimum(minValue);
    }

    float SpinControl::getMinimumValue() const {
        return pimpl_->spinControl_->getMinimum();
    }

    void SpinControl::setMaximumValue(float maxValue) {
        pimpl_->spinControl_->setMaximum(maxValue);
    }

    float SpinControl::getMaximumValue() const {
        return pimpl_->spinControl_->getMaximum();
    }

    void SpinControl::setValue(float value) {
        pimpl_->spinControl_->setValue(value);
    }

    float SpinControl::getValue() const {
        return pimpl_->spinControl_->getValue();
    }

    void SpinControl::setStep(float step) {
        pimpl_->spinControl_->setStep(step);
    }

    float SpinControl::getStep() const {
        return pimpl_->spinControl_->getStep();
    }

    void SpinControl::setDecimalPlaces(unsigned int decimalPlaces) {
        pimpl_->spinControl_->setDecimalPlaces(decimalPlaces);
    }

    unsigned int SpinControl::getDecimalPlaces() const {
        return pimpl_->spinControl_->getDecimalPlaces();
    }

    Widget::Ptr SpinControl::clone() const {
        return std::make_unique<SpinControl>(*this);
    }

    std::string SpinControl::getWidgetType() const {
        return "SpinControl";
    }

    void SpinControl::initEvents() {
        pimpl_->spinControl_->onValueChange([this](float value) {
            emit("valueChange", value);
        });
    }

    SpinControl::~SpinControl() = default;
}
