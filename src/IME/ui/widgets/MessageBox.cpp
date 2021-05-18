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

#include "IME/ui/widgets/MessageBox.h"
#include "IME/ui/widgets/WidgetImpl.h"
#include <TGUI/Widgets/MessageBox.hpp>

namespace ime::ui {
    class MessageBox::MessageBoxImpl {
    public:
        explicit MessageBoxImpl(tgui::Widget* widget) :
            messageBox_{static_cast<tgui::MessageBox*>(widget)}
        {}

        tgui::MessageBox* messageBox_;
    };

    ////////////////////////////////////////////////////////////////////////////

    MessageBox::MessageBox() :
        WidgetContainer(std::make_unique<priv::WidgetImpl<tgui::MessageBox>>(tgui::MessageBox::create())),
        pimpl_{std::make_unique<MessageBoxImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setRenderer(std::make_unique<MessageBoxRenderer>());
        setAsContainer(true);
        initEvents();
    }

    MessageBox::MessageBox(const MessageBox& other) :
        WidgetContainer(other),
        pimpl_{std::make_unique<MessageBoxImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        initEvents();
    }

    MessageBox &MessageBox::operator=(const MessageBox& rhs) {
        if (this != &rhs) {
            WidgetContainer::operator=(rhs);
            pimpl_ = std::make_unique<MessageBoxImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get());
            initEvents();
        }

        return *this;
    }

    MessageBox::MessageBox(MessageBox&& other) noexcept :
        WidgetContainer(std::move(other))
    {
        *this = std::move(other);
    }

    MessageBox &MessageBox::operator=(MessageBox&& rhs) noexcept {
        if (this != &rhs) {
            pimpl_ = std::move(rhs.pimpl_);
            initEvents();
        }

        return *this;
    }

    MessageBox::Ptr MessageBox::create(const std::string& title, const std::string& text,
        const std::initializer_list<std::string>& buttons)
    {
        auto messageBox = MessageBox::Ptr(new MessageBox());
        messageBox->setTitle(title);
        messageBox->setText(text);

        for (const auto& caption : buttons)
            messageBox->addButton(caption);

        return messageBox;
    }

    MessageBox::Ptr MessageBox::copy() const {
        return MessageBox::Ptr(static_cast<MessageBox*>(clone().release()));
    }

    Widget::Ptr MessageBox::clone() const {
        return std::make_unique<MessageBox>(*this);
    }

    MessageBoxRenderer* MessageBox::getRenderer() {
        return static_cast<MessageBoxRenderer*>(Widget::getRenderer());
    }

    const MessageBoxRenderer* MessageBox::getRenderer() const {
        return static_cast<const MessageBoxRenderer*>(Widget::getRenderer());
    }

    void MessageBox::setText(const std::string &text) {
        pimpl_->messageBox_->setText(text);
    }

    std::string MessageBox::getText() const {
        return pimpl_->messageBox_->getText().toStdString();
    }

    void MessageBox::addButton(const std::string &buttonCaption) {
        pimpl_->messageBox_->addButton(buttonCaption);
    }

    void MessageBox::setClientSize(Vector2f size) {
        pimpl_->messageBox_->setClientSize({size.x, size.y});
    }

    Vector2f MessageBox::getClientSize() const {
        return {pimpl_->messageBox_->getClientSize().x, pimpl_->messageBox_->getClientSize().y};
    }

    void MessageBox::setMaximumSize(Vector2f size) {
        pimpl_->messageBox_->setMaximumSize({size.x, size.y});
    }

    Vector2f MessageBox::getMaximumSize() const {
        return {pimpl_->messageBox_->getMaximumSize().x, pimpl_->messageBox_->getMaximumSize().y};
    }

    void MessageBox::setMinimumSize(Vector2f size) {
        pimpl_->messageBox_->setMinimumSize({size.x, size.y});
    }

    Vector2f MessageBox::getMinimumSize() const {
        return {pimpl_->messageBox_->getMinimumSize().x, pimpl_->messageBox_->getMinimumSize().y};
    }

    void MessageBox::setTitle(const std::string &title) {
        pimpl_->messageBox_->setTitle(title);
    }

    std::string MessageBox::getTitle() const {
        return pimpl_->messageBox_->getTitle().toStdString();
    }

    void MessageBox::setTitleTextSize(unsigned int size) {
        pimpl_->messageBox_->setTitleTextSize(size);
    }

    unsigned int MessageBox::getTitleTextSize() const {
        return pimpl_->messageBox_->getTitleTextSize();
    }

    void MessageBox::setTitleAlignment(MessageBox::TitleAlignment alignment) {
        pimpl_->messageBox_->setTitleAlignment(static_cast<tgui::MessageBox::TitleAlignment>(alignment));
    }

    MessageBox::TitleAlignment MessageBox::getTitleAlignment() const {
        return static_cast<TitleAlignment>(pimpl_->messageBox_->getTitleAlignment());
    }

    void MessageBox::setTitleButtons(unsigned int buttons) {
        pimpl_->messageBox_->setTitleButtons(buttons);
    }

    void MessageBox::close() {
        pimpl_->messageBox_->close();
    }

    void MessageBox::destroy() {
        pimpl_->messageBox_->destroy();
    }

    void MessageBox::setResizable(bool resizable) {
        pimpl_->messageBox_->setResizable(resizable);
    }

    bool MessageBox::isResizable() const {
        return pimpl_->messageBox_->isResizable();
    }

    void MessageBox::setDraggable(bool draggable) {
        pimpl_->messageBox_->setPositionLocked(!draggable);
    }

    bool MessageBox::isDraggable() const {
        return !pimpl_->messageBox_->isPositionLocked();
    }

    void MessageBox::setKeepInParent(bool enabled) {
        pimpl_->messageBox_->setKeepInParent(enabled);
    }

    bool MessageBox::isKeptInParent() const {
        return pimpl_->messageBox_->isKeptInParent();
    }

    std::string MessageBox::getWidgetType() const {
        return "MessageBox";
    }

    void MessageBox::initEvents() {
        pimpl_->messageBox_->onButtonPress([this](const tgui::String& buttonCaption) {
            emit("buttonPress", buttonCaption.toStdString());
        });

        pimpl_->messageBox_->onClose([this]{
            emit("closed");
        });

        pimpl_->messageBox_->onMinimize([this]{
            emit("minimize");
        });

        pimpl_->messageBox_->onMaximize([this]{
            emit("maximize");
        });

        pimpl_->messageBox_->onEscapeKeyPress([this]{
            emit("escapeKeyPress");
        });

        pimpl_->messageBox_->onSizeChange([this](tgui::Vector2f newSize) {
            emit("sizeChange", newSize.x, newSize.y);
        });
    }

    MessageBox::~MessageBox() = default;
}
