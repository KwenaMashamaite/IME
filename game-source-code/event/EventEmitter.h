/**
 * @brief Class for emitting events
 *
 * To add an event to the event emitter you simply have to call the addListener
 * function. In other words, events are created when a listener is added.
 * If an event already exists, then a listener is added to that event, otherwise
 * a new event is created. Once an Event is created, it won't be automatically 
 * fired. A call to the emit function must be made to fire an event
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
     * If the same listener is added multiple times, It will be treated as a unique
     * listener and hence given an identification number.
     *
     * @warning If the added listener is a member of a class, then the listener
     * must be removed from an event when the class instance goes out of scope.
     * If not removed, a non-existent listener will be invoked when the event is
     * fired and this will lead to undefined behavior
     */
    template<typename...Args>
    int addListener(const std::string &event, Callback<Args...> callback);

    /**
     * @brief Add listener to an event
     *
     * This function does the same thing as the addListener function. It just provides
     * a slightly more understandable syntax
     *
     * For example:
     *  returnButton.on("click", showMainMenu) as opposed to
     *  returnButton.addListener("click", showMainMenu)
     */
    template<typename...Args>
    int on(const std::string &event, Callback<Args...> callback);

    /**
     * @brief Add a listener to an event
     * @param event Event to add listener to
     * @param callback Function to execute when the event is fired
     *
     * This function will add a listener to an event. The listener will only be invoked
     * once and subsequently removed from the event. This means that the callback will
     * only run when an event is raised for the first time. Use addListener() or the on()
     * function if the callback is to be invoked each time an event is fired
     */
     template <typename ...Args>
    void addOnceListener(const std::string &event, Callback<Args...> callback);

    /**
     * @brief Remove a listener from an event
     * @param event Event to remove listener from
     * @param listenerId Identification number of the listener to be removed
     * @return True if a listener was removed from an event, false if the specified
     *         event does not have a listener with the specified id
     */
     bool removeListener(const std::string &event, int listenerId);

     /**
      * @brief Remove all listeners of an event
      * @param event Event to remove all listeners from
      * @return True if all listeners were removed, false if no such event exists
      *
      * @warning Use caution when removing all listeners. For instance, avoid calling this
      * function on an event emitter that is not local to the scope in which your in as this
      * could lead to undefined behavior.
      */
     bool removeAllListeners(const std::string &event);

    /**
     * @brief Fire an event
     * @tparam Args Template parameter pack name
     * @param event Name of the event to fire
     * @param args Arguments passed to event listeners
     */
    template<typename...Args>
    void emit(const std::string &event, Args...args);

private:
    /**
     * @brief Add a listener (callback) to an event
     * @tparam Args Template parameter pack name
     * @param event Event to add listener to
     * @param callback Function to execute when the event is fired
     * @param isCalledOnce True if listener is called only once, false for multiple times
     * @return listener's identification number
     */
    template<typename...Args>
    int addListener(const std::string &event, Callback<Args...> callback, bool isCalledOnce);

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
        Listener(int id, Callback<Args...> callback, bool isCalledOnce = false)
            : IListener(id), callback_(callback), isCalledOnce_(isCalledOnce){}

        Callback<Args...> callback_;
        bool isCalledOnce_;
    };

    using Listeners = std::vector<std::shared_ptr<IListener>>;
    std::unordered_map<std::string, Listeners> eventList_;
};

#include "EventEmitter.inl"

#endif
