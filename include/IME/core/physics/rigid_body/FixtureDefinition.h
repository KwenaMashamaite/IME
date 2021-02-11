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

#ifndef IME_FIXTUREDEFINITION_H
#define IME_FIXTUREDEFINITION_H

#include "IME/Config.h"
#include "IME/common/PropertyContainer.h"
#include "IME/core/physics/rigid_body/colliders/Collider.h"
#include <stdint.h>

namespace ime {
    /**
     * @brief Holds collision filtering data for a fixture
     *
     * Collision filtering allows you to prevent collisions between fixtures.
     * Collision filtering is achieved through categories and groups. For each
     * fixture you can specify which category it belongs to. You also specify
     * what other categories this fixture can collide with. For example, you
     * could specify in a multiplayer game that all players don't collide with
     * each other and monsters don't collide with each other, but players and
     * monsters should collide. This is done with masking bits. Note that there
     * are 16 collision categories and group filtering has higher precedence
     * than category filtering.
     *
     * Additional collision filtering occurs implicitly:
     *
     * 1. A fixture on a static body can only collide with a dynamic body.
     * 2. A fixture on a kinematic body can only collide with a dynamic body.
     * 3. Fixtures on the same body never collide with each other.
     * 4. You can optionally enable/disable collision between fixtures on
     *    bodies connected by a joint.
     */
    struct IME_API CollisionFilterData {
        using UInt16 = std::uint16_t; //!< unsigned short
        using Int16 = std::int16_t;   //!< singed short

        /**
         * @brief Constrictor
         */
        CollisionFilterData();

        ////////////////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////////////////

        /**
         * Specifies the categories the rigid body defined by this filter
         * data belongs to. The default value is 0x0001
         */
        UInt16 categoryBitMask;

        /**
         * Defines which categories of rigid bodies can collide with
         * the rigid body defined by this filter data. The default
         * value is 0xFFFF, a value of 0 disables all collisions
         */
        UInt16 collisionBitMask;

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
     * @brief Define the properties of a fixture
     *
     * A fixture definition is used to create a Fixture
     */
    struct IME_API FixtureDefinition {
        /**
         * @brief Set the default values
         */
        FixtureDefinition();

        /**
         * @brief Destructor
         */
        ~FixtureDefinition();

        ////////////////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////////////////

        const Collider* collider;       //!< The collider to be attached to a rigid body
        float friction;                 //!< The friction coefficient, usually in the range [0,1].
        float restitution;              //!< The restitution (elasticity) in the range [0,1].
        float density;                  //!< The density of the fixture in in kg/m^2
        bool isSensor;                  //!< A flag indicating whether o not the fixture is a sensor
        float restitutionThreshold;     //!< Restitution velocity threshold in in m/s
        PropertyContainer userData;     //!< May be used to store application specific fixture data
        CollisionFilterData filterData; //!< Collision filtering data
    };
}

#endif //IME_FIXTUREDEFINITION_H
