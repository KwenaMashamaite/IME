#include "IME/core/managers/EventManager.h"

namespace IME {
    bool EventManager::removeEventListener(const std::string &event, int id) {
        return eventEmitter_.removeEventListener(event, id);
    }

    std::shared_ptr<EventManager> EventManager::instance() {
        static std::weak_ptr<EventManager> instance_;
        if (const auto result = instance_.lock())
            return result;
        return (instance_ = std::shared_ptr<EventManager>(new EventManager())).lock();
    }
}