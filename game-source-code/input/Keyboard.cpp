#include "Keyboard.h"
#include "globals/Globals.h"

using Globals::Events;

Keyboard::Keyboard() {
    handlerIdNumbers_.add("keyPress", Events::keyPressed.addListener(
        [this](Key key) {pressKey(key);}
    ));

    handlerIdNumbers_.add("keyRelease", Events::keyReleased.addListener(
        [this](Key key) {releaseKey(key);}
    ));
}

void Keyboard::update(){
    for (const auto& iter : currentKeyMap_)
        previousKeyMap_[iter.first] = iter.second;
}

void Keyboard::pressKey(Key keyId) {
    currentKeyMap_[keyId] = true;
}

void Keyboard::releaseKey(Key keyId) {
    currentKeyMap_[keyId] = false;
}

bool Keyboard::wasKeyHeld(Key key){
    return getKeyState(previousKeyMap_, key);
}

bool Keyboard::isKeyPressed(Key keyId){
    return (isKeyHeld(keyId) && !wasKeyHeld(keyId));
}

bool Keyboard::isKeyHeld(Key key){
    return getKeyState(currentKeyMap_, key);
}

bool Keyboard::getKeyState(const std::unordered_map<Key, bool>& keyMap, Key keyId){
    auto iter = keyMap.find(keyId);
    if (iter != keyMap.end())
        return iter->second;
    return false;
}

Keyboard::~Keyboard(){
    Events::keyPressed.removeListener(handlerIdNumbers_.getIdFor("keyPress"));
    Events::keyReleased.removeListener(handlerIdNumbers_.getIdFor("keyRelease"));
    Events::mouseButtonPressed.removeListener(handlerIdNumbers_.getIdFor("mouseButtonPress"));
    Events::mouseButtonReleased.removeListener(handlerIdNumbers_.getIdFor("mouseButtonRelease"));
    Events::mouseMoved.removeListener(handlerIdNumbers_.getIdFor("mouseMove"));
}