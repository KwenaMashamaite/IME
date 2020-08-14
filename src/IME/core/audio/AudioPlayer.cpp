#include "IME/core/audio/AudioPlayer.h"

namespace IME{
    Audio::AudioPlayer::AudioPlayer(const std::string &path)
        : isMuted_(false),
          volumeBeforeMute_(100.0f)
    {}

    void Audio::AudioPlayer::adjustVolume(float offset) {
        if (auto currentVolume = getVolume(); currentVolume + offset > 100.0f)
            setVolume(100.0f);
        else if (currentVolume + offset < 0.0f)
            setVolume(0.0f);
        else
            setVolume(currentVolume + offset);
    }

    void Audio::AudioPlayer::setMute(bool mute) {
        if (mute && !isMuted_) {
            isMuted_ = true;
            volumeBeforeMute_ = getVolume();
            setVolume(0.0f);
            EventEmitter::emit("muted");
        } else if (!mute && isMuted_) {
            isMuted_ = false;
            setVolume(volumeBeforeMute_);
            EventEmitter::emit("unmuted");
        }
    }

    bool Audio::AudioPlayer::isMuted() const {
        return isMuted_;
    }

    void Audio::AudioPlayer::setPath(const std::string &audioFilesPath) {
        path_ = audioFilesPath;
    }

    const std::string &Audio::AudioPlayer::getAudioFilePath() const {
        return path_;
    }

    void Audio::AudioPlayer::restart() {
        stop();
        play();
    }
}
