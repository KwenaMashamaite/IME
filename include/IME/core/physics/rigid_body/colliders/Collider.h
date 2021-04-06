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

#ifndef IME_COLLIDER_H
#define IME_COLLIDER_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/common/PropertyContainer.h"
#include "IME/common/Object.h"
#include <memory>

class b2Shape;
class b2Fixture;

namespace ime {
    class Body;

    /**
     * @brief Holds collision filtering data for a collider
     *
     * Collision filtering allows you to disable or enable collisions
     * between colliders. Collision filtering is achieved through
     * categories and groups. For each collider you can specify which
     * category it belongs to. You also specify what other categories
     * this collider can collide with. For example, you could specify
     * in a multiplayer game that all players don't collide with each
     * other and monsters don't collide with each other, but players
     * and monsters should collide. This is done with masking bits.
     * Note that there are 16 collision categories and group filtering
     * has higher precedence than category filtering.
     *
     * Additional collision filtering occurs implicitly:
     *
     * 1. A collider on a static body can only collide with a dynamic body.
     * 2. A collider on a kinematic body can only collide with a dynamic body.
     * 3. Colliders on the same body never collide with each other.
     * 4. You can optionally enable/disable collision between colliders on
     *    bodies connected by a joint.
     */
    struct IME_API CollisionFilterData {
        /**
         * @brief Constrictor
         */
        CollisionFilterData() :
            categoryBitMask{0x0001},
            collisionBitMask{0xFFFF},
            groupIndex{0}
        {}

        ////////////////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////////////////

        /**
         * Specifies the categories the rigid body defined by this filter
         * data belongs to. The default value is 0x0001
         */
        Uint16 categoryBitMask;

        /**
         * Defines which categories of rigid bodies can collide with
         * the rigid body defined by this filter data. The default
         * value is 0xFFFF, a value of 0 disables all collisions
         */
        Uint16 collisionBitMask;

        /**
         * Collision group index
         *
         * Collision groups allow some a certain group of bodies to never
         * collide or always collide. A value of zero (default) means no
         * collision group, a negative value means the group never collides
         * and a positive value means the group always collide. Note that
         * non-zero group filtering always wins against the mask bits
         */
        Int16 groupIndex;
    };

    /**
     * @brief Abstract Base class for colliders
     *
     * A collider enables collisions between rigid bodies/game objects.
     * It defines the shape of a rigid body/game object for the purpose
     * of physical collisions. Usually a collider is attached to a rigid
     * Body which is then attached to a GameObject. A game object that has
     * a rigid body attached to it which does not have a collider will be
     * affected by physics (impulses, gravity, friction etc), but the game
     * object cannot react/respond to collisions.
     *
     * Colliders are invisible however they may be drawn on the render
     * window during debug mode by enabling debug drawing of the physics
     * World.
     *
     * Rigid bodies enable physics while colliders enable collisions
     */
    class IME_API Collider : public Object {
    public:
        using Ptr = std::shared_ptr<Collider>; //!< Shared collider pointer
        using BodyPtr = std::shared_ptr<Body>; //!< Shared Body pointer

        /**
         * @brief The type of the collider
         */
        enum class Type {
            Circle,  //!< Circle collider
            Box,     //!< Box collider
            Polygon, //!< Polygon collider
            Edge     //!< Edge collider
        };

        /**
         * @brief Construct a collider
         * @param type Type of the collider
         *
         * @warning The collider must be attached to a rigid body before
         * any of its functions are are called. Calling a member function
         * without a rigid body is undefined behavior
         */
        explicit Collider(Type type);

        /**
         * @brief Move constructor
         */
        Collider(Collider&&) noexcept;

        /**
         * @brief Move assignment operator
         */
        Collider& operator=(Collider&&) noexcept;

        /**
         * @brief Create a copy of the collider
         * @return A copy of the collider
         *
         * @warning The collider must be attached to a rigid body before
         * any of its functions are are called. Calling a member function
         * before attaching the collider to a rigid body is undefined behavior
         */
        virtual Collider::Ptr clone() const = 0;

        /**
         * @brief Get the name of this class
         * @return The name of this class
         *
         * Note that this function is only implemented by child classes
         * of Object which also serve as a base class for other classes
         *
         * @see Object::getClassType and Object::getClassName
         */
        std::string getClassType() const override;

        /**
         * @brief Get the type of the collider
         * @return The type of the collider
         */
        Type getType() const;

        /**
         * @brief Set the density of the collider
         * @param density The density to set
         *
         * The colliders density is used to compute the mass properties of
         * the rigid body. The density can be zero or positive. You should
         * use similar densities for all of your colliders. This will improve
         * stacking stability
         *
         * By default, the density is 1.0f
         */
        void setDensity(float density);

        /**
         * @brief Get the density of the collider
         * @return The density of the collider
         */
        float getDensity() const;

        /**
         * @brief Set the coefficient of friction
         * @param friction The coefficient to set
         *
         * Friction is used to make objects slide along each other realistically
         * The friction parameter is usually set between 0 and 1, but can be
         * any non-negative value. A friction value of 0 turns off friction
         * and a value of 1 makes the friction strong
         *
         * @note This will not change the coefficient of existing contacts
         *
         * By default, the friction is 0.2f
         */
        void setFriction(float friction);

        /**
         * @brief Get the coefficient of friction
         * @return The coefficient of friction
         */
        float getFriction() const;

        /**
         * @brief Set the coefficient of restitution
         * @param restitution The coefficient to set
         *
         * Restitution is used to make objects bounce. The restitution value
         * is usually set to be between 0 and 1. Consider dropping a ball on
         * a table. A value of zero means the ball won't bounce. This is
         * called an inelastic collision. A value of one means the ball's
         * velocity will be exactly reflected. This is called a perfectly
         * elastic collision
         *
         * @note This will not change the restitution of existing contacts
         *
         * By default, the restitution is 0.0f
         */
        void setRestitution(float restitution);

        /**
         * @brief Get the coefficient of restitution of the collider
         * @return The coefficient of restitution of the collider
         */
        float getRestitution() const;

        /**
         * @brief Set the restitution threshold of the collider
         * @param threshold The new restitution threshold
         *
         * @note This will not change the restitution threshold of existing
         * contacts
         *
         * By default, the restitution threshold is 1.0f
         */
        void setRestitutionThreshold(float threshold);

        /**
         * @brief Get the restitution velocity threshold of the collider
         * @return The restitution velocity
         */
        float getRestitutionThreshold() const;

        /**
         * @brief Set if the collider is a sensor or not
         * @param sensor True to set as sensor, otherwise false
         *
         * A sensor detects a collision but does not generate a collision
         * response. This is useful if you only want to know when two
         * colliders overlap. You can flag any collider as being a sensor.
         * Sensors may be attached to static, kinematic, or dynamic bodies. 
         * Remember that you may have multiple colliders per body and you 
         * can have any mix of sensors and non-sensor colliders. Also, sensors 
         * only form contacts when at least one body is dynamic, so you will 
         * not get a contact for kinematic versus kinematic, kinematic versus 
         * static, or static versus static
         *
         * By default, the collider is not a sensor
         */
        void setSensor(bool sensor);

        /**
         * @brief Check whether or not the collider is a sensor
         * @return True if the collider is a sensor, otherwise false
         */
        bool isSensor() const;

        /**
         * @brief Set the collision filter data of the collider
         * @param filterData The new collision filter data
         *
         * This function will not update contacts until the next time
	     * step when either parent body is active or awake
         *
         * By default, the collider does not belong to any collision group
         * and the rigid body the collider is attached to will collide with
         * any rigid body (that is also collidable) it comes into contact
         * with
         */
        void setCollisionFilter(const CollisionFilterData& filterData);

        /**
         * @brief Get the collision filter data for the collider
         * @return The collision filter data of the collider
         */
        const CollisionFilterData& getCollisionFilterData() const;

        /**
         * @brief Reset the collision filtering data to default
         *
         * By default, the collider does not belong to any collision group
         * and the rigid body the collider is attached to will collide with
         * any rigid body (that is also collidable) it comes into contact
         * with
         */
        void resetCollisionFilterData();

        /**
         * @brief Enable or disable the collider
         * @param enable True to enable or false to disable
         *
         * This function will only modify the collision bitmask and leave the
         * category bit and group index as is. When @a enable is set to
         * false, the collision bitmask will be set to 0 causing the collider
         * to not collide with any other collider and when @a enable is set
         * to true, the collision bitmask will be set to the value it was
         * before it was set to zero.
         *
         * This function is a just a shortcut for:
         *
         * @code
         * // When set this way, you will also have to save/remember the previous
         * // collision bitmask value if you wish to restore it and not set a new
         * // one
         * auto filterData = collider.getCollisionFilterData();
         * filterData.collisionBitMask = 0;
         * collider.setCollisionFilter(filterData);
         * @endcode
         *
         * By default, the collider is enabled
         *
         * @see setCollisionFilter
         */
        void setEnable(bool enable);

        /**
         * @brief Get the body the collider is attached to
         * @return The body this collider is attached to if any, otherwise a
         *         nullptr
         */
        BodyPtr getBody();
        const BodyPtr& getBody() const;

        /**
         * @brief Check if the collider contains a point or not
         * @param point The point to be checked in world coordinates
         * @return True if the collider contains the point, otherwise false
         */
        bool containsPoint(Vector2f point) const;

        /**
         * @brief Get the user data extracted from the collider definition
         * @return The user data
         */
        PropertyContainer& getUserData();

        /**
         * @brief Destructor
         */
        ~Collider() override = 0;

    protected:
        /**
         * @brief Copy constructor
         */
        Collider(const Collider&);

        /**
         * @brief Copy assignment operator
         */
        Collider& operator=(const Collider&);

        /**
         * @internal
         * @brief Get the internal collider
         * @return The internal collider
         *
         * @warning This function is intended for internal use and should
         * never be called outside of IME
         */
        virtual b2Shape& getInternalShape() = 0;
        virtual const b2Shape& getInternalShape() const = 0;

    private:
        /**
         * @brief Attach the collider ot a rigid body
         * @param body The rigid body to attach the collider to
         */
        void setBody(BodyPtr body);

        /**
         * @brief Update the colliders collision filter
         */
        void updateCollisionFilter();

    private:
        Type type_;                          //!< The type of the collider
        std::unique_ptr<b2Fixture> fixture_; //!< Internal collider
        BodyPtr body_;                       //!< The body this collider is attached to
        friend class Body;                   //!< Needs access to constructor
        PropertyContainer userData_;         //!< Application specific collider data
        CollisionFilterData filterData_;     //!< Stores the collision filter data for the collider
        std::uint16_t prevCollisionBitMask_; //!< Previous collision bitmask before setEnable(false)
    };
}

#endif //IME_COLLIDER_H
