/**
 * @brief class for publishing predefined and custom events
 */

#ifndef EVENTEMITTER_H
#define EVENTEMITTER_H

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <functional>

template <typename... Args>
using Callback = std::function<void(Args...)>;

class EventEmitter {
public:
    /**
     * @brief Register a callback to an event
     * @tparam Args Template parameter pack name
     * @param eventName Name of the event to register callback on
     * @param callback Function to execute when the event is fired
     * @return Callback identification number
     */
    template<typename...Args>
    int addEventListener(std::string &&eventName, Callback<Args...> callback);

    /**
     * @brief Remove a callback from an event
     * @param eventName Name of the event to remove callback function from
     * @param callbackId Identification number of the callback
     */
     bool removeEventListener(std::string &&eventName, int callbackId);

    /**
     * @brief Raise/publish an event
     * @tparam Args Template parameter pack name
     * @param eventName Name of the event to publish
     * @param args Arguments passed to event handlers
     */
    template<typename...Args>
    void emit(std::string &&eventName, Args...args);

private:
    //Event listener identification number
    inline static auto previousListenerId = 0;

    //Base class for template class
    struct IListener{
        explicit IListener(int id) : id_(id){}
        virtual ~IListener() = default;
        int id_;
    };

    template <typename ...Args>
    struct Listener : public IListener{
        Listener(int id, Callback<Args...> callback, bool isNotifiable = true)
            : IListener(id), callback_(callback), isNotifiable_(isNotifiable){}

        Callback<Args...> callback_;
        bool isNotifiable_;
    };

    using Listeners = std::vector<std::shared_ptr<IListener>>;
    std::unordered_map<std::string, Listeners> eventList_;
};

#include "EventEmitter.inl"

#endif