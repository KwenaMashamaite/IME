#include "resources/ResourceManager.h"
#include "SoundEffectPlayer.h"

Audio::SoundEffectPlayer::SoundEffectPlayer(const std::string &path)
    : path_(path),
      soundEffects_(ResourceHolder<sf::SoundBuffer>(path, {})),
      currentEffectName_(""),
      isMuted_(false),
      volumeBeforeMute_(100.0f)
      {}

void Audio::SoundEffectPlayer::play(const std::string &filename){
    if (currentEffectName_ != filename) {
        currentSoundEffect_.setBuffer(*soundEffects_.get(filename));
        currentEffectName_ = filename;
        play();
    }
}

void Audio::SoundEffectPlayer::stop() {
    if (currentSoundEffect_.getStatus() == sf::Sound::Status::Playing) {
        currentSoundEffect_.stop();
        emit("stopped");
    }
}

void Audio::SoundEffectPlayer::pause() {
    if (currentSoundEffect_.getStatus() == sf::Sound::Status::Playing) {
        currentSoundEffect_.pause();
        emit("paused");
    }
}

void Audio::SoundEffectPlayer::play() {
    if (currentSoundEffect_.getStatus() == sf::Sound::Status::Paused
        || currentSoundEffect_.getStatus() == sf::Sound::Status::Stopped)
    {
        currentSoundEffect_.play();
        emit("playing", currentEffectName_);
    }
}

void Audio::SoundEffectPlayer::setVolume(float volume) {
    if (volume != currentSoundEffect_.getVolume()
        && (volume >=0 && volume <= 100)) {
        currentSoundEffect_.setVolume(volume);
        emit("volumeChanged", volume);
    }
}

void Audio::SoundEffectPlayer::setLoop(bool isLooped) {
    if (currentSoundEffect_.getLoop() != isLooped) {
        currentSoundEffect_.setLoop(isLooped);
        emit("loopChanged", isLooped);
    }
}

Audio::Status Audio::SoundEffectPlayer::getStatus() const {
    switch (currentSoundEffect_.getStatus()) {
        case sf::Music::Status::Playing:
            return Status::Playing;
        case sf::Music::Status::Paused:
            return Status::Paused;
        case sf::Music::Status::Stopped:
            return Status::Stopped;
    }
}

float Audio::SoundEffectPlayer::getVolume() const {
    return currentSoundEffect_.getVolume();
}

void Audio::SoundEffectPlayer::setPath(const std::string &audioFilePath) {
    path_ = audioFilePath;
}

void Audio::SoundEffectPlayer::load(const std::initializer_list<std::string>& audioFiles) {
    std::for_each(audioFiles.begin(), audioFiles.end(), [this](const auto& filename){
        soundEffects_.load(filename);
    });
}

bool Audio::SoundEffectPlayer::isLooped() const {
    return currentSoundEffect_.getLoop();
}

float Audio::SoundEffectPlayer::getDuration() const {
    if (currentSoundEffect_.getBuffer())
        return currentSoundEffect_.getBuffer()->getDuration().asSeconds();
    return 0.0f;
}

void Audio::SoundEffectPlayer::seek(float position) {
    currentSoundEffect_.setPlayingOffset(sf::seconds(position));
}

const std::string &Audio::SoundEffectPlayer::getAudioFilePath() const {
    return path_;
}

const std::string &Audio::SoundEffectPlayer::getCurrentAudioFileName() const {
    return currentEffectName_;
}

float Audio::SoundEffectPlayer::getPlayingPosition() const {
    return currentSoundEffect_.getPlayingOffset().asSeconds();
}

void Audio::SoundEffectPlayer::next() {
    if (soundEffects_.getSize() > 1)
        ;//@todo play next song
}

void Audio::SoundEffectPlayer::prev() {
    if (soundEffects_.getSize() > 1u && getDuration() <= 1.0f)
        ; //@todo Play previous song
    else{ //Restart
        stop();
        play();
    }
}

bool Audio::SoundEffectPlayer::isMuted() const {
    return isMuted_;
}

void Audio::SoundEffectPlayer::adjustVolume(float offset) {
    auto currentVolume = getVolume();
    if (currentVolume + offset > 100.0f)
        setVolume(100.0f);
    else if (currentVolume + offset < 0.0f)
        setVolume(0.0f);
    else
        setVolume(currentVolume + offset);
}

void Audio::SoundEffectPlayer::setMute(bool mute) {
    if (mute && !isMuted_) {
        isMuted_ = true;
        volumeBeforeMute_ = getVolume();
        setVolume(0.0f);
        emit("muteChanged", isMuted_);
    }else if (!mute && isMuted_){
        isMuted_ = false;
        setVolume(volumeBeforeMute_);
        emit("muteChanged", isMuted_);
    }
}
