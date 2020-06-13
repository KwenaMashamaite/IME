#include "resources/ResourceManager.h"
#include "MusicPlayer.h"

void Audio::MusicPlayer::play(const std::string &song){
    song_ = ResourceManager::getMusic(song);
    song_->play();
    emit("playing");
}

void Audio::MusicPlayer::setLoop(bool isLoop){
    if (song_ && song_->getLoop() != isLoop) {
        song_->setLoop(isLoop);
        emit("loopChanged", isLoop);
    }
}

void Audio::MusicPlayer::pause(){
    if (song_ && song_->getStatus() == sf::Music::Status::Playing) {
        song_->pause();
        emit("paused");
    }
}

void Audio::MusicPlayer::resume(){
    if (song_ && (song_->getStatus() == sf::Music::Status::Paused
        || song_->getStatus() == sf::Music::Status::Stopped))
    {
        song_->play();
        emit("playing");
    }
}

void Audio::MusicPlayer::stop() {
    if (song_ && song_->getStatus() == sf::Music::Status::Playing) {
        song_->stop();
        emit("stopped");
    }
}

void Audio::MusicPlayer::setVolume(float volume) {
    if (song_ && song_->getVolume() != volume
        && (volume >=0 && volume <= 100)) {
        song_->setVolume(volume);
        emit("volumeChanged", volume);
    }
}

Audio::Status Audio::MusicPlayer::getStatus() const {
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
}

float Audio::MusicPlayer::getVolume() const {
    if (song_)
        return song_->getVolume();
}
