#include "Event.h"
#include <algorithm>

template <typename... Args>
int Event<Args...>::addListener(const EventHandler<Args...> &callback) {
    auto handlerId = ++handlerIdCounter_;
    auto isNotifiable = true;
    auto handlerListSizeBeforeInsertion = handlerList_.size();
    handlerList_.push_back(std::move(Handler{handlerId, isNotifiable, callback}));
    if (handlerListSizeBeforeInsertion == handlerList_.size()) { //Insertion failed
        handlerIdCounter_--;
        return -1;
    }
    return handlerId;
}

template <typename... Args>
bool Event<Args...>::removeListener(unsigned int handlerId) {
    if (handlerId > handlerIdCounter_) //Event handler doesn't exist
        return false;
    auto iter = std::find_if(handlerList_.begin(), handlerList_.end(),
                [handlerId](const Handler& handler){return handler.id_ == handlerId;});
    if (iter != handlerList_.end()) {
        handlerList_.erase(iter);
        return true;
    }
    return false;
}

template <typename... Args>
void Event<Args...>::notifyListeners(Args... args) {
    for (auto&  handler : handlerList_)
        if (handler.callback_ && handler.isNotifiable_)
            handler.callback_(std::forward<Args>(args)...);
}

template<typename... Args>
void Event<Args...>::setNotificationPause(bool isNotifiable, unsigned int handlerId) {
    auto iter = std::find_if(std::begin(handlerList_), std::end(handlerList_),
                [handlerId](const Handler& handler){ return handler.id_ == handlerId;});
    if (iter != handlerList_.end())
        (*iter).isNotifiable_ = isNotifiable;
}