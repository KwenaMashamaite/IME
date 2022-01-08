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

#include "IME/ui/widgets/Panel.h"
#include "IME/utility/Helpers.h"
#include "IME/ui/widgets/WidgetImpl.h"
#include <TGUI/Widgets/Panel.hpp>

namespace ime::ui {
    static unsigned int count = 1; // Keeps track of how many widgets of this type have been instantiated

    Panel::Panel(const std::string& width, const std::string& height) :
        WidgetContainer(std::make_unique<priv::WidgetImpl<tgui::Panel>>(tgui::Panel::create({width.c_str(), height.c_str()})))
    {
        setName("Panel" + std::to_string(count++));
        setRenderer(std::make_unique<PanelRenderer>());
        setAsContainer(true);
        initEvents();
    }

    Panel::Panel(const Panel& other) :
        WidgetContainer(other)
    {
        setName("Panel" + std::to_string(count++));
        initEvents();
    }

    Panel &Panel::operator=(const Panel& rhs) {
        if (this != &rhs) {
            WidgetContainer::operator=(rhs);
            initEvents();
        }

        return *this;
    }

    Panel::Ptr Panel::create(const std::string& width, const std::string& height) {
        return Panel::Ptr(new Panel(width, height));
    }

    Panel::Ptr Panel::copy() const {
        return Panel::Ptr(static_cast<Panel*>(clone().release()));
    }

    PanelRenderer* Panel::getRenderer() {
        return static_cast<PanelRenderer*>(Widget::getRenderer());
    }

    const PanelRenderer* Panel::getRenderer() const {
        return static_cast<const PanelRenderer*>(Widget::getRenderer());
    }

    Widget::Ptr Panel::clone() const {
        return std::make_unique<Panel>(*this);
    }

    std::string Panel::getWidgetType() const {
        return "Panel";
    }

    void Panel::initEvents() {
        auto widget = static_cast<tgui::Panel*>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get());

        widget->onDoubleClick([this](tgui::Vector2f mousePos) {
            emit("doubleClick");
            emit("doubleClick", Vector2f{mousePos.x, mousePos.y});
        });
    }
}
