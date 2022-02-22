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

#include "IME/core/physics/rigid_body/PhysicsEngine.h"
#include "IME/utility/Helpers.h"
#include "IME/core/physics/rigid_body/joints/DistanceJoint.h"
#include "IME/graphics/DebugDrawer.h"
#include "IME/core/scene/Scene.h"
#include "IME/graphics/RenderTarget.h"
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
         * @brief PhysicsEngine::AABBCallback wrapper
         */
        class B2QueryCallback : public b2QueryCallback {
        public:
            explicit B2QueryCallback(const AABBCallback* callback){
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
            const AABBCallback* callback_; //!< Invoked for every fixture that overlaps the query AABB
        };

        ////////////////////////////////////////////////////////////////////////
        // RayCast callback wrapper
        ////////////////////////////////////////////////////////////////////////

        /**
         * @brief PhysicsEngine::RayCastCallback wrapper
         */
        class B2RayCastCallback : public b2RayCastCallback {
        public:
            explicit B2RayCastCallback(const RayCastCallback* callback) {
                IME_ASSERT(callback, "Cannot create b2Callback from a nullptr")
                callback_ = callback;
            }

            // Called by Box2d when a ray cast collides with a fixture
            float ReportFixture(b2Fixture *b2_fixture, const b2Vec2 &point,
                const b2Vec2 &normal, float fraction) override
            {
                using namespace utility;
                return (*callback_)(convertFixtureToCollider(b2_fixture),
                        Vector2f{metresToPixels(point.x), metresToPixels(point.y)},
                        Vector2f{metresToPixels(normal.x), metresToPixels(normal.y)},
                        fraction);
            }

            ~B2RayCastCallback() override {
                callback_ = nullptr;
            }

        private:
            const RayCastCallback* callback_; //!< Invoked for each fixture that collides with the ray
        };
    } // anonymous namespace

    /////////////////////////////////////////////////////////////////////////////
    // PhysicsEngine class implementation
    ////////////////////////////////////////////////////////////////////////////

    // ContactListener wrapper
    class PhysicsEngine::B2ContactListener : public b2ContactListener {
    public:
        // Called by Box2d when two fixtures begin to overlap
        void BeginContact(b2Contact *contact) override {
            emit("contactBegin", contact);
        }

        // Called by Box2d when two fixtures stop overlapping
        void EndContact(b2Contact *contact) override {
            emit("contactEnd", contact);
        }

        // Called by Box2d after collision detection, but before collision
        // resolution. May be called multiple times per time step per contact
        // due to continuous collision detection. Note that the function is not
        // called if the body that the fixture is attached to is not awake
        // or when the body is awake but the fixture is a sensor
        void PreSolve(b2Contact *contact, const b2Manifold*) override {
            emit("contactStay", contact);
        }

    private:
        // Emit contact events
        static void emit(const std::string& event, b2Contact *contact) {
            auto colliderA = convertFixtureToCollider(contact->GetFixtureA());
            auto colliderB = convertFixtureToCollider(contact->GetFixtureB());

            colliderA->emitContact(event, colliderB);
            colliderB->emitContact(event, colliderA);
            colliderA = colliderB = nullptr;
        }
    };

    PhysicsEngine::PhysicsEngine(Scene& scene, Vector2f gravity) :
        scene_{scene},
        world_{std::make_unique<b2World>(b2Vec2{gravity.x, gravity.y})},
        fixedTimeStep_{true},
        isDebugDrawEnabled_{false},
        timescale_{1.0f},
        iterations_{3, 8}
    {
        b2ContactListener_ = std::make_unique<B2ContactListener>();
        world_->SetContactListener(b2ContactListener_.get());

#if defined(IME_DEBUG)
        using WindowRef = std::reference_wrapper<priv::RenderTarget>;
        postRenderId_ = scene_.on_("postRender", ime::Callback<WindowRef>([this](WindowRef) {
            if (isDebugDrawEnabled_)
                debugDraw();
        }));

        scene_.onDestruction([this] {
            postRenderId_ = -1;
        });
#endif
    }

    PhysicsEngine::Ptr PhysicsEngine::create(Scene &scene, const Vector2f& gravity) {
        return PhysicsEngine::Ptr(new PhysicsEngine(scene, gravity));
    }

    void PhysicsEngine::setGravity(const Vector2f& gravity) {
        world_->SetGravity(b2Vec2{gravity.x, gravity.y});
    }

    Vector2f PhysicsEngine::getGravity() const {
        return Vector2f{world_->GetGravity().x, world_->GetGravity().x};
    }

    void PhysicsEngine::setIterations(const PhysIterations &iterations) {
        iterations_ = iterations;
    }

    const PhysIterations &PhysicsEngine::getIterations() const {
        return iterations_;
    }

    void PhysicsEngine::setTimescale(float timescale) {
        if (timescale < 0)
            timescale_ = 0.0f;
        else
            timescale_ = timescale;
    }

    float PhysicsEngine::getTimescale() const {
        return timescale_;
    }

    void PhysicsEngine::setContinuousPhysicsEnable(bool enable) {
        world_->SetContinuousPhysics(enable);
    }

    bool PhysicsEngine::isContinuousPhysicsEnabled() const {
        return world_->GetContinuousPhysics();
    }

    void PhysicsEngine::setFixedStep(bool fixed) {
        fixedTimeStep_ = fixed;
    }

    bool PhysicsEngine::isFixedStep() const {
        return fixedTimeStep_;
    }

    RigidBody::Ptr PhysicsEngine::createBody(RigidBody::Type type) {
        if (world_->IsLocked()) {
            IME_PRINT_WARNING("Operation ignored: createBody() called inside a world callback")
            return nullptr;
        }

        return RigidBody::Ptr(new RigidBody(this, type));
    }

    Joint::Ptr PhysicsEngine::createJoint(const JointDefinition& definition) {
        if (world_->IsLocked()) {
            IME_PRINT_WARNING("Operation ignored: createJoint() called inside a world callback")
            return nullptr;
        }

        switch (definition.type) {
            case JointType::Distance:
                return Joint::Ptr(new DistanceJoint(static_cast<const DistanceJointDefinition&>(definition), this));
            default:
                return nullptr;
        }
    }

    void PhysicsEngine::update(Time deltaTime) {
        world_->Step(deltaTime.asSeconds() * timescale_, static_cast<int32>(iterations_.velocity), static_cast<int32>(iterations_.position));
    }

    void PhysicsEngine::setAutoClearForcesEnable(bool autoClear) {
        world_->SetAutoClearForces(autoClear);
    }

    bool PhysicsEngine::isAutoClearForcesEnabled() const {
        return world_->GetAutoClearForces();
    }

    void PhysicsEngine::clearForces() {
        world_->ClearForces();
    }

    void PhysicsEngine::setSleepEnable(bool sleep) {
        world_->SetAllowSleeping(sleep);
    }

    bool PhysicsEngine::isSleepEnabled() const {
        return world_->GetAllowSleeping();
    }

    void PhysicsEngine::setSubSteppingEnable(bool subStep) {
        world_->SetSubStepping(subStep);
    }

    bool PhysicsEngine::isSubSteppingEnabled() const {
        return world_->GetSubStepping();
    }

    std::size_t PhysicsEngine::getBodyCount() const {
        return world_->GetBodyCount();
    }

    std::size_t PhysicsEngine::getJointCount() const {
        return world_->GetJointCount();
    }


    bool PhysicsEngine::isLocked() const {
        return world_->IsLocked();
    }

    void PhysicsEngine::rayCast(const RayCastCallback &callback, Vector2f startPoint,
                                Vector2f endPoint)
    {
        auto queryCallback = B2RayCastCallback(&callback);
        world_->RayCast(&queryCallback,
            b2Vec2{utility::pixelsToMetres(startPoint.x), utility::pixelsToMetres(startPoint.y)},
            b2Vec2{utility::pixelsToMetres(endPoint.x), utility::pixelsToMetres(endPoint.y)});
    }

    void PhysicsEngine::queryAABB(const AABBCallback& callback, const AABB &aabb) {
        auto queryCallback = B2QueryCallback(&callback);
        world_->QueryAABB(&queryCallback, *(aabb.getInternalAABB()));
    }

    Scene &PhysicsEngine::getScene() {
        return scene_;
    }

    void PhysicsEngine::setDebugDrawEnable(bool enable) {
#if defined(IME_DEBUG)
        isDebugDrawEnabled_ = enable;
#else
        IME_UNUSED(enable);
#endif
    }

    bool PhysicsEngine::isDebugDrawEnabled() const {
        return isDebugDrawEnabled_;
    }

    DebugDrawerFilter &PhysicsEngine::getDebugDrawerFilter() {
        return debugDrawerFilter_;
    }

    const DebugDrawerFilter &PhysicsEngine::getDebugDrawerFilter() const {
        return debugDrawerFilter_;
    }

    void PhysicsEngine::debugDraw() {
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

    std::unique_ptr<b2World>& PhysicsEngine::getInternalWorld() {
        return world_;
    }

    void PhysicsEngine::createDebugDrawer(priv::RenderTarget &renderWindow) {
#if defined(IME_DEBUG)
        if (!debugDrawer_) {
            debugDrawer_ = std::make_unique<priv::DebugDrawer>(renderWindow);
            world_->SetDebugDraw(debugDrawer_.get());
        }
#else
        IME_UNUSED(renderWindow);
#endif
    }

    PhysicsEngine::~PhysicsEngine() {
#if defined(IME_DEBUG)
        if (postRenderId_ != -1)
            scene_.unsubscribe_("postRender", postRenderId_);
#endif
    }
}
