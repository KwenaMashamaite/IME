#include "EventEmitter.h"
#include <algorithm>

bool EventEmitter::removeListener(std::string &&event, int callbackId) {
    if (callbackId > previousListenerId)
        return false;
    auto eventIter = eventList_.find(event);
    if (eventIter != eventList_.end()) {
        auto& listeners = eventIter->second;
        auto listenerIter = std::find_if(listeners.begin(), listeners.end(),
            [callbackId](std::shared_ptr<IListener>& listener){
                return listener->id_ == callbackId;
        });
        if (listenerIter != listeners.end()) {
            listeners.erase(listenerIter);
            return true;
        }
    }
    return false;
}