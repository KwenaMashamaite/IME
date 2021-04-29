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

template<typename T>
inline DrawableContainer<T>::DrawableContainer(RenderLayerContainer &renderLayers) :
    renderLayers_{renderLayers}
{
    static_assert(std::is_base_of<Drawable, T>::value, "A DrawableContainer can only store instances of classes derived from Drawable");
}

template<typename T>
inline T* DrawableContainer<T>::add(std::unique_ptr<T> drawable, int renderOrder,
    const std::string &renderLayer)
{
    IME_ASSERT(drawable, "Cannot add a nullptr to a DrawableContainer");
    renderLayers_.get().add(*drawable, renderOrder, renderLayer);
    return ObjectContainer<T>::addObject(std::move(drawable));
}
