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

#include "IME/core/scene/Scene.h"
#include "IME/core/loop/Engine.h"
#include "IME/core/physics/World.h"
#include "IME/core/entity/GameObject.h"

namespace ime {
    Scene::Scene(Engine &engine) :
        engine_{engine},
        cache_{engine.getPersistentData()},
        guiContainer_{engine.getRenderTarget()},
        timescale_{1.0f},
        isManaged_{false},
        isEntered_{false},
        isVisibleWhenPaused_{false},
        hasPhysicsSim_{false}
    {
        // "postStep" event is dispatched by the scene manager immediately after a physics step
        eventEmitter_.on("postStep", Callback<>([this] {
            shapeContainer_.forEach([](Shape::sharedPtr shape) {
                if (shape->hasRigidBody()) {
                    auto body = shape->getRigidBody();
                    shape->setPosition(body->getPosition());
                    shape->setRotation(body->getRotation());
                }
            });

            entityContainer_.forEach([](GameObject::sharedPtr gameObject) {
                auto body = gameObject->getRigidBody();
                gameObject->getTransform().setPosition(body->getPosition());
                gameObject->getTransform().setRotation(body->getRotation());
            });
        }));
    }

    void Scene::setName(const std::string &name) {
        name_ = name;
    }

    const std::string &Scene::getName() const {
        return name_;
    }

    void Scene::setVisibleOnPause(bool show) {
        isVisibleWhenPaused_ = show;
    }

    bool Scene::isVisibleOnPause() const {
        return isVisibleWhenPaused_;
    }

    bool Scene::isEntered() const {
        return isEntered_;
    }

    void Scene::setTimescale(float timescale) {
        if (timescale < 0)
            timescale_ = 0.0f;
        else
            timescale_ = timescale;
    }

    float Scene::getTimescale() const {
        return timescale_;
    }

    Engine &Scene::engine() const {
        return engine_;
    }

    World& Scene::physics() {
        return *world_;
    }

    input::InputManager &Scene::input() {
        return inputManager_;
    }

    audio::AudioManager &Scene::audio() {
        return audioManager_;
    }

    TimerManager &Scene::timer() {
        return timerManager_;
    }

    EventEmitter &Scene::eventEmitter() {
        return eventEmitter_;
    }

    EventDispatcher &Scene::globalEventEmitter() {
        return *EventDispatcher::instance();
    }

    PropertyContainer &Scene::cache() {
        return cache_;
    }

    ui::GuiContainer &Scene::gui() {
        return guiContainer_;
    }

    ShapeContainer &Scene::shapes() {
        return shapeContainer_;
    }

    EntityContainer &Scene::entities() {
        return entityContainer_;
    }

    void Scene::createWorld(Vector2f gravity) {
        world_ = World::create(*this, gravity);
        hasPhysicsSim_ = true;
    }
}