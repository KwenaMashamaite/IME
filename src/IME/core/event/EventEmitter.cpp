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

#include "IME/core/event/EventEmitter.h"
#include <algorithm>

namespace ime {
    EventEmitter::EventEmitter() :
        isActive_{true}
    {}

    EventEmitter::EventEmitter(const EventEmitter &other) {
        std::scoped_lock lock(other.mutex_);
        auto temp{other.eventList_};
        std::swap(eventList_, temp);
    }

    EventEmitter &EventEmitter::operator=(const EventEmitter &rhs) {
        if (this != &rhs) {
            std::scoped_lock lock(mutex_, rhs.mutex_);
            eventList_ = rhs.eventList_;
        }

        return *this;
    }

    EventEmitter::EventEmitter(EventEmitter&& other) noexcept {
        std::scoped_lock lock(other.mutex_);
        std::swap(eventList_, other.eventList_);
    }

    EventEmitter &EventEmitter::operator=(EventEmitter&& rhs) noexcept {
        if (this != &rhs) {
            std::scoped_lock lock(mutex_, rhs.mutex_);
            eventList_ = std::move(rhs.eventList_);
        }

        return *this;
    }

    bool EventEmitter::removeEventListener(const std::string &event, int id) {
        std::scoped_lock lock(mutex_);
        if (hasEvent(event)) {
            if (auto [found, index] = hasListener(event, id); found) {
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

    std::size_t EventEmitter::getEventListenerCount(const std::string& event) const {
        std::scoped_lock lock(mutex_);
        if (hasEvent(event))
            return eventList_.at(event).size();
        return 0;
    }

    std::size_t EventEmitter::getEventsCount() const {
        std::scoped_lock lock(mutex_);
        return eventList_.size();
    }

    bool EventEmitter::hasEvent(const std::string &event) const {
        std::scoped_lock lock(mutex_);
        return eventList_.find(event) != eventList_.end();
    }

    bool EventEmitter::suspendEventListener(const std::string &event, int id, bool suspend) {
        std::scoped_lock lock(mutex_);
        IListener* listener = getListener(event, id);

        if (listener) {
            listener->isSuspended_ = suspend;
            return true;
        }

        return false;
    }

    bool EventEmitter::suspendEventListener(int id, bool suspend) {
        std::scoped_lock lock(mutex_);

        return std::any_of(eventList_.begin(), eventList_.end(), [=] (auto& pair) {
            return suspendEventListener(pair.first, id, suspend);
        });
    }

    bool EventEmitter::isEventListenerSuspended(const std::string& event, int id) const {
        std::scoped_lock lock(mutex_);
        const IListener* listener = getListener(event, id);

        if (listener)
            return listener->isSuspended_;
        else
            return false;
    }

    bool EventEmitter::isEventListenerSuspended(int id) const {
        std::scoped_lock lock(mutex_);

        return std::any_of(eventList_.begin(), eventList_.end(), [=] (auto& pair) {
            return isEventListenerSuspended(pair.first, id);
        });
    }

    bool EventEmitter::hasEventListener(const std::string &event, int id) const {
        return hasListener(event, id).first;
    }

    void EventEmitter::setActive(bool active) {
        isActive_ = active;
    }

    bool EventEmitter::isActive() const {
        return isActive_;
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

    EventEmitter::IListener* EventEmitter::getListener(const std::string &event, int id) {
        return dynamic_cast<EventEmitter::IListener*>(const_cast<EventEmitter::IListener*>(std::as_const(*this).getListener(event, id)));
    }

    const EventEmitter::IListener* EventEmitter::getListener(const std::string& event, int id) const {
        if (auto [found, index] = hasListener(event, id); found)
            return eventList_.at(event).at(index).get();
        else
            return nullptr;
    }
}
