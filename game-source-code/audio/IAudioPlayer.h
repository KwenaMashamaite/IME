/**
 * @brief Interface for audio players
 */

#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "event/EventEmitter.h"
#include <string>

namespace Audio {
    class IAudioPlayer : public EventEmitter{
    public:
        /**
         * @brief Play audio
         * @param filename Filename of the audio to play
         */
        virtual void play(const std::string &filename) = 0;

        /**
         * @brief Stop the currently playing or paused audio
         */
        virtual void stop() = 0;

        /**
         * @brief Pause the currently playing audio
         */
        virtual void pause() = 0;

        /**
         * @brief Resume paused audio
         */
        virtual void resume() = 0;

        /**
         * @brief Set the volume of the audio
         * @param volume Volume to set
         */
        virtual void setVolume(float volume) = 0;

        /**
         * @brief Destructor
         */
        virtual ~IAudioPlayer() = default;

    protected:
        /**
         * @brief Prevent external publishing of events
         *
         * Only the class knows the conditions under which an event may be
         * fired. Therefore, events must not be raised externally as this
         * may result in events being raised at the wong time, resulting
         * in undesired and incorrect behavior
         */
        using::EventEmitter::emit;
    };
}

#endif
