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

#include "IME/core/scene/RenderLayer.h"
#include "IME/graphics/IDrawable.h"
#include "IME/graphics/Window.h"
#include "IME/core/game_object/GameObject.h"
#include <algorithm>

namespace ime {
    RenderLayer::RenderLayer(unsigned int index) :
        index_{index},
        shouldRender_{true}
    {}

    void RenderLayer::setName(const std::string &name) {
        name_ = name;
    }

    const std::string &RenderLayer::getName() const {
        return name_;
    }

    void RenderLayer::setDrawable(bool render) {
        shouldRender_ = render;
    }

    bool RenderLayer::isDrawable() const {
        return shouldRender_;
    }

    void RenderLayer::setIndex(unsigned int index) {
        index_ = index;
    }

    unsigned int RenderLayer::getIndex() const {
        return index_;
    }

    void RenderLayer::addDrawable(IDrawable& object, int renderOrder) {
        drawables_.insert({renderOrder, std::ref(object)});
    }

    void RenderLayer::addGameObject(GameObject::Ptr gameObject, int renderOrder) {
        if (gameObject)
            addDrawable(gameObject->getSprite(), renderOrder);
    }

    void RenderLayer::render(Window &window) {
        std::for_each(drawables_.begin(), drawables_.end(), [&window](auto& pair) {
            pair.second.get().draw(window);
        });
    }
}
