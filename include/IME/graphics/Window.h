/**
 * @brief Window that can serve as a target for 2D drawing
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "IME/common/Position.h"
#include "IME/common/Dimensions.h"
#include "IME/utility/NonCopyable.h"
#include "IDrawable.h"
#include "Colour.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

namespace IME {
    namespace Graphics {
        namespace UI {
            class GuiContainer;
        }

        class Window : Utility::NonCopyable {
        public:
            /**
             * @brief Window styles
             */
            enum class Style{
                None = 0,            // No border / title bar (this flag and all others are mutually exclusive)
                Titlebar = 1 << 0,   // Title bar + fixed border
                Resize = 1 << 1,     // Title bar + resizable border + maximize button
                Close = 1 << 2,      // Title bar + close button
                Fullscreen = 1 << 3,  // Fullscreen mode
                Default = Titlebar | Resize | Close ///< Default window style
            };

            /**
             * @brief Constructor
             *
             * @warning Only a single instance of the class can exist at a time.
             * Attempting to instantiate the class while there is an active
             * instance will terminate the program
             */
            Window();

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
            void create(const std::string &title, float width, float height,
                    Style style = Style::Default);

            /**
             * @brief Change the window's icon
             * @param filename Filename of the window icon to set
             *
             * The OS default icon is used by default
             */
            void setIcon(const std::string& filename);

            /**
             * @brief Set the frame rate limit of the window
             * @param framerateLimit Frame rate limit
             *
             * The frame rate is not limited by default. If set, it can be
             * disabled by providing 0 as the argument
             */
            void setFramerateLimit(unsigned int framerateLimit);

            /**
             * @brief Enable or disable vertical synchronization
             * @param isVsyncEnabled True to enable Vsync or false to disable it
             *
             * Activating vertical synchronization will limit the number
             * of frames displayed to the refresh rate of the monitor.
             * This can avoid some visual artifacts, and limit the framerate
             * to a good value (but not constant across different computers).
             *
             * Vertical synchronization is disabled by default.
             */
            void setVsyncEnabled(bool isVsyncEnabled);

            /**
             * @brief Get the frame rate limit of the window
             * @return The frame rate limit if it has been set, otherwise -1
             *         if the frame rate is not limited
             */
            unsigned int getFramerateLimit() const;

            /**
             * @brief Get the dimensions of the window
             * @return Dimensions of the window
             */
            static Dimensions getDimensions();

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
            bool pollEvent(sf::Event &event);

            /**
             * @brief Close the window
             */
            void close();

            /**
             * @brief Draw drawable object on the window
             * @param drawable Object to draw
             */
            void draw(const sf::Drawable& drawable);

            /**
             * @brief Draw drawable on the window
             * @param drawable Object to draw
             */
            void draw(IDrawable& drawable);

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
             * @brief Destructor.
             *
             * Ensures a new Window instance can be created when an existing
             * Window instance is destroyed
             */
            ~Window();

        private:
            //SFML render window.
            sf::RenderWindow window_;
            //Dimensions of the window
            static Dimensions dimensions_;
            //Frame rate limit
            unsigned int frameRateLimit_;
            //Instantiation state
            inline static auto isInstantiated_ = false;
            friend class UI::GuiContainer;
        };
    }
}

#endif