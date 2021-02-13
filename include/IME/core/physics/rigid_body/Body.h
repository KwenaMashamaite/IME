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

#ifndef IME_BODY_H
#define IME_BODY_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/common/Transform.h"
#include "IME/core/physics/rigid_body/BodyDefinition.h"
#include "IME/core/physics/rigid_body/FixtureDefinition.h"
#include "IME/core/physics/rigid_body/Fixture.h"
#include <memory>
#include <vector>
#include <functional>
#include <unordered_map>

class b2Body;

namespace ime {
    class World; //!< World class forward declaration
    class Scene; //!< Scene class forward declaration

    /**
     * @brief A rigid body
     *
     * Bodies have position and velocity. You can apply forces, torques, and
     * impulses to bodies. Bodies can be static, kinematic, or dynamic:
     *
     * 1. A static body does not move under simulation and behaves as if it
     *    has infinite mass.
     *
     * 2. A kinematic body moves under simulation according to its velocity.
     *    Kinematic bodies do not respond to forces
     *
     * 3. A dynamic body is fully simulated. They can be moved manually by the
     *    user, but normally they move according to forces
     *
     * A body is not constructed directly, use the World::createBody function
     * to construct a rigid body
     */
    class IME_API Body : public std::enable_shared_from_this<Body> {
    public:
        using sharedPtr = std::shared_ptr<Body>; //!< Shared Body pointer
        using WorldPtr = std::shared_ptr<World>; //!< Shared World pointer

        /**
         * @brief Create a fixture and attach it to this body
         * @param definition The fixture definition to contract fixture from
         * @return The created fixture or nullptr if the callbacks are being
         *         dispatched
         *
         * A body may have more than one fixture
         *
         * @note All fixtures attached to a body are destroyed when the body
         * is destroyed
         *
         * @warning This function is locked during world callbacks
         */
        Fixture::sharedPtr createFixture(const FixtureDefinition& definition);

        /**
         * @brief Create a fixture from a collider and attach it to this body
         * @param collider The collider to construct the fixture from
         * @param density The density of the collider (set zero for static bodies)
         * @return The created fixture or nullptr if the callbacks are being
         *         dispatched
         *
         * The body will be created from default FixtureDefinition properties.
         * The mass of the body is automatically updated
         *
         * @note This function does not keep a reference to the collider, it is
         * cloned
         *
         * @warning This function is locked during callbacks
         */
        Fixture::sharedPtr createFixture(Collider::sharedPtr collider, float density);

        /**
         * @brief Get a fixture by its id
         * @param id The unique identifier of the fixture
         * @return The fixture with the given id or a nullptr if the body
         *         does not have a fixture with the given id
         */
        Fixture::sharedPtr getFixtureById(unsigned int id);

        /**
         * @brief Destroy a fixture
         * @param fixture The fixture to be removed
         *
         * The mass of the body will be adjusted if the body is dynamic and the
         * fixture has a positive density.
         *
         * @note All fixtures attached to a body are destroyed when the body
         * is destroyed
         *
         * @warning This function is locked during world callbacks
         */
        void destroyFixture(Fixture::sharedPtr fixture);

        /**
         * @brief Set the position of the bodies origin and rotation
         * @param transform The transform to be set
         */
        void setTransform(const Transform& transform);

        /**
         * @brief Get the transform for the body's origin
         * @return The world transform of the body
         */
        Transform getTransform() const;

        /**
         * @brief Set the world position of the body's local origin
         * @param position The position to set
         */
        void setPosition(Vector2f position);

        /**
         * @brief Get the world position of the body's origin
         * @return The world position of the body's origin
         */
        Vector2f getPosition() const;

        /**
         * @brief Set the body's rotation about the world origin
         * @param angle The body's world rotation
         */
        void setRotation(float angle);

        /**
         * @brief Get the body's world rotation
         * @return The current world rotation of the body
         */
        float getRotation() const;

        /**
         * @brief Get the world position of the centre of mass
         * @return The world position centre position
         */
        Vector2f getWorldCenter() const;

        /**
         * @brief Get the local position of the centre of mass
         * @return The local position of the centre of mass
         */
        Vector2f getLocalCenter() const;

        /**
         * @brief Set the linear velocity of the centre of mass
         * @param velocity The new linear velocity of the centre of mass
         */
        void setLinearVelocity(Vector2f velocity);

        /**
         * @brief Get the linear velocity of the centre of mass
         * @return The linear velocity of the center of mass.
         */
        Vector2f getLinearVelocity() const;

        /**
         * @brief Set the angular velocity
         * @param omega The new angular velocity in radians/second
         */
        void setAngularVelocity(float omega);

        /**
         * @brief Get the angular velocity
         * @return The new angular velocity in radians/second
         */
        float getAngularVelocity() const;

        /**
         * @brief Apply a force at a world point
         * @param force The force to apply in Newtons (N)
         * @param point The point at which to apply the force
         * @param wake True to wake the body if sleeping, otherwise false
         *
         * If the force is not applied at the centre of mass, it will
         * generate a torque and affect the angular velocity. This
         * wakes up the body
         */
        void applyForce(Vector2f force, Vector2f point, bool wake = true);

        /**
         * @brief Apply a force to the centre of mass
         * @param force The force to be applied in Newton
         * @param wake True to wake up the body, otherwise false
         *
         * This function will force the body to wake up
         */
        void applyForceToCenter(Vector2f force, bool wake = true);

        /**
         * @brief Apply a torque
         * @param torque The torque to be applied about the z-axis in N-m
         * @param wake True to wake the body, otherwise false
         *
         * This function affects the angular velocity. This function
         * will wake the body if sleeping
         */
        void applyTorque(float torque, bool wake = true);

        /**
         * @brief Apply an impulse at a world point
         * @param impulse The impulse to be applied in N-s or kg-m/s
         * @param point The world position to apply the impulse
         * @param wake True to wake the body otherwise false
         *
         * This function will affect the velocity and the angular velocity if
         * the point of application is not at the centre of mass
         *
         * This function will force the body to wake if it is sleeping
         */
        void applyLinearImpulse(Vector2f impulse, Vector2f point, bool wake = true);

        /**
         * @brief Apply an impulse at the centre of mass
         * @param impulse The impulse to be applied in N-s or kg-m/s
         * @param wake True to wake the body otherwise false
         */
        void applyLinearImpulseToCenter(Vector2f impulse, bool wake);

        /**
         * @brief Apply an angular impulse
         * @param impulse The impulse to be applied in kg*m*m/s
         * @param wake True to wake the body, otherwise false
         */
        void applyAngularImpulse(float impulse, bool wake);

        /**
         * @brief Get the total mass of the body
         * @return The mass of the body in kilograms (Kg)
         */
        float getMass() const;

        /**
         * @brief Get the rotational inertia of the body about the local origin
         * @return The rotational inertia in kg-m^2
         */
        float getInertia() const;

        /**
         * @brief Get the local coordinate of a world coordinate
         * @param worldPoint The world coordinate to be converted to local
         * @return The given world coordinate relative to the body's origin
         */
        Vector2f getLocalPoint(Vector2f worldPoint) const;

        /**
         * @brief Get the world coordinate of a local coordinate
         * @param localPoint A point on the body measured relative to the
         *        body's origin
         * @return The given point in world coordinates
         */
        Vector2f getWorldPoint(Vector2f localPoint) const;

        /**
         * @brief Get the local rotation of a world rotation
         * @param worldVector The world rotation to get local rotation from
         * @return @a worldVector in local rotation
         */
        Vector2f getLocalRotation(Vector2f worldVector) const;

        /**
         * @brief Get the world rotation of a local rotation
         * @param localVector The local rotation to be converted to world rotation
         * @return The given local rotation in world rotation
         */
        Vector2f getWorldRotation(Vector2f localVector) const;

        /**
         * @brief Get the world velocity of a local point
         * @param localPoint Local point to get world velocity of
         * @return The world velocity of a point
         */
        Vector2f getLinearVelocityFromLocalPoint(Vector2f localPoint) const;

        /**
         * @brief Get the world linear velocity of a world point on the body
         * @param worldPoint The world point
         * @return The world velocity of a point
         */
        Vector2f getLinearVelocityFromWorldPoint(Vector2f worldPoint) const;

        /**
         * @brief Set the linear damping of the body
         * @param damping The new linear damping
         *
         * The linear damping is used to reduce the linear velocity. The
         * damping parameter can be larger than 1.0f but the damping effect
         * becomes sensitive to the time step when the damping parameter is
         * large. Units are 1/time
         */
        void setLinearDamping(float damping);

        /**
         * @brief Get the linear damping of the body
         * @return The linear damping of the body
         */
        float getLinearDamping() const;

        /**
         * @brief Set the angular damping
         * @param damping  The new angular damping
         *
         * The angular damping is used to reduce the angular velocity. The
         * damping parameter can be larger than 1.0f but the damping effect
         * becomes sensitive to the time step when the damping parameter is
         * large. Units are 1/time
         */
        void setAngularDamping(float damping);

        /**
         * @brief Get the angular damping of the body
         * @return The angular damping of the body
         */
        float getAngularDamping() const;

        /**
         * @brief Set the gravity scale of the body
         * @param scale The gravity scale
         */
        void setGravityScale(float scale);

        /**
         * @brief Get the gravity cale of the body
         * @return The gravity scale of the body
         */
        float getGravityScale() const;

        /**
         * @brief Set the type of this body
         * @param type The type of this body
         */
        void setType(BodyType type);

        /**
         * @brief Get the body type
         * @return The type of this body
         */
        BodyType getType() const;

        /**
         * @brief Set whether or not the body is fast moving
         * @param fast True to set as fast moving, otherwise false
         *
         * When set to true, the body is prevented from tunnelling through
         * other moving bodies (The body is treated like a bullet for
         * continuous collision detection). All bodies are prevented from
         * from tunneling through kinematic and static bodies. This option is
         * only considered for dynamic bodies
         *
         * @warning You should use this function sparingly since it increases
         * processing time
         */
        void setFastBody(bool fast);

        /**
         * @brief Check if the body is a fast moving body or not
         * @return True if body is a fast moving body, otherwise false
         *
         * @see setFastBody
         */
        bool isFastBody() const;

        /**
         * @brief Set whether or not this body sleeps
         * @param sleeps True to allow sleep or false to keep the body awake
         *         at all times
         *
         * @note Setting the body to never sleep increases CPU usage
         */
        void setSleeps(bool sleeps);

        /**
         * @brief Check if the body sleeps or not
         * @return True if the body sleeps or false if the body never sleeps
         *
         * @see setSleeps
         */
        bool sleeps() const;

        /**
         * @brief Awake the body or put it to sleep
         * @param awake True to awake the body or false to put it to sleep
         *
         * A sleeping body is not simulated. Note that if a body is awake and
         * collides with a sleeping body, then the sleeping body wakes up.
         * Bodies will also wake up if a joint or contact attached to them is
         * destroyed
         */
        void setAwake(bool awake);

        /**
         * @brief Check if the body is awake or sleeping
         * @return True if awake, otherwise false
         */
        bool isAwake() const;

        /**
         * @brief Enable or disable a body
         * @param enable True to enable or false to disable
         *
         * A disabled body is not simulated and cannot be collided with or
         * woken up. If you pass a flag of true, all fixtures will be added
         * to the broad-phase. If you pass a flag of false, all fixtures will
         * be removed from the broad-phase and all contacts will be destroyed.
         * Fixtures and joints are otherwise unaffected. You may continue to
         * create/destroy fixtures and joints on disabled bodies. Fixtures on
         * a disabled body are implicitly disabled and will not participate
         * in collisions, ray-casts, or queries. Joints connected to a disabled
         * body are implicitly disabled. A disabled body is still owned by a
         * world object and remains in the body list.
         *
         * @warning Enabling a disabled body is almost as expensive as creating
         * the body from scratch, so use this function sparingly
         */
        void setEnabled(bool enable);

        /**
         * @brief Check whether or not the body is enabled
         * @return True if enabled or false if disabled
         */
        bool isEnabled() const;

        /**
         * @brief Set whether or not this body can rotate
         * @param rotate True to allow rotations or false to disallow rotations
         */
        void setFixedRotation(bool rotate);

        /**
         * @brief Check if the body can rotate or not
         * @return True if the body cn rotate, otherwise false
         *
         * @see setFixedRotation
         */
        bool isFixedRotation() const;

        /**
         * @brief Get the world the body is in
         * @return The world the body belong sto
         */
        WorldPtr getWorld();
        const WorldPtr& getWorld() const;

        /**
         * @brief Get the user data extracted from the body definition
         * @return The user data
         */
        PropertyContainer& getUserData();

        /**
         * @brief Get the unique identifier of the body
         * @return The unique identifier of the body
         */
        unsigned int getId() const;

        /**
         * @brief Execute a function for each fixture on the body
         * @param callback The function to be executed
         *
         * The callback is passed a fixture on invocation
         */
        void forEachFixture(Callback<Fixture::sharedPtr> callback);

        /**
         * @internal
         * @brief Get the internal body
         * @return The internal body
         *
         * @warning This function is intended for internal use and should
         * never be called outside of IME
         */
        std::unique_ptr<b2Body, std::function<void(b2Body*)>>& getInternalBody();
        const std::unique_ptr<b2Body, std::function<void(b2Body*)>>& getInternalBody() const;

    private:
        /**
         * @brief Create a body
         * @param definition The definition of the body
         * @param world The world the body is in
         */
        Body(const BodyDefinition& definition, WorldPtr world);

    private:
        std::unique_ptr<b2Body, std::function<void(b2Body*)>> body_;  //!< Internal rigid body
        unsigned int id_;                           //!< The id of this body
        WorldPtr world_;                            //!< The world the body is in
        PropertyContainer userData_;                //!< Application specific body data
        friend class World;                         //!< Needs access to constructor

        std::unordered_map<int, Fixture::sharedPtr> fixtures_;  //!< Fixtures attached to this body
    };
}

#endif //IME_BODY_H
