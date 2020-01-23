#include "InputManager.h"

InputManager::InputManager() : mouseCoordinates_{0, 0} {

}

void InputManager::pressKey(InputManager::Key keyId) {
    currentKeyMap_[keyId] = true;
}

void InputManager::releaseKey(InputManager::Key keyId) {
    currentKeyMap_[keyId] = false;
}

void InputManager::update(){
    for (auto& iter : currentKeyMap_)
        previousKeyMap_[iter.first] = iter.second;
    for (auto& iter : currentMouseButtonState_)
        previousMouseButtonState_[iter.first] = iter.second;
}

bool InputManager::wasKeyDown(InputManager::Key keyId) const {
    return getKeyState(previousKeyMap_, keyId);
}

bool InputManager::isKeyPressed(InputManager::Key keyId) const{
    return (isKeyDown(keyId) && !wasKeyDown(keyId));
}

bool InputManager::isMouseButtonPressed(InputManager::MouseButton mouseButton) const {
    return (getKeyState(currentMouseButtonState_, mouseButton)
            && !getKeyState(previousMouseButtonState_, mouseButton));
}

bool InputManager::isKeyDown(InputManager::Key keyId) const{
    return getKeyState(currentKeyMap_, keyId);
}

template <typename T, typename U>
bool InputManager::getKeyState(const std::unordered_map<T, bool>& keyMap, U keyId) const{
    auto key = keyMap.find(keyId);
    if (key != keyMap.end())
        return key->second;
    return false;
}

void InputManager::pressMouse(InputManager::MouseButton mouseButton) {
    currentMouseButtonState_[mouseButton] = true;
}

void InputManager::releaseMouse(InputManager::MouseButton mouseButton) {
    currentMouseButtonState_[mouseButton] = false;
}

void InputManager::setMouseCoordinates(unsigned int x, unsigned int y) {
    mouseCoordinates_.x = x;
    mouseCoordinates_.y = y;
}

MousePosition InputManager::getMouseCoords() const {
    return mouseCoordinates_;
}