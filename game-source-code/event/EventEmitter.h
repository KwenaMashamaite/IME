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
     * @param event Name of the event to register callback on
     * @param callback Function to execute when the event is fired
     * @return Callback identification number
     *
     * The function returns a positive integer after the callback function
     * is added to the event handler list. The identification number must be
     * remembered in order to perform other operations on the handler such
     * as removing it from the event handler list.
     *
     * @note If the same handler is registered multiple times (i.e, function
     * called with the same argument multiple times), It will be treated as a
     * unique handler and hence given an identification number.
     *
     * @warning If the registered callback function is a member of a class or
     * a lambda expression that captures "this", then the callback function must
     * be removed from the event handler list when the object goes out of scope.
     * If not removed, the event will try to invoke a non-existent handler and
     * this will lead to undefined behavior
     */
    template<typename...Args>
    int addListener(std::string &&event, Callback<Args...> callback);

    /**
     * @brief Remove a callback from an event
     * @param event Name of the event to remove callback function from
     * @param callbackId Identification number of the callback to be removed
     * @return True if callback was removed from an event, false if callback
     *         with the specified id does not exist
     */
     bool removeListener(std::string &&event, int callbackId);

    /**
     * @brief Raise/publish an event
     * @tparam Args Template parameter pack name
     * @param event Name of the event to publish
     * @param args Arguments passed to event handlers
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