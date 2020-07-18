#include "EventEmitter.h"
#include <algorithm>

bool EventEmitter::removeEventListener(const std::string &event, int listenerId) {
    if (listenerId > previousListenerId)
        return false;
    auto foundEvent = eventList_.find(event);
    if (foundEvent != eventList_.end()) {
        auto& listeners = foundEvent->second;
        auto foundListener = std::find_if(listeners.begin(), listeners.end(),
            [listenerId](std::shared_ptr<IListener>& listener) {
                return listener->id_ == listenerId;
            }
        );
        if (foundListener != listeners.end()) {
            listeners.erase(foundListener);
            return true;
        }
    }
    return false;
}

bool EventEmitter::removeAllEventListeners(const std::string &event) {
    auto found = eventList_.find(event);
    if (found != eventList_.end()) {
        auto& listeners = found->second;
        listeners.clear();
        return true;
    }
    return false;
}

int EventEmitter::getNumOfEventListenersFor(const std::string& event) const {
    auto found = eventList_.find(event);
    if (found != eventList_.end())
        return found->second.size();
    return -1;
}


bool EventEmitter::hasEvent(const std::string &event) const {
    return eventList_.find(event) == eventList_.end();
}
