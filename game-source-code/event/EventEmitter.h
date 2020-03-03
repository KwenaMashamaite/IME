/**
 * @brief Class for emitting events
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
     * @brief Add a listener (callback) to an event
     * @tparam Args Template parameter pack name
     * @param event Event to add listener to
     * @param callback Function to execute when the event is fired
     * @return listener's identification number
     *
     * This function returns a positive integer after the listener is added
     * to the event listener list. The identification number must be
     * remembered in order to perform other operations on the listener such
     * as removing it from the event listener list.
     *
     * @note If the same listener is added multiple times, It will be treated
     * as a unique listener and hence given an identification number.
     *
     * @warning If the added listener is a member of a class, then the listener
     * must be removed from an event when the class instance goes out of scope.
     * If not removed, a non-existent listener will be invoked when the event is
     * fired and this will lead to undefined behavior
     */
    template<typename...Args>
    int addListener(std::string &&event, Callback<Args...> callback);

    /**
     * @brief Remove a listener from an event
     * @param event Name Event to remove listener from
     * @param listenerId Identification number of the listener to be removed
     * @return True if a listener was removed from an event, false if the specified
     *         event does not have a listener with the specified id
     */
     bool removeListener(std::string &&event, int listenerId);

     /**
      * @brief Remove all listeners of an event
      * @param event Event to remove all listeners from
      * @return True if all listeners were removed, false if no such event exists
      */
     bool removeAllListeners(std::string&& event);

    /**
     * @brief Fire an event
     * @tparam Args Template parameter pack name
     * @param event Name of the event to fire
     * @param args Arguments passed to event listeners
     */
    template<typename...Args>
    void emit(std::string &&event, Args...args);

private:
    //Event listener identification number
    inline static auto previousListenerId = 0;

    //Base class for template class
    struct IListener{
        explicit IListener(int id) : id_(id){}
        virtual ~IListener() = default;
        int id_;
    };

    //Listener of an event
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