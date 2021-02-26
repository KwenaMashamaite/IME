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

#ifndef IME_WORLD_H
#define IME_WORLD_H

#include "IME/Config.h"
#include "IME/common/Vector2.h"
#include "IME/core/time/Time.h"
#include "IME/core/physics/rigid_body/Body.h"
#include "IME/core/physics/rigid_body/AABB.h"
#include "IME/core/physics/rigid_body/joints/Joint.h"
#include "IME/core/physics/ContactListener.h"
#include <unordered_map>
#include <memory>
#include <vector>

class b2World;

namespace ime {
    class GameObject; //!< GameObject class forward declaration
    class Window;     //!< Window class forward declaration

    namespace priv {
        class DebugDrawer;
    }

    /**
     * @brief The World is responsible for creating, managing, colliding and
     *        updating all of the bodies within it
     */
    class IME_API World : public std::enable_shared_from_this<World> {
    public:
        using Ptr = std::shared_ptr<World>;  //!< Shared World pointer
        using GameObjectPtr = std::shared_ptr<GameObject>; //!< Shared GameObject pointer

        /**
         * Callback function passed to queryAABB function
         *
         * The callback is called for every collider that overlaps the query
         * AABB. The callback must return false to terminate the query early
         * or true to continue with the query until all colliders have been
         * processed
         */
        using AABBCallback = std::function<bool(Collider::Ptr)>;

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
         * any shape, ray cast all shapes, or ray cast the closest shape.
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
        using RayCastCallback = std::function<float(Collider::Ptr,
            Vector2f, Vector2f, float)>;

        /**
         * @brief Controls the filter flags of the debug drawer
         *
         * The flags determine what gets rendered by the debug drawer
         */
        struct DebugDrawerFilter {
            /**
             * @brief Constructor
             */
            DebugDrawerFilter() :
                drawAABB{false},
                drawShapes{true},
                drawJoints{false},
                drawCentreOfMass{false}
            {}

            //////////////////////////////////////////////////////////////////////
            // Member data
            //////////////////////////////////////////////////////////////////////

            bool drawAABB;          //!< A flag indicating whether or not to draw rigid body AABB
            bool drawShapes;        //!< A flag indicating whether or not to draw rigid body shapes/colliders
            bool drawJoints;        //!< A flag indicating whether or not to draw joint
            bool drawCentreOfMass;  //!< A flag indicating whether or not to draw rigid body centre of mass
        };

        /**
         * @brief Create the physics simulation
         * @param scene The scene this world belongs to
         * @param gravity The acceleration of bodies due to gravity
         * @return The created physics world
         *
         * @note This class does not keep a reference to the created object
         */
        static World::Ptr create(Scene& scene, Vector2f gravity);

        /**
         * @brief Set the gravity of the world
         * @param gravity The new gravity
         */
        void setGravity(Vector2f gravity);

        /**
         * @brief Get the gravity of the world
         * @return The gravity of the world
         */
        Vector2f getGravity() const;

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
         */
        void enableContinuousPhysics(bool enable);

        /**
         * @brief Check whether continuous physics is enabled or not
         * @return True if enabled, otherwise false
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
         * @brief Create a rigid body from its definition
         * @param definition The body definition to construct a rigid body from
         * @return The created body or a nullptr if this function is called
         *         inside a world callback
         *
         * This
         * @a definition is left unspecified, th
         *
         * @warning This function is locked during callbacks. This usually
         * means you should not attempt to create a body inside a callback
         * dispatched by the world (Callbacks are dispatched during a step)
         */
        Body::Ptr createBody(const BodyDefinition& definition);

        /**
         * @brief Create a body and attach it to a game object
         * @param entity The entity to attach the body to
         * @param definition The definition to construct the rigid body from
         *
         * @note If the world is in the middle of a step, the body will not
         * be created. This usually means you should not attempt to create a
         * body inside a callback dispatched by the world (Callbacks are
         * dispatched during a step)
         */
        void createBody(GameObjectPtr gameObject, const BodyDefinition& definition);

        /**
         * @brief Get the body by its unique identifier
         * @param id The id of the body to retrieve
         * @return The body with the given id or a nullptr if there is no
         *         body with the given id in the world
         */
        Body::Ptr getBodyById(unsigned int id);

        /**
         * @brief Destroy a rigid body
         * @param body The rigid body to be destroyed
         * @return True if the body was destroyed or false if the world is
         *         in the middle of a step or the body does not exist
         *
         * This function destroys all associated shapes and joints
         *
         * @warning This function is locked during callbacks. This usually
         * means you should not attempt to destroy a joint inside a callback
         * dispatched by the world (Callbacks are dispatched during a step)
         *
         * @see createBody(const BodyDefinition&)
         */
        bool destroyBody(Body::Ptr body);

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
         * @brief Destroy a joint
         * @param joint Joint to be destroyed
         * @return True if the joint was destroyed or false if the joint
         *         does not exist or if this function is called inside a
         *         world callback
         *
         * @note If the joined bodies were set to not collide, they may start
         * colliding after the joint is destroyed
         *
         * @warning This function is locked during callbacks. This usually
         * means you should not attempt to destroy a joint inside a callback
         * dispatched by the world (Callbacks are dispatched during a step)
         *
         * @see createJoint
         */
        bool destroyJoint(Joint::Ptr joint);

        /**
         * @brief Destroy all the bodies in the world
         *
         * @warning This function is locked during callbacks. This usually
         * means you should not attempt to create a body inside a callback
         * dispatched by the world (Callbacks are dispatched during a step)
         */
        void destroyAllBodies();

        /**
         * @brief Destroy all the joints in the world
         *
         * @warning This function is locked during callbacks. This usually
         * means you should not attempt to create a joint inside a callback
         * dispatched by the world (Callbacks are dispatched during a step)
         */
        void destroyAllJoints();

        /**
         * @brief Update the physics world
         * @param timeStep The amount o time to simulate
         * @param velocityIterations Iteration for the velocity solver
         * @param positionIterations  Iteration for the constraint solver
         *
         * This function performs integration, collision detection and
         * constraint solution. The iteration count controls how many times
         * the constraint solver sweeps over all the contacts and joints in
         * the world. More iteration always yields  a better simulation. But
         * don't trade a small time step for a large iteration count. 60Hz and
         * 10 iterations is far better than 30Hz and 20 iterations.
         *
         * @note There is a trade-off between performance and accuracy when
         * selecting velocity and position iterations. Using fewer iterations
         * increases performance but accuracy suffers. Likewise, using more
         * iterations decreases performance but improves the quality of your
         * simulation. The recommended velocity and position iterations are 8
         * and 3 respectively. All iterations take place in a single step/update
         *
         * @note This function is called automatically by the scene and does
         * not need to be invoked directly
         */
        void update(Time timeStep, unsigned int velocityIterations,
            unsigned int positionIterations);

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
         * @brief Set whether or not the world sleeps
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
         * @brief Execute a callback for each body in the world
         * @param callback The function to be executed on each body
         *
         * The callback is passed a reference to a pointer to the body
         * on invocation
         */
        void forEachBody(Callback<Body::Ptr&> callback);

        /**
         * @brief Execute a callback for each joint in the world
         * @param callback The function to be executed on each joint
         *
         * The callback is passed a reference to a pointer to the joint
         * on invocation
         */
        void forEachJoint(Callback<Joint::Ptr&> callback);

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
         * @brief Get the contact listener
         * @return The contact listener
         */
        ContactListener& getContactListener();

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
         * of the rigid bodies, however you can use the getDebugDrawFilter
         * to control what gets rendered by the debug drawer.
         *
         * Debug drawing is useful in many different ways. For instance say
         * you have a rigid body attached to a game object and when the game
         * object collides with a wall, the game object sprite always enters
         * the wall by half of its size due to a origin mismatched between
         * the sprite and the rigid body. In this case enabling debug draw
         * and drawing the sprite will point out the problem immediately,
         * saving you a lot of debugging time.
         *
         * Be default, debug drawing is disabled
         *
         * @note Debug drawing is only available in project debug mode
         */
        void enableDebugDraw(bool enable);

        /**
         * @brief Check if debug draw is enabled or not
         * @return True if debug draw is enabled, otherwise false
         *
         * @see enableDebugDraw
         */
        bool isDebugDrawEnabled() const;

        /**
         * @brief Get the debug drawer filter data
         * @return A reference to the debug drawer filter data
         *
         * The returned data may be manipulated to set what is rendered by
         * the debug drawer
         *
         * @see enableDebugDraw
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
         * @brief Remove the body with a specific id
         * @param id The id of the body to remove
         * @return True if the body was removed, otherwise false
         *
         * @warning This function is intended for internal use and should
         * never be called outside of IME
         */
        bool removeBodyById(unsigned int id);

        /**
         * @internal
         * @brief Instantiate a debug drawer
         * @param renderWindow The render target for debug drawing
         *
         * Note that only one debug drawer can be instantiated
         *
         * @warning This function is intended for internal use and should
         * never be called outside of IME
         *
         * @see enableDebugDraw
         */
        void createDebugDrawer(Window& renderWindow);

        /**
         * @brief Destructor
         */
        ~World();

    private:
        /**
         * @brief Construct the world object
         * @param scene The scene this world belongs to
         * @param gravity The acceleration of bodies due to gravity
         */
        World(Scene& scene, Vector2f gravity);

        /**
         * @brief Draw physics entities
         *
         * @see enableDebugDraw
         */
        void debugDraw();

    private:
        Scene& scene_;                         //!< The scene this world belongs to
        std::unique_ptr<b2World> world_;       //!< The physics world simulation
        bool fixedTimeStep_;                   //!< A flag indicating whether updates are fixed or variable
        bool isDebugDrawEnabled_;              //!< A flag indicating whether or not debug drawing is enabled
        float timescale_;                      //!< Controls the speed of the simulation without affecting the render fps
        ContactListener contactListener_;      //!< Listens for contact between colliders and alerts interested parties
        DebugDrawerFilter debugDrawerFilter_;  //!< Control what gets renders by the debug drawer
        int postRenderId_;                     //!< Post render callback id

        std::unique_ptr<priv::DebugDrawer> debugDrawer_;   //!< Draws physics entities when debug draw is enabled
        std::unordered_map<int, Body::Ptr> bodies_;  //!< All bodies in this simulation
        std::unordered_map<int, Joint::Ptr> joints_; //!< All joints in this simulation

        class B2ContactListener;
        std::unique_ptr<B2ContactListener> b2ContactListener_;
    };
}

#endif //IME_WORLD_H
