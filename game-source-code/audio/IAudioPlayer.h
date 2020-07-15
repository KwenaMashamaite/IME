/**
 * @brief Interface for audio players
 */

#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include "event/EventEmitter.h"
#include <initializer_list>
#include <string>

namespace Audio {
    /**
     * @brief Audio status
     */
    enum class Status{
        Playing,
        Paused,
        Stopped
    };

    class IAudioPlayer : public EventEmitter{
    public:
        /**
         * @brief Set the path to the audio files
         * @param audioFilePath Path to the audio files
         */
        virtual void setPath(const std::string& audioFilePath) = 0;

        /**
         * @brief Load audio files into player
         * @param audioFileNames Names of the audio files to load
         * @throw FileNotFound if an audio file cannot be found in the specified path
         */
        virtual void load(const std::initializer_list<std::string>& audioFiles) = 0;

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
         * @brief Play paused or stopped audio file
         */
        virtual void play() = 0;

        /**
         * @brief Play next audio file
         *
         * This function does nothing if there's no more audio files to play
         */
        virtual void next() = 0;

        /**
         * @brief Play previous audio file
         */
        virtual void prev() = 0;

        /**
         * @brief Set the volume of the audio
         * @param volume Volume to set
         *
         * This function completely overrides the current volume. To adjust the
         * volume by a certain offset @see setVolumeOffset
         */
        virtual void setVolume(float volume) = 0;

        /**
         * @brief Loop/unloop audio
         * @param isLooped Set to true to loop audio, false to unloop audio
         */
        virtual void setLoop(bool isLooped) = 0;

        /**
         * @brief Check if playing audio file is looped or not
         * @return True if audio file is looped, false if audio file is not
         *          looped
         */
        virtual bool isLooped() const = 0;

        /**
         * @brief Check if audio player is muted or not
         * @return True if audio player is muted or false if audio player is
         *         not muted
         */
        virtual bool isMuted() const = 0;

        /**
         * @brief Turn the volume up/down by a given offset
         * @param offset Value to increase/decrease the volume by
         *
         * This function adds on to the current volume of the audio player.
         * A positive offset increases the volume while a negative offset
         * decreases the volume. This function will unmmute the audio player
         * if its muted
         */
        virtual void adjustVolume(float offset) = 0;

        /**
         * @brief Get the duration of the current audio file
         * @return Duration of the current audio file
         *
         * The duration is in seconds
         */
        virtual float getDuration() const = 0;

        /**
         * @brief Get the current playing position of the audio file
         * @return Current playing position of the audio file
         */
        virtual float getPlayingPosition() const = 0;

        /**
         * @brief Change the current playing position of the audio file
         * @param position New playing position of the audio file
         *
         * The new position must be between zero and the duration of the song
         */
        virtual void seek(float position) = 0;

        /**
         * @brief Get the current status of the audio file
         * @return Current status of the audio file
         */
        virtual Status getStatus() const = 0;

        /**
         * @brief Get the volume of an audio file
         * @return Volume of an audio file
         */
        virtual float getVolume() const = 0;

        /**
         * @brief Get the path to the audio files
         * @return Path to the audio files
         */
        virtual const std::string& getAudioFilePath() const = 0;

        /**
         * @brief Get the name of the current audio file
         * @return Name of the current audio file
         */
        virtual const std::string& getCurrentAudioFileName() const = 0;

        /**
         * @brief Mute or ummute the audio
         * @param mute True to mute the audio or false to unmute the audio
         */
        virtual void setMute(bool mute) = 0;

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
