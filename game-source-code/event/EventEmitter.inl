//File includes implementations of template functions only. Regular functions (non-templates)
// should be placed in .cpp file to avoid the "multiple definition" error

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
        auto listenerId = ++previousListenerId;
        auto listener = std::make_shared<Listener<Args...>>(listenerId, callback, isCalledOnce);
        auto found = eventList_.find(event);
        if (found != eventList_.end()) {
            auto& listeners = found->second;
            listeners.push_back(std::move(listener));
        }else
            eventList_.insert(std::pair(event, std::vector<std::shared_ptr<IListener>>{std::move(listener)}));

        return listenerId;
    }

    template<typename... Args>
    void EventEmitter::emit(const std::string &event, Args... args) {
        auto found = eventList_.find(event);
        if (found != eventList_.end()) {
            auto& listeners = found->second;
            for (auto& listenerBasePtr : listeners) {
                auto listenerPtr = std::dynamic_pointer_cast<Listener<Args...>>(listenerBasePtr);
                if (listenerPtr && listenerPtr->callback_) {
                    listenerPtr->callback_(args...);
                    if (listenerPtr->isCalledOnce_)
                        removeEventListener(event, listenerPtr->id_);
                }
            }
        }
    }
}
