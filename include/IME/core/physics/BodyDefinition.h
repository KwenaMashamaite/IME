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

#ifndef IME_BODYDEFINITION_H
#define IME_BODYDEFINITION_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"

namespace ime {
    /**
    * @brief The rigid body type
    */
    enum class BodyType {
        Static = 0, //!< Zero mass, zero velocity, may be moved manually
        Kinematic,  //!< Zero mass, non-zero velocity set by user, moved by physics engine
        Dynamic     //!< Positive mass, non-zero velocity determined by forces, moved by physics engine
    };

    /**
     * @brief Defines the properties of a rigid body
     *
     * The body definition holds the data needed to create and initialize
     * a rigid Body.
     */
    struct IME_API BodyDefinition {
        /**
         * @brief Default constructor
         */
        BodyDefinition();

        ////////////////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////////////////

        BodyType bodyType;       //!< The type of the body
        Vector2f position;       //!< The world position of the body
        float angle;             //!< The world angle of the body in radians
        Vector2f linearVelocity; //!< The linear velocity of the body's origin in world coordinates
        float angularVelocity;   //!< The angular velocity of the body
        float linearDamping;     //!< Linear damping is use to reduce the linear velocity (Units are 1/time)
        float angularDamping;    //!< Angular damping is use to reduce the angular velocity (Units are 1/time)
        bool canSleep;           //!< A flag indicating whether or not this body can fall asleep
        bool isAwake;            //!< A flag indicating whether the body is initially awake or not
        bool isFixedRotation;    //!< A flag indicating whether or not the body should be able to rotate
        bool isFastBody;         //!< A flag indicating if this is a fast body or not (Used for tunneling prevention)
        bool isEnabled;          //!< A flag indicating whether or not the body is initially enabled or disabled
        float gravityScale;      //!< Gravity scale of this body (1 by default)
    };
}

#endif //IME_BODYDEFINITION_H
