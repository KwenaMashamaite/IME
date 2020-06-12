/**
 * @brief Class for managing audio
 *
 * This class allows us to play multiple audio files of different types
 * (Music or SoundEffect; @see @class Music and @class SoundEffectPlayer)
 * simultaneously
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
         * @brief Play audio file
         * @param filename Filename of the audio to play
         *
         * The audio file must be loaded first otherwise nothing will play
         * @see loadAudioFiles(AudioType, std::initializer_list<std::string>)
         */
        void play(const std::string& filename);

        /**
         * @brief Pause playing audio file
         * @param filename Filename of the audio to pause
         */
        void pause(const std::string& filename);

        /**
         * @brief Resume paused audio file
         * @param filename Filename of the audio to pause
         */
        void resume(const std::string& filename);

        /**
         * @brief Stop playing audio file
         * @param filename Filename of the audio to stop
         *
         * A Stopped audio file cannot be resumed, it needs to be replayed
         */
        void stop(const std::string& filename);

        /**
         * @brief Pause all playing audio
         *
         * Paused audio may be resumed using @see resumeAll()
         */
        void pauseAll();

        /**
         * @brief Resume all paused audio
         */
        void resumeAll();

        /**
         * @brief Stop all playing audio
         *
         * A stopped audio file cannot be resumed, it needs to be replayed
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
