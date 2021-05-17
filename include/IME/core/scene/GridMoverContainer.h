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

#ifndef IME_GRIDMOVERCONTAINER_H
#define IME_GRIDMOVERCONTAINER_H

#include "IME/Config.h"
#include "IME/core/physics/tilemap/GridMover.h"
#include "IME/common/ObjectContainer.h"
#include "IME/core/event/Event.h"
#include "IME/core/time/Time.h"

namespace ime {
    
    /// @internal
    namespace priv {
        class Window;
    }

    /**
     * @brief A container for GridMover objects
     */
    class IME_API GridMoverContainer : public ObjectContainer<GridMover> {
    public:
        /**
         * @internal
         * @brief Update the grid movers
         * @param deltaTime Time passed since last update
         *
         * @warning This function is intended for internal use only and
         * should never be called outside of IME
         */
        void update(Time deltaTime);

        /**
         * @internal
         * @brief Handle a system event
         * @param event The system event to be handled
         *
         * @warning This function is intended for internal use only and
         * should never be called outside of IME
         */
        void handleEvent(Event event);

        /**
         * @internal
         * @brief Render the grid movers path
         * @param window Window to render path on
         *
         * @warning This function is intended for internal use only and
         * should never be called outside of IME
         */
        void render(priv::Window& window) const;
    };
}

#endif //IME_GRIDMOVERCONTAINER_H
