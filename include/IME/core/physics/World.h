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
#include <memory>
#include <vector>

class b2World;

namespace ime {
    class Entity; //!< Entity class forward declaration

    /**
     * @brief The World is responsible for creating, managing, colliding and
     *        updating all of the bodies within it
     */
    class IME_API World {
    public:
        /**
         * @brief Construct the world object
         * @param scene The scene this world belongs to
         * @param gravity The acceleration of bodies due to gravity
         */
        World(Scene& scene, Vector2f gravity);

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
         * @return The created body or a nullptr if callbacks are being
         *         dispatched
         *
         * @warning This function is locked during callbacks
         */
        std::shared_ptr<Body> createBody(const BodyDefinition& definition);

        /**
         * @brief Create a body and attach it to an entity
         * @param entity The entity to attach the body to
         * @param definition The definition to construct the rigid body from
         */
        void createBody(std::shared_ptr<Entity> entity, const BodyDefinition& definition);

        /**
         * @brief Destroy a rigid body
         * @param body The rigid body to be destroyed
         *
         * This function destroys all associated shapes and joints
         *
         * @warning This function is locked during callbacks
         */
        void destroyBody(std::shared_ptr<Body> body);

        /**
         * @brief Destroy all the bodies in the world
         */
        void destroyAllBodies();

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
        void update(Time timeStep, unsigned int velocityIterations, unsigned int positionIterations);

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
        void forEachBody(Callback<std::shared_ptr<Body>&> callback);

        /**
         * @brief Get the number of bodies in the world
         * @return The number of bodies in th world
         */
        std::size_t getBodyCount() const;

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
        b2World* getInternalWorld();

        /**
         * @brief Destructor
         */
        ~World();

    private:
        Scene& scene_;                              //!< The scene this world belongs to
        b2World* world_;                            //!< The physics world simulation
        std::vector<std::shared_ptr<Body>> bodies_; //!< All bodies in this simulation
        bool fixedTimeStep_;                        //!< A flag indicating whether updates are fixed or variable
        float timescale_;                           //!< Controls the speed of the simulation without affecting the render fps
    };
}

#endif //IME_WORLD_H
