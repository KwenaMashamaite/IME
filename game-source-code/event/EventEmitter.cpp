#include "EventEmitter.h"
#include <algorithm>

bool EventEmitter::removeEventListener(const std::string &event, int listenerId) {
    if (listenerId > previousListenerId)
        return false;
    auto eventIter = eventList_.find(event);
    if (eventIter != eventList_.end()) {
        auto& listeners = eventIter->second;
        auto listenerIter = std::find_if(listeners.begin(), listeners.end(),
            [listenerId](std::shared_ptr<IListener>& listener){
                return listener->id_ == listenerId;
        });
        if (listenerIter != listeners.end()) {
            listeners.erase(listenerIter);
            return true;
        }
    }
    return false;
}

bool EventEmitter::removeAllEventListeners(const std::string &event) {
    auto iter = eventList_.find(event);
    if (iter != eventList_.end()) {
        auto& listeners = iter->second;
        listeners.clear();
        return true;
    }
    return false;
}
