//File includes implementations of template functions only. Regular functions (non-templates)
// should be placed in .cpp file to avoid the "multiple definition" error

template<typename... Args>
int EventEmitter::addListener(const std::string &event, Callback<Args...> callback) {
    static const auto isCallbackInvokedOnce = false;
    return addListener(event, callback, isCallbackInvokedOnce);
}

template<typename... Args>
int EventEmitter::on(const std::string &event, Callback<Args...> callback) {
    return addListener(event, callback);
}

template<typename... Args>
void EventEmitter::addOnceListener(const std::string &event, Callback<Args...> callback) {
    static const auto isCallbackInvokedOnce = true;
    addListener(event, callback, isCallbackInvokedOnce);
}

template<typename...Args>
int EventEmitter::addListener(const std::string &event, Callback<Args...> callback, bool isCalledOnce) {
    auto listenerId = previousListenerId++;
    auto listener = std::make_shared<Listener<Args...>>(listenerId, callback, isCalledOnce);
    auto iter = eventList_.find(event);
    if (iter != eventList_.end()) {
        auto& listeners = iter->second;
        listeners.push_back(std::move(listener));
    }else
        eventList_.insert(std::pair(event, std::vector<std::shared_ptr<IListener>>{std::move(listener)}));

    return listenerId;
}

template<typename... Args>
void EventEmitter::emit(const std::string &event, Args... args) {
    auto iter = eventList_.find(event);
    if (iter != eventList_.end()) {
        auto& listeners = iter->second;
        for (auto& listenerBasePtr : listeners) {
            auto listenerPtr = std::dynamic_pointer_cast<Listener<Args...>>(listenerBasePtr);
            if (listenerPtr && listenerPtr->callback_) {
                listenerPtr->callback_(args...);
                if (listenerPtr->isCalledOnce_)
                    removeListener(event, listenerPtr->id_);
            }
        }
    }
}