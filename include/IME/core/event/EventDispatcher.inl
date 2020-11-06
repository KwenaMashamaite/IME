template<typename... Args>
void EventDispatcher::dispatchEvent(const std::string &event, Args &&... args) {
    eventEmitter_.emit(event, std::forward<Args>(args)...);
}

template<typename... Args>
int EventDispatcher::onEvent(const std::string &event, Callback<Args...> callback) {
    return eventEmitter_.addEventListener(event, std::move(callback));
}
