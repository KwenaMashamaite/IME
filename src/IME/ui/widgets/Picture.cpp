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
#include "WidgetImpl.h"
#include <TGUI/Widgets/Picture.hpp>

namespace ime::ui {
    class Picture::PictureImpl {
    public:
        PictureImpl(std::shared_ptr<tgui::Widget> widget) :
            picture_{std::static_pointer_cast<tgui::Picture>(widget)}
        {}

        std::shared_ptr<tgui::Picture> picture_;
    };

    ////////////////////////////////////////////////////////////////////////////
    
    Picture::Picture() :
        ClickableWidget(std::make_unique<priv::WidgetImpl<tgui::Picture>>(tgui::Picture::create())),
        pimpl_{std::make_unique<PictureImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()))}
    {
        setRenderer(std::make_shared<PictureRenderer>());

        pimpl_->picture_->onDoubleClick([this](tgui::Vector2f mousePos) {
            emit("doubleClick");
            emit("doubleClick", mousePos.x, mousePos.y);
        });
    }

    Picture::Picture(const std::string &filename, bool transparentTexture) :
        ClickableWidget(std::make_unique<priv::WidgetImpl<tgui::Picture>>(
            tgui::Picture::create(ime::ResourceManager::getInstance()->getTexture(filename).getInternalTexture(),
            transparentTexture))),
        pimpl_{std::make_unique<PictureImpl>(std::static_pointer_cast<tgui::Widget>(getInternalPtr()))}
    {
        setRenderer(std::make_shared<PictureRenderer>());

        pimpl_->picture_->onDoubleClick([this](tgui::Vector2f mousePos) {
            emit("doubleClick");
            emit("doubleClick", mousePos.x, mousePos.y);
        });
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
        pimpl_{std::make_unique<PictureImpl>(*other.pimpl_)}
    {}

    Picture &Picture::operator=(const Picture& rhs) {
        if (this != &rhs) {
            pimpl_ = std::make_unique<PictureImpl>(*rhs.pimpl_);
        }

        return *this;
    }

    Picture::Picture(Picture &&) noexcept = default;
    Picture &Picture::operator=(Picture &&) noexcept = default;

    Picture::Ptr Picture::create() {
        return Ptr(new Picture());
    }

    Picture::Ptr Picture::copy() {
        return std::static_pointer_cast<Picture>(clone());
    }

    Picture::Ptr Picture::create(const std::string &filename, bool transparentTexture) {
        return Ptr(new Picture(filename, transparentTexture));
    }

    Picture::Ptr Picture::create(const std::string &filename,
        UIntRect frame, bool transparentTexture)
    {
        return Ptr(new Picture(filename, frame, transparentTexture));
    }

    std::shared_ptr<PictureRenderer> Picture::getRenderer() {
        return std::static_pointer_cast<PictureRenderer>(Widget::getRenderer());
    }

    const std::shared_ptr<PictureRenderer> Picture::getRenderer() const {
        return std::static_pointer_cast<PictureRenderer>(Widget::getRenderer());
    }

    void Picture::ignoreMouseEvents(bool ignore) {
        pimpl_->picture_->ignoreMouseEvents(ignore);
    }

    bool Picture::isMouseEventsIgnored() const {
        return pimpl_->picture_->isIgnoringMouseEvents();
    }

    Widget::Ptr Picture::clone() const {
        return std::make_shared<Picture>(*this);

    }

    std::string Picture::getWidgetType() const {
        return "Picture";
    }

    Picture::~Picture() = default;
}

