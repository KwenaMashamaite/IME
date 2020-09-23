/**
 * @brief
 */

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include "IME/core/event/EventEmitter.h"
#include <memory>
#include <string>

namespace IME {
    class EventManager {
    public:
        /**
         * @brief Copy constructor
         */
        EventManager(const EventManager&) = delete;

        /**
         * @brief Assignment operator
         */
        EventManager& operator=(const EventManager&) = delete;

        /**
         * @brief Add an event listener to an event
         * @param event Event to add event listener to
         * @param callback Function to execute when the event is fired
         * @return The event listeners identification number
         */
        template<typename... Args>
        int onEvent(const std::string& event, Callback<Args...> callback);

        /**
         * @brief Fire an event
         * @param event Event to fire
         * @param args Arguments passed to event listeners
         *
         * This function will invoke all event listeners of the fired event
         */
        template<typename... Args>
        void fireEvent(const std::string& event, Args&& ...args);

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
        static std::shared_ptr<EventManager> instance();

    private:
        /**
         * @brief Default constructor
         */
        EventManager() = default;

    private:
        //The sole class instance
        std::shared_ptr<EventManager> instance_;
        //Event publisher
        EventEmitter eventEmitter_;
    };

    #include "IME/core/managers/EventManager.inl"
}

#endif
