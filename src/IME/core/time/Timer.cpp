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
        status_{Status::Stopped},
        isDispatched_{false},
        repeatCount_{0},
        dispatchCount_{0}
    {}

    Timer Timer::create(Time interval, Callback<> callback, int repeatCount) {
        auto timer = Timer();
        timer.setInterval(interval);
        timer.setRepeat(repeatCount);
        timer.setTimeoutCallback(std::move(callback));
        return timer;
    }

    Timer Timer::create(Time interval, Callback<Timer &> callback, int repeatCounter) {
        auto timer = create(interval, []{}, repeatCounter);
        timer.setTimeoutCallback(std::move(callback));
        return timer;
    }

    void Timer::setInterval(Time interval) {
        if (interval_ == interval)
            return;

        interval_ = interval;
        if (interval_ < Time::Zero) {
            interval_ = remainingDuration_ = Time::Zero;
            if (status_ == Status::Running)
                stop();
        } else if (status_ == Status::Running)
            restart();
        else
            remainingDuration_ = interval_;
    }

    Time Timer::getInterval() const {
        return interval_;
    }

    Time Timer::getRemainingDuration() const {
        return remainingDuration_;
    }

    void Timer::setRepeat(int repeatCount) {
        if (repeatCount < 0)
            repeatCount_ = -1;
        else
            repeatCount_ = repeatCount;
    }

    int Timer::getRepeatCount() const {
        return repeatCount_;
    }

    bool Timer::isRepeating() const {
        return repeatCount_ > 0;
    }

    void Timer::setTimeoutCallback(Callback<> callback) {
        callback_ = std::move(callback);
        dispatchCount_ = 0;
    }

    void Timer::setTimeoutCallback(Callback<Timer&> callback) {
        setTimeoutCallback([this, callback = std::move(callback)] {
            callback(*this);
        });
    }

    void Timer::start() {
        IME_ASSERT(callback_, "The timeout callback must be set before starting the timer, see setTimeoutCallback() function")
        if (status_ != Status::Running) {
            status_ = Status::Running;
            dispatchCount_ = 0;
        } else
            restart();
    }

    void Timer::stop() {
        status_ = Status::Stopped;
        remainingDuration_ = interval_;
    }

    void Timer::pause() {
        if (status_ == Status::Running)
            status_ = Status::Paused;
    }

    void Timer::restart() {
        if (status_ == Status::Stopped)
            start();
        else {
            stop();
            // The dispatch counter is reset when the timer starts, however we
            // must preserve it if its a restart instead of normal start()
            auto dispatchCount = dispatchCount_;
            start();
            dispatchCount_ = dispatchCount;
        }
    }

    Timer::Status Timer::getStatus() const {
        return status_;
    }

    void Timer::update(Time deltaTime) {
        if (status_ != Status::Running || remainingDuration_ < Time::Zero)
            return;

        remainingDuration_ -= deltaTime;
        if (remainingDuration_ <= Time::Zero && callback_) {
            callback_();
            isDispatched_ = true;
            dispatchCount_++;
            if (repeatCount_ < 0 || (repeatCount_ > 0 && (dispatchCount_ <= repeatCount_)))
                restart();
            else
                stop();
        }
    }

    int Timer::getDispatchCount() const {
        return dispatchCount_;
    }

    bool Timer::isDispatched() const {
        return isDispatched_;
    }
}
