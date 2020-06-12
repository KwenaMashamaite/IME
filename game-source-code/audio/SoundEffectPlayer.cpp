#include "resources/ResourceManager.h"
#include "SoundEffectPlayer.h"

void Audio::SoundEffectPlayer::play(const std::string &filename){
    soundEffect_.setBuffer(ResourceManager::getSoundBuffer(filename));
    soundEffect_.play();
    emit("playing");
}

void Audio::SoundEffectPlayer::stop() {
    if (soundEffect_.getStatus() == sf::Sound::Status::Playing) {
        soundEffect_.stop();
        emit("stopped");
    }
}

void Audio::SoundEffectPlayer::pause() {
    if (soundEffect_.getStatus() == sf::Sound::Status::Playing) {
        soundEffect_.pause();
        emit("paused");
    }
}

void Audio::SoundEffectPlayer::resume() {
    if (soundEffect_.getStatus() == sf::Sound::Status::Paused
        || soundEffect_.getStatus() == sf::Sound::Status::Stopped)
    {
        soundEffect_.play();
        emit("playing");
    }
}

void Audio::SoundEffectPlayer::setVolume(float volume) {
    if (volume != soundEffect_.getVolume()) {
        soundEffect_.setVolume(volume);
        emit("volumeChanged", volume);
    }
}
