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

#include "IME/ui/widgets/ChildWindow.h"
#include "../../utility/Helpers.h"
#include "WidgetImpl.h"
#include <TGUI/Widgets/ChildWindow.hpp>

namespace ime::ui {
    class ChildWindow::ChildWindowImpl {
    public:
        ChildWindowImpl(std::shared_ptr<tgui::Widget> widget) :
            window_{std::static_pointer_cast<tgui::ChildWindow>(widget)}
        {}

        std::shared_ptr<tgui::ChildWindow> window_;
    };

    ////////////////////////////////////////////////////////////////////////////

    ChildWindow::ChildWindow(const std::string &title, unsigned int titleButtons) :
        WidgetContainer(std::make_unique<priv::WidgetImpl<tgui::ChildWindow>>(tgui::ChildWindow::create(title, titleButtons))),
        pimpl_{std::make_unique<ChildWindowImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()))}
    {
        setRenderer(std::make_shared<ChildWindowRenderer>());
        setAsContainer(true);

        pimpl_->window_->onClose([this]{
            emit("closed");
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

        pimpl_->window_->onSizeChange([this](tgui::Vector2f newSize) {
            emit("sizeChange", newSize.x, newSize.y);
        });
    }

    ChildWindow::ChildWindow(const ChildWindow& other) :
        WidgetContainer(other),
        pimpl_{std::make_unique<ChildWindowImpl>(*other.pimpl_)}
    {}

    ChildWindow &ChildWindow::operator=(const ChildWindow& rhs) {
        if (this != &rhs) {
            pimpl_ = std::make_unique<ChildWindowImpl>(*rhs.pimpl_);
        }

        return *this;
    }

    ChildWindow::ChildWindow(ChildWindow &&) noexcept = default;
    ChildWindow &ChildWindow::operator=(ChildWindow &&) noexcept = default;

    ChildWindow::Ptr ChildWindow::create(const std::string& title, unsigned int titleButtons) {
        return ChildWindow::Ptr(new ChildWindow(title, titleButtons));
    }

    ChildWindow::Ptr ChildWindow::copy() {
        return std::static_pointer_cast<ChildWindow>(clone());
    }

    std::shared_ptr<ChildWindowRenderer> ChildWindow::getRenderer() {
        return std::static_pointer_cast<ChildWindowRenderer>(Widget::getRenderer());
    }

    const ChildWindowRenderer::Ptr ChildWindow::getRenderer() const {
        return std::static_pointer_cast<ChildWindowRenderer>(Widget::getRenderer());
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
        return std::make_shared<ChildWindow>(*this);
    }

    std::string ChildWindow::getWidgetType() const {
        return "ChildWindow";
    }

    ChildWindow::~ChildWindow() = default;
}