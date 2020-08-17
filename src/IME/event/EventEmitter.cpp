#include "IME/event/EventEmitter.h"
#include <algorithm>

namespace IME {
    bool EventEmitter::removeEventListener(const std::string &event, int listenerId) {
        if (hasEvent(event)) {
            if (auto [found, index] = hasEventListener(event, listenerId); found) {
                eventList_.at(event).erase(eventList_.at(event).begin() + index);
                return true;
            }
        }
        return false;
    }

    bool EventEmitter::removeAllEventListeners(const std::string &event) {
        if (hasEvent(event)) {
            eventList_.at(event).clear();
            return true;
        }
        return false;
    }

    int EventEmitter::getNumOfEventListenersFor(const std::string& event) const {
        if (hasEvent(event))
            return eventList_.at(event).size();
        return -1;
    }

    int EventEmitter::getNumberOfEvents() const {
        return eventList_.size();
    }

    bool EventEmitter::hasEvent(const std::string &event) const {
        return eventList_.find(event) != eventList_.end();
    }

    std::pair<bool, int> EventEmitter::hasEventListener(const std::string &event, int listenerId) const {
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
