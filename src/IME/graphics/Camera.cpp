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

#include "IME/graphics/Camera.h"
#include "WindowImpl.h"
#include <SFML/Graphics/View.hpp>

namespace ime {
    class Camera::CameraImpl {
    public:
        /**
         * @brief Construct the camera from its centre and size
         * @param window The render window
         * @param centre The centre of the zone to display
         * @param size Size of the zone to display
         */
        explicit CameraImpl(Window& window) :
            window_{window.getImpl()->getSFMLWindow()},
            view{window_.getDefaultView()}
        {
            window_.setView(view);
        }

        void setCenter(float x, float y) {
            view.setCenter(x, y);
            window_.setView(view);
        }

        void setCenter(const Vector2f &centre) {
            view.setCenter({centre.x, centre.y});
            window_.setView(view);
        }

        Vector2f getCenter() const {
            return {view.getCenter().x, view.getCenter().y};
        }

        void setSize(float width, float height) {
            view.setSize(width, height);
            window_.setView(view);
        }

        void setSize(const Vector2f &size) {
            view.setSize({size.x, size.y});
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
            view.setViewport({viewport.top, viewport.left, viewport.width, viewport.height});
            window_.setView(view);
        }

        FloatRect getViewport() const {
            auto viewport = view.getViewport();
            return {viewport.top, viewport.left, viewport.width, viewport.height};
        }

        void reset(const FloatRect &rectangle) {
            view.reset({rectangle.top, rectangle.left, rectangle.width, rectangle.height});
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

        void move(const Vector2f &offset) {
            view.move({offset.x, offset.y});
            window_.setView(view);
        }

        void rotate(float angle) {
            view.rotate(angle);
            window_.setView(view);
        }

        void zoom(float factor) {
            view.zoom(factor);
            window_.setView(view);
        }

        Vector2f windowCoordToWorldCoord(const Vector2i &point) const {
            auto worldCoord = window_.mapPixelToCoords({point.x, point.y});
            return {worldCoord.x, worldCoord.y};
        }

        Vector2i worldCoordToWindowCoord(const Vector2f &point) const {
            auto windowCoord = window_.mapCoordsToPixel({point.x, point.y});
            return {windowCoord.x, windowCoord.y};
        }

    private:
        sf::RenderWindow& window_;
        sf::View view;
    };

    ///////////////////////////////////////////////////////////////////////////

    Camera::Camera(Window &window) :
        pimpl_{std::make_unique<CameraImpl>(window)}
    {}

    std::string Camera::getClassName() const {
        return "Camera";
    }

    void Camera::setCenter(float x, float y) {
        pimpl_->setCenter(x, y);
    }

    void Camera::setCenter(const Vector2f &centre) {
        pimpl_->setCenter(centre);
    }

    Vector2f Camera::getCenter() const {
        return pimpl_->getCenter();
    }

    void Camera::setSize(float width, float height) {
        pimpl_->setSize(width, height);
    }

    void Camera::setSize(const Vector2f &size) {
        pimpl_->setSize(size);
    }

    Vector2f Camera::getSize() const {
        return pimpl_->getSize();
    }

    void Camera::setRotation(float angle) {
        pimpl_->setRotation(angle);
    }

    float Camera::getRotation() const {
        return pimpl_->getRotation();
    }

    void Camera::setViewport(const FloatRect &viewport) {
        pimpl_->setViewport(viewport);
    }

    FloatRect Camera::getViewport() const {
        return pimpl_->getViewport();
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
        pimpl_->move(offset);
    }

    void Camera::rotate(float angle) {
        pimpl_->rotate(angle);
    }

    void Camera::zoom(float factor) {
        pimpl_->zoom(factor);
    }

    Vector2f Camera::windowCoordToWorldCoord(const Vector2i &point) const {
        return pimpl_->windowCoordToWorldCoord(point);
    }

    Vector2i Camera::worldCoordToWindowCoord(const Vector2f &point) const {
        return pimpl_->worldCoordToWindowCoord(point);
    }

    Camera::~Camera() = default;
}
