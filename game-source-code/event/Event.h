/**
 * @brief class template for creating custom events (Not thread safe)
 */

#ifndef EVENT_H
#define EVENT_H

#include <functional>
#include <vector>

template <typename... Args>
using EventHandler = std::function<void(Args...)>;

template <typename... Args>
class Event{
public:
    /**
     * @brief Register a callback function to an event
     * @param callback Function to execute when event takes place
     * @return Event handlers (callback function) unique identification number
     *
     * The function returns a positive integer if the callback function was
     * successfully added to the event handler list, otherwise it returns -1 if
     * the operation was unsuccessful. The identification number must be remembered
     * in order to perform other operations on the handler such as removing it
     * from the event handler list.
     *
     * @note If the same handler is registered multiple times (i.e, function
     * called with the same argument multiple times), It will be treated
     * as a unique handler and hence given an identification number.
     *
     * @warning If the registered callback function is a member of a class or a lambda
	 * expression that captures "this", then the callback function must be removed from
	 * the event handler list when the object goes out of scope. If not removed, the event
	 * will try to invoke a non-existent handler and this will lead to undefined behavior
     */
    int addListener(const EventHandler<Args...> &callback);

    /**
     * @brief Temporarily stop a handler from receiving event notifications
     * @param isNotifiable Set to false to pause event notifications and true
     *                      to resume event notifications
     * @param handlerId Event handler to pause/resume event notifications on
     *
     * This function stops event notifications on a handler without removing it
     * from the event handler list. This allows the handler to resume receiving
     * event notifications at a later time without re-adding it
     */
    void setNotificationPause(bool isNotifiable, unsigned int handlerId);

    /**
     * @brief Deregister/remove a callback function from an event
     * @param handlerId Event handlers identification number
     * @return True if handler was successfully removed, false if
     *         handler does not exist and could not be removed
     */
    bool removeListener(unsigned int handlerId);

    /**
     * @brief Notify registered event handlers when event is raised
     * @param args Arguments passed to event handlers
     */
    void notifyListeners(Args... args);

private:
    //handler identification numbers
    inline static auto handlerIdCounter_ = 0;
    struct Handler{
        int id_;
        bool isNotifiable_;
        EventHandler<Args...> callback_;
    };
    //list of event handlers
    std::vector<Handler> handlerList_;
};

#include "Event.inl"

#endif