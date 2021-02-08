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
#include "IME/core/physics/rigid_body/Shape.h"

namespace ime {
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

        ////////////////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////////////////

        const Shape* shape;         //!< The shape of the fixture
        float friction;             //!< The friction coefficient, usually in the range [0,1].
        float restitution;          //!< The restitution (elasticity) in the range [0,1].
        float density;              //!< The density of the fixture in in kg/m^2
        bool isSensor;              //!< A flag indicating whether o not the fixture is a sensor
        float restitutionThreshold; //!< Restitution velocity threshold in in m/s
        PropertyContainer userData; //!< May be used to store application specific fixture data
    };
}

#endif //IME_FIXTUREDEFINITION_H
