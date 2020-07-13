/**
 * @brief Class for managing audio
 *
 * This class allows us to play multiple audio files of different types
 * (Music or SoundEffect, @see @class Music and @class SoundEffectPlayer)
 * simultaneously. Each audio file is played in a separate thread
 */

#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include "IAudioPlayer.h"
#include "MusicPlayer.h"
#include "SoundEffectPlayer.h"
#include <unordered_map>
#include <initializer_list>
#include <memory>
#include <string>

namespace Audio {
    class AudioManager {
    public:
        /**
         * @brief Audio type
         */
        enum class AudioType{
            SoundEffect,
            Music
        };

        /**
         * @brief Load audio files
         * @param audioType The type of audio file to be loaded
         * @param filenames File names of the audio files to be load
         * @throw FileNotFound if the specified audio files cannot be found on disk
         *
         * Use AudioType::Music for long and big audio files and AudioType::SoundEffect
         * for small, short audio files. @see @class MusicPlayer and @class SoundEffectPlayer
         */
        void loadAudioFiles(AudioType audioType, std::initializer_list<std::string> filenames);

        /**
         * @brief Play an audio file
         * @param filename Filename of the audio to play
         *
         * The audio file must be loaded first otherwise nothing will play
         * @see loadAudioFiles(AudioType, std::initializer_list<std::string>)
         * The audio file will be played in a seperate thread. This means
         * that, the main thread is not blocked and other audio file may be
         * played simultaneously
         */
        void play(const std::string& filename);

        /**
         * @brief Pause playing audio file
         * @param filename Filename of the audio to pause
         */
        void pause(const std::string& filename);

        /**
         * @brief Stop playing audio file
         * @param filename Filename of the audio to stop
         *
         * Stopping an audio file (playing/paused) will reset the current
         * playing position to the beginning
         */
        void stop(const std::string& filename);

        /**
         * @brief Remove an audio file from an audio player
         * @param filename Filename of the audio to remove
         */
        void remove(const std::string& filename);

        /**
         * @brief Loop/unloop an audio file
         * @param filename Filename of the audio to set loop for
         * @param isLooped Set true to loop and false to unloop
         *
         * All audio files are not looped by default
         */
        void setLoopFor(const std::string& filename, bool isLooped);

        /**
         * @brief Set the volume for an audio file
         * @param filename Filename of the audio to set volume for
         * @param volume Volume to set, (mute) 0 <= volume <= 100 (max)
         *
         * The default volume is 100 (max)
         */
        void setVolumeFor(const std::string& filename, float volume);

        /**
         * @brief Get the volume of an audio file
         * @param filename Audio file to get volume of
         * @return Volume of an audio file
         *
         * This function will return zero
         */
        float getVolumeFor(const std::string& filename);

        /**
         * @brief Play all paused/stopped audio files
         */
        void playAll();

        /**
         * @brief Pause all playing audio files
         */
        void pauseAll();

        /**
         * @brief Stop all playing audio files
         *
         * Stopping an audio file (playing/paused) will reset the current
         * playing position to the beginning
         */
        void stopAll();

    private:
        //Filenames of the audio files to be played
        std::unordered_map<std::string, AudioType> audioFilenames_;
        //Currently playing audio files - Each audio has its own player
        std::unordered_map<std::string, std::unique_ptr<IAudioPlayer>> audioPlayers_;
    };
}

#endif
