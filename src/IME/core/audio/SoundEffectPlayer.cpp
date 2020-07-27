#include "IME/core/audio/SoundEffectPlayer.h"

namespace IME::Audio{
    SoundEffectPlayer::SoundEffectPlayer(const std::string &path)
        : AudioPlayer(path),
          soundEffects_(ResourceHolder<sf::SoundBuffer>(path, {})),
          currentEffectName_("")
          {}

    void SoundEffectPlayer::play(const std::string &filename){
        if (currentEffectName_ != filename) {
            currentSoundEffect_.setBuffer(*soundEffects_.get(filename));
            currentEffectName_ = filename;
            play();
        }
    }

    void SoundEffectPlayer::stop() {
        if (currentSoundEffect_.getStatus() == sf::Sound::Status::Playing) {
            currentSoundEffect_.stop();
            emit("stopped");
        }
    }

    void SoundEffectPlayer::pause() {
        if (currentSoundEffect_.getStatus() == sf::Sound::Status::Playing) {
            currentSoundEffect_.pause();
            emit("paused");
        }
    }

    void SoundEffectPlayer::play() {
        if (currentSoundEffect_.getStatus() == sf::Sound::Status::Paused
            || currentSoundEffect_.getStatus() == sf::Sound::Status::Stopped)
        {
            currentSoundEffect_.play();
            emit("playing", currentEffectName_);
        }
    }

    void SoundEffectPlayer::setVolume(float volume) {
        if (volume != currentSoundEffect_.getVolume()
            && (volume >=0 && volume <= 100)) {
            currentSoundEffect_.setVolume(volume);
            emit("volumeChanged", volume);
        }
    }

    void SoundEffectPlayer::setLoop(bool isLooped) {
        if (currentSoundEffect_.getLoop() != isLooped) {
            currentSoundEffect_.setLoop(isLooped);
            emit("loopChanged", isLooped);
        }
    }

    Status SoundEffectPlayer::getStatus() const {
        switch (currentSoundEffect_.getStatus()) {
            case sf::Music::Status::Playing:
                return Status::Playing;
            case sf::Music::Status::Paused:
                return Status::Paused;
            case sf::Music::Status::Stopped:
                return Status::Stopped;
        }
    }

    float SoundEffectPlayer::getVolume() const {
        return currentSoundEffect_.getVolume();
    }

    void SoundEffectPlayer::loadFromFile(const std::initializer_list<std::string>& audioFiles) {
        std::for_each(audioFiles.begin(), audioFiles.end(), [this](const auto& filename){
            soundEffects_.loadFromFile(filename);
        });
    }

    bool SoundEffectPlayer::isLooped() const {
        return currentSoundEffect_.getLoop();
    }

    float SoundEffectPlayer::getDuration() const {
        if (currentSoundEffect_.getBuffer())
            return currentSoundEffect_.getBuffer()->getDuration().asSeconds();
        return 0.0f;
    }

    void SoundEffectPlayer::seek(float position) {
        currentSoundEffect_.setPlayingOffset(sf::seconds(position));
    }

    const std::string &SoundEffectPlayer::getCurrentAudioFileName() const {
        return currentEffectName_;
    }

    float SoundEffectPlayer::getPlayingPosition() const {
        return currentSoundEffect_.getPlayingOffset().asSeconds();
    }

    void SoundEffectPlayer::next() {
        if (soundEffects_.getSize() > 1)
            ;//@todo play next song
    }

    void SoundEffectPlayer::prev() {
        if (soundEffects_.getSize() > 1u && getDuration() <= 1.0f)
            ; //@todo Play previous song
        else{ //Restart
            stop();
            play();
        }
    }
}
