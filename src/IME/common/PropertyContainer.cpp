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

#include "IME/common/PropertyContainer.h"
#include "IME/utility/Helpers.h"
#include <algorithm>

namespace ime {
    bool PropertyContainer::addProperty(const Property &property) {
        return properties_.emplace(property.getName(), property).second;
    }

    bool PropertyContainer::addProperty(Property &&property) {
        return properties_.insert({property.getName(), std::move(property)}).second;
    }

    bool PropertyContainer::removeProperty(const std::string &name) {
        if (hasProperty(name)) {
            properties_.erase(name);
            return true;
        }
        return false;
    }

    std::size_t PropertyContainer::getCount() const {
        return properties_.size();
    }

    void PropertyContainer::clear() {
        properties_.clear();
    }

    bool PropertyContainer::hasProperty(const std::string &name) const {
        return properties_.find(name) != properties_.end();
    }

    void PropertyContainer::forEachProperty(const Callback<Property&>& callback) const {
        std::for_each(properties_.begin(), properties_.end(), [&callback](auto property) {
            callback(property.second);
        });
    }

    bool PropertyContainer::propertyHasValue(const std::string &name) const {
        if (hasProperty(name))
            return properties_.at(name).hasValue();
        return false;
    }
}
