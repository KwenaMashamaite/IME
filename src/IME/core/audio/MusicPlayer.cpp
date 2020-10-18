#include "IME/core/audio/MusicPlayer.h"
#include "IME/core/managers/ResourceManager.h"

namespace IME::Audio {
    void MusicPlayer::play(const std::string &song){
        if (currentMusicFileName_ != song) {
            song_ = ResourceManager::getInstance()->getMusic(song);
            currentMusicFileName_ = song;
            play();
        }
    }

    void MusicPlayer::setLoop(bool isLoop){
        if (song_ && song_->getLoop() != isLoop) {
            song_->setLoop(isLoop);
            emit("loopChanged", isLoop);
        }
    }

    void MusicPlayer::pause(){
        if (song_ && song_->getStatus() == sf::Music::Status::Playing) {
            song_->pause();
            emit("paused");
        }
    }

    void MusicPlayer::play(){
        if (song_ && (song_->getStatus() == sf::Music::Status::Paused
            || song_->getStatus() == sf::Music::Status::Stopped))
        {
            song_->play();
            emit("playing", currentMusicFileName_);
        }
    }

    void MusicPlayer::stop() {
        if (song_ && song_->getStatus() == sf::Music::Status::Playing) {
            song_->stop();
            emit("stopped");
        }
    }

    void MusicPlayer::setVolume(float volume) {
        if (song_ && song_->getVolume() != volume
            && (volume >=0 && volume <= 100)) {
            if (isMuted())
                setMute(false);
            song_->setVolume(volume);
            emit("volumeChanged", volume);
        }
    }

    Status MusicPlayer::getStatus() const {
        if (song_) {
            switch (song_->getStatus()) {
                case sf::Sound::Status::Playing:
                    return Status::Playing;
                case sf::Sound::Status::Paused:
                    return Status::Paused;
                case sf::Sound::Status::Stopped:
                    return Status::Stopped;
            }
        }
        return Audio::Status::Stopped;
    }

    float MusicPlayer::getVolume() const {
        if (song_)
            return song_->getVolume();
        return 100.0f; //Default volume is maximum
    }

    bool MusicPlayer::isLooped() const {
        if (song_)
            return song_->getLoop();
        return false;
    }

    const std::string& MusicPlayer::getCurrentAudioFileName() const {
        return currentMusicFileName_;
    }

    float MusicPlayer::getDuration() const {
        if (song_)
            return song_->getDuration().asSeconds();
        return 0.0f;
    }

    void MusicPlayer::seek(float position) {
        if (song_) {
            song_->setPlayingOffset(sf::seconds(position));
            emit("playingPositionChanged", position);
        }
    }

    float MusicPlayer::getPlayingPosition() const {
        if (song_)
            song_->getPlayingOffset().asSeconds();
        return 0.0f;
    }
}