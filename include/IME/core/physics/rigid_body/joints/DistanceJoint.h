//////////////////////////////////////////////////////////////////////////////////
//// IME - Infinite Motion Engine
////
//// Copyright (c) 2020-2021 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
////
//// Permission is hereby granted, free of charge, to any person obtaining a copy
//// of this software and associated documentation files (the "Software"), to deal
//// in the Software without restriction, including without limitation the rights
//// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//// copies of the Software, and to permit persons to whom the Software is
//// furnished to do so, subject to the following conditions:
////
//// The above copyright notice and this permission notice shall be included in all
//// copies or substantial portions of the Software.
////
//// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//// SOFTWARE.
//////////////////////////////////////////////////////////////////////////////////

#ifndef IME_DISTANCEJOINT_H
#define IME_DISTANCEJOINT_H

#include "IME/Config.h"
#include "IME/core/physics/rigid_body/joints/Joint.h"
#include "IME/core/physics//rigid_body/joints/JointDefinition.h"

class b2DistanceJoint;

namespace ime {
    class World;
    class Body;

    /**
     * @return Distance joint definition
     */
    struct IME_API DistanceJointDefinition : public JointDefinition {
        /**
         * @brief Constructor
         */
        DistanceJointDefinition();

        /**
         * @brief Joint the bodies and initialize the rest length
         * @param bodyA The first body
         * @param bodyB The second body
         * @param anchorA The attach point on body A in world coordinates
         * @param anchorB The attach point on body B in world coordinates
         *
         * The minimum and maximum lengths are set to the rest length
         */
        void join(Body* bodyA, Body* bodyB, Vector2f anchorA, Vector2f anchorB);

        ////////////////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////////////////

        Vector2f bodyALocalAnchorPoint; //!< The local anchor point relative to bodyA's origin
        Vector2f bodyBLocalAnchorPoint; //!< The local anchor point relative to bodyB's origin
        float length;                   //!< The rest length of this joint. Clamped to a stable minimum value
        float minLength;                //!< Minimum length. Clamped to a stable minimum value
        float maxLength;                //!< Maximum length. Must be greater than or equal to the minimum length
    };

    /**
     * @brief Constrains two points on two rigid bodies to remain at a fixed
     *        distance from each other
     *
     * When you specify a distance joint the two bodies should already be in
     * place. Then you specify the two anchor points in world coordinates.
     * The first anchor point is connected to body 1, and the second anchor
     * point is connected to body 2. These points imply the length of the
     * distance constraint
     */
    class IME_API DistanceJoint final : public Joint {
    public:
        using Ptr = std::unique_ptr<Joint>; //!< Unique joint pointer

        /**
         * @brief Get the name of this class
         * @return The name of this class
         */
        std::string getClassName() const override;

        /**
         * @brief Set the rest length
         * @param length The rest length to set
         * @return The clamped length
         */
        float setRestLength(float length);

        /**
         * @brief Get the rest length
         * @return The rest length
         */
        float getRestLength() const;

        /**
         * @brief Set the minimum length
         * @param minLength The new minimum length
         * @return The clamped length
         *
         * By default the minimum length is 0.0f
         */
        float setMinimumLength(float minLength);

        /**
         * @brief Get the minimum length
         * @return The minimum length
         *
         * By default, the maximum length is the maximum float value on
         * your computer (Very large number)
         */
        float getMinimumLength() const;

        /**
         * @brief Set the maximum length
         * @param maxLength The new maximum length
         * @return The clamped length
         */
        float setMaxLength(float maxLength);

        /**
         * @brief Get the maximum length
         * @return The maximum length
         *
         * By default the maximum length is
         */
        float getMaximumLength() const;

        /**
         * @brief Get the current length
         * @return The current length
         */
        float getCurrentLength() const;

        /**
         * @brief Get the anchor point on body A in local coordinates
         * @return The anchor point in local coordinates
         */
        Vector2f getBodyALocalAnchorPoint() const;

        /**
         * @brief Get the anchor point on body A in world coordinates
         * @return The anchor point in world coordinates
         */
        Vector2f getBodyAWorldAnchorPoint() const override;

        /**
         * @brief Get the anchor point on body B in local coordinates
         * @return The anchor point on body B in local coordinates
         */
        Vector2f getBodyBLocalAnchorPoint() const;

        /**
         * @brief Get the anchor point on body B in world coordinates
         * @return The anchor point on body B in world coordinates
         */
        Vector2f getBodyBWorldAnchorPoint() const override;

        /**
         * @brief Get the type of the joint
         * @return The type of the joint
         */
        JointType getType() const override;

        /**
         * @brief Get the first body attached to ths joint
         * @return The first body attached to this joint
         */
        Body* getBodyA() override;
        const Body* getBodyA() const override;

        /**
         * @brief Get the second body attached to ths joint
         * @return The second body attached to this joint
         */
        Body* getBodyB() override;
        const Body* getBodyB() const override;

        /**
         * @brief Get the reaction force on body B at the joint anchor
         * @param fpsLimit The games Frames Per Second limit
         * @return The reaction force on Body B at the joint anchor in
         *         Newtons (N)
         */
        Vector2f getReactionForce(float fpsLimit) const override;

        /**
         * @brief Get the reaction torque on body B
         * @param fpsLimit The games Frames Per Second limit
         * @return The reaction torque on body B in N*m
         */
        float getReactionTorque(float fpsLimit) const override;

        /**
         * @brief Get the application specific Joint data
         * @return Application specific joint data
         *
         * This data is extracted from the JointDefinition
         */
        PropertyContainer &getUserData() override;
        const PropertyContainer &getUserData() const override;

        /**
         * @brief Check if the joint bodies can collide with each other or not
         * @return True if the bodies can collide with each other, otherwise
         *         false
         */
        bool canBodiesCollide() const override;

        /**
         * @internal
         * @brief Get the internal joint
         * @return The internal joint
         *
         * @warning This function is intended for internal use and should
         * never be called outside of IME
         */
        b2Joint *getInternalJoint() override;
        const b2Joint *getInternalJoint() const override;

        /**
         * @brief Destructor
         */
        ~DistanceJoint() override;

    private:
        /**
         * @brief Default constructor
         * @param definition The definition to construct the joint from
         * @param world The world to create this joint in
         *
         * Remember that the coordinates of the anchor points are in world
         * coordinates and not local coordinates, sometimes {0, 0} is
         * mistaken for the body origin when using this function
         * (use Body::getWorldCentre when not sure about the origin)
         */
        DistanceJoint(const DistanceJointDefinition& definition, World* world);

    private:
        std::unique_ptr<b2DistanceJoint> joint_;  //!< Internal joint
        PropertyContainer userData_;              //!< Application specific user date
        Body* bodyA_;                             //!< First attached body
        Body* bodyB_;                             //!< Second attached body
        friend class World;                       //!< Needs access to constructor
    };
}

#endif //IME_DISTANCEJOINT_H
