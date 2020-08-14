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
        eventList_.at(event).push_back(std::move(listener));
    else
        eventList_.insert({event, std::vector<std::shared_ptr<IListener>>{std::move(listener)}});

    return listenerId;
}

template<typename... Args>
void EventEmitter::emit(const std::string &event, Args... args) {
    if (hasEvent(event)) {
        auto& listeners = eventList_.at(event);
        for (auto& listenerBase : listeners) {
            auto listener = std::dynamic_pointer_cast<Listener<Args...>>(listenerBase);
            if (listener && listener->callback_) {
                std::invoke(listener->callback_, std::forward<Args>(args)...);
                if (listener->isCalledOnce_)
                    removeEventListener(event, listener->id_);
            }
        }
    }
}
