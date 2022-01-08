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

#ifndef IME_DEBUGDRAWERFILTER_H
#define IME_DEBUGDRAWERFILTER_H

#include "IME/Config.h"

namespace ime {
    /**
     * @brief Controls the filter flags of the debug drawer
     *
     * The flags determine what gets rendered by the debug drawer
     */
    struct IME_API DebugDrawerFilter {
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
}

#endif //IME_DEBUGDRAWERFILTER_H
