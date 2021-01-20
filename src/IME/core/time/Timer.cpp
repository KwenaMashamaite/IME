////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include "IME/core/time/Timer.h"

namespace ime {
    Timer::Timer() :
        isRunning_{false},
        isRepeating_{false},
        interval_{0.0f},
        remainingDuration_{0.0f}
    {}

    Timer Timer::create(Callback<> callback, float interval, bool repeat) {
        auto timer = Timer();
        timer.setInterval(interval);
        timer.setRepeat(repeat);
        timer.setTimeoutCallback(std::move(callback));
        return timer;
    }

    void Timer::setInterval(float interval) {
        if (interval_ == interval)
            return;

        interval_ = interval;
        if (interval_ < 0.0f) {
            interval_ = remainingDuration_ = 0.0f;
            if (isRunning_)
                stop();
        } else if (isRunning_)
            restart();
        else
            remainingDuration_ = interval_;
    }

    float Timer::getInterval() const {
        return interval_;
    }

    float Timer::getRemainingDuration() const {
        return remainingDuration_;
    }

    void Timer::setRepeat(bool repeat) {
        isRepeating_ = repeat;
    }

    bool Timer::isRepeating() const {
        return isRepeating_;
    }

    void Timer::setTimeoutCallback(Callback<> callback) {
        callback_ = std::move(callback);
        if (!callback_ && isRunning_)
            stop();
    }

    void Timer::start() {
        if (!isRunning_ && interval_ > 0.0f && callback_) {
            isRunning_ = true;
        } else if (isRunning_)
            restart();
    }

    void Timer::stop() {
        isRunning_ = false;
        remainingDuration_ = interval_;
    }

    void Timer::pause() {
        isRunning_ = false;
    }

    void Timer::restart() {
        stop();
        start();
    }

    bool Timer::isRunning() const {
        return isRunning_;
    }

    void Timer::update(float deltaTime) {
        if (!isRunning_ || remainingDuration_ <= 0.0f)
            return;

        remainingDuration_ -= deltaTime;
        if (remainingDuration_ <= 0.0f && callback_) {
            callback_();
            if (isRepeating_)
                restart();
            else
                stop();
        }
    }
}
