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

#include "IME/graphics/Camera.h"
#include "IME/core/object/GameObject.h"
#include "IME/graphics/RenderTarget.h"
#include "IME/utility/Helpers.h"

namespace ime {
    class Camera::CameraImpl {
    public:
        /**
         * @brief Construct the camera from its centre and size
         * @param window The render window
         * @param centre The centre of the zone to display
         * @param size Size of the zone to display
         */
        explicit CameraImpl(priv::RenderTarget& window) :
            window_{window.getThirdPartyWindow()},
            view{window_.getDefaultView()},
            followTarget_{nullptr},
            posChangeId_{-1},
            outlineColour_{Colour::Transparent},
            outlineThickness_{1},
            isDrawable_{true},
            onWinResize_{OnWinResize::Stretch}
        {
            window_.setView(view);
        }

        void setCenter(float x, float y) {
            view.setCenter(x, y);
            window_.setView(view);
        }

        void setCenter(const Vector2f& position) {
            setCenter(position.x, position.y);
        }

        Vector2f getCenter() const {
            return {view.getCenter().x, view.getCenter().y};
        }

        void setSize(float width, float height) {
            view.setSize(width, height);
            window_.setView(view);
        }

        Vector2f getSize() const {
            return {view.getSize().x, view.getSize().y};
        }

        void setRotation(float angle) {
            view.setRotation(angle);
            window_.setView(view);
        }

        float getRotation() const {
            return view.getRotation();
        }

        void setViewport(const FloatRect &viewport) {
            view.setViewport({viewport.left, viewport.top, viewport.width, viewport.height});
            window_.setView(view);
        }

        FloatRect getViewport() const {
            sf::FloatRect viewport = view.getViewport();
            return FloatRect{viewport.left, viewport.top, viewport.width, viewport.height};
        }

        void setWindowResizeResponse(Camera::OnWinResize response) {
            if (onWinResize_ != response) {
                if (response == OnWinResize::Letterbox) {
                    view = utility::letterbox(view, window_.getSize().x, window_.getSize().y);
                    window_.setView(view);
                } else if (response == OnWinResize::MaintainSize)
                    setSFMLView(sf::View(sf::FloatRect{0, 0, static_cast<float>(window_.getSize().x), static_cast<float>(window_.getSize().y)}));
                else if (onWinResize_ == OnWinResize::Letterbox) // Reset letterboxing
                    view.setViewport(sf::FloatRect(0, 0, 1, 1));

                onWinResize_ = response;
            }
        }

        Camera::OnWinResize getWindowResizeResponse() const {
            return onWinResize_;
        }

        void setDrawable(bool drawable) {
            isDrawable_ = drawable;
        }

        bool isDrawable() const {
            return isDrawable_;
        }

        void setOutlineThickness(float thickness) {
            if (thickness >= 0.0f)
                outlineThickness_ = thickness;
        }

        float getOutlineThickness() const {
            return outlineThickness_;
        }

        void setOutlineColour(const Colour &colour) {
            outlineColour_ = colour;
        }

        const Colour& getOutlineColour() const {
            return outlineColour_;
        }

        FloatRect getBounds() const {
            Vector2f size = getSize();
            auto [leftCoord, topCoord] = getCenter() - size / 2.0f;
            return {leftCoord, topCoord, size.x, size.y};
        }

        void reset(const FloatRect &rectangle) {
            view.reset({rectangle.left, rectangle.top, rectangle.width, rectangle.height});
            window_.setView(view);
        }

        void resetToDefault() {
            view = window_.getDefaultView();
            window_.setView(view);
        }

        void move(float offsetX, float offsetY) {
            view.move(offsetX, offsetY);
            window_.setView(view);
        }

        void zoom(float factor, const Vector2i& zoomPos) {
            if (zoomPos.x != std::numeric_limits<int>::max() && zoomPos.y != std::numeric_limits<int>::max()) {
                const Vector2f posBeforeZoom = windowCoordToWorldCoord(zoomPos);
                view.zoom(factor);
                window_.setView(view);
                const Vector2f posAfterZoom = windowCoordToWorldCoord(zoomPos);
                const Vector2f offset{posBeforeZoom - posAfterZoom};
                move(offset.x, offset.y);
            } else {
                view.zoom(factor);
                window_.setView(view);
            }
        }

        Vector2f windowCoordToWorldCoord(const Vector2i &point) const {
            sf::Vector2f worldCoord = window_.mapPixelToCoords(sf::Vector2i{point.x, point.y});
            return Vector2f{worldCoord.x, worldCoord.y};
        }

        Vector2i worldCoordToWindowCoord(const Vector2f &point) const {
            sf::Vector2i windowCoord = window_.mapCoordsToPixel(sf::Vector2f{point.x, point.y});
            return Vector2i{windowCoord.x, windowCoord.y};
        }

        void startFollow(GameObject* gameObject, const Vector2f& offset) {
            IME_ASSERT(gameObject, "A camera's follow target cannot be a nullptr")
            followTarget_ = gameObject;
            followOffset_ = offset;

            posChangeId_ = gameObject->onPropertyChange("position", [this](const Property& position) {
                setCenter(position.getValue<Vector2f>() + followOffset_);
            });

            gameObject->onDestruction([this] {
                followTarget_ = nullptr;
            });
        }

        void stopFollow() {
            if (followTarget_) {
                followTarget_->removeEventListener("position", posChangeId_);
                followTarget_ = nullptr;
            }
        }

        GameObject* getFollowTarget() const {
            return followTarget_;
        }

        bool isFollowingTarget() const {
            return followTarget_ != nullptr;
        }

        void setTargetFollowOffset(const Vector2f &offset) {
            followOffset_ = offset;
        }

        const Vector2f& getTargetFollowOffset() const {
            return followOffset_;
        }

        void setSFMLView(sf::View newView) {
            view = newView;
            window_.setView(view);
        }

        const sf::View& getSFMLView() {
            return view;
        }

    private:
        sf::RenderWindow& window_;
        sf::View view;
        GameObject* followTarget_;  //!< The game object to be followed by the camera
        int posChangeId_;           //!< The follow targets position change handler
        Vector2f followOffset_;     //!< The camera's follow offset from the targets position
        Colour outlineColour_;      //!< The cameras outline colour
        float outlineThickness_;
        bool isDrawable_;
        OnWinResize onWinResize_;
    };

    ///////////////////////////////////////////////////////////////////////////

    Camera::Camera(priv::RenderTarget &window) :
        pimpl_{std::make_unique<CameraImpl>(window)}
    {}

    std::string Camera::getClassName() const {
        return "Camera";
    }

    void Camera::setCenter(float x, float y) {
        Vector2f center = getCenter();
        if (center.x == x && center.y == y)
            return;

        pimpl_->setCenter(x, y);
        emitChange(Property{"centre", Vector2f{x, y}});
    }

    void Camera::setCenter(const Vector2f &centre) {
        setCenter(centre.x, centre.y);
    }

    Vector2f Camera::getCenter() const {
        return pimpl_->getCenter();
    }

    void Camera::setSize(float width, float height) {
        Vector2f size = getSize();

        if (size.x == width && size.y == height)
            return;

        pimpl_->setSize(width, height);
        emitChange(Property{"size", Vector2f{width, height}});
    }

    void Camera::setSize(const Vector2f &size) {
        setSize(size.x, size.y);
    }

    Vector2f Camera::getSize() const {
        return pimpl_->getSize();
    }

    void Camera::setRotation(float angle) {
        if (getRotation() == angle)
            return;

        pimpl_->setRotation(angle);
        emitChange(Property{"rotation", angle});
    }

    float Camera::getRotation() const {
        return pimpl_->getRotation();
    }

    void Camera::setViewport(const FloatRect &viewport) {
        if (getViewport() == viewport)
            return;

        pimpl_->setViewport(viewport);
        emitChange(Property{"viewport", viewport});
    }

    FloatRect Camera::getViewport() const {
        return pimpl_->getViewport();
    }

    void Camera::setWindowResizeResponse(Camera::OnWinResize response) {
        pimpl_->setWindowResizeResponse(response);
    }

    Camera::OnWinResize Camera::getWindowResizeResponse() const {
        return pimpl_->getWindowResizeResponse();
    }

    void Camera::setDrawable(bool drawable) {
        pimpl_->setDrawable(drawable);
    }

    bool Camera::isDrawable() const {
        return pimpl_->isDrawable();
    }

    void Camera::setOutlineThickness(float thickness) {
        pimpl_->setOutlineThickness(thickness);
    }

    float Camera::getOutlineThickness() const {
        return pimpl_->getOutlineThickness();
    }

    void Camera::setOutlineColour(const Colour &colour) {
        pimpl_->setOutlineColour(colour);
    }

    Colour Camera::getOutlineColour() const {
        return pimpl_->getOutlineColour();
    }

    FloatRect Camera::getBounds() const {
        return pimpl_->getBounds();
    }

    void Camera::reset(const FloatRect &rectangle) {
        pimpl_->reset(rectangle);
    }

    void Camera::resetToDefault() {
        pimpl_->resetToDefault();
    }

    void Camera::move(float offsetX, float offsetY) {
        pimpl_->move(offsetX, offsetY);
    }

    void Camera::move(const Vector2f &offset) {
        move(offset.x, offset.y);
    }

    void Camera::rotate(float angle) {
        setRotation(getRotation() + angle);
    }

    void Camera::zoom(float factor, const Vector2i& zoomPos) {
        pimpl_->zoom(factor, zoomPos);
    }

    void Camera::zoomIn(float factor, const Vector2i& zoomPos) {
        if (factor > 1)
            zoom(1.0f / factor, zoomPos);
    }

    void Camera::zoomOut(float factor, const Vector2i& zoomPos) {
        if (factor > 1)
            zoom(factor, zoomPos);
    }

    Vector2f Camera::windowCoordToWorldCoord(const Vector2i &point) const {
        return pimpl_->windowCoordToWorldCoord(point);
    }

    Vector2i Camera::worldCoordToWindowCoord(const Vector2f &point) const {
        return pimpl_->worldCoordToWindowCoord(point);
    }

    void Camera::startFollow(GameObject *gameObject, const Vector2f& offset) {
        if (getFollowTarget() == gameObject)
            return;

        pimpl_->startFollow(gameObject, offset);
    }

    void Camera::stopFollow() {
        if (!isFollowingTarget())
            return;

        pimpl_->stopFollow();
    }

    bool Camera::isFollowingTarget() const {
        return pimpl_->isFollowingTarget();
    }

    GameObject* Camera::getFollowTarget() const {
        return pimpl_->getFollowTarget();
    }

    void Camera::setTargetFollowOffset(const Vector2f &offset) {
        if (getTargetFollowOffset() == offset)
            return;

        pimpl_->setTargetFollowOffset(offset);
        emitChange(Property{"targetFollowOffset", offset});
    }

    const Vector2f &Camera::getTargetFollowOffset() const {
        return pimpl_->getTargetFollowOffset();
    }

    void Camera::setInternalView(std::any view) {
        pimpl_->setSFMLView(std::any_cast<sf::View>(view));
    }

    std::any Camera::getInternalView() {
        return std::any{std::cref(pimpl_->getSFMLView())};
    }

    Camera::~Camera() {
        stopFollow();
    }
}
