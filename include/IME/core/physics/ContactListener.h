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

#ifndef IME_CONTACTLISTENER_H
#define IME_CONTACTLISTENER_H

#include "IME/Config.h"
#include "IME/core/event/EventEmitter.h"
#include "IME/core/physics/rigid_body/Fixture.h"

namespace ime {
    class World;

    /**
     * @brief Subscribe to contact events
     *
     * These events are fired when fixtures start/cease to overlap.
     * The callbacks are passed the fixtures that started overlapping
     * or ceased overlapping
     *
     * @warning You cannot create/destroy bodies, fixtures and joints inside
     * these callbacks. For example, you may have a collision that applies
     * damage and try to destroy the associated game object and its rigid body.
     * However, it is not allowed to alter the physics world inside a callback
     * because you might destroy objects that are currently being processed,
     * leading to undefined behaviour. It is recommended to somehow flag the
     * game object for destruction inside the callback and destroy them after the
     * time step
     */
    class IME_API ContactListener {
    public:
        /**
         * @brief Add an event listener to a contact begin event
         * @param callback The function to be executed when event is fired
         * @return The callback id
         *
         * This function is called when two fixtures begin to overlap.
         * It is called for sensors and non-sensors
         *
         * @note The event can only occur inside the time step
         */
        int onContactBegin(Callback<Fixture::sharedPtr, Fixture::sharedPtr> callback);

        /**
         * @brief Add an event listener to a contact end event
         * @param callback The function to be executed when event is fired
         * @return The callback id
         *
         * This function is called when two fixtures cease to overlap.
         * It is called for sensors and non-sensors
         *
         * @note The function may be called when a body is destroyed, so
         * this event can occur outside the time step
         */
        int onContactEnd(Callback<Fixture::sharedPtr, Fixture::sharedPtr> callbackB);

        /**
         * @brief Add an event listener to a pre-solve event
         * @param callback The function to be executed when event is fired
         * @return The callback id
         *
         * This function is called after collision detection, but before
         * collision resolution
         *
         * @note The pre-solve event may be fired multiple times per time
         * step per contact due to continuous collision detection
         */
        int onPreSolve(Callback<Fixture::sharedPtr, Fixture::sharedPtr> callback);

        /**
         * @brief Add an event listener to a post-solve event
         * @param callback The function to be executed when event is fired
         * @return The callback id
         *
         * This function is called after the collision resolution
         */
        int onPostSolve(Callback<Fixture::sharedPtr, Fixture::sharedPtr> callback);

        /**
         * @brief Remove a callback from a contact
         * @param callbackId The event listeners identification number
         * @return True if the event listener was removed or false if
         *         there is no such listener in the event listener list
         */
        bool unsubscribe(int callbackId);

    private:
        EventEmitter eventEmitter_; //!< Publishes contact events
        friend class World;         //!< Needs access to the event emitter
    };
}

#endif //IME_CONTACTLISTENER_H
