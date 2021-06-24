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

#include "IME/graphics/RenderTarget.h"
#include "IME/utility/Helpers.h"
#include "IME/core/resources/ResourceManager.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#ifndef IME_RENDERTARGETIMPL_H
#define IME_RENDERTARGETIMPL_H

namespace ime {
    namespace ui {
        class GuiContainer; //!< GuiContainer class forward declaration
    }

    namespace input {
        class Mouse;
    }

    namespace priv {
        /**
         * @brief Window class implementation
         */
        class RenderTargetImpl {
        public:
            /**
             * @brief Constructor
             *
             * @warning Only a single instance of the class can exist at a time.
             * Attempting to instantiate the class while there is an active
             * instance will terminate the program
             */
            RenderTargetImpl();

            /**
             * @brief Create a render window
             * @param title Title of the window
             * @param width Width of the window
             * @param height Height of the window
             * @param style Style of the window
             *
             * The dimensions of the window must be positive, otherwise
             * the program will be terminated prematurely
             */
            void create(const std::string &title, unsigned int width,
                unsigned int height, Uint32 style = WindowStyle::Default);

            /**
             * @brief Set the title of the window
             * @param title The new title of the window
             *
             * @see getTitle
             */
            void setTitle(const std::string& title);

            /**
             * @brief Get the title of the window
             * @return The title of the window
             *
             * @see setTitle
             */
            const std::string& getTitle() const;

            /**
             * @brief Change the window's icon
             * @param filename Filename of the window icon to set
             *
             * The OS default icon is used by default
             */
            void setIcon(const std::string &filename);

            /**
             * @brief Get the dimensions of the window
             * @return Dimensions of the window
             */
            Vector2u getSize();

            /**
             * @brief Check if the window is open or not
             * @return true if open, false if not open
             */
            bool isOpen() const;

            /**
             * @brief Check if the event queue is empty or not.
             * @param event Event queue to be checked
             * @return true if event queue is not empty, false if it is empty
             */
            bool pollEvent(Event &event);

            /**
             * @brief Close the window
             */
            void close();

            /**
             * @brief Draw drawable on the window
             * @param drawable Object to be drawn
             */
            void draw(const sf::Drawable &drawable);

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
             * @brief Get a reference to the SFML render window instance
             * @return A reference to the SFML render window instance
             */
            sf::RenderWindow &getSFMLWindow() { return window_;}
            const sf::RenderWindow &getSFMLWindow() const { return window_;}

            /**
             * @brief Destructor.
             *
             * Ensures a new Window instance can be created when an existing
             * Window instance is destroyed
             */
            ~RenderTargetImpl();

        private:
            sf::RenderWindow window_;      //!< Render window
            std::string title_;                  //!< The title of the window
            static bool isInstantiated_;   //!< Instantiation state
        };
    }
}

#endif //IME_RENDERTARGETIMPL_H
