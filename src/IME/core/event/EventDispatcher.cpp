#include "IME/core/event/EventDispatcher.h"

namespace IME {
    bool EventDispatcher::removeEventListener(const std::string &event, int id) {
        return eventEmitter_.removeEventListener(event, id);
    }

    std::shared_ptr<EventDispatcher> EventDispatcher::instance() {
        std::scoped_lock lock(mutex_);
        static std::weak_ptr<EventDispatcher> instance_;
        if (const auto result = instance_.lock())
            return result;
        return (instance_ = std::shared_ptr<EventDispatcher>(new EventDispatcher())).lock();
    }
}