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

#ifndef IME_PHYSICSWORLD_H
#define IME_PHYSICSWORLD_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/core/time/Time.h"
#include "IME/core/physics/rigid_body/RigidBody.h"
#include "IME/core/physics/rigid_body/AABB.h"
#include "IME/core/physics/DebugDrawerFilter.h"
#include "IME/core/physics/rigid_body/joints/Joint.h"
#include "IME/core/physics/PhysicsIterations.h"
#include <unordered_map>
#include <memory>
#include <vector>

class b2World;

namespace ime {

    /// @internal
    namespace priv {
        class DebugDrawer;
        class RenderTarget;
    }

    /**
     * Callback function passed to queryAABB function
     *
     * The callback is called for every collider that overlaps the query
     * AABB. The callback must return false to terminate the query early
     * or true to continue with the query until all colliders have been
     * processed
     */
    using AABBCallback = std::function<bool(Collider* const)>;

    /**
     *  Callback function passed to rayCast Function
     *
     *  The callback is called for every collider that the ray collides
     *  with. The callback controls how the ray proceeds by the value
     *  it returns:
     *
     *  i)  -1: Ignore the current collider and continue with the ray casting.
     *          The collider will be filtered. That is, the ray cast will
     *          proceed as if the collider does not exist
     *
     *  ii)  0: Terminate the ray cast immediately
     *
     *  iii) 1: Don't clip the ray and continue. By default the ray is
     *          clipped if it collides with a collider. When 1 is returned
     *          the ray will continue as if it did not hit anything
     *
     *  iv) fraction : The fraction is provided to the callback when it is
     *                 called. If it is returned, then the ray will be
     *                 clipped to the current point of intersection.
     *
     * The value returned by the callback function allow you to ray cast
     * any collider, ray cast all colliders, or ray cast the closest collider.
     *
     * The argument list of the callback is as follows:
     *
     * first arg:  The collider that is currently colliding with the ray
     * second arg: The point of initial intersection (There may be more
     *             than one intersection depending on the value returned
     *             by the callback)
     * third arg:  The normal vector (rotation) at the point of intersection
     * forth arg:  The distance from the rays starting point to the current
     *              point of intersection (fraction)
     */
    using RayCastCallback = std::function<float(Collider* const, Vector2f, Vector2f, float)>;

    /**
     * @brief The physics world is responsible for creating, managing, colliding
     *        and updating all of the bodies within it
     */
    class IME_API PhysicsWorld final {
    public:
        using Ptr = std::unique_ptr<PhysicsWorld>;  //!< Unique World pointer

        /**
         * @brief Copy constructor
         */
        PhysicsWorld(const PhysicsWorld&) = delete;

        /**
         * @brief Copy assignment operator
         */
        PhysicsWorld& operator=(const PhysicsWorld&) = delete;

        /**
         * @brief Create the physics simulation
         * @param scene The scene this world belongs to
         * @param gravity The acceleration of bodies due to gravity
         * @return The created physics world
         *
         * @note This class does not keep a reference to the created object
         */
        static PhysicsWorld::Ptr create(Scene& scene, const Vector2f& gravity);

        /**
         * @brief Change the gravity of the world
         * @param gravity The new gravity
         */
        void setGravity(const Vector2f& gravity);

        /**
         * @brief Get the gravity of the world
         * @return The gravity of the world
         */
        Vector2f getGravity() const;

        /**
         * @brief Set the iterations per time-step of the world
         * @param iterations New iterations to set
         *
         * By default, the position and velocity iterations are 3 and 8
         * respectively
         *
         * @see ime::PhysIterations
         */
        void setIterations(const PhysIterations& iterations);

        /**
         * @brief Get the physics iterations per time step of the world
         * @return The physics iterations
         *
         * @see setIterations
         */
        const PhysIterations& getIterations() const;

        /**
         * @brief Set the simulation timescale
         * @param timescale The new timescale
         *
         * The timescale can be used to speed up or slow down the simulation
         * without changing the FPS limit. Values above 1.0f speed up the
         * simulation whilst values below 1.0f slow it down  A timescale of
         * zero freezes the simulation (Dynamic bodies stop moving).
         *
         * By default the timescale is 1.0f (real-time)
         *
         * @note The simulation timescale will be multiplied by the timescale
         * of the scene this simulation belongs to. If the scenes timescale
         * is set to 2.0f and the simulation timescale is 2.0f, then the
         * simulation will run 4 times as fast
         */
        void setTimescale(float timescale);

        /**
         * @brief Get the timescale
         * @return The timescale
         *
         * @see setTimescale
         */
        float getTimescale() const;

        /**
         * @brief Enable or disable continuous physics
         * @param enable True to enable otherwise false
         *
         * By default the physics engine uses continues physics
         */
        void enableContinuousPhysics(bool enable);

        /**
         * @brief Check whether continuous physics is enabled or not
         * @return True if enabled, otherwise false
         *
         * @see enableContinuousPhysics
         */
        bool isContinuousPhysicsEnabled() const;

        /**
         * @brief Set whether or not the world is updated in fixed times steps
         * @param fixed True to update world in fixed time steps otherwise false
         *
         * When set to false, the physics update is synced with the render
         * fps which may vary from time to time. It is advised to use fixed
         * time steps for consistent physics
         *
         * By default, the world is updated using a fixed time step
         */
        void setFixedStep(bool fixed);

        /**
         * @brief Check if the world is updated in fixed or variable time steps
         * @return True if world is updated in fixed time steps otherwise false
         *
         * @see setFixedUpdate
         */
        bool isFixedStep() const;

        /**
         * @brief Create a rigid body
         * @param type The type of the body to be created
         * @return The created body or a nullptr if this function is called
         *         inside a world callback
         *
         * By default, this function creates a static body
         *
         * @warning This function is locked during callbacks. This usually
         * means you should not attempt to create a body inside a callback
         * dispatched by the world (Callbacks are dispatched during a step)
         */
        RigidBody::Ptr createBody(RigidBody::Type type = RigidBody::Type::Static);

        /**
         * @brief Create a joint
         * @param definition Definition to create a joint from
         * @return The created joint or a nullptr if this function is called
         *          inside a world callback
         *
         * @note If the joined bodies are set to not collide, they will stop
         * colliding after the joint is created
         *
         * @warning This function is locked during callbacks. This usually
         * means you should not attempt to create a joint inside a callback
         * dispatched by the world (Callbacks are dispatched during a step)
         */
        Joint::Ptr createJoint(const JointDefinition& definition);

        /**
         * @internal
         * @brief Update the physics world
         * @param deltaTime The time passed since last update
         *
         * This function performs integration, collision detection and
         * constraint solution
         *
         * @warning This function is intended for internal use only and should
         * never be called outside of IME
         */
        void update(Time deltaTime);

        /**
         * @brief Enable or disable automatic force buffer clearance after an
         *        update
         * @param autoClear True to enable or false to disable
         *
         * By default, the force buffer on all bodies is cleared after each
         * call to update. You can disable automatic force buffer clearance
         * if you want to use subStepping
         *
         * @see enableSubStepping and clearForces
         */
        void autoClearForceBuffer(bool autoClear);

        /**
         * @brief Check whether or not the force buffer on all bodies is
         *        cleared after each update
         * @return True if the force buffer is automatically cleared, otherwise
         *          false
         *
         * @see autoClearForceBuffer
         */
        bool isForceBufferAutoCleared() const;

        /**
         * @brief Manually clear the force buffer on all bodies
         *
         * By default, forces are cleared automatically after each update.
         * The default behavior is modified by calling autoClearForces. The
         * purpose of this function is to support sub-stepping. Sub-stepping
         * is often used to maintain a fixed sized time step under a variable
         * frame-rate. When you perform sub-stepping you will disable auto
         * clearing of forces and instead call clearForces after all sub-steps
         * are complete in one pass of your game loop.
         *
         * @see enableSubStepping and autoClearForceBuffer
         */
        void clearForces();

        /**
         * @brief Set whether or not the world isSleepingAllowed
         * @param sleep True to enable sleeping or false to disable
         */
        void allowSleep(bool sleep);

        /**
         * @brief Check if the world can sleep or not
         * @return True if the world can sleep, otherwise false
         */
        bool isSleepingAllowed() const;

        /**
         * @brief Enable or disable sub-stepping
         * @param subStep True to enable sub-stepping, otherwise false
         */
        void enableSubStepping(bool subStep);

        /**
         * @brief Check if sub-stepping is enabled or not
         * @return True if enabled, or false if disabled
         */
        bool isSubSteppingEnabled() const;

        /**
         * @brief Get the number of bodies in the world
         * @return The number of bodies in th world
         */
        std::size_t getBodyCount() const;

        /**
         * @brief Get the number of joints in the world
         * @return The number of joints in the world
         */
        std::size_t getJointCount() const;

        /**
         * @brief Check if the world is in the middle of a time step or not
         * @return True if the world is in the middle of a time step, otherwise
         *         false
         *
         * @note Some functions are locked while the world is in a time step.
         * This means that any request to execute them will be denied
         */
        bool isLocked() const;

        /**
         * @brief Ray-cast the world for all the colliders in the path of the ray
         * @param callback The function to be executed when the ray collides
         *                 with a collider
         * @param startPoint The starting point of the ray
         * @param endPoint The ending point of the ray
         *
         * You can use ray casts to do line-of-sight checks, fire guns, etc.
         * The callback will be called for every collider hit by the ray and
         * the value it returns determines how the ray proceeds. Returning a
         * value of zero indicates the ray cast should be terminated. A value
         * of one indicates the ray cast should continue as if no hit occurred.
         * A value of -1 filters the collider (The the ray cast will proceed as
         * if the collider does not exist). If you return the fraction from the
         * argument list, the ray will be clipped to the current intersection
         * point. So you can ray cast any shape, ray cast all shapes, or ray
         * cast the closest shape by returning the appropriate value.
         *
         * @warning Due to round-off errors, ray casts can sneak through small
         * cracks between polygons in your static environment. If this is not
         * acceptable in your game, trying slightly overlapping your polygons
         */
        void rayCast(const RayCastCallback& callback, Vector2f startPoint,
            Vector2f endPoint);

        /**
         * @brief Query the world for all colliders that overlap the given AABB
         * @param callback The function to be executed for every Collider that
         *        overlaps the given AABB
         * @param aabb The AABB to query
         *
         * The callback is executed for every collider that overlaps @a aabb.
         * The callback must, on every invocation return true to continue with
         * the query or false to terminate the query. When true is returned,
         * the query will continue until all overlapping colliders are
         * processed
         */
        void queryAABB(const AABBCallback& callback, const AABB& aabb);

        /**
         * @brief Get the scene the simulation belongs to
         * @return The scene this simulation belongs to
         */
        Scene& getScene();

        /**
         * @brief Enable or disable debug drawing
         * @param enable True to enable debug drawing or false to disable it
         *
         * Debug drawing allows you to see what the rigid bodies are doing and
         * where they are in the world. When enabled, the physics simulation
         * will render all the bodies it contains using geometric shapes such
         * as circles and rectangles (Depending on the type of colliders on
         * the bodies). By default, the simulation will only render the shapes
         * of the rigid bodies, however you can use the getDebugDrawerFilter()
         * function to control what gets rendered by the debug drawer.
         *
         * Debug drawing is useful in many different ways. For instance say
         * you have a rigid body attached to a game object and when the game
         * object collides with a wall, the game object sprite always enters
         * the wall by half of its size due to a origin mismatched between
         * the sprite and the rigid body. In this case enabling debug draw
         * will point out the problem immediately, saving you a lot of debugging
         * time.
         *
         * Be default, debug drawing is disabled
         *
         * @note Debug drawing is only available when IME is linked to
         * in debug mode, calling this function when IME is linked to in
         * release mode has no effect
         */
        void setDebugDrawEnable(bool enable);

        /**
         * @brief Check if debug draw is enabled or not
         * @return True if debug draw is enabled, otherwise false
         *
         * @see setDebugDrawEnable
         */
        bool isDebugDrawEnabled() const;

        /**
         * @brief Get the debug drawer filter data
         * @return A reference to the debug drawer filter data
         *
         * The returned data may be manipulated to set what is rendered by
         * the debug drawer
         *
         * @code
         * world.getDebugDrawerFilter().drawAABB = true; // Draw bounding boxes
         * @endcode
         *
         * @see setDebugDrawEnable
         */
        DebugDrawerFilter& getDebugDrawerFilter();
        const DebugDrawerFilter& getDebugDrawerFilter() const;

        /**
         * @internal
         * @brief Get the internal physics world
         * @return The internal physics world
         *
         * @warning The pointer will be deallocated when the world goes out
         * of scope.
         *
         * @warning This function is intended for internal use and should
         * never be called outside of IME
         */
        std::unique_ptr<b2World>& getInternalWorld();

        /**
         * @internal
         * @brief Instantiate a debug drawer
         * @param renderWindow The render target for debug drawing
         *
         * Note that only one debug drawer can be instantiated and it can
         * only be instantiated when IME is in debug mode
         *
         * @warning This function is intended for internal use and should
         * never be called outside of IME
         *
         * @see setDebugDrawEnable
         */
        void createDebugDrawer(priv::RenderTarget& renderWindow);

        /**
         * @brief Destructor
         */
        ~PhysicsWorld();

    private:
        /**
         * @brief Construct the world object
         * @param scene The scene this world belongs to
         * @param gravity The acceleration of bodies due to gravity
         */
        PhysicsWorld(Scene& scene, Vector2f gravity);

        /**
         * @brief Draw physics entities
         *
         * @see setDebugDrawEnable
         */
        void debugDraw();

    private:
        Scene& scene_;                         //!< The scene this world belongs to
        std::unique_ptr<b2World> world_;       //!< The physics world simulation
        bool fixedTimeStep_;                   //!< A flag indicating whether updates are fixed or variable
        bool isDebugDrawEnabled_;              //!< A flag indicating whether or not debug drawing is enabled
        float timescale_;                      //!< Controls the speed of the simulation without affecting the render fps
        DebugDrawerFilter debugDrawerFilter_;  //!< Control what gets renders by the debug drawer
        int postRenderId_;                     //!< Post render callback id
        PhysIterations iterations_;            //!< Physics iterations per time-step

        class B2ContactListener;
        std::unique_ptr<B2ContactListener> b2ContactListener_; //!< Listens for collider contacts and notifies interested parties
        std::unique_ptr<priv::DebugDrawer> debugDrawer_;       //!< Draws physics entities when debug draw is enabled
    };
}

#endif //IME_PHYSICSWORLD_H
