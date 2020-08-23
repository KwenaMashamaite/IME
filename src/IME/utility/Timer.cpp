#include "IME/utility/Timer.h"
#include <chrono>
#include <thread>

namespace IME::Utility {
    void Timer::setTimeOut(Callback<> callback, int ms) {
        std::thread([=](){
            std::this_thread::sleep_for(std::chrono::milliseconds(ms));
            callback();
        }).detach();
    }

    void Timer::setInterval(Callback<bool&> callback, int ms) {
        std::thread([=, cancelInterval = false]() mutable {
            while (!cancelInterval) {
                std::this_thread::sleep_for(std::chrono::milliseconds(ms));
                callback(cancelInterval);
            }
        }).detach();
    }
}
