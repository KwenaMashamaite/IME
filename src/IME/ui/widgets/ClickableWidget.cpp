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

#include "IME/ui/widgets/ClickableWidget.h"
#include "IME/ui/widgets/WidgetImpl.h"
#include <TGUI/Widgets/ClickableWidget.hpp>

namespace ime::ui {
    struct ClickableWidget::ClickableWidgetImpl {
        explicit ClickableWidgetImpl(tgui::Widget* widget) {
            IME_ASSERT(widget, "A clickable widget cannot be instantiated from a nullptr")
            widget_ = dynamic_cast<tgui::ClickableWidget*>(widget);
            IME_ASSERT(widget_, "A non clickable widget derived from ClickableWidget, change to Widget")
        }

        //////////////////////////////////////////////////////////////////////
        // Member data
        //////////////////////////////////////////////////////////////////////

        tgui::ClickableWidget* widget_;
    };

    ClickableWidget::ClickableWidget(std::unique_ptr<priv::IWidgetImpl> widgetImpl) :
        Widget(std::move(widgetImpl)),
        pimpl_{std::make_unique<ClickableWidgetImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        initEvents();
    }

    ClickableWidget::ClickableWidget(const ClickableWidget& other) :
        Widget(other),
        pimpl_{std::make_unique<ClickableWidgetImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        initEvents();
    }

    ClickableWidget& ClickableWidget::operator=(const ClickableWidget& rhs) {
        if (this != &rhs) {
            Widget::operator=(rhs);
            pimpl_ = std::make_unique<ClickableWidgetImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get());
            initEvents();
        }

        return *this;
    }

    ClickableWidget::ClickableWidget(ClickableWidget&& other) noexcept = default;
    ClickableWidget& ClickableWidget::operator=(ClickableWidget &&rhs) noexcept = default;

    void ClickableWidget::initEvents() {
        //Events triggered by left mouse button
        pimpl_->widget_->onClick([this](tgui::Vector2f mousePos){
            emit("click");
            emit("click", ime::Vector2f{mousePos.x, mousePos.y});
        });

        pimpl_->widget_->onMousePress([this](tgui::Vector2f mousePos) {
            emit("leftMouseDown");
            emit("leftMouseDown", ime::Vector2f{mousePos.x, mousePos.y});
        });

        pimpl_->widget_->onMouseRelease([this](tgui::Vector2f mousePos) {
            emit("leftMouseUp");
            emit("leftMouseUp", ime::Vector2f{mousePos.x, mousePos.y});
        });

        //Events triggered by right mouse button
        pimpl_->widget_->onRightMousePress([this](tgui::Vector2f mousePos){
            emit("rightMouseDown");
            emit("rightMouseDown", ime::Vector2f{mousePos.x, mousePos.y});
        });

        pimpl_->widget_->onRightMouseRelease([this](tgui::Vector2f mousePos){
            emit("rightMouseUp");
            emit("rightMouseUp", ime::Vector2f{mousePos.x, mousePos.y});
        });

        pimpl_->widget_->onRightClick([this](tgui::Vector2f mousePos){
            emit("rightClick");
            emit("rightClick", ime::Vector2f{mousePos.x, mousePos.y});
        });
    }

    ClickableWidget::~ClickableWidget() = default;
}

