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

#include "IME/ui/widgets/WidgetContainer.h"
#include "../../utility/Helpers.h"
#include "WidgetImpl.h"
#include <TGUI/Container.hpp>

namespace ime::ui {
    //////////////////////////////////////////////////////////////////////////
    // Widget container class implementation
    //////////////////////////////////////////////////////////////////////////
    class WidgetContainer::Impl {
    public:
        Impl(std::shared_ptr<tgui::Widget> widget) {
            IME_ASSERT(widget, "A widget container cannot be a nullptr");
            tguiContainer_ = std::dynamic_pointer_cast<tgui::Container>(widget);
            IME_ASSERT(tguiContainer_, "A non container widget derived from WidgetContainer, change to Widget");
        }

        bool addWidget(ui::Widget::Ptr widget, const std::string &name)  {
            IME_ASSERT(widget, "Cannot add nullptr to a GUI container");
            if (widgets_.insert({name, widget}).second) {
                tguiContainer_->add(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr()), name);
                return true;
            }
            return false;
        }

        ui::Widget::Ptr getWidget(const std::string &name) const  {
            if (utility::findIn(widgets_, name))
                return widgets_.at(name);
            return utility::findRecursively(widgets_, name);
        }

        bool removeWidget(const std::string &name)  {
            if (utility::findIn(widgets_, name)) {
                tguiContainer_->remove(std::static_pointer_cast<tgui::Widget>(widgets_[name]->getInternalPtr()));
                widgets_.erase(name);
                return true;
            }
            return false;
        }

        ui::Widget::Ptr getWidgetAtPosition(Vector2f pos) const  {
            auto widget = tguiContainer_->getWidgetAtPosition({pos.x, pos.y});
            if (widget)
                return widgets_.at(widget->getWidgetName().toStdString());
            return nullptr;
        }

        void removeAllWidgets()  {
            tguiContainer_->removeAllWidgets();
            widgets_.clear();
        }

        void moveWidgetToFront(ui::Widget::Ptr widget)  {
            tguiContainer_->moveWidgetToFront(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr()));
        }

        void moveWidgetToBack(ui::Widget::Ptr widget)  {
            tguiContainer_->moveWidgetToBack(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr()));
        }

        size_t moveWidgetForward(ui::Widget::Ptr widget)  {
            return tguiContainer_->moveWidgetForward(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr()));
        }

        size_t moveWidgetBackward(ui::Widget::Ptr widget)  {
            return tguiContainer_->moveWidgetBackward(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr()));
        }

        ui::Widget::Ptr getFocusedWidget() const  {
            auto widget = tguiContainer_->getFocusedChild();
            if (widget)
                return widgets_.at(widget->getWidgetName().toStdString());
            return nullptr;
        }

        ui::Widget::Ptr getFocusedLeaf() const  {
            auto widget = tguiContainer_->getFocusedLeaf();
            if (widget)
                return widgets_.at(widget->getWidgetName().toStdString());
            return nullptr;
        }

        bool focusNextWidget(bool recursive)  {
            return tguiContainer_->focusNextWidget(recursive);
        }

        bool focusPreviousWidget(bool recursive)  {
            return tguiContainer_->focusPreviousWidget(recursive);
        }

    private:
        std::shared_ptr<tgui::Container> tguiContainer_;
        std::unordered_map<std::string, Widget::Ptr> widgets_;
    }; // class Impl

    //////////////////////////////////////////////////////////////////////////
    // Widget container class delegation
    //////////////////////////////////////////////////////////////////////////
    WidgetContainer::WidgetContainer(std::unique_ptr<priv::IWidgetImpl> widgetImpl) :
        Widget(std::move(widgetImpl)),
        pimpl_{std::make_unique<Impl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()))}
    {}

    WidgetContainer::WidgetContainer(WidgetContainer &&) = default;

    WidgetContainer &WidgetContainer::operator=(WidgetContainer &&) = default;

    bool WidgetContainer::addWidget(Widget::Ptr widget, const std::string &name) {
        return pimpl_->addWidget(std::move(widget), name);
    }

    Widget::Ptr WidgetContainer::getWidget(const std::string &name) const {
        return pimpl_->getWidget(name);
    }

    Widget::Ptr WidgetContainer::getWidgetAtPosition(Vector2f pos) const {
        return pimpl_->getWidgetAtPosition(pos);
    }

    bool WidgetContainer::removeWidget(const std::string &name) {
        return pimpl_->removeWidget(name);
    }

    void WidgetContainer::removeAllWidgets() {
        pimpl_->removeAllWidgets();
    }

    void WidgetContainer::moveWidgetToFront(Widget::Ptr widget) {
        pimpl_->moveWidgetToFront(std::move(widget));
    }

    void WidgetContainer::moveWidgetToBack(Widget::Ptr widget) {
        pimpl_->moveWidgetToBack(std::move(widget));
    }

    std::size_t WidgetContainer::moveWidgetForward(Widget::Ptr widget) {
        return pimpl_->moveWidgetForward(std::move(widget));
    }

    std::size_t WidgetContainer::moveWidgetBackward(Widget::Ptr widget) {
        return pimpl_->moveWidgetBackward(std::move(widget));
    }

    Widget::Ptr WidgetContainer::getFocusedWidget() const {
        return pimpl_->getFocusedWidget();
    }

    Widget::Ptr WidgetContainer::getFocusedLeaf() const {
        return pimpl_->getFocusedLeaf();
    }

    bool WidgetContainer::focusPreviousWidget(bool recursive) {
        return pimpl_->focusPreviousWidget(recursive);
    }

    bool WidgetContainer::focusNextWidget(bool recursive) {
        return pimpl_->focusNextWidget(recursive);
    }

    WidgetContainer::~WidgetContainer() = default;
}
