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

#include "IME/ui/widgets/Picture.h"
#include "IME/core/resources/ResourceManager.h"
#include "IME/ui/widgets/WidgetImpl.h"
#include <TGUI/Widgets/Picture.hpp>

namespace ime::ui {
    static unsigned int count = 1; // Keeps track of how many widgets of this type have been instantiated

    class Picture::PictureImpl {
    public:
        explicit PictureImpl(tgui::Widget* widget) :
            picture_{static_cast<tgui::Picture*>(widget)}
        {}

        tgui::Picture* picture_;
    };

    ////////////////////////////////////////////////////////////////////////////
    
    Picture::Picture() :
        ClickableWidget(std::make_unique<priv::WidgetImpl<tgui::Picture>>(tgui::Picture::create())),
        pimpl_{std::make_unique<PictureImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("Picture" + std::to_string(count++));
        setRenderer(std::make_unique<PictureRenderer>());
        initEvents();
    }

    Picture::Picture(const std::string &filename, bool transparentTexture) :
        ClickableWidget(std::make_unique<priv::WidgetImpl<tgui::Picture>>(
            tgui::Picture::create(ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture(),
            transparentTexture))),
        pimpl_{std::make_unique<PictureImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("Picture" + std::to_string(count++));
        setRenderer(std::make_unique<PictureRenderer>());
        initEvents();
    }

    Picture::Picture(const std::string &filename, UIntRect frame, bool transparentTexture) :
        Picture()
    {
        auto texture = Texture(filename, frame);
        pimpl_->picture_->getRenderer()->setTexture(texture.getInternalTexture());
        pimpl_->picture_->getRenderer()->setTransparentTexture(transparentTexture);
    }

    Picture::Picture(const Picture& other) :
        ClickableWidget(other),
        pimpl_{std::make_unique<PictureImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get())}
    {
        setName("Picture" + std::to_string(count++));
        initEvents();
    }

    Picture &Picture::operator=(const Picture& rhs) {
        if (this != &rhs) {
            ClickableWidget::operator=(rhs);
            pimpl_ = std::make_unique<PictureImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()).get());
            initEvents();
        }

        return *this;
    }

    Picture::Picture(Picture&& other) noexcept :
        ClickableWidget(std::move(other))
    {
        *this = std::move(other);
    }

    Picture &Picture::operator=(Picture&& rhs) noexcept {
        if (this != &rhs) {
            pimpl_ = std::move(rhs.pimpl_);
            initEvents();
        }

        return *this;
    }

    Picture::Ptr Picture::create() {
        return Picture::Ptr(new Picture());
    }

    Picture::Ptr Picture::copy() const {
        return Picture::Ptr(static_cast<Picture*>(clone().release()));
    }

    Picture::Ptr Picture::create(const std::string &filename, bool transparentTexture) {
        return Ptr(new Picture(filename, transparentTexture));
    }

    Picture::Ptr Picture::create(const std::string &filename,
        UIntRect frame, bool transparentTexture)
    {
        return Ptr(new Picture(filename, frame, transparentTexture));
    }

    PictureRenderer* Picture::getRenderer() {
        return static_cast<PictureRenderer*>(Widget::getRenderer());
    }

    const PictureRenderer* Picture::getRenderer() const {
        return static_cast<const PictureRenderer*>(Widget::getRenderer());
    }

    void Picture::ignoreMouseEvents(bool ignore) {
        pimpl_->picture_->ignoreMouseEvents(ignore);
    }

    bool Picture::isMouseEventsIgnored() const {
        return pimpl_->picture_->isIgnoringMouseEvents();
    }

    Widget::Ptr Picture::clone() const {
        return std::make_unique<Picture>(*this);

    }

    std::string Picture::getWidgetType() const {
        return "Picture";
    }

    void Picture::initEvents() {
        pimpl_->picture_->onDoubleClick([this](tgui::Vector2f mousePos) {
            emit("doubleClick");
            emit("doubleClick", mousePos.x, mousePos.y);
        });
    }

    Picture::~Picture() = default;
}

