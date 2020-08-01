#include "IME/utility/Clock.h"
#include <ctime>

namespace IME::Utility {
    Clock::Clock() {
        timeWhenClockWasLastReset_ = getProcessTimeInSeconds();
    }

    double Clock::getProcessTimeInSeconds() {
        clock_t time = clock();
        return static_cast<double>(time) / CLOCKS_PER_SEC;
    }

    double Clock::getElapsedTimeInSeconds() {
        return getProcessTimeInSeconds() - timeWhenClockWasLastReset_;
    }

    double Clock::restart() {
        auto timeElasped = getElapsedTimeInSeconds();
        timeWhenClockWasLastReset_ = getProcessTimeInSeconds();
        return timeElasped;
    }
}
