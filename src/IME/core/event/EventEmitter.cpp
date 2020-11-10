////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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

#include "IME/core/event/EventEmitter.h"
#include <algorithm>

namespace IME {
    EventEmitter::EventEmitter(const EventEmitter &other) {
        std::scoped_lock lock(other.mutex_);
        eventList_ = other.eventList_;
    }

    EventEmitter &EventEmitter::operator=(const EventEmitter &rhs) {
        if (this != &rhs) {
            std::scoped_lock lock(mutex_, rhs.mutex_);
            eventList_ = rhs.eventList_;
        }
        return *this;
    }

    bool EventEmitter::removeEventListener(const std::string &event, int listenerId) {
        std::scoped_lock lock(mutex_);
        if (hasEvent(event)) {
            if (auto [found, index] = hasListener(event, listenerId); found) {
                eventList_.at(event).erase(eventList_.at(event).begin() + index);
                return true;
            }
        }
        return false;
    }

    bool EventEmitter::removeAllEventListeners(const std::string &event) {
        std::scoped_lock lock(mutex_);
        if (hasEvent(event)) {
            eventList_.at(event).clear();
            return true;
        }
        return false;
    }

    int EventEmitter::getNumOfEventListenersFor(const std::string& event) const {
        std::scoped_lock lock(mutex_);
        if (hasEvent(event))
            return eventList_.at(event).size();
        return -1;
    }

    int EventEmitter::getNumberOfEvents() const {
        std::scoped_lock lock(mutex_);
        return eventList_.size();
    }

    bool EventEmitter::hasEvent(const std::string &event) const {
        std::scoped_lock lock(mutex_);
        return eventList_.find(event) != eventList_.end();
    }

    bool EventEmitter::hasEventListener(const std::string &event, int listenerId) const {
        return hasListener(event, listenerId).first;
    }

    std::pair<bool, int> EventEmitter::hasListener(const std::string &event, int listenerId) const {
        std::scoped_lock lock(mutex_);
        if (hasEvent(event)) {
            auto &eventListeners = eventList_.at(event);
            auto found = std::find_if(eventListeners.begin(), eventListeners.end(), [=](const auto &listener) {
                return listener->id_ == listenerId;
            });

            if (found != eventListeners.end())
                return {true, std::distance(eventListeners.begin(), found)};
        }
        return {false, -1};
    }
}
