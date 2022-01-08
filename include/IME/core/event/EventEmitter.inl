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

template<typename... Args>
int EventEmitter::addEventListener(const std::string &event, Callback<Args...> callback) {
    return addListener(event, callback, false);
}

template<typename... Args>
int EventEmitter::on(const std::string &event, Callback<Args...> callback) {
    return addEventListener(event, callback);
}

template<typename... Args>
int EventEmitter::addOnceEventListener(const std::string &event, Callback<Args...> callback) {
    return addListener(event, callback, true);
}

template<typename...Args>
int EventEmitter::addListener(const std::string &event, Callback<Args...> callback, bool isCalledOnce) {
    IME_ASSERT(callback, "Cannot add nullptr as an event listener");

    std::scoped_lock lock(mutex_);
    static auto previousListenerId = 0u;
    auto listenerId = ++previousListenerId;
    auto listener = std::make_shared<Listener<Args...>>(listenerId, callback, isCalledOnce);
    if (hasEvent(event))
        eventList_.at(event).push_back(std::move(listener));
    else
        eventList_.insert({event, std::vector<std::shared_ptr<IListener>>{std::move(listener)}});

    return listenerId;
}

template<typename... Args>
void EventEmitter::emit(const std::string &event, Args... args) {
    std::scoped_lock lock(mutex_);
    if (hasEvent(event)) {
        auto& listeners = eventList_.at(event);
        for (auto& listenerBase : listeners) {
            auto listener = std::dynamic_pointer_cast<Listener<Args...>>(listenerBase);
            if (listener && listener->callback_) {
                std::invoke(listener->callback_, args...);
                if (listener->isCalledOnce_)
                    removeEventListener(event, listener->id_);
            }
        }
    }
}
