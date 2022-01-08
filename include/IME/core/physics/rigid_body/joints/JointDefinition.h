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

#ifndef IME_JOINTDEFINITION_H
#define IME_JOINTDEFINITION_H

#include "IME/Config.h"
#include "IME/common/PropertyContainer.h"
#include <memory>

namespace ime {
    class RigidBody;

    /**
     * @brief The types of joints
     */
    enum class JointType {
        Distance //!< Distance joint
    };

    /**
     * @brief Define the properties of a Joint
     *
     * A joint definition is used to create a Joint
     */
    struct IME_API JointDefinition {
        /**
         * @brief Constructor
         */
        JointDefinition();

        /**
         * @brief Destructor
         */
        ~JointDefinition();

        ////////////////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////////////////

        JointType type;              //!< The type of the joint defined by this definition (set automatically)
        RigidBody* bodyA;            //!< The first attached body
        RigidBody* bodyB;            //!< The second attached body
        bool areBodiesCollidable;    //!< A flag indicating whether or not the joined bodies can collide with each other
        PropertyContainer userData;  //!< May be used to store application specific Joint data
    };
}

#endif //IME_JOINTDEFINITION_H
