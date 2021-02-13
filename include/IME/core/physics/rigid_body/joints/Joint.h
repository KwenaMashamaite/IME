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

#ifndef IME_JOINT_H
#define IME_JOINT_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "JointDefinition.h"

class b2Joint;

namespace ime {
    /**
     * @brief Interface for Joint classes
     *
     * Joints are used to constrain rigid bodies to the world or to each other
     * e.g a pulley
     *
     * Note that joints are not constructed directly, use the createJoint
     * method on a World instance to create a joint
     */
    class IME_API Joint {
    public:
        using sharedPtr = std::shared_ptr<Joint>; //!< Shared joint pointer
        using BodyPtr = std::shared_ptr<Body>; //!< Shared body pointer

        /**
         * @brief Constructor
         */
        Joint() {
            auto static counter = 0u;
            id_ = counter++;
        }

        /**
         * @brief Get the type of the joint
         * @return The type of the joint
         */
        virtual JointType getType() const = 0;

        /**
         * @brief Get the first body attached to ths joint
         * @return The first body attached to this joint
         */
        virtual BodyPtr getBodyA() = 0;

        /**
         * @brief Get the second body attached to this joint
         * @return The second body attached to this joint
         */
        virtual BodyPtr getBodyB() = 0;

        /**
         * @brief Get the anchor point on body A in world coordinates
         * @return The anchor point in world coordinates
         */
        virtual Vector2f getBodyAWorldAnchorPoint() const = 0;

        /**
         * @brief Get the anchor point on body B in world coordinates
         * @return The anchor point on body B in world coordinates
         */
        virtual Vector2f getBodyBWorldAnchorPoint() const = 0;

        /**
         * @brief Get the reaction force on body B at the joint anchor
         * @param fpsLimit The games Frames Per Second limit
         * @return The reaction force on Body B at the joint anchor in
         *         Newtons (N)
         */
        virtual Vector2f getReactionForce(float fpsLimit) const = 0;

        /**
         * @brief Get the reaction torque on body B
         * @param fpsLimit The games Frames Per Second limit
         * @return The reaction torque on body B in N*m
         */
        virtual float getReactionTorque(float fpsLimit) const = 0;

        /**
         * @brief Get the application specific Joint data
         * @return Application specific joint data
         *
         * This data is extracted from the JointDefinition
         */
        virtual PropertyContainer& getUserData() = 0;
        virtual const PropertyContainer& getUserData() const = 0;

        /**
         * @brief Check if the joint bodies can collide with each other or not
         * @return True if the bodies can collide with each other, otherwise
         *         false
         */
        virtual bool canBodiesCollide() const = 0;

        /**
         * @internal
         * @brief Get the internal joint
         * @return The internal joint
         *
         * @warning This function is intended for internal use and should
         * never be called outside of IME
         */
        virtual b2Joint* getInternalJoint() = 0;
        virtual const b2Joint* getInternalJoint() const = 0;

        /**
         * @brief Get the unique identifier for this entity
         * @return The unique identifier
         */
        unsigned int getId() const {return id_;}

        /**
         * @brief Destructor
         */
        virtual ~Joint() = default;

    private:
        unsigned int id_; //!< unique identifier for this joint
    };
}

#endif //IME_JOINT_H
