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

#ifndef IME_RENDERTARGET_H
#define IME_RENDERTARGET_H

#include "IME/utility/NonCopyable.h"
#include "IME/common/Vector2.h"
#include "IME/core/event/Event.h"
#include "IME/graphics/Drawable.h"
#include "IME/graphics/Colour.h"
#include "IME/graphics/WindowStyles.h"
#include <string>

namespace ime {
    namespace priv {
        class RenderTargetImpl;

        /**
         * @brief Window that can serve as a target for 2D drawing
         *
         * This class is an abstraction of ime::Window, which is externally
         * exposed through the public api. ime::RenderTarget encapsulates
         * third party functionality that is intended for internal only.
         * This way we avoid polluting ime::Window with functions that the
         * user is not supposed to call. Both ime::RenderTarget and ime::Window
         * operate on the same third party window instance
         */
        class RenderTarget : utility::NonCopyable {
        public:
            /**
             * @brief Constructor
             *
             * @warning Only a single instance of the class can exist at a time.
             * Attempting to instantiate the class while there is an active
             * instance will terminate the program
             */
            RenderTarget();

            /**
             * @brief Move constructor
             */
            RenderTarget(RenderTarget&&) = delete;

            /**
             * @brief Move assignment operator
             */
            RenderTarget& operator=(RenderTarget&&) = delete;

            /**
             * @brief Create a render window
             * @param title Title of the window
             * @param width Width of the window
             * @param height Height of the window
             * @param style Style of the window
             */
            void create(const std::string &title, unsigned int width,
                unsigned int height, Uint32 style = WindowStyle::Default);

            /**
             * @brief Change the window's icon
             * @param filename Filename of the window icon to set
             *
             * The OS default icon is used by default
             */
            void setIcon(const std::string& filename);

            /**
             * @brief Check if the event queue is empty or not.
             * @param event Event queue to be checked
             * @return true if event queue is not empty, false if it is empty
             *
             * @warning This function is intended for internal use only and should
             * never be called outside of IME
             */
            bool pollEvent(Event &event);

            /**
             * @brief Draw drawable on the window
             * @param drawable Object to be drawn
             */
            void draw(const Drawable& drawable);

            /**
             * @brief Display drawn objects on the window
             */
            void display();

            /**
             * @brief Clear the entire window with a single colour
             * @param colour Colour to clear window with
             */
            void clear(Colour colour = Colour::Black);

            /**
             * @brief Get the window implementation
             * @return The window implementation
             */
            const std::unique_ptr<priv::RenderTargetImpl>& getImpl() const;

            /**
             * @brief Destructor.
             *
             * Ensures a new Window instance can be created when an existing
             * Window instance is destroyed
             */
            ~RenderTarget();

        private:
            std::unique_ptr<priv::RenderTargetImpl> pImpl_;
        };
    }
}

#endif // IME_RENDERTARGET_H
