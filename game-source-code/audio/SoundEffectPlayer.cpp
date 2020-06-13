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
    if (volume != soundEffect_.getVolume()
        && (volume >=0 && volume <= 100)) {
        soundEffect_.setVolume(volume);
        emit("volumeChanged", volume);
    }
}

void Audio::SoundEffectPlayer::setLoop(bool isLooped) {
    if (soundEffect_.getLoop() != isLooped) {
        soundEffect_.setLoop(isLooped);
        emit("loopChanged", isLooped);
    }
}

Audio::Status Audio::SoundEffectPlayer::getStatus() const {
    switch (soundEffect_.getStatus()) {
        case sf::Music::Status::Playing:
            return Status::Playing;
        case sf::Music::Status::Paused:
            return Status::Paused;
        case sf::Music::Status::Stopped:
            return Status::Stopped;
    }
}

float Audio::SoundEffectPlayer::getVolume() const {
    return soundEffect_.getVolume();
}
