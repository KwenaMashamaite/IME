template<typename... Args>
void EventManager::fireEvent(const std::string &event, Args &&... args) {
    eventEmitter_.emit(event, std::forward(args)...);
}

template<typename... Args>
int EventManager::onEvent(const std::string &event, Callback<Args...> callback) {
    return eventEmitter_.addEventListener(event, std::move(callback));
}
