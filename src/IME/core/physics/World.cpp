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
#include "IME/core/game_object/GameObject.h"
#include "IME/core/physics/rigid_body/joints/DistanceJoint.h"
#include "IME/graphics/DebugDrawer.h"
#include "IME/core/scene/Scene.h"
#include "IME/graphics/Window.h"
#include <box2d/b2_world.h>
#include <box2d/b2_contact.h>

namespace ime {
    namespace
    {
        /**
         * @brief Convert Box2d fixture to own collider
         * @param fixture Box2d fixture to be converted
         * @return Own collider
         */
        Collider* convertFixtureToCollider(b2Fixture* fixture) {
            // Every IME Collider object has an instance of a b2Fixture.
            // When the b2Fixture is instantiated, the Collider that contains
            // it is passed as user data to Box2d so that we can retrieve it later.
            return reinterpret_cast<Collider*>(fixture->GetUserData().pointer);
        }

        ////////////////////////////////////////////////////////////////////////
        // Own callback wrappers so that they can be sent to Box2d
        ////////////////////////////////////////////////////////////////////////

        /**
         * @brief World::AABBCallback wrapper
         */
        class B2QueryCallback : public b2QueryCallback {
        public:
            explicit B2QueryCallback(const World::AABBCallback* callback){
                IME_ASSERT(callback, "Cannot create b2Callback from a nullptr")
                callback_ = callback;
            }

            // Called by box2d when a fixture overlaps the query AABB
            bool ReportFixture(b2Fixture *b2_fixture) override {
                return (*callback_)(convertFixtureToCollider(b2_fixture));
            }

            ~B2QueryCallback() override {
                callback_ = nullptr;
            }

        private:
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
            explicit B2RayCastCallback(const World::RayCastCallback* callback) {
                IME_ASSERT(callback, "Cannot create b2Callback from a nullptr")
                callback_ = callback;
            }

            // Called by Box2d when a ray cast collides with a fixture
            float ReportFixture(b2Fixture *b2_fixture, const b2Vec2 &point,
                const b2Vec2 &normal, float fraction) override
            {
                using namespace utility;
                return (*callback_)(convertFixtureToCollider(b2_fixture),
                        {metresToPixels(point.x), metresToPixels(point.y)},
                        {metresToPixels(normal.x), metresToPixels(normal.y)},
                        fraction);
            }

            ~B2RayCastCallback() override {
                callback_ = nullptr;
            }

        private:
            const World::RayCastCallback* callback_; //!< Invoked for each fixture that collides with the ray
        };
    } // anonymous namespace

    /////////////////////////////////////////////////////////////////////////////
    // World class implementation
    ////////////////////////////////////////////////////////////////////////////

    // ContactListener wrapper
    class World::B2ContactListener : public b2ContactListener {
    public:
        explicit B2ContactListener(ContactListener& contactListener) :
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
        void PreSolve(b2Contact *contact, const b2Manifold*) override {
            emit("preSolve", contact);
        }

        // Called by box2d after collision resolution
        void PostSolve(b2Contact *contact, const b2ContactImpulse*) override {
            emit("postSolve", contact);
        }

    private:
        ContactListener& contactListener_;

        void emit(const std::string& event, b2Contact *contact) {
            auto* colliderA = convertFixtureToCollider(contact->GetFixtureA());
            auto* colliderB = convertFixtureToCollider(contact->GetFixtureB());

            //contactListener_.eventEmitter_.emit(event, colliderA, colliderB);

            auto gameObjectA = colliderA->getBody().getGameObject();
            auto gameObjectB = colliderB->getBody().getGameObject();

            if (gameObjectA && gameObjectB) {
                gameObjectA->emitCollisionEvent(event, gameObjectB);
                gameObjectB->emitCollisionEvent(event, gameObjectA);
            }

            colliderA = colliderB = nullptr;
        }
    };

    World::World(Scene& scene, Vector2f gravity) :
        scene_{scene},
        world_{std::make_unique<b2World>(b2Vec2{gravity.x, gravity.y})},
        fixedTimeStep_{true},
        isDebugDrawEnabled_{false},
        timescale_{1.0f}
    {
        b2ContactListener_ = std::make_unique<B2ContactListener>(contactListener_);
        world_->SetContactListener(b2ContactListener_.get());

#if defined(IME_DEBUG)
        using WindowRef = std::reference_wrapper<Window>;
        postRenderId_ = scene_.on_("postRender", ime::Callback<WindowRef>([this](WindowRef) {
            if (isDebugDrawEnabled_)
                debugDraw();
        }));

        scene_.onDestruction([this] {
            postRenderId_ = -1;
        });
#endif
    }

    World::Ptr World::create(Scene &scene, Vector2f gravity) {
        return World::Ptr(new World(scene, gravity));
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

    Body::Ptr World::createBody(Body::Type type) {
        if (world_->IsLocked()) {
            IME_PRINT_WARNING("Operation ignored: createBody() called inside a world callback")
            return nullptr;
        }

        return Body::Ptr(new Body(shared_from_this(), type));
    }

    void World::createBody(const GameObject::Ptr& gameObject, Body::Type type) {
        IME_ASSERT(gameObject, "Cannot attach a rigid body to a nullptr")
        auto rigidBody = createBody(type);
        rigidBody->setGameObject(gameObject);
        gameObject->attachRigidBody(std::move(rigidBody));
    }

    Joint::Ptr World::createJoint(const JointDefinition& definition) {
        if (world_->IsLocked()) {
            IME_PRINT_WARNING("Operation ignored: createJoint() called inside a world callback")
            return nullptr;
        }

        switch (definition.type) {
            case JointType::Distance:
                return Joint::Ptr(new DistanceJoint(static_cast<const DistanceJointDefinition&>(definition), shared_from_this()));
            default:
                return nullptr;
        }
    }

    void World::update(Time timeStep, unsigned int velocityIterations, unsigned int positionIterations) {
        world_->Step(timeStep.asSeconds() * timescale_, static_cast<int32>(velocityIterations), static_cast<int32>(positionIterations));
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

    std::size_t World::getBodyCount() const {
        return world_->GetBodyCount();
    }

    std::size_t World::getJointCount() const {
        return world_->GetJointCount();
    }


    bool World::isLocked() const {
        return world_->IsLocked();
    }

    void World::rayCast(const World::RayCastCallback &callback, Vector2f startPoint,
        Vector2f endPoint)
    {
        auto queryCallback = B2RayCastCallback(&callback);
        world_->RayCast(&queryCallback,
            {utility::pixelsToMetres(startPoint.x), utility::pixelsToMetres(startPoint.y)},
            {utility::pixelsToMetres(endPoint.x), utility::pixelsToMetres(endPoint.y)});
    }

    void World::queryAABB(const World::AABBCallback& callback, const AABB &aabb) {
        auto queryCallback = B2QueryCallback(&callback);
        world_->QueryAABB(&queryCallback, *(aabb.getInternalAABB()));
    }

    ContactListener &World::getContactListener() {
        return contactListener_;
    }

    Scene &World::getScene() {
        return scene_;
    }

    void World::enableDebugDraw(bool enable) {
#if defined(IME_DEBUG)
        isDebugDrawEnabled_ = enable;
#else
        IME_UNUSED(enable);
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
        IME_ASSERT(debugDrawer_, "Cannot debug draw without a debug drawer, call 'createDebugDrawer' function to instantiate one")

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

    void World::createDebugDrawer(Window &renderWindow) {
#if defined(IME_DEBUG)
        if (!debugDrawer_) {
            debugDrawer_ = std::make_unique<priv::DebugDrawer>(renderWindow);
            world_->SetDebugDraw(debugDrawer_.get());
        }
#else
        IME_UNUSED(renderWindow);
#endif
    }

    World::~World() {
        if (postRenderId_ != -1)
            scene_.unsubscribe_("postRender", postRenderId_);
    }
}
