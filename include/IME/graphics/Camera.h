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

#ifndef IME_CAMERA_H
#define IME_CAMERA_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/common/Rect.h"
#include "IME/core/object/Object.h"
#include "IME/graphics/Colour.h"
#include <memory>
#include <any>
#include <limits>

namespace ime {
    class GameObject;

    /// @internal
    namespace priv {
        class RenderTarget;
    }

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
     * instantiate a scene and it is accessed with ime::Scene::getCamera or
     * ime::Scene::getCameras
     */
    class IME_API Camera : public Object {
    public:
        /**
         * @brief Defines how the camera response to a window resize event
         */
        enum class OnWinResize {
            /**
             * This option squeezes/stretches the camera to match the new size
             * of the window
             */
            Stretch,

            /**
             * This option scales the camera while maintaining its aspect
             * ratio. If the aspect ratio of the camera and that of the window
             * do not match, black bars will appear vertically (to the left and
             * right of the camera) or horizontally (above and below the camera)
             */
            Letterbox,

            /**
             * This option updates the size of the camera to that of the window
             * without squeezing, stretching or scaling. This means that you
             * will see more or less of the scene depending on the new size of
             * the window
             */
            MaintainSize
        };

        /**
         * @internal
         * @brief Constructor
         * @param window The render target
         *
         * @warning This function is intended for internal use only and must
         * not be called outside of IME
         */
        explicit Camera(priv::RenderTarget& window);

        /**
         * @brief Copy constructor
         */
        Camera(const Camera&) = delete;

        /**
         * @brief Copy assignment operator
         */
        Camera& operator=(const Camera&) = delete;

        /**
         * @brief Move constructor
         */
        Camera(Camera&&) = delete;

        /**
         * @brief Move assignment operator
         */
        Camera& operator=(Camera&&) = delete;

        /**
         * @brief Get the name of this class
         * @return The name of this class
         */
        std::string getClassName() const override;

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
         * @brief Set how the camera responds to the window when it is resized
         * @param response The on resize event response
         *
         * By default, the response is ime::Camera::onWinResize::Stretch
         *
         * @see getWindowResizeResponse
         */
        void setWindowResizeResponse(OnWinResize response);

        /**
         * @brief Get the cameras response to a window resize event
         * @return The window resize response
         *
         * @see setWindowResizeResponse
         */
        OnWinResize getWindowResizeResponse() const;

        /**
         * @brief Set whether or not the scene should render the camera
         * @param drawable True to render the camera, otherwise false
         *
         * By default, the camera is drawable
         *
         * @see isDrawable
         */
        void setDrawable(bool drawable);

        /**
         * @brief Check if the camera is rendered by the scene
         * @return True if its contents are rendered, otherwise false
         *
         * @see setDrawable
         */
        bool isDrawable() const;

        /**
         * @brief Set the outline thickness
         * @param thickness The new outline thickness (must be >= 0)
         *
         * The outline thickness together with the outline colour enables
         * visualization if the camera bounds
         *
         * By default, the outline thickness is 1
         *
         * @see setOutlineColour, getOutlineThickness
         */
        void setOutlineThickness(float thickness);

        /**
         * @brief Get the outline thickness of the camera
         * @return The outline thickness
         *
         * @see setOutlineThickness
         */
        float getOutlineThickness() const;

        /**
         * @brief Set the outline colour
         * @param colour The new outline colour
         *
         * The outline colour together with the outline thickness enables
         * visualization of the camera bounds
         *
         * By default the outline colour is ime::Colour::Transparent
         *
         * @see setOutlineThickness, getOutlineColour
         */
        void setOutlineColour(const Colour& colour);

        /**
         * @brief Get the outline colour
         * @return The outline colour
         *
         * @see setOutlineColour
         */
        Colour getOutlineColour() const;

        /**
         * @brief Get the camera bounds
         * @return The bounds of the camera
         */
        FloatRect getBounds() const;

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
         * @param zoomPos Position to zoom at (leave unspecified to zoom at center)
         * @param factor The zoom factor to apply
         *
         * Resizing the view simulates a zoom, as the zone displayed on
         * screen grows or shrinks.
         *
         * @a factor is a multiplier:
         * @li 1 keeps the size unchanged
         * @li > 1 makes the view bigger (objects appear smaller)
         * @li < 1 makes the view smaller (objects appear bigger)
         *
         * By default the camera zooms in or out at its centre
         *
         * @see setSize
         */
        void zoom(float factor, const Vector2i& zoomPos = {std::numeric_limits<int>::max(), std::numeric_limits<int>::max()});

        /**
         * @brief Zoom the camera in
         * @param zoomPos Position to zoom in at (leave unspecified to zoom at center)
         * @param factor The zoom factor
         *
         * The @a factor argument must be greater than 1 in order to zoom out,
         * values equal to 1 or less than are ignored
         *
         * By default, the camera zooms out from its centre
         *
         * @see zoomOut, setCenter
         */
        void zoomIn(float factor, const Vector2i& zoomPos = {std::numeric_limits<int>::max(), std::numeric_limits<int>::max()});

        /**
         * @brief Zoom the camera out
         * @param zoomPos Position to zoom out at (leave unspecified to zoom at center)
         * @param factor The zoom out factor
         *
         * The @a factor argument must be greater than 1 in order to zoom out,
         * values equal to 1 or less than are ignored
         *
         * By default, the camera zooms in at its centre
         *
         * @see zoomIn, setCenter
         */
        void zoomOut(float factor, const Vector2i& zoomPos = {std::numeric_limits<int>::max(), std::numeric_limits<int>::max()});

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
         * @brief Set the camera to follow a GameObject
         * @param gameObject The game object to be followed
         * @param offset The offset of the camera from the game objects position
         *
         * * A positive @a x offset places the camera to the right of the target,
         * while a negative @a x offset places the camera to the left of the
         * target. Similarly, a positive @a y offset places the camera below
         * the target while a negative @a y offset places the camera above the
         * target.
         *
         * By default, the camera will keep the game object at its centre
         *
         * @warning @a gameObject must not be a nullptr, otherwise undefined
         * behavior
         *
         * @see stopFollow, setFollowOffset
         */
        void startFollow(GameObject* gameObject, const Vector2f& offset = {0, 0});

        /**
         * @brief Stop the camera from following a game object
         *
         * @see setFollow
         */
        void stopFollow();

        /**
         * @brief Check if the camera is following a game object or not
         * @return True if the camera is following a game object, otherwise false
         *
         * @see startFollow
         */
        bool isFollowingTarget() const;

        /**
         * @brief Get that game object followed by the camera
         * @return The game object followed by the camera or a nullptr if
         *          the camera is not following any game object
         *
         * @see startFollow
         */
        GameObject* getFollowTarget() const;

        /**
         * @brief Set the camera's follow offset from the targets position
         * @param offset The new follow offset
         *
         * A positive @a x offset places the camera to the right of the target,
         * while a negative @a x offset places the camera to the left of the
         * target. Similarly, a positive @a y offset places the camera below
         * the target while a negative @a y offset places the camera above the
         * target
         *
         * By default the offset is Vector2f{0, 0} which means that the camera
         * keeps the game object at its centre
         */
        void setTargetFollowOffset(const Vector2f& offset);

        /**
         * @brief Get the camera's follow target offset
         * @return Th camera's follow target offset
         */
        const Vector2f& getTargetFollowOffset() const;

        /**
         * @internal
         * @brief Set a new internal view
         * @param view The new view
         *
         * @warning This function is intended for internal use only and should
         * never be called outside of IME
         */
        void setInternalView(std::any view);

        /**
         * @internal
         * @brief Get the internal view
         * @return Constant Reference wrapper to the internal view
         *
         * @warning This function is intended for internal use only and should
         * never be called outside of IME
         */
        std::any getInternalView();

        /**
         * @brief Destructor
         */
        ~Camera() override;

    private:
        class CameraImpl;
        std::unique_ptr<CameraImpl> pimpl_;
    };
}

#endif //IME_CAMERA_H
