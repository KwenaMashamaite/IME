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
#include "IME/utility/Helpers.h"
#include "IME/ui/widgets/WidgetImpl.h"
#include <TGUI/Container.hpp>
#include <iostream>

namespace ime::ui {
    //////////////////////////////////////////////////////////////////////////
    // Widget container class implementation
    //////////////////////////////////////////////////////////////////////////
    class WidgetContainer::WidgetContainerImpl {
    public:
        explicit WidgetContainerImpl(tgui::Widget* widget) {
            IME_ASSERT(widget, "A widget container cannot be a nullptr")
            tguiContainer_ = dynamic_cast<tgui::Container*>(widget);
            IME_ASSERT(tguiContainer_, "A non container widget derived from WidgetContainer, change to Widget")
        }

        /// The shallow copy is intentional because the implementation and the
        /// base class must operate on the same third party widget. @param other
        /// is a copied version of the argument passed to the copy constructor
        /// of ime::WidgetContainer, therefore no additional copies are required
        WidgetContainerImpl(const WidgetContainerImpl& other) :
            tguiContainer_{static_cast<tgui::Container*>(other.tguiContainer_)}
        {}

        WidgetContainerImpl& operator=(const WidgetContainerImpl& impl) {
            if (this != &impl) {
                auto temp{impl};
                std::swap(tguiContainer_, temp.tguiContainer_);
                std::swap(widgets_, temp.widgets_);
            }

            return *this;
        }

        WidgetContainerImpl(WidgetContainerImpl&&) noexcept = default;
        WidgetContainerImpl& operator=(WidgetContainerImpl&&) noexcept = default;

        Widget* addWidget(Widget::Ptr widget, const std::string &name)  {
            IME_ASSERT(widget, "Cannot add nullptr to a WidgetContainer")
            auto [iter, inserted] = widgets_.insert({name, std::move(widget)});
            if (inserted) {
                tguiContainer_->add(std::static_pointer_cast<tgui::Widget>(iter->second->getInternalPtr()), name);
                return iter->second.get();
            }

            std::cerr << "IME ERROR: A widget with the name \"" + name + "\" already exists in the container, widget names must be unique";
            exit(-3); //@TODO - Replace magic number with error code
        }

        ui::Widget* getWidget(const std::string &name) const  {
            if (utility::findIn(widgets_, name))
                return widgets_.at(name).get();
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

        ui::Widget* getWidgetAtPosition(Vector2f pos) const  {
            auto widget = tguiContainer_->getWidgetAtPosition({pos.x, pos.y});
            if (widget)
                return widgets_.at(widget->getWidgetName().toStdString()).get();
            return nullptr;
        }

        void removeAllWidgets()  {
            tguiContainer_->removeAllWidgets();
            widgets_.clear();
        }

        void moveWidgetToFront(const ui::Widget* widget)  {
            IME_ASSERT(widget, "Widget to be moved cannot be a nullptr")
            tguiContainer_->moveWidgetToFront(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr()));
        }

        void moveWidgetToBack(const ui::Widget* widget)  {
            IME_ASSERT(widget, "Widget to be moved cannot be a nullptr")
            tguiContainer_->moveWidgetToBack(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr()));
        }

        size_t moveWidgetForward(const ui::Widget* widget)  {
            IME_ASSERT(widget, "Widget to be moved cannot be a nullptr")
            return tguiContainer_->moveWidgetForward(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr()));
        }

        size_t moveWidgetBackward(const ui::Widget* widget)  {
            IME_ASSERT(widget, "Widget to be moved cannot be a nullptr")
            return tguiContainer_->moveWidgetBackward(std::static_pointer_cast<tgui::Widget>(widget->getInternalPtr()));
        }

        ui::Widget* getFocusedWidget() const  {
            auto widget = tguiContainer_->getFocusedChild();
            if (widget)
                return widgets_.at(widget->getWidgetName().toStdString()).get();
            return nullptr;
        }

        ui::Widget* getFocusedLeaf() const  {
            auto widget = tguiContainer_->getFocusedLeaf();
            if (widget)
                return widgets_.at(widget->getWidgetName().toStdString()).get();
            return nullptr;
        }

        bool focusNextWidget(bool recursive)  {
            return tguiContainer_->focusNextWidget(recursive);
        }

        bool focusPreviousWidget(bool recursive)  {
            return tguiContainer_->focusPreviousWidget(recursive);
        }

        std::size_t getCount() const {
            return widgets_.size();
        }

        void forEach(const Callback<Widget*>& callback) const {
            std::for_each(widgets_.begin(), widgets_.end(), [&callback](auto& pair) {
                callback(pair.second.get());
            });
        }

        // Temporarily made public so it can be copied in WidgetContainer copy constructor
        std::unordered_map<std::string, Widget::Ptr> widgets_;

    private:
        tgui::Container* tguiContainer_;
    }; // class WidgetContainerImpl

    //////////////////////////////////////////////////////////////////////////
    // WidgetContainer class delegation
    //////////////////////////////////////////////////////////////////////////
    WidgetContainer::WidgetContainer(std::unique_ptr<priv::IWidgetImpl> widgetImpl) :
        Widget(std::move(widgetImpl)),
        pimpl_{std::make_unique<WidgetContainerImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {}

    WidgetContainer::WidgetContainer(const WidgetContainer& other) :
        Widget(other),
        pimpl_{std::make_unique<WidgetContainerImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        for (const auto& [name, widget] : other.pimpl_->widgets_) {
            pimpl_->widgets_.insert({name, widget->clone()});
        }
    }

    WidgetContainer &WidgetContainer::operator=(const WidgetContainer& rhs) {
        if (this != &rhs) {
            Widget::operator=(rhs);
            pimpl_ = std::make_unique<WidgetContainerImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get());
        }

        return *this;
    }

    WidgetContainer::WidgetContainer(WidgetContainer&&) noexcept = default;
    WidgetContainer &WidgetContainer::operator=(WidgetContainer&&) noexcept = default;

    Widget* WidgetContainer::addWidget(Widget::Ptr widget, const std::string &name) {
        return pimpl_->addWidget(std::move(widget), name);
    }

    Widget* WidgetContainer::getWidget(const std::string &name) const {
        return pimpl_->getWidget(name);
    }

    Widget* WidgetContainer::getWidgetAtPosition(Vector2f pos) const {
        return pimpl_->getWidgetAtPosition(pos);
    }

    bool WidgetContainer::removeWidget(const std::string &name) {
        return pimpl_->removeWidget(name);
    }

    void WidgetContainer::removeAllWidgets() {
        pimpl_->removeAllWidgets();
    }

    void WidgetContainer::moveWidgetToFront(const Widget* widget) {
        pimpl_->moveWidgetToFront(widget);
    }

    void WidgetContainer::moveWidgetToBack(const Widget* widget) {
        pimpl_->moveWidgetToBack(widget);
    }

    std::size_t WidgetContainer::moveWidgetForward(const Widget* widget) {
        return pimpl_->moveWidgetForward(widget);
    }

    std::size_t WidgetContainer::moveWidgetBackward(const Widget* widget) {
        return pimpl_->moveWidgetBackward(widget);
    }

    void WidgetContainer::moveWidgetToFront(const std::string &widget) {
        moveWidgetToFront(getWidget(widget));
    }

    void WidgetContainer::moveWidgetToBack(const std::string &widget) {
        moveWidgetToBack(getWidget(widget));
    }

    size_t WidgetContainer::moveWidgetForward(const std::string &widget) {
        return moveWidgetForward(getWidget(widget));
    }

    size_t WidgetContainer::moveWidgetBackward(const std::string &widget) {
        return moveWidgetBackward(getWidget(widget));
    }

    Widget* WidgetContainer::getFocusedWidget() const {
        return pimpl_->getFocusedWidget();
    }

    Widget* WidgetContainer::getFocusedLeaf() const {
        return pimpl_->getFocusedLeaf();
    }

    bool WidgetContainer::focusPreviousWidget(bool recursive) {
        return pimpl_->focusPreviousWidget(recursive);
    }

    std::size_t WidgetContainer::getCount() const {
        return pimpl_->getCount();
    }

    void WidgetContainer::forEach(const Callback<Widget*> &callback) const {
        pimpl_->forEach(callback);
    }

    bool WidgetContainer::focusNextWidget(bool recursive) {
        return pimpl_->focusNextWidget(recursive);
    }

    WidgetContainer::~WidgetContainer() = default;
}
