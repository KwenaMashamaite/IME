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

#ifndef IME_GAMEOBJECTCONTAINER_H
#define IME_GAMEOBJECTCONTAINER_H

#include "IME/Config.h"
#include "IME/core/object/ObjectContainer.h"
#include "IME/core/object/GameObject.h"
#include "IME/core/scene/RenderLayerContainer.h"

namespace ime {
    /**
     * @brief A container for GameObject instances
     */
    class IME_API GameObjectContainer : public ObjectContainer<GameObject> {
    public:
        /**
         * @brief Constructor
         * @param renderLayers The render layer container for
         */
        explicit GameObjectContainer(RenderLayerContainer& renderLayers);

        /**
         * @brief Add a game object to the container
         * @param gameObject The game object to be added
         * @param renderOrder The render order of the game object
         * @param renderLayer The render layer the game object belongs to
         * @return A pointer to the game object after its added to the container
         *
         * If the render layer is unspecified or the specified layer cannot
         * be found then the game object will be added to the @a default layer.
         * The @a default layer is created by the Scene when you instantiate
         * it. Note that the @a default layer may be deleted from the scenes
         * render layers, however you must make sure that the layer you specify
         * during a call to this function already exists otherwise undefined
         * behavior
         */
        GameObject* add(GameObject::Ptr gameObject, int renderOrder = 0u,
             const std::string& renderLayer = "default");

        /**
         * @brief Add a game object to the container
         * @param gameObject The game object to be added
         * @param renderOrder The render order of the game object
         * @param renderLayer The render layer the game object belongs to
         * @return A pointer casted to type T after the or a nullptr if the object is
         *         not convertible to T
         *
         * If the render layer is unspecified or the specified layer cannot
         * be found then the game object will be added to the @a default layer.
         * The @a default layer is created by the Scene when you instantiate
         * it. Note that the @a default layer may be deleted from the scenes
         * render layers, however you must make sure that the layer you specify
         * during a call to this function already exists otherwise undefined
         * behavior
         */
        template <typename T>
        T* add(GameObject::Ptr gameObject, int renderOrder = 0u,
               const std::string& renderLayer = "default")
        {
            return dynamic_cast<T*>(add(std::move(gameObject), renderOrder, renderLayer));
        }

        /**
         * @brief Add a game object to a group in the container
         * @param group The group to assign the game object to
         * @param gameObject The game object to be added
         * @param renderOrder The render order of the game object
         * @param renderLayer The render layer the game object belongs to
         * @return A pointer to the object in the container
         *
         * * If the render layer is unspecified or the specified layer cannot
         * be found then the game object will be added to the @a default layer.
         * The @a default layer is created by the Scene when you instantiate
         * it. Note that the @a default layer may be deleted from the scenes
         * render layers, however you must make sure that the layer you specify
         * during a call to this function already exists otherwise undefined
         * behavior
         */
        GameObject* add(const std::string& group, GameObject::Ptr gameObject,
             int renderOrder = 0u, const std::string& renderLayer = "default");

    private:
        std::reference_wrapper<RenderLayerContainer> renderLayers_;
        using ObjectContainer<GameObject>::addObject;
    };
}

#endif //IME_GAMEOBJECTCONTAINER_H
