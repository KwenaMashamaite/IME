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

#include "IME/core/scene/RenderLayerContainer.h"
#include <algorithm>

namespace ime {
    RenderLayer::Ptr RenderLayerContainer::create(const std::string& name) {
        IME_ASSERT(!hasLayer(name), "The render layer '" + name + "' already exists, try a different name");
        auto index = layers_.empty() ? 0 : ((*(layers_.rbegin())).first + 1);
        auto layer = RenderLayer::Ptr(new RenderLayer(index));
        layer->setTag(name);

        layers_.insert({index, layer});
        inverseLayers_.insert({name, index});

        return layer;
    }

    void RenderLayerContainer::add(const Drawable &drawable, int renderOrder,
                                   const std::string &renderLayer)
    {
        auto layer = findByName(renderLayer);
        if (!layer && renderLayer != "default") {
            layer = findByName("default");
            IME_ASSERT(layer, "The render layer '" + renderLayer + "' could not be found in the scenes render layers and the fallback layer 'default' is removed");
            IME_PRINT_WARNING("The render layer '" + renderLayer + "' does not exist, the object was added to the 'default' layer");
        }

        layer->add(drawable, renderOrder);
    }

    std::string RenderLayerContainer::getClassName() const {
        return "RenderLayerContainer";
    }

    RenderLayer::Ptr RenderLayerContainer::front() const {
        if (layers_.empty())
            return nullptr;

        return layers_.begin()->second;
    }

    RenderLayer::Ptr RenderLayerContainer::back() const {
        if (layers_.empty())
            return nullptr;

        return (layers_.rbegin())->second;
    }

    RenderLayer::Ptr RenderLayerContainer::findByIndex(unsigned int index) const {
        if (isIndexValid(index))
            return layers_.at(index);

        return nullptr;
    }

    RenderLayer::Ptr RenderLayerContainer::findByName(const std::string &name) const {
        if (hasLayer(name))
            return layers_.at(inverseLayers_.at(name));

        return nullptr;
    }

    bool RenderLayerContainer::isIndexValid(unsigned int index) const {
        return layers_.find(index) != layers_.end();
    }

    bool RenderLayerContainer::hasLayer(const std::string &name) const {
        return inverseLayers_.find(name) != inverseLayers_.end();
    }

    bool RenderLayerContainer::removeByIndex(unsigned int index) {
        if (isIndexValid(index)) {
            inverseLayers_.erase(layers_[index]->getTag());
            layers_.erase(index);
            return true;
        }

        return false;
    }

    bool RenderLayerContainer::removeByName(const std::string &name) {
        if (hasLayer(name)) {
            layers_.erase(inverseLayers_[name]);
            inverseLayers_.erase(name);
            return true;
        }

        return false;
    }

    void RenderLayerContainer::removeAll() {
        layers_.clear();
    }

    void RenderLayerContainer::moveUp(unsigned int index) {
        swap(index, index + 1);
    }

    void RenderLayerContainer::moveUp(const std::string &name) {
        if (hasLayer(name))
            moveUp(inverseLayers_[name]);
    }

    void RenderLayerContainer::moveDown(unsigned int index) {
        swap(index, index - 1);
    }

    void RenderLayerContainer::moveDown(const std::string &name) {
        if (hasLayer(name))
            moveDown(inverseLayers_[name]);
    }

    void RenderLayerContainer::moveToFront(unsigned int index) {
        if (!(isIndexValid(index) && std::prev(layers_.end())->first != index))
            return;

        for (auto iter = std::next(layers_.begin(), index); iter != layers_.end(); ++iter) {
            auto next = std::next(iter);

            if (next == layers_.end())
                break;

            swap(iter->first, next->first);

            // After swap function iter is swapped with next, so we restore it
            iter = std::prev(iter);
        }
    }

    void RenderLayerContainer::moveToFront(const std::string &name) {
        if (hasLayer(name))
            moveToFront(inverseLayers_[name]);
    }

    void RenderLayerContainer::sendToBack(unsigned int index) {
        if (!(isIndexValid(index) && layers_.begin()->first != index))
            return;

        for (auto iter = std::prev(layers_.rend(), index + 1); iter != layers_.rend(); ++iter) {
            auto next = std::next(iter);

            if (next == layers_.rend())
                break;

            swap(iter->first, next->first);
        }
    }

    void RenderLayerContainer::sendToBack(const std::string &name) {
        if (hasLayer(name))
            sendToBack(inverseLayers_[name]);
    }

    bool RenderLayerContainer::swap(unsigned int layerOneIndex, unsigned int layerTwoIndex) {
        if (layerOneIndex == layerTwoIndex)
            return false;

        auto first(layers_.extract(layerOneIndex));
        auto second(layers_.extract(layerTwoIndex));

        // std::map::extract() is destructive, therefore we re-insert the removed
        // entry if a swap is not possible
        if (first.empty() && second.empty())
            return false;
        else if (first.empty()) {
            layers_.insert(std::move(second));
            return false;
        } else if (second.empty()) {
            layers_.insert(std::move(first));
            return false;
        }

        std::swap(first.key(), second.key());

        layers_.insert(std::move(first));
        layers_.insert(std::move(second));

        // Update indexes
        layers_[layerOneIndex]->setIndex(layerOneIndex);
        layers_[layerTwoIndex]->setIndex(layerTwoIndex);

        // Update inverse map
        inverseLayers_[layers_[layerOneIndex]->getTag()] = layerOneIndex;
        inverseLayers_[layers_[layerTwoIndex]->getTag()] = layerTwoIndex;

        return true;
    }

    void RenderLayerContainer::swap(const std::string &layerOne, const std::string &layerTwo) {
        if (hasLayer(layerOne) && hasLayer(layerTwo))
            swap(inverseLayers_[layerOne], inverseLayers_[layerTwo]);
    }

    std::size_t RenderLayerContainer::getCount() const {
        return layers_.size();
    }

    void RenderLayerContainer::forEachLayer(Callback callback) {
        std::for_each(layers_.begin(), layers_.end(), [&callback](auto& pair) {
            callback(pair.second);
        });
    }

    void RenderLayerContainer::render(Window &window) const {
        std::for_each(layers_.begin(), layers_.end(), [&window](auto& pair) {
            if (pair.second->isDrawable())
                pair.second->render(window);
        });
    }
}
