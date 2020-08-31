#include "IME/core/audio/SoundEffectPlayer.h"
#include "IME/core/managers/ResourceManager.h"

namespace IME::Audio{
    SoundEffectPlayer::SoundEffectPlayer(const std::string &path)
        : AudioPlayer(path),
          currentEffectName_("")
          {}

    void SoundEffectPlayer::play(const std::string &filename){
        if (currentEffectName_ != filename) {
            soundEffect_.setBuffer(ResourceManager::getInstance()->getSoundBuffer(filename));
            currentEffectName_ = filename;
            play();
        }
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
        if (soundEffect_.getStatus() == sf::Sound::Status::Paused
            || soundEffect_.getStatus() == sf::Sound::Status::Stopped)
        {
            soundEffect_.play();
            emit("playing", currentEffectName_);
        }
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
            case sf::Music::Status::Playing:
                return Status::Playing;
            case sf::Music::Status::Paused:
                return Status::Paused;
            case sf::Music::Status::Stopped:
                return Status::Stopped;
        }
    }

    float SoundEffectPlayer::getVolume() const {
        return soundEffect_.getVolume();
    }

    void SoundEffectPlayer::loadFromFile(const std::initializer_list<std::string>& audioFileNames) {
        auto prevSfxPath = ResourceManager::getInstance()->getPathFor(ResourceType::SoundBuffer);
        ResourceManager::getInstance()->setPathFor(ResourceType::SoundBuffer,getAudioFilePath());
        for (const auto& filename : audioFileNames)
            ResourceManager::getInstance()->loadFromFile(ResourceType::SoundBuffer, filename);
        ResourceManager::getInstance()->setPathFor(ResourceType::SoundBuffer, prevSfxPath);
    }

    bool SoundEffectPlayer::isLooped() const {
        return soundEffect_.getLoop();
    }

    float SoundEffectPlayer::getDuration() const {
        if (soundEffect_.getBuffer())
            return soundEffect_.getBuffer()->getDuration().asSeconds();
        return 0.0f;
    }

    void SoundEffectPlayer::seek(float position) {
        soundEffect_.setPlayingOffset(sf::seconds(position));
    }

    const std::string &SoundEffectPlayer::getCurrentAudioFileName() const {
        return currentEffectName_;
    }

    float SoundEffectPlayer::getPlayingPosition() const {
        return soundEffect_.getPlayingOffset().asSeconds();
    }
}
