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

#ifndef IME_DRAWABLECONTAINER_H
#define IME_DRAWABLECONTAINER_H

#include "IME/core/object/ObjectContainer.h"
#include "IME/graphics/Drawable.h"
#include "IME/core/scene/RenderLayerContainer.h"

namespace ime {
    /**
     * @brief A container for Drawable objects
     */
    template <typename T>
    class DrawableContainer : public ObjectContainer<T> {
    public:
        /**
         * @brief Constructor
         * @param renderLayers The render layer container for
         */
        explicit DrawableContainer(RenderLayerContainer& renderLayers);

        /**
         * @brief Add a drawable object to the container
         * @param drawable The drawable object to be added
         * @param renderOrder The render order of the object in the render layer
         * @param renderLayer The RenderLayer the object belongs to
         * @return A pointer to the drawable in the container
         *
         * If the render layer is unspecified or the specified layer cannot be
         * found then the drawable will be added to the 'default' layer. The
         * 'default' render layer is created by the Scene when you instantiate
         * it. Note that the 'default' layer may be deleted from the scenes
         * render layers, however you must make sure that the layer you specify
         * during a call to this function already exists otherwise undefined
         * behavior
         */
        T* add(std::unique_ptr<T> drawable, int renderOrder = 0u,
            const std::string& renderLayer = "default");

    private:
        std::reference_wrapper<RenderLayerContainer> renderLayers_;
        using ObjectContainer<T>::addObject;
    };

    #include "IME/core/scene/DrawableContainer.inl"

    class Sprite;
    class Shape;

    using SpriteContainer = DrawableContainer<Sprite>; //!< Shape object container
    using ShapeContainer = DrawableContainer<Shape>;   //!< Sprite object container
}

#endif //IME_DRAWABLECONTAINER_H
