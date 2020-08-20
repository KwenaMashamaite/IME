#include "IME/core/audio/AudioManager.h"
#include "IME/utility/Helpers.h"
#include <algorithm>

using IME::Utility::findIn;

namespace IME::Audio{
    AudioManager::AudioManager(const std::string &musicFilePath,
        const std::string &soundEffectFilePath)
        : musicFilesPath_(musicFilePath),
        soundEffectFilesPath_(soundEffectFilePath)
        {}

    void AudioManager::loadAudioFiles(AudioType audioType,
         std::initializer_list<std::string> filenames)
     {
        std::for_each(filenames.begin(), filenames.end(), [=](const auto& filename){
            if (audioType == AudioType::Music)
                ResourceManager::getInstance()->loadFromFile(ResourceType::Music, filename);
            else
                ResourceManager::getInstance()->loadFromFile(ResourceType::SoundBuffer, filename);

            audioFilenames_.insert({filename, audioType});
        });
    }

    void AudioManager::play(const std::string& filename) {
        if (findIn(audioPlayers_, filename)) {
            audioPlayers_[filename]->play(filename);
            return;
        }

        if (findIn(audioFilenames_, filename)) {
            std::unique_ptr<AudioPlayer> audioPlayer;
            if (audioFilenames_.at(filename) == AudioType::Music)
                audioPlayer = std::make_unique<Audio::MusicPlayer>(musicFilesPath_);
            else
                audioPlayer = std::make_unique<Audio::SoundEffectPlayer>(soundEffectFilesPath_);

            audioPlayer->play(filename);
            audioPlayers_.insert({filename, std::move(audioPlayer)});
        }
    }

    void AudioManager::pause(const std::string& filename) {
        if (findIn(audioPlayers_, filename))
            audioPlayers_.at(filename)->pause();
    }

    void AudioManager::stop(const std::string& filename) {
        if (findIn(audioPlayers_, filename))
            audioPlayers_.at(filename)->stop();
    }

    bool AudioManager::remove(const std::string &filename) {
        if (findIn(audioPlayers_, filename)) {
            audioPlayers_.at(filename)->stop();
            return audioPlayers_.erase(filename);
        }
        return false;
    }

    void AudioManager::setVolumeFor(const std::string &filename, float volume) {
        if (findIn(audioPlayers_, filename))
            audioPlayers_.at(filename)->setVolume(volume);
    }

    void AudioManager::setLoopFor(const std::string &filename, bool isLooped) {
        if (findIn(audioPlayers_, filename))
            audioPlayers_.at(filename)->setLoop(isLooped);
    }

    void AudioManager::playAll() {
        std::for_each(audioPlayers_.begin(), audioPlayers_.end(),
            [](const auto& audioPlayer) {
                audioPlayer.second->play();
        });
    }

    void AudioManager::pauseAll() {
        std::for_each(audioPlayers_.begin(), audioPlayers_.end(),
            [](const auto& audioPlayer) {
                audioPlayer.second->pause();
            }
        );
    }

    void AudioManager::stopAll() {
        std::for_each(audioPlayers_.begin(), audioPlayers_.end(),
            [](const auto& audioPlayer) {
                audioPlayer.second->stop();
            }
        );
    }

    float AudioManager::getVolumeFor(const std::string &filename) {
        if (findIn(audioPlayers_, filename))
            return audioPlayers_.at(filename)->getVolume();
        return 0.0f;
    }
}
