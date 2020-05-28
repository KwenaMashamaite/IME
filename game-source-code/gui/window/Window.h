/**
 * @brief Window that can serve as a target for 2D drawing
 */

#ifndef WINDOW_H
#define WINDOW_H

#include "common/Common.h"
#include "event/EventEmitter.h"
#include "gui/IDrawable.h"
#include <SFML/Graphics.hpp>
#include <string>

namespace Gui {
    using Common::Position;
    using Common::Dimensions;

    class Window : sf::NonCopyable {
    public:
        /**
         * @brief Constructor
         *
         * @warning Only a single instance of the class can exist
         *          at a time. Attempting to instantiate the class
         *          while there is an active instance will terminate
         *          the program
         */
        Window();

        /**
         * @brief Create a render window
         * @param name Name of the render window
         * @param width Width of the window
         * @param height Height of the window
         *
         * The dimensions of the window must be positive, otherwise
         * the program will be terminated prematurely
         */
        void create(const std::string &name, float width, float height);

        /**
         * @brief Set the frame rate limit of the window
         * @param framerateLimit Frame rate limit
         *
         * The frame rate is not limited by default. If set, it can be
         * disabled by providing 0 as the argument
         */
        void setFramerateLimit(unsigned int framerateLimit);

        /**
         * @brief Get the dimensions of the window
         * @return Dimensions of the window
         */
        static Dimensions getDimensions(){ return dimensions_;}

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
        void draw(Gui::IDrawable& drawable);

        /**
         * @brief Display drawn objects on the window
         */
        void display();

        /**
         * @brief Clear the entire window with a single colour
         * @param colour Colour to clear window with
         */
        void clear(sf::Color colour = sf::Color::Black);

        /**
         * @brief Add a listener to a window event
         * @tparam Args Template parameter pack name
         * @param event Event to add listener to
         * @param callback Function to execute when the event is fired
         * @return listener's identification number
         */
        template <typename ...Args>
        static int addListener(const std::string& event, Callback<Args...> callback){
            eventEmitter_.addListener(event, callback);
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
        static bool removeListener(const std::string& event, int callbackId){
            return eventEmitter_.removeListener(event, callbackId);
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
}

#endif