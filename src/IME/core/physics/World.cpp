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
#include "../../utility/Helpers.h"
#include "IME/core/game_object/GameObject.h"
#include "IME/core/physics/rigid_body/joints/DistanceJoint.h"
#include "../../graphics/DebugDrawer.h"
#include "IME/core/scene/Scene.h"
#include "IME/graphics/Window.h"
#include <box2d/b2_world.h>
#include <box2d/b2_contact.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world_callbacks.h>

namespace ime {
    namespace
    {
        /**
         * @brief Convert Box2d fixture pointer to own fixture pointer
         * @param fixture Box2d fixture pointer to be converted
         * @return Own Fixture pointer
         */
        Fixture::sharedPtr getOwnFixture(b2Fixture* fixture, World& world) {
            // Every IME Fixture object has an instance of b2Fixture.
            // When the b2Fixture is instantiated, the id of Fixture that
            // contains it is passed as user data so that we can retrieve it later.
            return world.getBodyById(fixture->GetBody()->GetUserData().pointer)
                     ->getFixtureById(fixture->GetUserData().pointer);
        }

        ////////////////////////////////////////////////////////////////////////
        // Own callback wrappers so that they can be sent to Box2d
        ////////////////////////////////////////////////////////////////////////

        /**
         * @brief World::AABBCallback wrapper
         */
        class B2QueryCallback : public b2QueryCallback {
        public:
            B2QueryCallback(const World::AABBCallback* callback, World& world) :
                world_{world}
            {
                IME_ASSERT(callback, "Cannot create b2Callback from a nullptr");
                callback_ = callback;
            }

            // Called by box2d when a fixture overlaps the query AABB
            bool ReportFixture(b2Fixture *b2_fixture) override {
                return (*callback_)(getOwnFixture(b2_fixture, world_));
            }

            ~B2QueryCallback() {
                callback_ = nullptr;
            }

        private:
            World& world_;
            const World::AABBCallback* callback_; //!< Invoked for every fixture that overlaps the query AABB
        };

        ////////////////////////////////////////////////////////////////////////
        // RayCast callback wrapper
        ////////////////////////////////////////////////////////////////////////

        /**
         * @brief World::RayCastCallback wrapper
         */
        class B2RayCastCallback : public b2RayCastCallback {
        public:
            B2RayCastCallback(const World::RayCastCallback* callback, World& world) :
                world_{world}
            {
                IME_ASSERT(callback, "Cannot create b2Callback from a nullptr");
                callback_ = callback;
            }

            // Called by Box2d when a ray cast collides with a fixture
            float ReportFixture(b2Fixture *b2_fixture, const b2Vec2 &point,
                const b2Vec2 &normal, float fraction) override
            {
                using namespace utility;
                return (*callback_)(getOwnFixture(b2_fixture, world_),
                        {metresToPixels(point.x), metresToPixels(point.y)},
                        {metresToPixels(normal.x), metresToPixels(normal.y)},
                        fraction);
            }

            ~B2RayCastCallback() {
                callback_ = nullptr;
            }

        private:
            World& world_;
            const World::RayCastCallback* callback_; //!< Invoked for each fixture that collides with the ray
        };

    } // anonymous namespace

    /////////////////////////////////////////////////////////////////////////////
    // World class implementation
    ////////////////////////////////////////////////////////////////////////////

    // ContactListener wrapper
    class World::B2ContactListener : public b2ContactListener {
    public:
        explicit B2ContactListener(ContactListener& contactListener, World& world) :
            world_{world},
            contactListener_{contactListener}
        {}

        // Called by Box2d when two fixtures begin to overlap
        void BeginContact(b2Contact *contact) override {
            emit("contactBegin", contact);
        }

        // Called by Box2d when two fixtures stop overlapping
        void EndContact(b2Contact *contact) override {
            emit("contactEnd", contact);
        }

        // Called by Box2d after collision detection, but before collision resolution
        // may be called multiple times per time step per contact due to continuous collision detection
        void PreSolve(b2Contact *contact, __attribute__((unused)) const b2Manifold *oldManifold) override {
            emit("preSolve", contact);
        }

        // Called by box2d after collision resolution
        void PostSolve(b2Contact *contact, __attribute__((unused)) const b2ContactImpulse *impulse) override {
            emit("postSolve", contact);
        }

    private:
        World& world_;
        ContactListener& contactListener_;

        void emit(const std::string& event, b2Contact *contact) {
            contactListener_.eventEmitter_.emit(event,
                getOwnFixture(contact->GetFixtureA(), world_),
                getOwnFixture(contact->GetFixtureB(), world_));
        }
    };

    World::World(Scene& scene, Vector2f gravity) :
        scene_{scene},
        world_{std::make_unique<b2World>(b2Vec2{gravity.x, gravity.y})},
        fixedTimeStep_{true},
        isDebugDrawEnabled_{false},
        timescale_{1.0f}
    {
        b2ContactListener_ = std::make_unique<B2ContactListener>(contactListener_, *this);
        world_->SetContactListener(b2ContactListener_.get());

        using WindowRef = std::reference_wrapper<Window>;
        postRenderId_ = scene_.on_("postRender", ime::Callback<WindowRef>([this](WindowRef) {
            if (isDebugDrawEnabled_)
                debugDraw();
        }));
    }

    World::sharedPtr World::create(Scene &scene, Vector2f gravity) {
        return World::sharedPtr(new World(scene, gravity));
    }

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
        bodies_.insert({body->id_, body});
        return body;
    }

    void World::createBody(GameObject::sharedPtr gameObject, const BodyDefinition &definition) {
        if (gameObject) {
            gameObject->attachRigidBody(createBody(definition));
        }
    }

    Body::sharedPtr World::getBodyById(unsigned int id) {
        if (utility::findIn(bodies_, id))
            return bodies_.at(id);

        return nullptr;
    }

    bool World::destroyBody(Body::sharedPtr body) {
        if (!world_->IsLocked()) {
            if (utility::findIn(bodies_, body->getId())) {
                world_->DestroyBody(bodies_[body->getId()]->getInternalBody().get());
                bodies_.erase(body->getId());
                return true;
            }
        }

        return false;
    }

    Joint::sharedPtr World::createJoint(const JointDefinition& definition) {
        if (world_ && !world_->IsLocked()) {
            Joint::sharedPtr joint;
            switch (definition.type) {
                case JointType::Distance:
                    joint = Joint::sharedPtr(new DistanceJoint(static_cast<const DistanceJointDefinition&>(definition), shared_from_this()));
                    break;
                default:
                    return nullptr;
            }

            joints_.insert({joint->getId(), joint});
            return joint;
        }
        return nullptr;
    }

    bool World::destroyJoint(Joint::sharedPtr joint) {
        if (world_ && !world_->IsLocked()) {
            if (utility::findIn(joints_, joint->getId())) {
                world_->DestroyJoint(joints_[joint->getId()]->getInternalJoint());
                joints_.erase(joint->getId());
                return true;
            }
        }

        return false;
    }

    void World::destroyAllBodies() {
        // Destroy all bodies in box2D first
        std::for_each(bodies_.begin(), bodies_.end(), [this] (auto pair) {
            world_->DestroyBody(pair.second->getInternalBody().get());
        });

        bodies_.clear();
    }

    void World::destroyAllJoints() {
        // Destroy all joints in box2D first
        std::for_each(joints_.begin(), joints_.end(), [this] (auto pair) {
            world_->DestroyJoint(pair.second->getInternalJoint());
        });

        joints_.clear();
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
        std::for_each(bodies_.begin(), bodies_.end(), [&callback](auto pair) {
            callback(pair.second);
        });
    }

    void World::forEachJoint(Callback<Joint::sharedPtr &> callback) {
        std::for_each(joints_.begin(), joints_.end(), [&callback](auto pair) {
            callback(pair.second);
        });
    }

    std::size_t World::getBodyCount() const {
        return world_->GetBodyCount();
    }

    bool World::isLocked() const {
        return world_->IsLocked();
    }

    void World::rayCast(const World::RayCastCallback &callback, Vector2f startPoint,
        Vector2f endPoint)
    {
        auto queryCallback = B2RayCastCallback(&callback, *this);
        world_->RayCast(&queryCallback,
            {utility::pixelsToMetres(startPoint.x), utility::pixelsToMetres(startPoint.y)},
            {utility::pixelsToMetres(endPoint.x), utility::pixelsToMetres(endPoint.y)});
    }

    void World::queryAABB(const World::AABBCallback& callback, const AABB &aabb) {
        auto queryCallback = B2QueryCallback(&callback, *this);
        world_->QueryAABB(&queryCallback, *(aabb.getInternalAABB()));
    }

    ContactListener &World::getContactListener() {
        return contactListener_;
    }

    Scene &World::getScene() {
        return scene_;
    }

    void World::enableDebugDraw(bool enable) {
#if !defined(NDEBUG)
        isDebugDrawEnabled_ = enable;
#endif
    }

    bool World::isDebugDrawEnabled() const {
        return isDebugDrawEnabled_;
    }

    World::DebugDrawerFilter &World::getDebugDrawerFilter() {
        return debugDrawerFilter_;
    }

    const World::DebugDrawerFilter &World::getDebugDrawerFilter() const {
        return debugDrawerFilter_;
    }

    void World::debugDraw() {
        IME_ASSERT(debugDrawer_, "Cannot debug draw without a debug drawer, call 'createDebugDrawer' function to instantiate one");

        // Reset the flags in case of a change since last step
        uint32 flags = 0;
        flags += debugDrawerFilter_.drawShapes * b2Draw::e_shapeBit;
        flags += debugDrawerFilter_.drawJoints * b2Draw::e_jointBit;
        flags += debugDrawerFilter_.drawAABB * b2Draw::e_aabbBit;
        flags += debugDrawerFilter_.drawCentreOfMass * b2Draw::e_centerOfMassBit;
        debugDrawer_->SetFlags(flags);

        world_->DebugDraw();
    }

    std::unique_ptr<b2World>& World::getInternalWorld() {
        return world_;
    }

    bool World::removeBodyById(unsigned int id) {
        // This function  does not remove the internal body because
        // it is called by the custom deleter of the internal body
        return utility::eraseIn(bodies_, id);
    }

    void World::createDebugDrawer(Window &renderWindow) {
        if (!debugDrawer_) {
            debugDrawer_ = std::make_unique<priv::DebugDrawer>(renderWindow);
            world_->SetDebugDraw(debugDrawer_.get());
        }
    }

    World::~World() {
        scene_.unsubscribe_("postRender", postRenderId_);
    }
}
