/**
 * @brief Window that can serve as a target for 2D drawing
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "IME/common/Definitions.h"
#include "IME/event/EventEmitter.h"
#include "IME/gui/common/IDrawable.h"
#include "IME/gui/common/Colour.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

namespace IME {
    namespace Gui {
        using Definitions::Position;
        using Definitions::Dimensions;

        class Window : sf::NonCopyable {
        public:
            /**
             * @brief Window styles
             */
            enum class Style{
                None = 0,            // No border / title bar (this flag and all others are mutually exclusive)
                Titlebar = 1 << 0,   // Title bar + fixed border
                Resize = 1 << 1,     // Title bar + resizable border + maximize button
                Close = 1 << 2,      // Title bar + close button
                Fullscreen = 1 << 3  // Fullscreen mode
            };

            /**
             * @brief Mouse cursor styles
             */
            enum class CursorType{
                Arrow,                  //Arrow cursor (default)
                ArrowWait,              // Busy arrow cursor
                Wait,                   // Busy cursor
                Text,                   // I-beam, cursor when hovering over a field allowing text entry
                Hand,                   // Pointing hand cursor
                SizeHorizontal,         // Horizontal double arrow cursor
                SizeVertical,           // Vertical double arrow cursor
                SizeTopLeftBottomRight, // Double arrow cursor going from top-left to bottom-right
                SizeBottomLeftTopRight, // Double arrow cursor going from bottom-left to top-right
                SizeAll,                // Combination of SizeHorizontal and SizeVertical
                Cross,                  // Crosshair cursor
                Help,                   // Help cursor
                NotAllowed              // Action not allowed cursor
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
            void create(const std::string &title, float width, float height, Style style);

            /**
             * @brief Set the frame rate limit of the window
             * @param framerateLimit Frame rate limit
             *
             * The frame rate is not limited by default. If set, it can be
             * disabled by providing 0 as the argument
             */
            void setFramerateLimit(unsigned int framerateLimit);

            /**
             * @brief Change the displayed mouse cursor type
             * @param cursorType Mouse cursor type to display
             */
            void setCursorType(CursorType cursorType);

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
             * @brief Process window events
             *
             * This function will notify all event listeners if any events
             * have been captured by the window.
             * @note Calling this function will empty the event queue for
             *       that frame
             */
            void processEvents();

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
             * @brief Add a listener to a window event
             * @tparam Args Template parameter pack name
             * @param event Event to add listener to
             * @param callback Function to execute when the event is fired
             * @return listener's identification number
             */
            template <typename ...Args>
            static int addEventListener(const std::string& event, Callback<Args...> callback){
                eventEmitter_.addEventListener(event, callback);
            }

            /**
             * @brief  Remove a listener from a window event
             * @param  event Event to remove listener from
             * @param  listenerId Identification number of the listener
             *         to be removed
             * @return True if a listener was removed from an event,
             *         false if the specified event does not have a
             *         listener with the specified id
             */
            static bool removeEventListener(const std::string& event, int callbackId){
                return eventEmitter_.removeEventListener(event, callbackId);
            }

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
            //Instantiation state
            inline static auto isInstantiated_ = false;
            //Event Emitter
            inline static EventEmitter eventEmitter_{};
        };
    } // namespace Gui
} // namespace IME

#endif