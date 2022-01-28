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

#ifndef IME_CAMERACONTAINER_H
#define IME_CAMERACONTAINER_H

#include "IME/Config.h"
#include "IME/graphics/Camera.h"
#include "IME/core/object/ObjectContainer.h"

namespace ime {
    /// @internal
    namespace priv {
        class RenderTarget;
    }

    /**
     * @brief Container for additional scene cameras
     */
    class IME_API CameraContainer : public ObjectContainer<Camera> {
    public:
        /**
         * @internal
         * @brief Constructor
         * @param renderTarget
         *
         * @warning This function is intended for internal use only and must
         * not be called outside of IME
         */
        explicit CameraContainer(priv::RenderTarget& renderTarget);

        /**
         * @brief Copy constructor
         */
        CameraContainer(const CameraContainer&) = delete;

        /**
         * @brief Copy assignment operator
         */
        CameraContainer& operator=(const CameraContainer&) = delete;

        /**
         * @brief Move constructor
         */
        CameraContainer(CameraContainer&&) = delete;

        /**
         * @brief Move assignment operator
         */
        CameraContainer& operator=(CameraContainer&&) = delete;

        /**
         * @brief Add a new camera to the scene
         * @param tag The unique identifier
         * @param group The group to assign the camera to
         * @return The created camera
         */
        Camera* add(const std::string& tag, const std::string& group = "none");

    private:
        priv::RenderTarget& renderTarget_;
        using ObjectContainer::addObject;
    };
}

#endif //IME_CAMERACONTAINER_H
