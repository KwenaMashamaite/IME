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

#include "IME/core/time/TimerManager.h"

namespace ime {
    void TimerManager::addTimer(Timer timer) {
        if (timer.canStart()) {
            timer.start();
            activeTimers_.push_back(std::move(timer));
        }
    }

    void TimerManager::setTimeout(Time delay, Callback<Timer &> callback) {
        addTimer(Timer::create(delay, std::move(callback)));
    }

    void TimerManager::setTimeout(Time delay, Callback<> callback) {
        addTimer(Timer::create(delay, std::move(callback)));
    }

    void TimerManager::setInterval(Time delay, Callback<Timer&> callback, int repeatCount) {
        addTimer(Timer::create(delay, std::move(callback), repeatCount));
    }

    void TimerManager::setInterval(Time delay, Callback<> callback, int repeatCount) {
        addTimer(Timer::create(delay, std::move(callback), repeatCount));
    }

    void TimerManager::update(Time deltaTime) {
        for (auto& timer : activeTimers_)
            timer.update(deltaTime);
    }

    std::size_t TimerManager::getTimerCount() const {
        return activeTimers_.size();
    }

    void TimerManager::clear() {
        activeTimers_.clear();
    }

    void TimerManager::preUpdate() {
        activeTimers_.erase(std::remove_if(activeTimers_.begin(), activeTimers_.end(), [](Timer& timer) {
            return timer.getStatus() == Timer::Status::Stopped;
        }), activeTimers_.end());
    }
}
