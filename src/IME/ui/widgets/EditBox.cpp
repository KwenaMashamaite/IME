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

#include "IME/ui/widgets/EditBox.h"
#include "WidgetImpl.h"
#include <TGUI/Widgets/EditBox.hpp>

namespace ime::ui {
    class EditBox::EditBoxImpl {
    public:
        EditBoxImpl(std::shared_ptr<tgui::Widget> widget) :
            editbox_{std::static_pointer_cast<tgui::EditBox>(widget)}
        {}
        
        std::shared_ptr<tgui::EditBox> editbox_;
    };

    ////////////////////////////////////////////////////////////////////////////
    
    EditBox::EditBox(const std::string& defaultText) :
        ClickableWidget(std::make_unique<priv::WidgetImpl<tgui::EditBox>>(tgui::EditBox::create())),
        pimpl_{std::make_unique<EditBoxImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()))}
    {
        setRenderer(std::make_shared<EditBoxRenderer>());
        pimpl_->editbox_->setDefaultText(defaultText);

        pimpl_->editbox_->onTextChange([this](const tgui::String& text) {
            emit("textEnter", text.toStdString());
        });

        pimpl_->editbox_->onReturnKeyPress([this](const tgui::String& text) {
            emit("enterKeyPress", text.toStdString());
        });
    }

    EditBox::EditBox(EditBox &&) = default;

    EditBox &EditBox::operator=(EditBox &&) = default;

    EditBox::Ptr EditBox::create(const std::string& defaultText) {
        return Ptr(new EditBox(defaultText));
    }

    EditBox::Ptr EditBox::copy(EditBox::ConstPtr other, bool shareRenderer) {
        auto widget = create();

        return widget;
    }

    std::shared_ptr<EditBoxRenderer> EditBox::getRenderer() {
        return std::static_pointer_cast<EditBoxRenderer>(Widget::getRenderer());
    }

    const std::shared_ptr<EditBoxRenderer> EditBox::getRenderer() const {
        return std::static_pointer_cast<EditBoxRenderer>(Widget::getRenderer());
    }

    void EditBox::setText(const std::string &content) {
        pimpl_->editbox_->setText(content);
    }

    std::string EditBox::getText() const {
        return pimpl_->editbox_->getText().toStdString();
    }

    void EditBox::setDefaultText(const std::string &text) {
        pimpl_->editbox_->setDefaultText(text);
    }

    std::string EditBox::getDefaultText() const {
        return pimpl_->editbox_->getDefaultText().toStdString();
    }

    void EditBox::setMaximumCharacters(unsigned int maxChars) {
        pimpl_->editbox_->setMaximumCharacters(maxChars);
    }

    unsigned int EditBox::getMaximumCharacters() const {
        return pimpl_->editbox_->getMaximumCharacters();
    }

    void EditBox::limitTextWidth(bool limitWidth) {
        pimpl_->editbox_->limitTextWidth(limitWidth);
    }

    bool EditBox::isTextWidthLimited() const {
        return pimpl_->editbox_->isTextWidthLimited();
    }

    void EditBox::setReadOnly(bool readOnly) {
        pimpl_->editbox_->setReadOnly(readOnly);
    }

    bool EditBox::isReadOnly() const {
        return pimpl_->editbox_->isReadOnly();
    }

    void EditBox::setCaretPosition(std::size_t charactersBeforeCaret) {
        pimpl_->editbox_->setCaretPosition(charactersBeforeCaret);
    }

    std::size_t EditBox::getCaretPosition() const {
        return pimpl_->editbox_->getCaretPosition();
    }

    void EditBox::setSuffix(const std::string &suffix) {
        pimpl_->editbox_->setSuffix(suffix);
    }

    std::string EditBox::getSuffix() const {
        return pimpl_->editbox_->getSuffix().toStdString();
    }

    std::string EditBox::getWidgetType() const {
        return "EditBox";
    }

    EditBox::~EditBox() = default;
}
