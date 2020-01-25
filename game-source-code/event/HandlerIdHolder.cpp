#include "HandlerIdHolder.h"

void Utility::HanderIdHolder::add(const std::string &handlerName, int handlerId) {
    eventHandlerId_.insert(std::pair(handlerName, handlerId));
}

int Utility::HanderIdHolder::getIdFor(const std::string &handlerName) {
    auto findPair = eventHandlerId_.find(handlerName);
    if (findPair != eventHandlerId_.end())
        return findPair->second;
    else
        return -1;
}