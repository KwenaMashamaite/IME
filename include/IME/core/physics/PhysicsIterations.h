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

#ifndef IME_PHYSITERATIONS_H
#define IME_PHYSITERATIONS_H

#include "IME/Config.h"

namespace ime {
    /**
     * @brief Controls the reaction of ime::RigidBody objects when they collide
     *
     * When a collision is detected between two rigid bodies, a calculation
     * is performed to resolve the collision (push the two bodies such that
     * they no longer overlap). This calculation is performed by an iterative
     * solver. The solver determines if and how the velocity and position of
     * the two bodies should change. For example, when a ball hits a wall, it
     * should as expected, bounce of the wall. A single iteration per update
     * may not give accurate results as you may still see the ball overlap the
     * wall. The velocity and position iterations affect the accuracy of the
     * physics simulation.
     *
     * There is a trade-off between performance and accuracy when selecting
     * the iterations. Using fewer iterations increases performance but
     * accuracy suffers. Likewise, using more iterations decreases performance
     * but improves the quality the simulation simulation. You can play around
     * with different combinations and observe how your simulations improves
     * or degrades.
     *
     * @note Physics iterations are only valid for collision resolution between
     * ime::RigidBody objects with ime::Collider attached to them. If your game
     * does not make use of them, for example your only interested in grid-based
     * physics (see ime::GridMover), then these values should be set to zero
     */
    struct IME_API PhysIterations {
        unsigned int position; //!< Position iterations per time-step
        unsigned int velocity; //!< Velocity iterations per time-step
    };
}

#endif //IME_PHYSITERATIONS_H
