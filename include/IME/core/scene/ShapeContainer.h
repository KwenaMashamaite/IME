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

#ifndef IME_SHAPECONTAINER_H
#define IME_SHAPECONTAINER_H

#include "IME/Config.h"
#include "IME/core/scene/Container.h"
#include "IME/graphics/shapes/Shape.h"
#include <memory>
#include <vector>

namespace ime {
    /**
     * @brief Shape container class
     *
     * This class mimics a factory class but it is not one. It is just a
     * convenience class for instantiating and storing geometry shapes
     * so that they can be automatically simulated and rendered by the
     * scene on your behalf. You can create the shape using its constructor
     * and manually update it (This is allowed). However, the advantage
     * of creating a shape through this class is that, when the shape has a
     * rigid body attached to it, you don't have to do something like this:
     *
     * @code
     * GameScene::render(ime::Window& window) {
     *     for (auto& shape : m_shapes) {
     *         shape.setPosition(shape.getRigidBody()->getPosition());
     *         shape.setRotation(shape.getRigidBody()->getRotation());
     *         shape.setOrigin(shape.getRigidBody()->getLocalCentre());
     *
     *         window.draw(myShape);
     *     }
     * }
     * @endcode
     *
     * The above code has the disadvantage that the transform of the shape
     * is always out of sync with the rigid body attached to it after a physics
     * step. So if you intend to attach a rigid body to the shape, it is
     * recommended that you create a shape using this class
     *
     * @note This class is not meant to be instantiated directly as it will
     * be instantiated by the Scene
     */
    class IME_API ShapeContainer final : public Container<Shape> {
    public:
        /**
         * @brief Create a shape
         * @param type The type of the shape to be created
         * @return The created shape
         *
         * @note a reference to the shape is kept so that it can be simulated
         * if it has a rigid body attached and rendered so that you don't have
         * to do that manually
         */
        Shape::sharedPtr createShape(Shape::Type type);

        /**
         * @brief Create a shape
         * @param type The type of the shape to be created
         * @return The created shape casted to the desired type
         *
         * @note a reference to the shape is kept so that it can be simulated
         * if it has a rigid body attached and rendered so that you don't have
         * to do that manually
         *
         * @warning if the template parameter and the type provided don't
         * match then accessing the returned pointer is undefined behavior
         * For example, when the type is Shape::Type::Rectangle, then the
         * template argument must be RectangleShape like so createShape<RectangleShape>(...)
         */
        template<class T>
        std::shared_ptr<T> createShape(Shape::Type type);
    };

    #include "IME/core/scene/ShapeContainer.inl"
}

#endif //IME_SHAPECONTAINER_H
