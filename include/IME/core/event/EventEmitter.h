////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020 Kwena Mashamaite (kmash.ime@gmail.com)
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

/**
 * @brief Class for creating and publishing events
 *
 * This class is invaluable when writing event-based systems such
 * as Graphical User interface (GUI) applications.
 *
 * @note There is no function for creating an event. Events are
 * created when a listener/callback is added for the first time.
 * All Subsequent event listeners will be added to the created
 * event. Events are not fired automatically, a call to the emit
 * function must be made to fire an event and notify event listeners
 */

#ifndef IME_EVENTEMITTER_H
#define IME_EVENTEMITTER_H

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <functional>
#include <mutex>

namespace IME {
    template <typename... Args>
    using Callback = std::function<void(Args...)>;

    class EventEmitter {
    public:
        /**
         * @brief Default copy constructor
         */
        EventEmitter() = default;

        /**
         * @brief Copy constructor
         */
        EventEmitter(const EventEmitter& other);

        /**
         * @brief Assignment operator
         */
        EventEmitter& operator=(const EventEmitter& rhs);

        /**
         * @brief Add a listener (callback) to an event
         * @tparam Args Template parameter pack name
         * @param event Event to add listener to
         * @param callback Function to execute when the event is fired
         * @return listener's identification number
         *
         * If the same listener is added multiple times, It will be treated
         * as a unique listener and hence given an identification number.
         * @warning If the added listener is a member of a class, then the
         * listener must be removed from an event when the class instance
         * goes out of scope. If not removed, a non-existent listener will
         * be invoked when the event is fired; this may lead to undefined
         * behavior
         */
        template<typename...Args>
        int addEventListener(const std::string &event, Callback<Args...> callback);

        /**
         * @brief Add listener to an event
         *
         * This function does the same thing as the addEventListener() function.
         * It just provides a slightly more readable syntax. For example:
         *
         *  @example:
         *  returnButton.on("click", showMainMenu) as opposed to
         *  returnButton.addEventListener("click", showMainMenu)
         */
        template<typename...Args>
        int on(const std::string &event, Callback<Args...> callback);

        /**
         * @brief Add a listener to an event
         * @param event Event to add listener to
         * @param callback Function to execute when the event is fired
         * @return Listener's identification number
         *
         * The listener will only be invoked once and subsequently removed
         * from the event. This means that the callback will only execute
         * when an event is raised for the first time. Use addEventListener()
         * or the on() function if the callback is to be invoked each time an
         * event is fired
         */
         template <typename ...Args>
        int addOnceEventListener(const std::string &event, Callback<Args...> callback);

        /**
         * @brief  Remove a listener from an event
         * @param  event Event to remove listener from
         * @param  listenerId Identification number of the listener to
         *         be removed
         * @return True if a listener was removed from an event, false
         *         if the specified event does not have a listener with
         *         the specified id
         */
         bool removeEventListener(const std::string &event, int listenerId);

         /**
          * @brief Remove all listeners of an event
          * @param  event Event to remove all listeners from
          * @return True if all listeners were removed, false if no such
          *         event exists
          *
          * @warning Exercise caution when using this function
          */
         bool removeAllEventListeners(const std::string &event);

        /**
         * @brief Fire an event
         * @tparam Args Template parameter pack name
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
         * @brief Get the number of event listeners currently registered to an event
         * @param event Event to get number of event listeners for
         * @return Number of event listeners registered to an event or -1 if
         *         no such event exists
         */
        int getNumOfEventListenersFor(const std::string& event) const;

        /**
         * @brief Get the current number of events
         * @return Current umber of events
         */
        int getNumberOfEvents() const;

        /**
         * @brief Check if an event has a certain event listener
         * @param event Name of the event
         * @param listenerId Identification number of the listener to be checked
         * @return True if the specified event has an event listener with the specified
         *         id, otherwise false
         */
        bool hasEventListener(const std::string& event, int listenerId) const;

    private:
        /**
         * @brief  Add a listener (callback) to an event
         * @tparam Args Template parameter pack name
         * @param  event Event to add listener to
         * @param  callback Function to execute when the event is fired
         * @param  isCalledOnce True if listener is called only when the event
         *         is raised for the first time, false for multiple times
         * @return listener's identification number
         */
        template<typename...Args>
        int addListener(const std::string &event, Callback<Args...> callback, bool isCalledOnce);

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
        //Base class for template class
        struct IListener {
            explicit IListener(int id) : id_(id){}
            virtual ~IListener() = default;
            int id_;
        };

        //Listener of an event
        template <typename ...Args>
        struct Listener : public IListener {
            Listener(int id, Callback<Args...> callback, bool isCalledOnce = false)
                : IListener(id), callback_(callback), isCalledOnce_(isCalledOnce){}

            Callback<Args...> callback_;
            bool isCalledOnce_;
        };

        using Listeners = std::vector<std::shared_ptr<IListener>>;
        std::unordered_map<std::string, Listeners> eventList_;
        mutable std::recursive_mutex mutex_;
    };

    #include "EventEmitter.inl"
}

#endif
