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

#include "IME/ui/widgets/ChildWindow.h"
#include "IME/ui/widgets/WidgetImpl.h"
#include <TGUI/Widgets/ChildWindow.hpp>

namespace ime::ui {
    static unsigned int count = 1; // Keeps track of how many widgets of this type have been instantiated

    class ChildWindow::ChildWindowImpl {
    public:
        explicit ChildWindowImpl(tgui::Widget* widget) :
            window_{static_cast<tgui::ChildWindow*>(widget)}
        {}

        tgui::ChildWindow* window_;
    };

    ////////////////////////////////////////////////////////////////////////////

    ChildWindow::ChildWindow(const std::string &title, unsigned int titleButtons) :
        WidgetContainer(std::make_unique<priv::WidgetImpl<tgui::ChildWindow>>(tgui::ChildWindow::create(title, titleButtons))),
        pimpl_{std::make_unique<ChildWindowImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("ChildWindow" + std::to_string(count++));
        setRenderer(std::make_unique<ChildWindowRenderer>());
        setAsContainer(true);
        initEvents();
    }

    ChildWindow::ChildWindow(const ChildWindow& other) :
        WidgetContainer(other),
        pimpl_{std::make_unique<ChildWindowImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("ChildWindow" + std::to_string(count++));
        initEvents();
    }

    ChildWindow &ChildWindow::operator=(const ChildWindow& rhs) {
        if (this != &rhs) {
            WidgetContainer::operator=(rhs);
            pimpl_ = std::make_unique<ChildWindowImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get());
            initEvents();
        }

        return *this;
    }

    ChildWindow::ChildWindow(ChildWindow&& other) noexcept = default;
    ChildWindow &ChildWindow::operator=(ChildWindow&& rhs) noexcept = default;

    ChildWindow::Ptr ChildWindow::create(const std::string& title, unsigned int titleButtons) {
        return ChildWindow::Ptr(new ChildWindow(title, titleButtons));
    }

    ChildWindow::Ptr ChildWindow::copy() const {
        return ChildWindow::Ptr(static_cast<ChildWindow*>(clone().release()));
    }

    ChildWindowRenderer* ChildWindow::getRenderer() {
        return static_cast<ChildWindowRenderer*>(Widget::getRenderer());
    }

    const ChildWindowRenderer* ChildWindow::getRenderer() const {
        return static_cast<const ChildWindowRenderer*>(Widget::getRenderer());
    }

    void ChildWindow::setClientSize(Vector2f size) {
        pimpl_->window_->setClientSize({size.x, size.y});
    }

    Vector2f ChildWindow::getClientSize() const {
        return {pimpl_->window_->getClientSize().x, pimpl_->window_->getClientSize().y};
    }

    void ChildWindow::setMaximumSize(Vector2f size) {
        pimpl_->window_->setMaximumSize({size.x, size.y});
    }

    Vector2f ChildWindow::getMaximumSize() const {
        return {pimpl_->window_->getMaximumSize().x, pimpl_->window_->getMaximumSize().y};
    }

    void ChildWindow::setMinimumSize(Vector2f size) {
        pimpl_->window_->setMinimumSize({size.x, size.y});
    }

    Vector2f ChildWindow::getMinimumSize() const {
        return {pimpl_->window_->getMinimumSize().x, pimpl_->window_->getMinimumSize().y};
    }

    void ChildWindow::setTitle(const std::string &title) {
        pimpl_->window_->setTitle(title);
    }

    std::string ChildWindow::getTitle() const {
        return pimpl_->window_->getTitle().toStdString();
    }

    void ChildWindow::setTitleTextSize(unsigned int size) {
        pimpl_->window_->setTitleTextSize(size);
    }

    unsigned int ChildWindow::getTitleTextSize() const {
        return pimpl_->window_->getTitleTextSize();
    }

    void ChildWindow::setTitleAlignment(ChildWindow::TitleAlignment alignment) {
        pimpl_->window_->setTitleAlignment(static_cast<tgui::ChildWindow::TitleAlignment>(alignment));
    }

    ChildWindow::TitleAlignment ChildWindow::getTitleAlignment() const {
        return static_cast<TitleAlignment>(pimpl_->window_->getTitleAlignment());
    }

    void ChildWindow::setTitleButtons(unsigned int buttons) {
        pimpl_->window_->setTitleButtons(buttons);
    }

    void ChildWindow::close() {
        pimpl_->window_->close();
    }

    void ChildWindow::destroy() {
        pimpl_->window_->destroy();
    }

    void ChildWindow::setResizable(bool resizable) {
        pimpl_->window_->setResizable(resizable);
    }

    bool ChildWindow::isResizable() const {
        return pimpl_->window_->isResizable();
    }

    void ChildWindow::setDraggable(bool draggable) {
        pimpl_->window_->setPositionLocked(!draggable);
    }

    bool ChildWindow::isDraggable() const {
        return !pimpl_->window_->isPositionLocked();
    }

    void ChildWindow::setKeepInParent(bool enabled) {
        pimpl_->window_->setKeepInParent(enabled);
    }

    bool ChildWindow::isKeptInParent() const {
        return pimpl_->window_->isKeptInParent();
    }

    Widget::Ptr ChildWindow::clone() const {
        return std::make_unique<ChildWindow>(*this);
    }

    std::string ChildWindow::getWidgetType() const {
        return "ChildWindow";
    }

    void ChildWindow::initEvents() {
        pimpl_->window_->onClose([this]{
            emit("close");
        });

        pimpl_->window_->onMinimize([this]{
            emit("minimize");
        });

        pimpl_->window_->onMaximize([this]{
            emit("maximize");
        });

        pimpl_->window_->onEscapeKeyPress([this]{
            emit("escapeKeyPress");
        });
    }

    ChildWindow::~ChildWindow() = default;
}