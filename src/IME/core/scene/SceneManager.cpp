////////////////////////////////////////////////////////////////////////////////
// IME - Infinite Motion Engine
//
// Copyright (c) 2020-2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
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
#include "IME/core/physics/PhysicsEngine.h"
#include "IME/graphics/RenderTarget.h"
#include "IME/graphics/RenderTargetImpl.h"
#include "IME/graphics/shapes/RectangleShape.h"
#include "IME/utility/Helpers.h"

namespace ime::priv {
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
        auto* activeScene = scenes_.top().get();

        if (activeScene->isEntered()) {
            if (activeScene->isCached())
                activeScene->onResumeFromCache();
        } else if (enterScene) {
            activeScene->isEntered_ = true;
            activeScene->onEnter();
        }
    }

    Scene::Ptr SceneManager::popCached(const std::string &name) {
        auto found = cachedScenes_.find(name);

        if (found != cachedScenes_.end()) {
            auto scene = std::move(found->second);
            cachedScenes_.erase(found);
            return scene;
        }

        return nullptr;
    }

    Scene *SceneManager::getCached(const std::string &name) {
        return const_cast<Scene*>(std::as_const(*this).getCached(name));
    }

    const Scene *SceneManager::getCached(const std::string &name) const {
        if (isCached(name))
            return cachedScenes_.at(name).get();
        else
            return nullptr;
    }

    void SceneManager::cache(const std::string &name, Scene::Ptr scene) {
        IME_ASSERT(scene, "Cached scene must not be a nullptr")
        scene->setCached(true, name);
        cachedScenes_.insert({name, std::move(scene)});
    }

    bool SceneManager::isCached(const std::string &name) const {
        return cachedScenes_.find(name) != cachedScenes_.end();
    }

    bool SceneManager::removeCached(const std::string &name) {
        std::size_t sizeBefore = cachedScenes_.size();
        cachedScenes_.erase(name);
        return cachedScenes_.size() < sizeBefore;
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

        if (const auto& [isCached, cacheAlias] = poppedScene->cacheState_; isCached)
            cachedScenes_.insert({cacheAlias, std::move(poppedScene)});

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

    Scene* SceneManager::getActiveScene() {
        return const_cast<Scene*>(std::as_const(*this).getActiveScene());
    }

    const Scene *SceneManager::getActiveScene() const {
        if (scenes_.empty() || !scenes_.top()->isEntered())
            return nullptr;
        else
            return scenes_.top().get();
    }

    Scene *SceneManager::getBackgroundActiveScene() {
        return const_cast<Scene*>(std::as_const(*this).getBackgroundScene());
    }

    const Scene *SceneManager::getBackgroundScene() const {
        if (prevScene_ && prevScene_->isVisibleWhenPaused_)
            return prevScene_;

        return nullptr;
    }

    std::size_t SceneManager::getSceneCount() const {
        return scenes_.size();
    }

    void SceneManager::clear() {
        prevScene_ = nullptr;
        while (!scenes_.empty())
            scenes_.pop();
    }

    void SceneManager::clearCachedScenes() {
        cachedScenes_.clear();
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

    void SceneManager::render(priv::RenderTarget &window) {
        auto static renderScene = [](Scene* scene, Camera* camera, priv::RenderTarget& renderWindow) {
            scene->onPreRender();

            if (!camera->isDrawable())
                return;

            // Reset view so that the scene can be rendered on the current camera
            const sf::View& view = std::any_cast<std::reference_wrapper<const sf::View>>(camera->getInternalView()).get();
            renderWindow.getImpl()->getSFMLWindow().setView(view);

            if (scene->hasTilemap_) {
                scene->tileMap_->draw(renderWindow);
                scene->gridMovers_.render(renderWindow);
            }

            scene->renderLayers_.render(renderWindow);

            // Render camera outline
            static RectangleShape camOutline;

            auto [x, y, width, height] = camera->getBounds();
            camOutline.setSize({width, height});
            camOutline.setPosition(x, y);
            camOutline.setFillColour(Colour::Transparent);
            camOutline.setOutlineThickness(-camera->getOutlineThickness());
            camOutline.setOutlineColour(camera->getOutlineColour());
            renderWindow.draw(camOutline);

            scene->onPostRender();
        };

        // Render the scene on each camera to update its view
        auto static renderEachCam = [](Scene* scene, priv::RenderTarget& renderTarget) {
            // Render secondary cameras
            scene->getCameras().forEach([scene, &renderTarget](Camera* secondaryCam) {
                renderScene(scene, secondaryCam, renderTarget);
            });

            // Render main/default camera
            renderScene(scene, &scene->getCamera(), renderTarget);
        };

        if (!scenes_.empty() && scenes_.top()->isEntered()) {
            // Render background scene
            if (prevScene_ && prevScene_->isEntered() && prevScene_->isVisibleOnPause()) {
                renderEachCam(prevScene_, window);
                prevScene_->getGui().draw();
            }

            // Render active scene
            Scene* activeScene = scenes_.top().get();
            renderEachCam(activeScene, window);
            activeScene->internalEmitter_.emit("postRender", std::ref(window));
            activeScene->getGui().draw();
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

        // Handle a camera's response to a window resize event
        static auto updateCameraScale = [](Camera* camera, unsigned int windowWidth, unsigned int windowHeight) {
            Camera::OnWinResize response = camera->getWindowResizeResponse();

            if (response == Camera::OnWinResize::Letterbox) {
                const sf::View& view = std::any_cast<std::reference_wrapper<const sf::View>>(camera->getInternalView()).get();
                camera->setInternalView(std::any{utility::letterbox(view, windowWidth, windowHeight)});
            } else if (response == Camera::OnWinResize::MaintainSize)
                camera->setInternalView(std::any{sf::View(sf::FloatRect(0, 0, static_cast<float>(windowWidth), static_cast<float>(windowHeight)))});
        };

        // Update all system components of a scene
        static auto updateSystem = [](Scene* scene, Event e) {
            if (e.type == Event::Resized) {
                scene->getCameras().forEach([&e](Camera* camera) {
                    updateCameraScale(camera, e.size.width, e.size.height);
                });

                updateCameraScale(&scene->getCamera(), e.size.width, e.size.height);
            }

            // Absorb key event if Keyboard is disabled
            if (!scene->inputManager_.isInputEnabled(input::InputType::Keyboard) &&
                (e.type == Event::KeyPressed || e.type == Event::KeyReleased))
            {
                return;
            }

            // Absorb mouse event if the Mouse is disabled
            if (!scene->inputManager_.isInputEnabled(input::InputType::Mouse) &&
                (e.type == Event::MouseButtonPressed || e.type == Event::MouseButtonReleased
                || e.type == Event::MouseMoved || e.type == Event::MouseWheelScrolled))
            {
                return;
            }

            // Absorb joystick event if Joystick is disabled
            if (!scene->inputManager_.isInputEnabled(input::InputType::Joystick) &&
                (e.type == Event::JoystickButtonPressed || e.type == Event::JoystickButtonReleased ||
                e.type == Event::JoystickMoved || e.type == Event::JoystickConnected ||
                e.type == Event::JoystickDisconnected))
            {
                return;
            }

            scene->inputManager_.handleEvent(e);
            scene->guiContainer_.handleEvent(e);
            scene->gridMovers_.handleEvent(e);
            scene->onHandleEvent(e);
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

    void SceneManager::forEachScene(const Callback<const Scene::Ptr&>& callback) {
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
            scene->audioManager_.removePlayedAudio();
            scene->internalEmitter_.emit("preUpdate", dt * scene->getTimescale());
        };

        update(scenes_.top().get(), deltaTime);

        if (prevScene_ && prevScene_->isEntered() && prevScene_->isTimeUpdatedWhenPaused_)
            update(prevScene_, deltaTime);
    }

    void SceneManager::updateScene(const Time& deltaTime, Scene* scene, bool fixedUpdate) {
        if (!(!scenes_.empty() && scenes_.top()->isEntered()))
            return;

        if (!fixedUpdate) {
            scene->timerManager_.update(deltaTime * scene->getTimescale());
            scene->guiContainer_.update(deltaTime);
        }

        updatePhysicsWorld(scene, deltaTime, fixedUpdate);
        updateExternalScene(scene, deltaTime, fixedUpdate);
    }

    void SceneManager::updatePhysicsWorld(Scene *scene, const Time &deltaTime, bool fixedUpdate) {
        if (scene->hasPhysicsSim_) {
            scene->internalEmitter_.emit("preStep", deltaTime * scene->getTimescale());

            /// This function is called by the engine for both fixed and normal
            /// update. The only way to know which is which is via @fixedUpdate
            /// flag (explains, this explains why the bodies of the if-else
            /// statement below are the same
            if (fixedUpdate && scene->world_->isFixedStep()) {
                scene->world_->update(deltaTime * scene->getTimescale());
            } else if (!fixedUpdate && !scene->world_->isFixedStep())
                scene->world_->update(deltaTime * scene->getTimescale());

            scene->internalEmitter_.emit("postStep", deltaTime * scene->getTimescale());
        }
    }

    void SceneManager::updateExternalScene(Scene* scene, const Time& deltaTime, bool fixedUpdate) {
        if (fixedUpdate) {
            scene->getGridMovers().update(deltaTime * scene->getTimescale());
            scene->onFixedUpdate(deltaTime * scene->getTimescale());
        } else {
            if (scene->hasTilemap_)
                scene->tileMap_->update(deltaTime * scene->getTimescale());

            scene->getGameObjects().forEach([&scene, &deltaTime](GameObject* gameObject) {
                if (gameObject->isActive()) {
                    gameObject->getSprite().updateAnimation(deltaTime * scene->getTimescale());
                    gameObject->update(deltaTime * scene->getTimescale());
                }
            });

            // Update sprite animations
            scene->getSprites().forEach([&scene, &deltaTime](Sprite* sprite) {
                sprite->updateAnimation(deltaTime * scene->getTimescale());
            });

            // Update user scene after all internal updates
            scene->onUpdate(deltaTime * scene->getTimescale());

            // Emit internal post update
            scene->internalEmitter_.emit("postUpdate", deltaTime * scene->getTimescale());

            // Normal update is always called after fixed update: fixedUpdate -> update -> postUpdate
            scene->onPostUpdate(deltaTime * scene->getTimescale());
        }
    }

    SceneManager::~SceneManager() {
        prevScene_ = nullptr;
    }
}
