template <typename Callable, typename...Args>
void Timer::setTimeoutSync(int delay, Callable callback, Args&&...args) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    callback(std::forward<Args>(args)...);
}

template <typename Callable, typename...Args>
void Timer::setTimeout(int delay, Callable callback, Args...args){
    std::thread([=](){
        setTimeoutSync(delay, std::move(callback), std::move(args)...);
    }).detach();
}

template <typename Callable, typename...Args>
void Timer::setIntervalSync(int delay, Callable callback, Args...args){
    auto cancelInterval = false;
    while (!cancelInterval) { //Loop terminated by callback
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        callback(cancelInterval, args...);
    }
}

template <typename Callable, typename...Args>
void Timer::setInterval(int delay, Callable callback, Args...args){
    std::thread([=]() {
        setIntervalSync(delay, std::move(callback), std::move(args)...);
    }).detach();
}