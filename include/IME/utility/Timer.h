/**
 * @brief Class for timing purposes
 */

#ifndef TIMER_H
#define TIMER_H

#include "IME/event/EventEmitter.h"

namespace IME {
    namespace Utility {
        class Timer {
        public:
            /**
             * @brief Execute a callback function once after a delay
             * @param callback Function to execute
             * @param ms Time to wait before executing callback in milliseconds
             *
             * The timing and callback execution is done in a separate thread,
             * therefore this function is not blocking. It will return immediately
             * after initiating the new thread
             */
            void setTimeOut(Callback<> callback, int ms);

            /**
             * @brief Execute a callback function repeatedly after a delay
             * @param callback Function to execute
             * @param ms Time to wait before executing callback in milliseconds
             *
             * The timing and callback execution is done in a separate thread,
             * therefore this function is not blocking. It will return immediately
             * after initiating the new thread. The callback function will execute
             * forever every delay milliseconds. The interval can be stopped by
             * setting the argument provided on invocation to false.
             */
            void setInterval(Callback<bool&> callback, int ms);
        };
    }
}

#endif //IME_TIMER_H
