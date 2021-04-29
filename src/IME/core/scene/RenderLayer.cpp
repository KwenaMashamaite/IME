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
#include "IME/graphics/Drawable.h"
#include "IME/graphics/Window.h"
#include "IME/core/game_object/GameObject.h"
#include <algorithm>

namespace ime {
    RenderLayer::RenderLayer(unsigned int index) :
        index_{index},
        shouldRender_{true}
    {}

    std::string RenderLayer::getClassName() const {
        return "RenderLayer";
    }

    void RenderLayer::setDrawable(bool render) {
        shouldRender_ = render;
        emitChange(Property{"drawable", render});
    }

    bool RenderLayer::isDrawable() const {
        return shouldRender_;
    }

    void RenderLayer::toggleDrawable() {
        setDrawable(!shouldRender_);
    }

    void RenderLayer::setIndex(unsigned int index) {
        index_ = index;
        emitChange(Property{"index", index});
    }

    unsigned int RenderLayer::getIndex() const {
        return index_;
    }

    void RenderLayer::add(const Drawable& drawable, int renderOrder) {
        if (has(drawable))
            return;

        auto handlerId = drawable.onDestruction([this, drawableRef = std::cref(drawable)] {
            remove(drawableRef);
        });

        drawables_.insert({renderOrder, std::pair{std::cref(drawable), handlerId}});
    }

    bool RenderLayer::has(const Drawable &drawable) const {
        return std::any_of(drawables_.begin(), drawables_.end(), [&drawable](auto& pair) {
            return pair.second.first.get() == drawable;
        });
    }

    bool RenderLayer::remove(const Drawable &drawable) {
        for (auto& [renderOrder, interDrawable] : drawables_) {
            if (drawable == interDrawable.first) {
                auto range = drawables_.equal_range(renderOrder);
                for (auto iter = range.first; iter != range.second; ++iter) {
                    auto& [drawableRef, destructionId] = iter->second;
                    if (drawableRef.get() == drawable) {
                        drawableRef.get().removeDestructionListener(destructionId);
                        drawables_.erase(iter);
                        return true;
                    }
                }
            }
        }
        return false;
    }

    void RenderLayer::removeAll() {
        removeDestructionHandlers();
        drawables_.clear();
    }

    std::size_t RenderLayer::getCount() const {
        return drawables_.size();
    }

    void RenderLayer::render(Window &window) const {
        std::for_each(drawables_.begin(), drawables_.end(), [&window](auto& pair) {
            pair.second.first.get().draw(window);
        });
    }

    void RenderLayer::removeDestructionHandlers() {
        std::for_each(drawables_.begin(), drawables_.end(), [](auto& pair) {
            pair.second.first.get().removeDestructionListener(pair.second.second);
        });
    }

    RenderLayer::~RenderLayer() {
        emit("destruction");
        removeDestructionHandlers();
    }
}
