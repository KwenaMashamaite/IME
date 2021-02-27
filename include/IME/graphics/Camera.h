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

#ifndef IME_CAMERA_H
#define IME_CAMERA_H

#include "IME/Config.h"
#include "IME/utility/NonCopyable.h"
#include "IME/common/Vector2.h"
#include "IME/common/Rect.h"
#include <memory>

namespace ime {
    class Window;

    /**
     * @brief A 2D camera that defines what region is shown on screen in a Scene
     *
     * A camera is composed of a source rectangle, which defines what part of
     * the Scene is shown, and a target viewport, which defines where the
     * contents of the source rectangle will be displayed on the render Window.
     *
     * The viewport allows to map the scene to a custom part  of the render
     * window, and can be used for split-screen or for displaying a minimap,
     * for example. If the source rectangle doesn't have the same size as the
     * viewport, its contents will be stretched to fit in
     *
     * You do not instantiate a camera directly, it is created when you
     * instantiate a scene and it is accessible within the scene. Each
     * scene instance has its own camera
     */
    class IME_API Camera : utility::NonCopyable {
    public:
        /**
         * @brief Move constructor
         */
        Camera(Camera&&) = delete;

        /**
         * @brief Move assignment operator
         */
        Camera& operator=(Camera&&) = delete;

        /**
         * @brief Set the centre of the camera
         * @param x X coordinate of the new centre
         * @param y Y coordinate of the new centre
         */
        void setCenter(float x, float y);

        /**
         * @brief Set the centre of the camera
         * @param centre The new centre of the camera
         */
        void setCenter(const Vector2f& centre);

        /**
         * @brief Get the centre of the camera
         * @return The centre of the camera
         */
        Vector2f getCenter() const;

        /**
         * @brief Set the size of the camera
         * @param width The new width of the camera
         * @param height The new height of the camera
         *
         * By default, the camera is the same size as the render window
         */
        void setSize(float width, float height);

        /**
         * @brief Set the size of the camera
         * @param size The new size of the camera
         *
         * By default, the camera is the same size as the render window
         */
        void setSize(const Vector2f& size);

        /**
         * @brief Get the size of the camera
         * @return The size of the camera
         */
        Vector2f getSize() const;

        /**
         * @brief Set the orientation of the camera
         * @param angle The orientation to set in degrees
         *
         * By default, the rotation is 0 degrees
         */
        void setRotation(float angle);

        /**
         * @brief Get the current orientation of the camera
         * @return The rotation of the camera in degrees
         */
        float getRotation() const;

        /**
         * @brief Set the target viewport
         * @param viewport The new viewport rectangle
         *
         * The viewport is the rectangle into which the contents of the
         * camera are displayed, expressed as a factor (between 0 and 1)
         * of the size of the RenderWindow. For example, a view which takes
         * the left side of the target would be defined with
         * View.setViewport(sf::FloatRect(0, 0, 0.5, 1)).
         *
         * By default, a camera has a viewport which covers the entire render
         * window
         */
        void setViewport(const FloatRect& viewport);

        /**
         * @brief Get the target viewport of the rectangle of the camera
         * @return The viewport rectangle, expressed as a factor of the target
         *         size
         *
         * @see setViewPort
         */
        FloatRect getViewport() const;

        /**
         * @brief Reset the camera to the given rectangle
         * @param rectangle Rectangle defining the zone to display
         *
         * @note This function resets the rotation of the camera to 0 degrees
         */
        void reset(const FloatRect& rectangle);

        /**
         * @brief Reset the camera to its default settings
         */
        void resetToDefault();

        /**
         * @brief Move the camera relative to its current position
         * @param offsetX The value of the horizontal move offset
         * @param offsetY The value of the vertical move offset
         */
        void move(float offsetX, float offsetY);

        /**
         * @brief Move the camera relative to its current position
         * @param offset The move offset
         */
        void move(const Vector2f& offset);

        /**
         * @brief Rotate the camera relative to its current orientation
         * @param angle The angle to rotate the camera by in degrees
         *
         * @see setRotation
         */
        void rotate(float angle);

        /**
         * @brief Resize the camera rectangle relative to its current size
         * @param factor The zoom factor to apply
         *
         * Resizing the view simulates a zoom, as the zone displayed on
         * screen grows or shrinks.
         * @a factor is a multiplier:
         * @li 1 keeps the size unchanged
         * @li > 1 makes the view bigger (objects appear smaller)
         * @li < 1 makes the view smaller (objects appear bigger)
         *
         * @see setSize
         */
        void zoom(float factor);

        /**
         * @brief Convert a window coordinate to a world coordinate
         * @param point The window coordinate to be converted
         * @return The converted point in world coordinates
         *
         * Initially, both coordinate systems (world coordinates and window
         * pixels) match perfectly. But if you move or rotate the camera or
         * resize the render Window then a mismatch occurs, i.e. a point
         * located at (10, 50) on the render Window may map to the point
         * (150, 75) in your 2D world -- if the camera is translated by
         * (140, 25)
         */
        Vector2f windowCoordToWorldCoord(const Vector2i& point) const;

        /**
         * @brief Convert a world coordinate to a window coordinate
         * @param point The world point ot be converted
         * @return The converted point in window coordinates
         *
         * Initially, both coordinate systems (world coordinates and window
         * pixels) match perfectly. But if you move or rotate the camera or
         * resize the render Window then a mismatch occurs, i.e. a point
         * located at (10, 50) on the render Window may map to the point
         * (150, 75) in your 2D world -- if the camera is translated by
         * (140, 25)
         */
        Vector2i worldCoordToWindowCoord(const Vector2f& point) const;

        /**
         * @brief Destructor
         */
        ~Camera();

    private:
        /**
         * @brief Construct the camera from a rectangle
         * @param rectangle The rectangle defining the zone to display
         */
        explicit Camera(Window& window);

    private:
        class CameraImpl;
        std::unique_ptr<CameraImpl> pimpl_;
        friend class Scene; //!< Needs access to constructor
    };
}

#endif //IME_CAMERA_H
