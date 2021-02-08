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

#ifndef IME_FIXTURE_H
#define IME_FIXTURE_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/core/physics/rigid_body/FixtureDefinition.h"
#include <memory>

class b2Fixture;

namespace ime {
    class Body;
    /**
     * @brief Attaches a body to a shape for collision detection
     *
     * Bodies and shapes have no knowledge of each other and a Shape may be
     * used independently of the physics simulation. A fixture acts like a
     * middle man between a body and a shape. It allows a shape to be attached
     * to a body. A Body may have zero or multiple fixtures (compound body)
     *
     * A Fixture cannot be instantiated directly, use the createFixture
     * function on a Body instance to construct a fixture object
     */
    class IME_API Fixture {
    public:
        /**
         * @brief Set if the fixture is a sensor or not
         * @param sensor True to set as sensor, otherwise false
         *
         * A sensor detects a collision but does not generate a collision
         * response. This is useful if you only want to know when two
         * fixtures overlap. You can flag any fixture as being a sensor.
         * Sensors may be static, kinematic, or dynamic. Remember that you
         * may have multiple fixtures per body and you can have any mix of
         * sensors and solid fixtures. Also, sensors only form contacts when
         * at least one body is dynamic, so you will not get a contact for
         * kinematic versus kinematic, kinematic versus static, or static
         * versus static.
         */
        void setSensor(bool sensor);

        /**
         * @brief Check whether or not the fixture is  a sensor
         * @return True if the fixture is a sensor, otherwise false
         */
        bool isSensor() const;

        /**
         * @brief Get the body the fixture is attached to
         * @return The body attached to this fixture if any, otherwise a nullptr
         */
        Body* getBody();
        const Body* getBody() const;

        /**
         * @brief Check if the fixture contains a point or not
         * @param point The point to be checked in world coordinates
         * @return True if the fixture contains the point, otherwise false
         */
        bool containsPoint(Vector2f point) const;

        /**
         * @brief Set the density of the fixture
         * @param density The density to set
         *
         * The fixture density is used to compute the mass properties of the
         * parent body. The density can be zero or positive. You should use
         * similar densities for all your fixtures. This will improve stacking
         * stability
         */
        void setDensity(float density);

        /**
         * @brief Get the density of the fixture
         * @return The density of the fixture
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
         */
        void setRestitution(float restitution);

        /**
         * @brief Get the coefficient of restitution
         * @return The coefficient of restitution
         */
        float getRestitution() const;

        /**
         * @brief Set the restitution threshold
         * @param threshold The new restitution threshold
         *
         * @note This will not change the restitution threshold of existing
         * contacts
         */
        void setRestitutionThreshold(float threshold);

        /**
         * @brief Get the restitution velocity threshold
         * @return The restitution velocity
         */
        float getRestitutionThreshold() const;

        /**
         * @brief Get the user data extracted from the fixture definition
         * @return The user data
         */
        PropertyContainer& getUserData();

        /**
         * @brief Destructor
         */
        ~Fixture();

    private:
        /**
         * @brief Construct a fixture
         * @param definition The definition to construct fixture from
         * @param body The body this fixture will be attached to
         */
        Fixture(const FixtureDefinition& definition, Body* body);

    private:
        b2Fixture* fixture_; //!< Internal fixture
        Body* body_;         //!< The body this fixture is attached to
        friend class Body;   //!< Needs access to constructor
        PropertyContainer userData_; //!< Application specific fixture data
    };
}

#endif //IME_FIXTURE_H
