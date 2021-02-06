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

#include "IME/core/physics/World.h"
#include "IME/utility/Helpers.h"
#include "IME/core/entity/Entity.h"
#include <box2d/b2_world.h>

namespace ime {
    World::World(Scene& scene, Vector2f gravity) :
        scene_{scene},
        world_{new b2World(b2Vec2{gravity.x, gravity.y})},
        fixedTimeStep_{true},
        timescale_{1.0f}
    {}

    void World::setGravity(Vector2f gravity) {
        world_->SetGravity({gravity.x, gravity.y});
    }

    Vector2f World::getGravity() const {
        return {world_->GetGravity().x, world_->GetGravity().x};
    }

    void World::setTimescale(float timescale) {
        if (timescale < 0)
            timescale_ = 0.0f;
        else
            timescale_ = timescale;
    }

    float World::getTimescale() const {
        return timescale_;
    }

    void World::enableContinuousPhysics(bool enable) {
        world_->SetContinuousPhysics(enable);
    }

    bool World::isContinuousPhysicsEnabled() const {
        return world_->GetContinuousPhysics();
    }

    void World::setFixedStep(bool fixed) {
        fixedTimeStep_ = fixed;
    }

    bool World::isFixedStep() const {
        return fixedTimeStep_;
    }

    std::shared_ptr<Body> World::createBody(const BodyDefinition &definition) {
        auto body = std::shared_ptr<Body>(new Body(definition, this));
        bodies_.push_back(body);
        return body;
    }

    void World::createBody(std::shared_ptr<Entity> entity, const BodyDefinition &definition) {
        if (entity) {
            entity->attachBody(createBody(definition));
        }
    }

    void World::destroyBody(std::shared_ptr<Body> body) {
        if (world_ && !world_->IsLocked()) {
            if (auto [found, index] = utility::findIn(bodies_, body); found) {
                world_->DestroyBody(bodies_[index]->body_);
                bodies_.erase(bodies_.begin() + index);
            }
        }
    }

    void World::destroyAllBodies() {
        // Destroy all bodies in box2D first
        std::for_each(bodies_.begin(), bodies_.end(), [this] (auto body) {
            world_->DestroyBody(body->body_);
        });

        bodies_.clear();
    }

    void World::update(Time timeStep, unsigned int velocityIterations, unsigned int positionIterations) {
        world_->Step(timeStep.asSeconds() * timescale_, velocityIterations, positionIterations);
    }

    void World::allowSleep(bool sleep) {
        world_->SetAllowSleeping(sleep);
    }

    bool World::isSleepingAllowed() const {
        return world_->GetAllowSleeping();
    }

    void World::enableSubStepping(bool subStep) {
        world_->SetSubStepping(subStep);
    }

    bool World::isSubSteppingEnabled() const {
        return world_->GetSubStepping();
    }

    void World::forEachBody(Callback<std::shared_ptr<Body> &> callback) {
        std::for_each(bodies_.begin(), bodies_.end(), callback);
    }

    std::size_t World::getBodyCount() const {
        return world_->GetBodyCount();
    }

    bool World::isLocked() const {
        return world_->IsLocked();
    }

    b2World *World::getInternalWorld() {
        return world_;
    }

    World::~World() {
        delete world_;
        world_ = nullptr;
    }
}
