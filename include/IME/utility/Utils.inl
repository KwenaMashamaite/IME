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

template <typename Callable, typename...Args>
void setTimeoutSync(Time delay, const Callable& callback, Args&&...args) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay.asMilliseconds()));
    std::invoke(callback, std::forward<Args>(args)...);
}

template <typename Callable, typename...Args>
void setTimeout(Time delay, const Callable& callback, Args&&...args){
    std::thread([delay, &callback, args = std::move(args...)] {
        setTimeoutSync(delay, callback, std::forward<Args>(args)...);
    }).detach();
}

template <typename Callable, typename...Args>
void setIntervalSync(Time delay, const Callable& callback, Args&&...args){
    auto cancelInterval = false;
    while (!cancelInterval) { //Loop terminated by callback
        std::this_thread::sleep_for(std::chrono::milliseconds(delay.asMilliseconds()));
        callback(cancelInterval, std::forward<Args>(args)...);
    }
}

template <typename Callable, typename...Args>
void setInterval(Time delay, const Callable& callback, Args&&...args){
    std::thread([delay, &callback, args = std::move(args...)] {
        setIntervalSync(delay, callback, std::forward<Args>(args)...);
    }).detach();
}
