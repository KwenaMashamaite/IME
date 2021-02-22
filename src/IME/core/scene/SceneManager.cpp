////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include "IME/core/scene/SceneManager.h"
#include "IME/core/scene/Scene.h"
#include "IME/core/physics/World.h"
#include "IME/graphics/Window.h"

namespace ime {
    void SceneManager::pushScene(std::shared_ptr<Scene> scene, bool enterScene) {
        IME_ASSERT(scene, "Cannot add nullptr as a state");
        IME_ASSERT(!scene->isManaged_, R"(Scene )" + scene->getName() + R"( is already owned by a scene manager)");
        if (!scenes_.empty()) {
            prevScene_ = scenes_.top();
            if (scenes_.top()->isEntered()) {
                scenes_.top()->onPause();
            }
        }

        scene->isManaged_ = true;
        scenes_.push(scene);
        if (enterScene && !scene->isEntered()) {
            scene->isEntered_ = true;
            scene->onEnter();
        }
    }

    void SceneManager::popScene() {
        if (scenes_.empty())
            return;

        prevScene_ = nullptr;

        // Call onExit() after removing state from container because onExit may
        // push a scene and the new scene will be removed instead of this one
        auto poppedScene = scenes_.top();
        scenes_.pop();

        if (poppedScene->isEntered())
            poppedScene->onExit();

        if (!scenes_.empty()) {
            if (scenes_.size() >= 2) {
                auto currentScene = scenes_.top();
                scenes_.pop();
                prevScene_ = scenes_.top();
                scenes_.push(std::move(currentScene));
            }

            if (scenes_.top()->isEntered())
                scenes_.top()->onResume();
            else {
                scenes_.top()->isEntered_ = true;
                scenes_.top()->onEnter();
            }
        }
    }

    std::size_t SceneManager::getSceneCount() const {
        return scenes_.size();
    }

    void SceneManager::clear() {
        while (!scenes_.empty())
            popScene();
    }

    void SceneManager::enterTopScene() const {
        if (scenes_.empty())
            return;

        if (!scenes_.top()->isEntered()) {
            scenes_.top()->isEntered_ = true;
            scenes_.top()->onEnter();
        }
    }

    bool SceneManager::isEmpty() const {
        return scenes_.empty();
    }

    void SceneManager::render(Window &window) {
        if (!scenes_.empty() && scenes_.top()->isEntered()) {
            if (prevScene_ && prevScene_->isEntered() && prevScene_->isVisibleOnPause())
                prevScene_->render(window);

            scenes_.top()->render(window);
        }
    }

    void SceneManager::update(Time deltaTime) {
        updateScene(deltaTime, false);
    }

    void SceneManager::handleEvent(Event event) {
        if (scenes_.empty())
            return;

        if (!scenes_.top()->isEntered())
            return;

        scenes_.top()->inputManager_.handleEvent(event);
        scenes_.top()->guiContainer_.handleEvent(event);
        scenes_.top()->handleEvent(event);
    }

    void SceneManager::fixedUpdate(Time deltaTime) {
        updateScene(deltaTime, true);
    }

    void SceneManager::preUpdate(Time deltaTime) {
        if (scenes_.empty())
            return;

        if (!scenes_.top()->isEntered())
            return;

        auto scene = scenes_.top();
        scene->timerManager_.preUpdate();
        scene->timerManager_.update(deltaTime * scene->getTimescale());
        scene->audioManager_.removePlayedAudio();
    }

    void SceneManager::updateScene(Time deltaTime, bool fixedUpdate) {
        if (!(!scenes_.empty() && scenes_.top()->isEntered()))
            return;

        auto& scene = scenes_.top();
        scene->internalEmitter_.emit("preUpdate");
        scene->internalEmitter_.emit("preUpdate", deltaTime * scene->getTimescale());

        // Update physics simulation
        if (scene->hasPhysicsSim_) {
            scene->internalEmitter_.emit("preStep");
            scene->internalEmitter_.emit("preStep", deltaTime * scene->getTimescale());

            if (fixedUpdate && scene->world_->isFixedStep()) {
                scene->world_->update(deltaTime * scene->getTimescale(), 8, 3);
            } else if (!fixedUpdate && !scene->world_->isFixedStep())
                scene->world_->update(deltaTime * scene->getTimescale(), 8, 3);

            scene->internalEmitter_.emit("postStep");
            scene->internalEmitter_.emit("postStep", deltaTime * scene->getTimescale());
        }

        // Update scene
        if (fixedUpdate)
            scene->fixedUpdate(deltaTime * scene->getTimescale());
        else
            scene->update(deltaTime * scene->getTimescale());

        scene->internalEmitter_.emit("postUpdate");
        scene->internalEmitter_.emit("postUpdate", deltaTime * scene->getTimescale());
    }
}
