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

#ifndef IME_RENDERTARGET_H
#define IME_RENDERTARGET_H

#include "IME/common/Vector2.h"
#include "IME/core/event/Event.h"
#include "IME/graphics/Drawable.h"
#include "IME/graphics/Colour.h"
#include "IME/graphics/WindowStyles.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

namespace ime::priv {
    /**
     * @brief Window that can serve as a target for 2D drawing
     *
     * This class is an abstraction of sf::RenderWindow. It encapsulates
     * third party functionality that is intended for internal only.
     * This way we avoid polluting ime::Window (externally exposed) with
     * functions that the user is not supposed to call. Both ime::RenderTarget
     * and ime::Window operate on the same sf::RenderWindow instance
     */
    class RenderTarget {
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
         * @brief Copy constructor
         */
        RenderTarget(const RenderTarget&) = delete;

        /**
         * @brief Copy assignment operator
         */
        RenderTarget& operator=(const RenderTarget&) = delete;

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
         * @brief Draw drawable on the window
         * @param drawable Object to be drawn
         */
        void draw(const Drawable& drawable);

        /**
         * @brief Clear the entire window with a single colour
         * @param colour Colour to clear window with
         */
        void clear(Colour colour = Colour::Black);

        /**
         * @brief Display drawn objects on the window
         */
        void display();
        /**
         * @brief Get a reference to the SFML render window instance
         * @return A reference to the SFML render window instance
         */
        sf::RenderWindow &getThirdPartyWindow();
        const sf::RenderWindow &getThirdPartyWindow() const;

        /**
         * @brief Add a callback to a create event
         * @param callback The function to be executed after the window is
         *                 created
         *
         * Only one callback may be registered at a time. Pass @a nullptr to
         * remove the callback
         */
        void onCreate(Callback<> callback);

        /**
         * @brief Destructor
         *
         * Ensures a new Window instance can be created when an existing
         * Window instance is destroyed
         */
        ~RenderTarget();

    private:
        sf::RenderWindow window_;      //!< Render window
        std::string title_;            //!< The title of the window
        static bool isInstantiated_;   //!< Instantiation state
        Callback<> onCreate_;
    };
}

#endif // IME_RENDERTARGET_H
