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

#include "IME/core/scene/ShapeContainer.h"
#include "IME/utility/Helpers.h"
#include "IME/graphics/Window.h"
#include <algorithm>

namespace ime {
    Shape::sharedPtr ShapeContainer::createShape(Shape::Type type) {
        switch (type) {
            case Shape::Type::Rectangle:
                shapes_.push_back(RectangleShape::create());
                break;
            case Shape::Type::Circle:
                shapes_.push_back(CircleShape::create());
                break;
            case Shape::Type::Convex:
                shapes_.push_back(ConvexShape::create());
                break;
            default:
                IME_ASSERT(false, "Invalid shape type given");
        }
        return shapes_.back();
    }

    bool ShapeContainer::removeShape(Shape::sharedPtr shape) {
        return utility::eraseIn(shapes_, shape);
    }

    void ShapeContainer::removeAll() {
        shapes_.clear();
    }

    std::size_t ShapeContainer::getShapesCount() const {
        return shapes_.size();
    }

    void ShapeContainer::render(Window &window, Callback<Shape::sharedPtr> preRenderCallback) {
        forEachShape([&window, &preRenderCallback](Shape::sharedPtr shape) {
            if (preRenderCallback)
                preRenderCallback(shape);
            shape->draw(window);
        });
    }

    void ShapeContainer::forEachShape(Callback<Shape::sharedPtr> callback) {
        std::for_each(shapes_.begin(), shapes_.end(), callback);
    }
}
