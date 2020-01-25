#include "InputManager.h"
#include "event/HandlerIdHolder.h"
#include "globals/Globals.h"

using Globals::Events;
using Utility::HanderIdHolder;

InputManager::InputManager() : mouseCoordinates_{0, 0} {
    HanderIdHolder::add("keyPress", Events::keyPressed.addListener([this](InputManager::Key key) {
        pressKey(key);
    }));

    HanderIdHolder::add("keyRelease", Events::keyReleased.addListener([this](Key key) {
        releaseKey(key);
    }));

    HanderIdHolder::add("mouseButtonPress", Events::mouseButtonPressed.addListener([this](MouseButton button, int x, int y) {
        pressMouse(button);
    }));

    HanderIdHolder::add("mouseButtonRelease", Events::mouseButtonReleased.addListener([this](MouseButton button, int x, int y) {
        releaseMouse(button);
    }));

    HanderIdHolder::add("mouseMove", Events::mouseMoved.addListener([this](int xMouseCoord, int yMouseCoord) {
        setMouseCoordinates(xMouseCoord, yMouseCoord);
    }));
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
    auto iter = keyMap.find(keyId);
    if (iter != keyMap.end())
        return iter->second;
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

InputManager::~InputManager() {
    Events::keyPressed.removeListener(HanderIdHolder::getIdFor("keyPress"));
    Events::keyReleased.removeListener(HanderIdHolder::getIdFor("keyRelease"));
    Events::mouseButtonPressed.removeListener(HanderIdHolder::getIdFor("mouseButtonPress"));
    Events::mouseButtonReleased.removeListener(HanderIdHolder::getIdFor("mouseButtonRelease"));
    Events::mouseMoved.removeListener(HanderIdHolder::getIdFor("mouseMove"));
}