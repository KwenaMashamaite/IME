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

namespace ime::ui {
    Picture::Picture() :
        picture_{tgui::Picture::create()},
        renderer_{std::make_shared<PictureRenderer>()}
    {
        renderer_->setInternalPtr(picture_->getRenderer());
        initEvents();
    }

    Picture::Picture(const std::string &filename, bool transparentTexture) :
        picture_{tgui::Picture::create(
            ime::ResourceManager::getInstance()->getTexture(filename), transparentTexture)},
        renderer_{std::make_shared<PictureRenderer>()}
    {
        renderer_->setInternalPtr(picture_->getRenderer());
        initEvents();
    }

    Picture::Picture(const std::string &filename, UIntRect frame, bool transparentTexture) :
        renderer_{std::make_shared<PictureRenderer>()}
    {
        ime::ResourceManager::getInstance()->getTexture(filename); //Load the image in the engine first
        auto path = ime::ResourceManager::getInstance()->getPathFor(ResourceType::Texture);
        picture_ = tgui::Picture::create(
            {path + filename, {frame.left, frame.top, frame.width, frame.height}},
            transparentTexture);
        renderer_->setInternalPtr(picture_->getRenderer());
        initEvents();
    }

    Picture::sharedPtr Picture::create() {
        return std::make_shared<Picture>();
    }

    Picture::sharedPtr Picture::copy(Picture::constSharedPtr other, bool shareRenderer) {
        auto widget = create();
        widget->picture_ = widget->picture_->copy(other->picture_);

        if (!shareRenderer)
            widget->picture_->setRenderer(other->picture_->getRenderer()->clone());
        widget->renderer_->setInternalPtr(other->picture_->getRenderer());

        return widget;
    }

    Picture::sharedPtr Picture::create(const std::string &filename, bool transparentTexture) {
        return std::make_shared<Picture>(filename, transparentTexture);
    }

    Picture::sharedPtr Picture::create(const std::string &filename,
        UIntRect frame, bool transparentTexture)
    {
        return std::make_shared<Picture>(filename, frame, transparentTexture);
    }

    void Picture::setRenderer(std::shared_ptr<PictureRenderer> renderer) {
        IME_ASSERT(renderer, "Cannot set nullptr as renderer");
        renderer_ = renderer;
        picture_->setRenderer(renderer->getInternalPtr()->getData());
    }

    std::shared_ptr<PictureRenderer> Picture::getRenderer() {
        return renderer_;
    }

    void Picture::ignoreMouseEvents(bool ignore) {
        picture_->ignoreMouseEvents(ignore);
    }

    bool Picture::isMouseEventsIgnored() const {
        return picture_->isIgnoringMouseEvents();
    }

    void Picture::setTextSize(unsigned int charSize) {
        picture_->setTextSize(charSize);
    }

    unsigned int Picture::getTextSize() const {
        return picture_->getTextSize();
    }

    void Picture::setSize(float width, float height) {
        picture_->setSize({width, height});
    }

    void Picture::setSize(const std::string &width, const std::string &height) {
        picture_->setSize({width.c_str(), height.c_str()});
    }

    Vector2f Picture::getSize() const {
        return {picture_->getSize().x, picture_->getSize().y};
    }

    Vector2f Picture::getAbsoluteSize() {
        return {picture_->getFullSize().x, picture_->getFullSize().y};
    }

    void Picture::setWidth(float width) {
        picture_->setWidth(width);
    }

    void Picture::setWidth(const std::string &width) {
        picture_->setWidth(width.c_str());
    }

    void Picture::setHeight(float height) {
        picture_->setHeight(height);
    }

    void Picture::setHeight(const std::string &height) {
        picture_->setHeight(height.c_str());
    }

    void Picture::setMouseCursor(CursorType cursor) {
        picture_->setMouseCursor(static_cast<tgui::Cursor::Type>(static_cast<int>(cursor)));
    }

    CursorType Picture::getMouseCursor() const {
        return static_cast<CursorType>(static_cast<int>(picture_->getMouseCursor()));
    }

    std::string Picture::getWidgetType() const {
        return "Picture";
    }

    void Picture::showWithEffect(ShowAnimationType type, int duration) {
        picture_->showWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    void Picture::hideWithEffect(ShowAnimationType type, int duration) {
        picture_->hideWithEffect(static_cast<tgui::ShowAnimationType>(type), duration);
    }

    bool Picture::isAnimationPlaying() const {
        return picture_->isAnimationPlaying();
    }

    void Picture::setVisible(bool visible) {
        picture_->setVisible(visible);
    }

    bool Picture::isVisible() const {
        return picture_->isVisible();
    }

    void Picture::toggleVisibility() {
        picture_->setVisible(!picture_->isVisible());
    }

    bool Picture::contains(float x, float y) const {
        return picture_->isMouseOnWidget({x, y});
    }

    void Picture::setPosition(float x, float y) {
        picture_->setPosition({x, y});
    }

    void Picture::setPosition(Vector2f position) {
        setPosition(position.x, position.y);
    }

    void Picture::setPosition(const std::string &x, const std::string &y) {
        picture_->setPosition({x.c_str(), y.c_str()});
    }

    Vector2f Picture::getPosition() const {
        return {picture_->getPosition().x, picture_->getPosition().y};
    }

    Vector2f Picture::getAbsolutePosition() const {
        return {picture_->getAbsolutePosition().x, picture_->getAbsolutePosition().y};
    }

    void Picture::setRotation(float angle) {
        picture_->setRotation(angle);
    }

    void Picture::rotate(float angle) {
        picture_->setRotation(picture_->getRotation() + angle);
    }

    float Picture::getRotation() const {
        return picture_->getRotation();
    }

    void Picture::setScale(float factorX, float factorY) {
        picture_->setScale({factorX, factorY});
    }

    void Picture::setScale(Vector2f scale) {
        setScale(scale.x, scale.y);
    }

    void Picture::scale(float factorX, float factorY) {
        picture_->setScale({picture_->getScale().x + factorX,
        picture_->getScale().y + factorY});
    }

    void Picture::scale(Vector2f offset) {
        scale(offset.x, offset.y);
    }

    Vector2f Picture::getScale() const {
        return {picture_->getScale().x, picture_->getScale().y};
    }

    void Picture::setOrigin(float x, float y) {
        picture_->setOrigin({x, y});
    }

    void Picture::setOrigin(Vector2f origin) {
        setOrigin(origin.x, origin.y);
    }

    Vector2f Picture::getOrigin() const {
        return {picture_->getOrigin().x, picture_->getOrigin().y};
    }

    void Picture::move(float offsetX, float offsetY) {
        picture_->setPosition(getPosition().x + offsetX, getPosition().y + offsetY);
    }

    void Picture::move(Vector2f offset) {
        move(offset.x, offset.y);
    }

    void Picture::setEnabled(bool isEnable) {
        picture_->setEnabled(isEnable);
    }

    bool Picture::isEnabled() const {
        return picture_->isEnabled();
    }

    void Picture::toggleEnabled() {
        setEnabled(!isEnabled());
    }

    void Picture::setFocused(bool isFocused) {
        picture_->setFocused(isFocused);
    }

    bool Picture::isFocused() const {
        return picture_->isFocused();
    }

    std::shared_ptr<tgui::Widget> Picture::getInternalPtr() {
        return picture_;
    }

    void Picture::initEvents() {
        picture_->onMouseEnter([this]{emit("mouseEnter");});
        picture_->onMouseLeave([this]{emit("mouseLeave");});
        picture_->onFocus([this]{emit("focus");});
        picture_->onUnfocus([this]{emit("unfocus");});
        picture_->onAnimationFinish([this]{emit("animationFinish");});
        picture_->onSizeChange([this](tgui::Vector2f newSize) {
            emit("sizeChange", newSize.x, newSize.y);
        });

        picture_->onPositionChange([this](tgui::Vector2f newPos) {
            emit("positionChange", newPos.x, newPos.y);
        });

        //Events triggered by left mouse button
        picture_->onClick([this](tgui::Vector2f mousePos){
            emit("click");
            emit("click", mousePos.x, mousePos.y);
        });

        picture_->onDoubleClick([this](tgui::Vector2f mousePos) {
            emit("doubleClick");
            emit("doubleClick", mousePos.x, mousePos.y);
        });

        picture_->onMousePress([this](tgui::Vector2f mousePos) {
            emit("leftMouseDown");
            emit("leftMouseDown", mousePos.x, mousePos.y);
        });

        picture_->onMouseRelease([this](tgui::Vector2f mousePos) {
            emit("leftMouseUp");
            emit("leftMouseUp", mousePos.x, mousePos.y);
        });

        //Events triggered by right mouse button
        picture_->onRightMousePress([this](tgui::Vector2f mousePos){
            emit("rightMouseDown");
            emit("rightMouseDown", mousePos.x, mousePos.y);
        });

        picture_->onRightMouseRelease([this](tgui::Vector2f mousePos){
            emit("rightMouseUp");
            emit("rightMouseUp", mousePos.x, mousePos.y);
        });

        picture_->onRightClick([this](tgui::Vector2f mousePos){
            emit("rightClick");
            emit("rightClick", mousePos.x, mousePos.y);
        });
    }
}

