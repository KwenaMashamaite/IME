/**
 * @brief A singleton class that creates a communication interface between
 *        separate parts of a program through event dispatching
 *
 * @warning This classes instance is accessible from anywhere withing the program,
 * however the instance is destroyed when the last pointer to it goes out of scope.
 * This means that all event listeners that have been registered will be destroyed
 * and a call to dispatchEvent will not do anything. Therefore there must be
 * at least one pointer to the class instance that keeps it alive for as long
 * as its being used. @see instance()
 */

#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include "EventEmitter.h"
#include <memory>
#include <string>

namespace IME {
    class EventDispatcher {
    public:
        /**
         * @brief Copy constructor
         */
        EventDispatcher(const EventDispatcher&) = delete;

        /**
         * @brief Assignment operator
         */
        EventDispatcher& operator=(const EventDispatcher&) = delete;

        /**
         * @brief Add an event listener to an event
         * @param event Event to add an event listener to
         * @param callback Function to execute when the event is fired
         * @return The event listeners identification number
         */
        template<typename... Args>
        int onEvent(const std::string& event, Callback<Args...> callback);

        /**
         * @brief Fire an event
         * @param event Name of the event to fire
         * @param args Arguments to be passed to event listeners
         *
         * This function will invoke all event listeners of the fired event
         */
        template<typename... Args>
        void dispatchEvent(const std::string& event, Args&& ...args);

        /**
         * @brief Remove a listener from an event
         * @param event Event to remove listener from
         * @param id Identification number of the listener to be removed
         * @return True if the event listener was removed from the specified
         *         event or false if the specified event does not have an event
         *         listener with the specified id
         */
        bool removeEventListener(const std::string& event, int id);

        /**
         * @brief Get class instance
         * @return Shared pointer to class instance
         */
        static std::shared_ptr<EventDispatcher> instance();

    private:
        /**
         * @brief Default constructor
         */
        EventDispatcher() = default;

    private:
        //The sole class instance
        std::shared_ptr<EventDispatcher> instance_;
        //Event publisher
        EventEmitter eventEmitter_;
        inline static std::mutex mutex_;
    };

    #include "EventDispatcher.inl"
}

#endif
