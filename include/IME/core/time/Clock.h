/**
 * @brief This class models a clock
 */

#ifndef CLOCK_H
#define CLOCK_H

namespace IME {
    namespace Time {
        class Clock {
        public:
            /**
             * @brief Constructor
             */
            Clock();

            /**
             * @brief Get the time passed since the clock was reset
             * @return Time passed since the clock was reset in seconds
             */
            double getElapsedTimeInSeconds();

            /**
             * @brief Reset the clock and get the time passed since the clock
             *        last reset
             * @return Time passed since the clock was reset in seconds
             */
            double restart();

        private:
            //Stores the amount of time passed since last call to restart().
            double timeWhenClockWasLastReset_;

            /**
             * @brief Get the amount of time in seconds that has passed
             *        since the process started executing
             * @return Time that has passed since the process
             *         started executing
             */
            double getProcessTimeInSeconds();
        };
    }
}

#endif