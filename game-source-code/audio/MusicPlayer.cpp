#include "resources/ResourceManager.h"
#include "MusicPlayer.h"

void Audio::MusicPlayer::play(const std::string &song){
    song_ = ResourceManager::getMusic(song);
    if (song_)
        song_->play();
}

void Audio::MusicPlayer::setLoop(bool isLoop){
    if(song_)
        song_->setLoop(isLoop);
}

void Audio::MusicPlayer::pause(){
    if(song_)
        song_->pause();
}

void Audio::MusicPlayer::resume(){
    if(song_ && song_->getStatus() == sf::Music::Status::Paused)
        song_->play();
}

void Audio::MusicPlayer::stop() {
    if (song_)
        song_->stop();
}