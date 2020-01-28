/**
 * @brief Stream audio files from disk
 *
 * This class is ideal for playing long and big audio file such
 * as background music. The audio file is not loaded in memory
 * but rather streamed from the disk. The file must remain
 * accessible on the disk for as long as its being used. You can
 * use Audio::SoundEffectPLayer to play short sounds such as
 * gun shots and explosions
 */

#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "IAudioPlayer.h"
#include <SFML/Audio.hpp>
#include <string>
#include <memory>

namespace Audio {
    class MusicPlayer : public IAudioPlayer{
    public:
        /**
         * @brief play music file
         * @param filename File name of the Music to play
         */
        void play(const std::string &filename) override;

        /**
         * @brief Loop/unloop playing music
         * @param isLoop Set to true to loop music, false to unloop
         * 				  it is false by default
         */
        void setLoop(bool isLoop);

        /**
         * @brief Pause the Music
         */
        void pause() override;

        /**
         * @brief Resume paused music
         */
        void resume() override;

        /**
         * @brief Stop music
         */
        void stop() override;

    private:
        //pointer to playing music
        std::shared_ptr<sf::Music> song_;
    };
}

#endif