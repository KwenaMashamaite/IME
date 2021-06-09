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
#include "IME/core/physics/PhysicsWorld.h"
#include "IME/graphics/Window.h"
#include "IME/graphics/WindowImpl.h"

namespace ime::priv {
    namespace {
        // Iterations recommended by Box2d
        const unsigned int VELOCITY_ITERATIONS = 8;
        const unsigned int POSITION_ITERATIONS = 3;
    }

    SceneManager::SceneManager() :
        prevScene_{nullptr}
    {}

    void SceneManager::pushScene(Scene::Ptr scene, bool enterScene) {
        IME_ASSERT(scene, "Scene must not be a nullptr")
        if (!scenes_.empty()) {
            prevScene_ = scenes_.top().get();
            if (scenes_.top()->isEntered()) {
                scenes_.top()->onPause();
            }
        }

        scenes_.push(std::move(scene));
        if (enterScene && !scenes_.top()->isEntered()) {
            scenes_.top()->isEntered_ = true;
            scenes_.top()->onEnter();
        }
    }

    void SceneManager::popScene() {
        if (scenes_.empty())
            return;

        prevScene_ = nullptr;

        // Call onExit() after removing state from container because onExit may
        // push a scene and the new scene will be removed instead of this one
        auto poppedScene = std::move(scenes_.top());
        scenes_.pop();

        if (poppedScene->isEntered())
            poppedScene->onExit();

        if (!scenes_.empty()) {
            if (scenes_.size() >= 2) {
                auto currentScene = std::move(scenes_.top());
                scenes_.pop();
                prevScene_ = scenes_.top().get();
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
        prevScene_ = nullptr;
        while (!scenes_.empty())
            scenes_.pop();
    }

    void SceneManager::clearAllExceptActive() {
        if (!scenes_.empty()) {
            if (scenes_.top()->isEntered()) {
                auto activeScene = std::move(scenes_.top());
                clear();
                scenes_.push(std::move(activeScene));
            } else
                clear();
        }
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

    void SceneManager::render(priv::Window &window) {
        auto static renderScene = [](const Scene* scene, priv::Window& renderWindow) {
            // Reset the window view to that of the scene that is being rendered
            const sf::View& view = std::any_cast<std::reference_wrapper<const sf::View>>(scene->camera_->getInternalView()).get();
            renderWindow.getImpl()->getSFMLWindow().setView(view);

            if (scene->hasTilemap_) {
                scene->tileMap_->draw(renderWindow);
                scene->gridMovers_.render(renderWindow);
            }

            scene->renderLayers_.render(renderWindow);
            scene = nullptr;
        };

        if (!scenes_.empty() && scenes_.top()->isEntered()) {
            if (prevScene_ && prevScene_->isEntered() && prevScene_->isVisibleOnPause()) {
                renderScene(prevScene_, window);
                prevScene_->gui().draw();
            }

            renderScene(scenes_.top().get(), window);
            scenes_.top()->internalEmitter_.emit("postRender", std::ref(window));

            // Draw the gui on top of everything
            scenes_.top()->gui().draw();
        }
    }

    void SceneManager::update(Time deltaTime) {
        updateScene(deltaTime, scenes_.top().get(), false);

        if (prevScene_ && prevScene_->isEntered() && prevScene_->isTimeUpdatedWhenPaused_)
            updateScene(deltaTime, prevScene_, false);
    }

    void SceneManager::handleEvent(Event event) {
        if (scenes_.empty())
            return;

        if (!scenes_.top()->isEntered())
            return;

        // Update all system components of a scene
        static auto updateSystem = [](Scene* scene, Event e) {
            if (scene->isInputEnabled_) {
                scene->inputManager_.handleEvent(e);
                scene->guiContainer_.handleEvent(e);
                scene->gridMovers().handleEvent(e);
                scene->handleEvent(e);
            } else {
                // Only pass non-input events to the scene
                if (e.type == Event::Closed || e.type == Event::Resized
                    || e.type == Event::MouseEntered || e.type == Event::MouseLeft
                    || e.type == Event::LostFocus || e.type == Event::GainedFocus)
                {
                    scene->handleEvent(e);
                    scene->guiContainer_.handleEvent(e);
                }
            }
        };

        updateSystem(scenes_.top().get(), event);

        if (prevScene_ && prevScene_->isEntered() && prevScene_->isEventUpdatedWhenPaused_)
            updateSystem(prevScene_, event);
    }

    void SceneManager::fixedUpdate(Time deltaTime) {
        updateScene(deltaTime, scenes_.top().get(), true);

        if (prevScene_ && prevScene_->isEntered() && prevScene_->isTimeUpdatedWhenPaused_)
            updateScene(deltaTime, prevScene_, true);
    }

    void SceneManager::forEachScene(const Callback<const SceneManager::ScenePtr&>& callback) {
        std::stack<Scene::Ptr> temp;
        while (!scenes_.empty()) {
            callback(scenes_.top());
            temp.push(std::move(scenes_.top()));
            scenes_.pop();
        }

        while (!temp.empty()) {
            scenes_.push(std::move(temp.top()));
            temp.pop();
        }
    }

    void SceneManager::preUpdate(Time deltaTime) {
        if (scenes_.empty())
            return;

        if (!scenes_.top()->isEntered())
            return;

        static auto update = [](Scene* scene, Time dt) {
            scene->timerManager_.preUpdate();
            scene->timerManager_.update(dt * scene->getTimescale());
            scene->audioManager_.removePlayedAudio();
            scene->internalEmitter_.emit("preUpdate", dt * scene->getTimescale());
        };

        update(scenes_.top().get(), deltaTime);

        if (prevScene_ && prevScene_->isEntered() && prevScene_->isTimeUpdatedWhenPaused_)
            update(prevScene_, deltaTime);
    }

    void SceneManager::updateScene(Time deltaTime, Scene* scene, bool fixedUpdate) {
        if (!(!scenes_.empty() && scenes_.top()->isEntered()))
            return;

        // Update gui
        scene->guiContainer_.update(deltaTime);

        // Update physics simulation
        if (scene->hasPhysicsSim_) {
            scene->internalEmitter_.emit("preStep", deltaTime * scene->getTimescale());

            if (fixedUpdate && scene->world_->isFixedStep()) {
                scene->world_->update(deltaTime * scene->getTimescale(), VELOCITY_ITERATIONS, POSITION_ITERATIONS);
            } else if (!fixedUpdate && !scene->world_->isFixedStep())
                scene->world_->update(deltaTime * scene->getTimescale(), VELOCITY_ITERATIONS, POSITION_ITERATIONS);

            scene->internalEmitter_.emit("postStep", deltaTime * scene->getTimescale());
        }

        // Update user scene
        if (fixedUpdate) {
            scene->gridMovers().update(deltaTime * scene->getTimescale());
            scene->fixedUpdate(deltaTime * scene->getTimescale());
        } else {
            if (scene->hasTilemap_)
                scene->tileMap_->update(deltaTime * scene->getTimescale());

            //Update game objects - By default, the game object updates its sprite animation
            scene->gameObjects().forEach([&scene, &deltaTime](GameObject* gameObject) {
                gameObject->update(deltaTime * scene->getTimescale());
            });

            // Update sprite animations
            scene->sprites().forEach([&scene, &deltaTime](Sprite* sprite) {
                sprite->updateAnimation(deltaTime * scene->getTimescale());
            });

            // Update user scene after all internal updates
            scene->update(deltaTime * scene->getTimescale());

            // Emit internal post update
            scene->internalEmitter_.emit("postUpdate", deltaTime * scene->getTimescale());

            // Normal update is always called after fixed update: fixedUpdate -> update -> postUpdate
            scene->postUpdate(deltaTime * scene->getTimescale());
        }
    }

    SceneManager::~SceneManager() {
        prevScene_ = nullptr;
    }
}
