// File includes implementations of template functions only. Regular functions (non-templates)
// should be placed in .cpp file to avoid the "multiple definition" error

#include <IME/event/EventEmitter.h>

namespace IME {
    template<typename... Args>
    int EventEmitter::addEventListener(const std::string &event, Callback<Args...> callback) {
        return addListener(event, callback, false);
    }

    template<typename... Args>
    int EventEmitter::on(const std::string &event, Callback<Args...> callback) {
        return addEventListener(event, callback);
    }

    template<typename... Args>
    int EventEmitter::addOnceEventListener(const std::string &event, Callback<Args...> callback) {
        return addListener(event, callback, true);
    }

    template<typename...Args>
    int EventEmitter::addListener(const std::string &event, Callback<Args...> callback, bool isCalledOnce) {
        static auto previousListenerId = 0u;
        auto listenerId = ++previousListenerId;
        auto listener = std::make_shared<Listener<Args...>>(listenerId, callback, isCalledOnce);
        if (hasEvent(event))
            eventList_[event].push_back(std::move(listener));
        else
            eventList_.insert(std::pair(event, std::vector<std::shared_ptr<IListener>>{std::move(listener)}));

        return listenerId;
    }

    template<typename... Args>
    void EventEmitter::emit(const std::string &event, Args... args) {
        if (hasEvent(event)) {
            auto& listeners = eventList_[event];
            for (auto& listenerBase : listeners) {
                auto listener = std::dynamic_pointer_cast<Listener<Args...>>(listenerBase);
                if (listener && listener->callback_) {
                    listener->callback_(args...);
                    if (listener->isCalledOnce_)
                        removeEventListener(event, listener->id_);
                }
            }
        }
    }
}
