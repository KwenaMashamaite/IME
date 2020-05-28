#include "resources/ResourceManager.h"
#include "SoundEffectPlayer.h"

void Audio::SoundEffectPlayer::play(const std::string &filename){
    soundEffect_.setBuffer(ResourceManager::getSoundBuffer(filename));
    soundEffect_.play();
}

void Audio::SoundEffectPlayer::stop() {
    soundEffect_.stop();
}

void Audio::SoundEffectPlayer::pause() {
    soundEffect_.pause();
}

void Audio::SoundEffectPlayer::resume() {
    if (soundEffect_.getStatus() == sf::Sound::Status::Paused)
        soundEffect_.play();
}

void Audio::SoundEffectPlayer::setVolume(float volume) {
    soundEffect_.setVolume(volume);
}
