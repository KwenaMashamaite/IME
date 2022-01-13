////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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
        timescale_{1.0f},
        isExecutionComplete_{false},
        isRestarting_{false},
        isDispatched_{false},
        repeatCount_{0},
        dispatchCount_{0}
    {}

    Timer::Ptr Timer::create(Time interval, const Callback<>& callback, int repeatCount) {
        auto timer = std::make_unique<Timer>();
        timer->setInterval(interval);
        timer->setRepeatCount(repeatCount);
        timer->onTimeout(callback);
        return timer;
    }

    Timer::Ptr Timer::create(Time interval, const Callback<Timer &>& callback, int repeatCounter) {
        auto timer = create(interval, []{}, repeatCounter);
        timer->onTimeout(callback);
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

    Time Timer::getElapsedTime() const {
        return interval_ - remainingDuration_;
    }

    Time Timer::getRemainingDuration() const {
        return remainingDuration_;
    }

    void Timer::setRepeatCount(int repeatCount) {
        if (repeatCount < 0)
            repeatCount_ = -1;
        else
            repeatCount_ = repeatCount;
    }

    int Timer::getRepeatCount() const {
        return repeatCount_;
    }

    bool Timer::isRepeating() const {
        return repeatCount_ > 0 || repeatCount_ == -1;
    }

    void Timer::setLoop(bool loop) {
        if (loop)
            repeatCount_ = -1;
        else
            repeatCount_ = 0;
    }

    bool Timer::isLooped() const {
        return repeatCount_ == -1;
    }

    void Timer::setTimeoutCallback(const Callback<>& callback) {
        onTimeout(callback);
    }

    void Timer::setTimeoutCallback(const Callback<Timer&>& callback) {
        onTimeout(callback);
    }

    void Timer::start() {
        IME_ASSERT(onTimeout_, "The timeout callback must be set before starting the timer, see setTimeoutCallback() function")
        if (status_ != Status::Running) {
            if (status_ == Status::Paused)
                resume();
            else {
                status_ = Status::Running;
                dispatchCount_ = 0;

                if (onStart_ && !isRestarting_)
                    onStart_(*this);
            }
        } else
            restart();
    }

    void Timer::stop() {
        if (status_ == Status::Running || status_ == Status::Paused) {
            status_ = Status::Stopped;
            remainingDuration_ = interval_;

            if (onStop_ && !isRestarting_ && !isExecutionComplete_)
                onStop_(*this);
        }
    }

    void Timer::forceTimeout() {
        if (status_ != Status::Stopped && onTimeout_)
            onTimeout_();

        stop();
    }

    void Timer::pause() {
        if (status_ == Status::Running) {
            status_ = Status::Paused;

            if (onPause_)
                onPause_(*this);
        }
    }

    void Timer::resume() {
        if (status_ == Status::Paused) {
            status_ = Status::Running;

            if (onResume_ && !isRestarting_)
                onResume_(*this);
        }
    }

    void Timer::restart() {
        if (status_ == Status::Stopped)
            start();
        else {
            isRestarting_ = true;
            stop();
            // The dispatch counter is reset when the timer starts, however we
            // must preserve it if its a restart instead of normal start()
            auto dispatchCount = dispatchCount_;
            start();
            dispatchCount_ = dispatchCount;
            isRestarting_ = false;

            if (onRestart_)
                onRestart_(*this);
        }
    }

    Timer::Status Timer::getStatus() const {
        return status_;
    }

    bool Timer::isRunning() const {
        return status_ == Status::Running;
    }

    bool Timer::isPaused() const {
        return status_ == Status::Paused;
    }

    bool Timer::isStopped() const {
        return status_ == Status::Stopped;
    }

    void Timer::update(Time deltaTime) {
        if (status_ != Status::Running)
            return;

        remainingDuration_ -= (deltaTime * timescale_);
        if (remainingDuration_ < Time::Zero)
            remainingDuration_ = Time::Zero;

        if (onUpdate_)
            onUpdate_(*this);

        if (remainingDuration_ == Time::Zero && onTimeout_) {
            onTimeout_();
            isDispatched_ = true;
            dispatchCount_++;

            // Timer may be paused or stopped by the timeout callback
            if (status_ == Status::Running) {
                if (repeatCount_ < 0 || (repeatCount_ > 0 && (dispatchCount_ <= repeatCount_)))
                    restart();
                else {
                    // When no further callback executions will take place, we only want
                    // to invoke onTimeout_ callback and not onStop_ callback. The latter
                    // must only be triggered externally.
                    isExecutionComplete_ = true;
                    stop();
                    isExecutionComplete_ = false;
                }
            }
        }
    }

    int Timer::getDispatchCount() const {
        return dispatchCount_;
    }

    bool Timer::isDispatched() const {
        return isDispatched_;
    }

    void Timer::setTimescale(float timescale) {
        if (timescale_ > 0)
            timescale_ = timescale;
    }

    float Timer::getTimescale() const {
        return timescale_;
    }

    void Timer::onTimeout(const Timer::Callback<> &callback) {
        onTimeout_ = callback;
        dispatchCount_ = 0;
    }

    void Timer::onTimeout(const Timer::Callback<Timer &> &callback) {
        onTimeout([this, callback] {
            callback(*this);
        });
    }

    void Timer::onStart(const Timer::Callback<Timer&>& callback) {
        onStart_ = callback;
    }

    void Timer::onPause(const Timer::Callback<Timer&>& callback) {
        onPause_ = callback;
    }

    void Timer::onResume(const Timer::Callback<Timer &> &callback) {
        onResume_ = callback;
    }

    void Timer::onStop(const Timer::Callback<Timer&>& callback) {
        onStop_ = callback;
    }

    void Timer::onRestart(const Timer::Callback<Timer&>& callback) {
        onRestart_ = callback;
    }

    void Timer::onUpdate(const Timer::Callback<Timer &> &callback) {
        onUpdate_ = callback;
    }
}
