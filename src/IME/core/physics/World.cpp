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
#include <box2d/b2_fixture.h>

namespace ime {
    namespace {
        /**
         * @brief World::AABBCallback wrapper
         */
        class B2QueryCallback : public b2QueryCallback {
        public:
            explicit B2QueryCallback(const World::AABBCallback* callback) {
                IME_ASSERT(callback, "Cannot create b2Callback from a nullptr");
                callback_ = callback;
            }

            // Called by box2d when a fixture overlaps the querry AABB
            bool ReportFixture(b2Fixture *b2_fixture) override {
                // The syntax below is little bit nasty, so here's an explanation to
                // narrow down whats happening:
                //
                // Every Fixture object object has an instance of b2Fixture.
                // When a b2Fixture is created, a pointer to the Fixture that
                // contains it is passed as user data so that we can retrieve it later.
                // We do this because the World::AABBCallback takes a shared pointer
                // to our Fixture (abstraction), so there must be a way to convert
                // from b2Fixture to our Fixture
                return (*callback_)(std::shared_ptr<Fixture>(reinterpret_cast<Fixture*>(b2_fixture->GetUserData().pointer)));
            }

            ~B2QueryCallback() {
                callback_ = nullptr;
            }

        private:
            const World::AABBCallback* callback_; //!< Invoked for every fixture that overlaps the query AABB
        };

        /**
         * @brief World::RayCastCallback wrapper
         */
        class B2RayCastCallback : public b2RayCastCallback {
        public:
            explicit B2RayCastCallback(const World::RayCastCallback* callback) {
                IME_ASSERT(callback, "Cannot create b2Callback from a nullptr");
                callback_ = callback;
            }

            // Called by box2d when a ray cast collides with a fixture
            float ReportFixture(b2Fixture *b2_fixture, const b2Vec2 &point,
                const b2Vec2 &normal, float fraction) override
            {
                using namespace utility;
                auto fixture = std::shared_ptr<Fixture>(reinterpret_cast<Fixture*>(b2_fixture->GetUserData().pointer));
                return (*callback_)(std::move(fixture), {metresToPixels(point.x), metresToPixels(point.y)},
                        {metresToPixels(normal.x), metresToPixels(normal.y)}, fraction);
            }

            ~B2RayCastCallback() {
                callback_ = nullptr;
            }

        private:
            const World::RayCastCallback* callback_; //!< Invoked for each fixture that collides with the ray
        };
    }

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

    Body::sharedPtr World::createBody(const BodyDefinition &definition) {
        auto body = Body::sharedPtr(new Body(definition, shared_from_this()));
        bodies_.push_back(body);
        return body;
    }

    void World::createBody(Entity::sharedPtr entity, const BodyDefinition &definition) {
        if (entity) {
            entity->attachBody(createBody(definition));
        }
    }

    void World::destroyBody(Body::sharedPtr body) {
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

    void World::autoClearForceBuffer(bool autoClear) {
        world_->SetAutoClearForces(autoClear);
    }

    bool World::isForceBufferAutoCleared() const {
        return world_->GetAutoClearForces();
    }

    void World::clearForces() {
        world_->ClearForces();
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

    void World::forEachBody(Callback<Body::sharedPtr&> callback) {
        std::for_each(bodies_.begin(), bodies_.end(), callback);
    }

    std::size_t World::getBodyCount() const {
        return world_->GetBodyCount();
    }

    bool World::isLocked() const {
        return world_->IsLocked();
    }

    void World::rayCast(const World::RayCastCallback &callback, Vector2f startPoint,
        Vector2f endPoint) const
    {
        auto queryCallback = B2RayCastCallback(&callback);
        world_->RayCast(&queryCallback,
            {utility::pixelsToMetres(startPoint.x), utility::pixelsToMetres(startPoint.y)},
            {utility::pixelsToMetres(endPoint.x), utility::pixelsToMetres(endPoint.y)});
    }

    void World::queryAABB(const World::AABBCallback& callback, const AABB &aabb) const {
        auto queryCallback = B2QueryCallback(&callback);
        world_->QueryAABB(&queryCallback, *(aabb.getInternalAABB()));
    }

    b2World *World::getInternalWorld() {
        return world_;
    }

    World::~World() {
        delete world_;
        world_ = nullptr;
    }
}
