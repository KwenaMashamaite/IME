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

#ifndef IME_EVENTDISPATCHER_H
#define IME_EVENTDISPATCHER_H

#include "IME/Config.h"
#include "EventEmitter.h"
#include <memory>
#include <string>

namespace IME {
    /**
     * @brief A singleton class that creates a communication interface between
     *        separate parts of a program through event dispatching
     *
     * @warning This classes instance is accessible from anywhere withing the
     * program, however the instance is destroyed when the last pointer to it
     * goes out of scope. This means that all event listeners that have been
     * registered will be destroyed and a call to dispatchEvent will not do
     * anything. Therefore there must be at least one pointer to the class
     * instance that keeps it alive for as long as its being used
     */
    class IME_API EventDispatcher {
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
         * This function will invoke all event listeners of the specified
         * event
         */
        template<typename... Args>
        void dispatchEvent(const std::string& event, Args&& ...args);

        /**
         * @brief Remove an event listener from an event
         * @param event Event to remove event listener from
         * @param id Identification number of the event listener to be removed
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
        std::shared_ptr<EventDispatcher> instance_; //!< The only class instance
        EventEmitter eventEmitter_;                 //!< Event publisher
        inline static std::mutex mutex_;            //!< Synchronization primitive
    };

    #include "IME/core/event/EventDispatcher.inl"
}

#endif
