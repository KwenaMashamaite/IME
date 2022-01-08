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

#ifndef IME_EVENTEMITTER_H
#define IME_EVENTEMITTER_H

#include "IME/Config.h"
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <functional>
#include <mutex>

namespace ime {
    template <typename... Args>
    using Callback = std::function<void(Args...)>; //!< Event listener

    /**
     * @brief Create and publish events
     */
    class IME_API EventEmitter {
    public:
        /**
         * @brief Default constructor
         */
        EventEmitter() = default;

        /**
         * @brief Copy constructor
         */
        EventEmitter(const EventEmitter&);

        /**
         * @brief Copy assignment operator
         */
        EventEmitter& operator=(const EventEmitter&);

        /**
         * @brief Move constructor
         */
        EventEmitter(EventEmitter&&) noexcept;

        /**
         * @brief Move assignment operator
         */
        EventEmitter& operator=(EventEmitter&&) noexcept;

        /**
         * @brief Add an event listener (callback) to an event
         * @param event Event to add event listener to
         * @param callback Function to execute when the event is fired
         * @return The event listener's identification number
         *
         * Every event listener has a unique identification number. This
         * number must be remembered in order to remove the event listener.
         *
         * @note If the same callback function is added multiple times, It
         * will be treated as a unique event listener and hence given an
         * identification number
         */
        template<typename...Args>
        int addEventListener(const std::string &event, Callback<Args...> callback);

        /**
         * @brief Add an event listener to an event
         * @param event Event to add event listener to
         * @param callback Function to execute when the event is fired
         * @return The event listener's identification number
         *
         * This function does the same thing as the addEventListener() function.
         * It just provides a slightly more readable syntax:
         *
         *  @code
         *  returnButton.on("click", showMainMenu); as opposed to
         *  returnButton.addEventListener("click", showMainMenu);
         *  @endcode
         */
        template<typename...Args>
        int on(const std::string &event, Callback<Args...> callback);

        /**
         * @brief Add an event listener to an event
         * @param event Event to add event listener to
         * @param callback Function to execute when the event is fired
         * @return The event listener's identification number
         *
         * The event listener will be invoked once and subsequently removed
         * from the event. This means that the callback will only execute
         * when an event is fired for the first time. To execute a callback
         * each time the an event is fired
         *
         * @see addEventListener
         */
         template <typename ...Args>
        int addOnceEventListener(const std::string &event, Callback<Args...> callback);

        /**
         * @brief Remove an event listener from an event
         * @param event Event to remove listener from
         * @param id Identification number of the event listener to be removed
         * @return True if the event listener was removed from athe specified
         *         event or false if the specified event does exist or it does
         *         not have a listener with the given id
         */
         bool removeEventListener(const std::string &event, int id);

         /**
          * @brief Remove all event listeners of an event
          * @param  event Event to remove all listeners from
          * @return True if all listeners were removed, false if no such
          *         event exists
          */
         bool removeAllEventListeners(const std::string &event);

        /**
         * @brief Fire an event
         * @param event Name of the event to fire
         * @param args Arguments to be passed to event listeners
         */
        template<typename...Args>
        void emit(const std::string &event, Args...args);

        /**
         * @brief Check if an event exists or not
         * @param event Name of the event to check
         * @return True if event exists or false if the event does not exist
         */
        bool hasEvent(const std::string& event) const;

        /**
         * @brief Get the number of event listeners currently registered to
         *        an event
         * @param event Event to get number of event listeners for
         * @return The number of event listeners registered to an event or 0
         *         if no such event exists
         */
        std::size_t getEventListenerCount(const std::string& event) const;

        /**
         * @brief Get the current number of created events
         * @return Current umber of events
         */
        std::size_t getEventsCount() const;

        /**
         * @brief Check if an event has a certain event listener
         * @param event Name of the event
         * @param id Identification number of the listener to be checked
         * @return True if the specified event has an event listener with the
         *         specified id, otherwise false
         */
        bool hasEventListener(const std::string& event, int id) const;

    private:
        /**
         * @brief  Add an event listener (callback) to an event
         * @param  event Event to add listener to
         * @param  callback Function to execute when the event is fired
         * @param  isCalledOnce True if listener is called only when the event
         *         is raised for the first time, false for multiple times
         * @return listener's identification number
         */
        template<typename...Args>
        int addListener(const std::string &event, Callback<Args...> callback,
            bool isCalledOnce);

         /**
         * @brief Check if an event has a certain event listener
         * @param event Name of the event
         * @param listenerId Identification number of the listener to be checked
         * @return A pair, of which the first element is a bool that is true if
         *         the specified event has an event listener with the specified id, 
                   otherwise false and the second is an int which is the index of
                   the found event listener in the specified event listeners list
         *
         * @warning If the first element of the pair is false, the second element
         * is invalid (Function will return a negative index)
         */
        std::pair<bool, int>  hasListener(const std::string& event, int listenerId) const;

    private:
        /**
         * @brief Base class for template class
         *
         * This allows the template instance to be storable in a container
         */
        struct IListener {
            explicit IListener(int id) : id_(id){}
            virtual ~IListener() = default;
            int id_;
        };

        /**
         * @brief Event listener
         */
        template <typename ...Args>
        struct Listener : public IListener {
            Listener(int id, Callback<Args...> callback, bool isCalledOnce = false)
                : IListener(id), callback_(callback), isCalledOnce_(isCalledOnce){}

            Callback<Args...> callback_;
            bool isCalledOnce_;
        };

        using Listeners = std::vector<std::shared_ptr<IListener>>; //!< Alias
        std::unordered_map<std::string, Listeners> eventList_;     //!< Events container
        mutable std::recursive_mutex mutex_;                       //!< Synchronization primitive
    };

    #include "IME/core/event/EventEmitter.inl"
}

#endif
