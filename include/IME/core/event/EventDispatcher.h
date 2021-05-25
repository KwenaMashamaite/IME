////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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

namespace ime {
    /**
     * @brief A singleton class that creates a communication interface between
     *        separate parts of a program through event dispatching
     */
    class IME_API EventDispatcher {
    public:
        using Ptr = std::shared_ptr<EventDispatcher>; //!< Shared EventDispatcher pointer

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
        static EventDispatcher::Ptr instance();

    private:
        /**
         * @brief Default constructor
         */
        EventDispatcher() = default;

    private:
        EventDispatcher::Ptr instance_;  //!< The only class instance
        EventEmitter eventEmitter_;      //!< Event publisher
        inline static std::mutex mutex_; //!< Synchronization primitive
    };

    #include "IME/core/event/EventDispatcher.inl"
}

#endif //EventDispatcher_H

/**
 * @class ime::EventDispatcher
 * @ingroup core
 *
 * The global event emitter is available to anything class that needs
 * it (class, function etc..). Its responsibility is to decouple classes
 * from one another. You can emit a signal and anyone listening for that
 * signal will pick it up without knowing and caring where the signal came
 * from. Here is a simple example:
 *
 * @code
 * // main.cpp
 *
 * // We subscribe to a loading event that will be dispatched by some scene
 * // we don't know or care about, we are just interested in knowing that
 * // resource loading is complete
 * EventDispatcher::instance()->onEvent("loadingComplete", Callback<>([&engine] {
 *    engine.popScene();                // Remove the scene that emitted the event
 *    engine.pushScene(gameplayScene);  // Start the gameplay scene
 * }));
 *
 * engine.pushScene(loadingScene);
 * engine.run();
 *
 * // LoadingScene.cpp
 * // ...
 * // The caller does not need to keep asking the loading scene if it has
 * // finished loading the game assets, the scene lets everyone whose is
 * // interested know when it is done without knowing and caring who they are
 *
 * EventDispatcher::instance::dispatchEvent("loadingComplete");
 * @endcode
 *
 * @note This classes instance is accessible from anywhere withing the
 * program, however the instance is destroyed when the last pointer to it
 * goes out of scope. This means that all event listeners that have been
 * registered will be destroyed and a call to dispatchEvent will not do
 * anything. Therefore there must be at least one pointer to the class
 * instance that keeps it alive for as long as its being used. The Engine
 * keeps an instance alive for as long as it is running, therefore you
 * should use the global dispatcher only when the engine is running or keep
 * an instance alive yourself
 */
