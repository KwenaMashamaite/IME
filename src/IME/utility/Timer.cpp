#include "IME/utility/Timer.h"
#include <chrono>
#include <thread>
#include <future>

namespace IME::Utility {
    void Timer::setTimeOut(Callback<> callback, int ms) {
        std::async(std::launch::async, [=](){
            std::this_thread::sleep_for(std::chrono::milliseconds(ms));
            callback();
        });
    }

    void Timer::setInterval(Callback<bool&> callback, int ms) {
        std::async(std::launch::async, [=, cancelInterval = false]() mutable {
            while (!cancelInterval) {
                std::this_thread::sleep_for(std::chrono::milliseconds(ms));
                callback(cancelInterval);
            }
        });
    }
}
