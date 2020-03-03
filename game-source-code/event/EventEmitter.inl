//File includes implementations of template functions only. Regular functions (non-templates)
// should be placed in .cpp file to avoid the "multiple definition" error

template<typename...Args>
int EventEmitter::addListener(std::string &&event, Callback<Args...> callback) {
    auto listenerId = previousListenerId++;
    auto iter = eventList_.find(event);
    if (iter != eventList_.end()) {
        auto& listeners = iter->second;
        listeners.push_back(std::move(
            std::make_shared<Listener<Args...>>(listenerId, callback))
        );
    }else
        eventList_.insert(std::pair(event, std::vector<std::shared_ptr<IListener>>{
            std::make_shared<Listener<Args...>>(listenerId, callback)
        }));

    return listenerId;
}

template<typename... Args>
void EventEmitter::emit(std::string &&event, Args... args) {
    auto iter = eventList_.find(event);
    if (iter != eventList_.end()) {
        auto& listeners = iter->second;
        for (auto& listenerBasePtr : listeners) {
            auto listenerPtr = std::dynamic_pointer_cast<Listener<Args...>>(listenerBasePtr);
            if (listenerPtr && listenerPtr->callback_)
               listenerPtr->callback_(args...);
        }
    }
}