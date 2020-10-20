#include "IME/core/audio/SoundEffectPlayer.h"
#include "IME/core/managers/ResourceManager.h"

namespace IME::Audio{
    void SoundEffectPlayer::play(const std::string &filename){
        if (currentEffectName_ != filename) {
            soundEffect_.setBuffer(ResourceManager::getInstance()->getSoundBuffer(filename));
            currentEffectName_ = filename;
        }
        play();
    }

    void SoundEffectPlayer::stop() {
        if (soundEffect_.getStatus() == sf::Sound::Status::Playing) {
            soundEffect_.stop();
            emit("stopped");
        }
    }

    void SoundEffectPlayer::pause() {
        if (soundEffect_.getStatus() == sf::Sound::Status::Playing) {
            soundEffect_.pause();
            emit("paused");
        }
    }

    void SoundEffectPlayer::play() {
        soundEffect_.play();
        emit("playing", currentEffectName_);
    }

    void SoundEffectPlayer::setVolume(float volume) {
        if (volume != soundEffect_.getVolume()
            && (volume >=0 && volume <= 100)) {
            soundEffect_.setVolume(volume);
            emit("volumeChanged", volume);
        }
    }

    void SoundEffectPlayer::setLoop(bool isLooped) {
        if (soundEffect_.getLoop() != isLooped) {
            soundEffect_.setLoop(isLooped);
            emit("loopChanged", isLooped);
        }
    }

    Status SoundEffectPlayer::getStatus() const {
        switch (soundEffect_.getStatus()) {
            case sf::SoundSource::Status::Playing:
                return Status::Playing;
            case sf::SoundSource::Status::Paused:
                return Status::Paused;
            case sf::SoundSource::Status::Stopped:
                return Status::Stopped;
        }
    }

    float SoundEffectPlayer::getVolume() const {
        return soundEffect_.getVolume();
    }

    bool SoundEffectPlayer::isLooped() const {
        return soundEffect_.getLoop();
    }

    Duration SoundEffectPlayer::getDuration() const {
        if (soundEffect_.getBuffer())
            return {soundEffect_.getPlayingOffset().asSeconds(),
                    static_cast<float>(soundEffect_.getBuffer()->getDuration().asMilliseconds()),
                    static_cast<float>(soundEffect_.getPlayingOffset().asMicroseconds())};
        return {0.0f, 0.0f, 0.0f};
    }

    void SoundEffectPlayer::seek(float position) {
        soundEffect_.setPlayingOffset(sf::milliseconds(position));
    }

    const std::string &SoundEffectPlayer::getCurrentAudioFileName() const {
        return currentEffectName_;
    }

    Duration SoundEffectPlayer::getPlayingPosition() const {
        return {soundEffect_.getPlayingOffset().asSeconds(),
                static_cast<float>(soundEffect_.getPlayingOffset().asMilliseconds()),
                static_cast<float>(soundEffect_.getPlayingOffset().asMicroseconds())};
    }

    std::string SoundEffectPlayer::getType() {
        return "SfxPlayer";
    }

    void SoundEffectPlayer::setPitch(float pitch) {
        soundEffect_.setPitch(pitch);
    }

    float SoundEffectPlayer::getPitch() const {
        soundEffect_.getPitch();
    }
}
